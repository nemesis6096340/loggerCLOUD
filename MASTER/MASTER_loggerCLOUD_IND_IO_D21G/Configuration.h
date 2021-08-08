
#ifndef ARDUINO_CONFIGURATION_H
#define ARDUINO_CONFIGURATION_H
#include <Arduino.h>

const uint8_t DEFAULT_MAC[6] = {0x90, 0xA2, 0xDA, 0xAC, 0x00, 0x00};
const uint8_t DEFAULT_IP[4] = {192, 168, 1, 100};
const uint8_t DEFAULT_DNS[4] = {192, 168, 1, 1};
const uint8_t DEFAULT_GATE[4] = {192, 168, 1, 1};
const uint8_t DEFAULT_MASK[4] = {255, 255, 255, 0};
const uint16_t DEFAULT_PORT = 80;

const uint8_t DEFAULT_IP_SERVER[4] = {192, 168, 1, 200};
const uint16_t DEFAULT_PORT_SERVER = 8080;
const char *DEFAULT_URL_SERVER = "THM/enlaceTHM.php";

enum
{
	RUNNING_TIMER = 0,
	RUNNING_MODBUS_RTU = 1,
	RUNNING_MODBUS_TCP_IP = 2

} FLAGS_DEVICE_STATUS;

enum
{
	MODE_DHCP = 0,
	MODE_MODBUS_TCP_IP = 1,
	MODE_HTTP_CLIENT = 2,
	MODE_HTTP_SERVER = 3,
	MODE_NTP_CLIENT = 4,
	MODE_IO_SERIAL = 5,
	MODE_IO_WIRE = 6,
	MODE_IO_CONTROL = 7,

	ENABLE_MODE_DHCP = 8,
	ENABLE_MODE_MODBUS_TCP_IP = 9,
	ENABLE_MODE_HTTP_CLIENT = 10,
	ENABLE_MODE_HTTP_SERVER = 11,
	ENABLE_MODE_NTP_CLIENT = 12,
	ENABLE_MODE_IO_SERIAL = 13,
	ENABLE_MODE_IO_WIRE = 14,
	ENABLE_MODE_IO_CONTROL = 15
} FLAGS_CLIENT_MODE;

enum
{
	WIFI_NO_HARDWARE = 0,
	WIFI_CONNECTED = 1,
	WIFI_RUNNING = 2,
	WIFI_LINKING = 3,

	WIFI_FAIL_DHCP = 4,
	WIFI_FAIL_LINK = 5,
	WIFI_FAIL_REQUEST = 6,
	WIFI_FAIL_NTP = 7,

	ETHERNET_NO_HARDWARE = 8,
	ETHERNET_CONNECTED = 9,
	ETHERNET_RUNNING = 10,
	ETHERNET_LINKING = 11,
	ETHERNET_FAIL_DHCP = 12,
	ETHERNET_FAIL_LINK = 13,
	ETHERNET_FAIL_REQUEST = 14,
	ETHERNET_FAIL_NTP = 15

} FLAGS_CLIENT_STATUS;

typedef struct device_t
{
	uint32_t ID;
	uint16_t STATUS;
};

typedef struct modbusd_t
{
	uint16_t ADDR;
	uint32_t BAUD;
	uint16_t CONF;
};

typedef struct client_t
{
	uint16_t MODE;
	uint16_t STATUS;
	uint8_t MAC[6];
	uint8_t IP[4];
	uint8_t DNS[4];
	uint8_t GATE[4];
	uint8_t MASK[4];
	uint16_t PORT;
};

const int SIZE_URL = 32;
typedef struct server_t
{
	uint8_t IP[4];
	uint16_t PORT;
	uint8_t URL[SIZE_URL];
};

typedef struct settings_t
{
	device_t device;
	modbusd_t modbus;
	client_t client;
	server_t server;
};

const int SIZE_BUFFER_SETTINGS = sizeof(settings_t) / sizeof(uint16_t);

typedef union configuration_t
{
	settings_t settings;
	uint16_t buffer[SIZE_BUFFER_SETTINGS] = {0};
};

configuration_t configuration;

void defaultConfiguration()
{
	// Device config
	configuration.settings.device.ID = 0;
	configuration.settings.device.STATUS = 0;
	// Modbus config
	configuration.settings.modbus.ADDR = 247;
	configuration.settings.modbus.BAUD = 115200UL;
	configuration.settings.modbus.CONF = 6;
	// Ethernet Client config
	configuration.settings.client.MODE = 0x0F0F;
	configuration.settings.client.STATUS = 0x0000;
	memcpy(configuration.settings.client.MAC, DEFAULT_MAC, 6);
	memcpy(configuration.settings.client.IP, DEFAULT_IP, 4);
	memcpy(configuration.settings.client.DNS, DEFAULT_DNS, 4);
	memcpy(configuration.settings.client.GATE, DEFAULT_GATE, 4);
	memcpy(configuration.settings.client.MASK, DEFAULT_MASK, 4);
	configuration.settings.client.PORT = DEFAULT_PORT;
	// Ethernet Server config
	memcpy(configuration.settings.server.IP, DEFAULT_IP_SERVER, 4);
	configuration.settings.server.PORT = 8080;
	strcpy((char *)configuration.settings.server.URL, DEFAULT_URL_SERVER);
};

class Configuration
{
private:
public:
	Configuration();
	~Configuration();
};

#endif
