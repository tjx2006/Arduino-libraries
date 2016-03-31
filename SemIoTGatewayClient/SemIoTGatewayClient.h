#ifndef SEMIOTGATEWAYCLIENT_H
#define SEMIOTGATEWAYCLIENT_H
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <HardwareSerial.h>

#define UDP_GTW_OK_SIZE 5
#define UDP_GTW_OK_WORD "GTWOK"
#define UDP_GTW_PING_WORD "GTW"
#define DEBUG_LED_LIGHT LOW
#define DEBUG_LED_DARK HIGH

class SemIoTGatewayClient
{
public:
    SemIoTGatewayClient(WiFiUDP *udp=NULL, int udpPort = 33333, HardwareSerial *debugSerial=NULL, int debugLedPin = -1);
    ~SemIoTGatewayClient();
    void connectToSemIoTGateway();
    void connectToWPS();
    void gtwSearch();
    IPAddress gatewayIp();
    byte *mac();
    // TODO: offset, etc
    // FORMAT:
    // "WORD" (4B)
    // low_counter (2B)
    // high_counter (4B)
    // MAC (6B)
    // == 16 BYTES
    // TODO: checksum?
    void writeCountersToEeprom();
    void readCountersFromEeprom();
private:
    WiFiUDP *_udp;
    int _udpPort;
    IPAddress _gatewayIp;
    int _debugLedPin;
    HardwareSerial *_debugSerial;
    bool _debugLed;
    byte _mac[6];
    char _gtwOkBuffer[UDP_GTW_OK_SIZE];
};

#endif // SEMIOTGATEWAYCLIENT_H