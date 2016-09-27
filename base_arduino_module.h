#ifndef _BASE_ARDUINO_MODULE_H_
#define _BASE_ARDUINO_MODULE_H_

#define WIFI_SSID "dream_babbling"
#define WIFI_PWD "dreambab"

#define BABBLING_MAX_PACKET_SIZE 64

#include </home/florian/ros_catkin_ws/src/babbling_module/include/babbling_module/modules_defs.h>
#include <WiFi101.h>
#include <WiFiUdp.h>

class BabblingModule {
public:
	BabblingModule(uint8_t module_type);
	~BabblingModule();

	void begin();
	bool running();

	int getPacket(uint8_t* buffer);
	void sendPacket(uint8_t* buffer, size_t buf_sz);

protected:
	WiFiUDP _udp;
	IPAddress _remote_ip;
	uint16_t _remote_port = 0;

	uint8_t _module_type;

	volatile bool _started;
};

#endif
