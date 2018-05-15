#include "base_arduino_module.h"

BabblingModule::BabblingModule(uint8_t module_type) : _remote_port(0), _module_type(module_type), _started(false)
{

}

BabblingModule::~BabblingModule()
{

}

void BabblingModule::begin()
{
    if (WiFi.status() == WL_NO_SHIELD) {
        Serial.println("WiFi shield not present");
        while (true) ;
    }

    String fv = WiFi.firmwareVersion();
    Serial.print("Wifi Firmware version : ");
    Serial.println(fv);

    int status = WL_IDLE_STATUS;
    do {
        status = WiFi.begin(BAB_WIFI_SSID, BAB_WIFI_PWD);
    } while (status != WL_CONNECTED);
    
    IPAddress ip = WiFi.localIP();
    Serial.print("Local IP: ");
    Serial.println(ip);

    _udp.begin(BAB_ARDUINO_UDP_PORT);
}

bool BabblingModule::running()
{
    return _started &&  _remote_port > 0;
}

int BabblingModule::getPacket(uint8_t *buffer)
{
    unsigned int packet_sz = _udp.parsePacket();
    if (packet_sz == 0) {
        return -1;
    }

    _udp.read(buffer, packet_sz);
    if (buffer[0] == BAB_CMD_WHOAREYOU) {
        uint8_t out_buf[9] = {0};
        out_buf[0] = BAB_CMD_WHOIAM;
        out_buf[1] = BAB_TYPE_MODULE;
        out_buf[2] = _module_type;
        _remote_ip = _udp.remoteIP();
        _remote_port = _udp.remotePort();
        WiFi.macAddress(reinterpret_cast<uint8_t *>(&out_buf[3]));
        sendPacket(out_buf, 9);
        return -1;
    } else if (buffer[0] == BAB_CMD_START) {
        _started = true;
        return -1;
    } else if (buffer[0] == BAB_CMD_STOP) {
        _started = false;
        return -1;
    }
    return packet_sz;
}

void BabblingModule::sendPacket(uint8_t *buffer, size_t buf_sz)
{
    _udp.beginPacket(_remote_ip, _remote_port);
    _udp.write(buffer, buf_sz);
    _udp.endPacket();
}
