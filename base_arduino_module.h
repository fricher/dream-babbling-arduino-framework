#ifndef _BASE_ARDUINO_MODULE_H_
#define _BASE_ARDUINO_MODULE_H_

#define WIFI_SSID "dream_babbling"
#define WIFI_PWD "dreambab"

#define BABBLING_MAX_PACKET_SIZE 64

#include </home/florian/ros_catkin_ws/src/babbling_modules/include/babbling_modules/modules_defs.h>
#include <WiFi101.h>
#include <WiFiUdp.h>

class BabblingModule
{
public:
    BabblingModule ( uint8_t module_type );
    ~BabblingModule();

    /**
     * @brief Initializes the board's WiFi.
     *
     * @return void
     */
    void begin();

    /**
     * @brief Checks if the module is currently active.
     *
     * @return true if the module is active, false otherwise.
     */
    bool running();

    /**
     * @brief Grabs a packet from the udp socket.
     * 
     * @param buffer A buffer to hold the packet's data..
     * @return The size of the packet, or -1 if there was no packet or if the packet was handled by this class
     */
    int getPacket ( uint8_t *buffer );
    
    /**
     * @brief Sends a packet through the udp socket.
     * 
     * @param buffer The data to send.
     * @param buf_sz The size of buffer.
     * @return void
     */
    void sendPacket ( uint8_t *buffer, size_t buf_sz );

protected:
    WiFiUDP _udp;
    IPAddress _remote_ip;
    uint16_t _remote_port = 0;

    uint8_t _module_type;

    volatile bool _started;
};

#endif
