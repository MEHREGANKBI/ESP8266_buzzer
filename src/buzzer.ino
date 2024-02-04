#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#define LED_OFF 1
#define LED_ON 0
/*****************GLOBAL VARS**************/
// This is the html that is served when accessing root.
const char *html_raw =
	"<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" "
	"content=\"width=device-width,initial-scale=1.0\"><link type=\"image/png\" sizes=\"96x96\" "
	"rel=\"icon\" \"href=\"https://img.icons8.com/fluency/96/switches.png\"><link rel=\"apple-touch-icon\" "
	"href=\"https://img.icons8.com/fluency/96/switches.png\"><title>LED Controller</title><style>html,"
	"body{height:100%;margin:0;display:flex;justify-content:center;align-items:center;background-color:#003049}"
	".round-btn{display:inline-block;width:250px;height:250px;line-height:250px;text-align:center;border-radius:50%;"
	"background-color:#7CFC00;color:#fff;text-decoration:none;font-size:20px;cursor:pointer;border:8px solid #fff}</style>"
	"</head><body><a href=\"/buzz\" class=\"round-btn\">BUZZ</a></body></html>";

ESP8266WebServer server(80);
/*****************GLOBAL VARS**************/

/**************HTTP HANDLERS***************/
void handle_root()
{
	server.send(200, "text/html", html_raw);
}

void on_buzz(void)
{
	digitalWrite(LED_BUILTIN, LED_ON);
	delay(100);
	digitalWrite(LED_BUILTIN, LED_OFF);
	delay(100);
	digitalWrite(LED_BUILTIN, LED_ON);
	delay(100);
	digitalWrite(LED_BUILTIN, LED_OFF);
	handle_root();
}
/**************HTTP HANDLERS***************/



void config_AP()
{
	IPAddress local_IP(192, 168, 1, 184); // static ip. Change this setting if needed
	IPAddress gateway(192, 168, 1, 1); // Change this setting if needed
	IPAddress subnet(255, 255, 255, 0); // Change this setting if needed
	IPAddress primaryDNS(8, 8, 8, 8); // optional
	IPAddress secondaryDNS(8, 8, 4, 4); // optional

	Serial.println("\nConfiguring access point...");
	if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
		Serial.println("STA Failed to configure");
	}
}

void connect_wifi()
{
	delay(3000);
	config_AP();
	Serial.print("Connecting to the wireless interface...");
	const char *ssid = ""; //Enter your WIFI ssid
	const char *password = ""; //Enter your WIFI password
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.print("\nWiFi connected!\nIP address: ");
	Serial.println(WiFi.localIP());
}

void setup_httpserver()
{
	server.on("/", handle_root);
	server.on("/buzz", on_buzz);
	server.begin();
	Serial.println("HTTP server started");
}




void setup()
{
	pinMode(LED_BUILTIN, OUTPUT);
	// Turn on the LED initially.
	digitalWrite(LED_BUILTIN, LED_ON);
	Serial.begin(115200);
	connect_wifi();
	setup_httpserver();
	// Turn off LED when setup is done.
	digitalWrite(LED_BUILTIN, LED_OFF);
}

void loop()
{
	if (WiFi.status() != WL_CONNECTED) {
		digitalWrite(LED_BUILTIN, LED_ON);
		connect_wifi();
		digitalWrite(LED_BUILTIN, LED_OFF);
	}
	server.handleClient();
	delay(10);
}
