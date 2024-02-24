#include <WiFi.h>
#include <WebServer.h>

const char *ssid = "YourSSID";
const char *password = "YourPassword";

WebServer server(80);

const int relay1Pin = 12;       // Pin for Relay 1
const int relay2Pin = 13;       // Pin for Relay 2
const int limitSwitch1Pin = 14; // Pin for Limit Switch 1
const int limitSwitch2Pin = 15; // Pin for Limit Switch 2

bool relay1State = false;
bool relay2State = false;

void setup()
{
    Serial.begin(115200);

    pinMode(relay1Pin, OUTPUT);
    pinMode(relay2Pin, OUTPUT);
    pinMode(limitSwitch1Pin, INPUT_PULLUP);
    pinMode(limitSwitch2Pin, INPUT_PULLUP);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");

    server.on("/", handleRoot);
    server.on("/relay1", handleRelay1);
    server.on("/relay2", handleRelay2);

    server.begin();
    Serial.println("HTTP server started");
}

void loop()
{
    server.handleClient();

    // Read limit switches and update relay states
    bool limitSwitch1State = digitalRead(limitSwitch1Pin);
    bool limitSwitch2State = digitalRead(limitSwitch2Pin);

    // Update relay states based on limit switch states
    relay1State = !limitSwitch1State; // Invert because limit switch is normally closed
    relay2State = !limitSwitch2State;

    // Update relay outputs
    digitalWrite(relay1Pin, relay1State);
    digitalWrite(relay2Pin, relay2State);
}

void handleRoot()
{
    server.send(200, "text/html", "<h1>ESP32 Relay Control</h1>\
    <p>Relay 1: <a href=\"/relay1\"><button>Toggle</button></a></p>\
    <p>Relay 2: <a href=\"/relay2\"><button>Toggle</button></a></p>");
}

void handleRelay1()
{
    relay1State = !relay1State;
    digitalWrite(relay1Pin, relay1State);
    server.sendHeader("Location", "/");
    server.send(303);
}

void handleRelay2()
{
    relay2State = !relay2State;
    digitalWrite(relay2Pin, relay2State);
    server.sendHeader("Location", "/");
    server.send(303);
}
