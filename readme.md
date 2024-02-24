`In this sketch:`

Replace "`YourSSID`" and "`YourPassword`" with your WiFi network credentials.
Connect relay modules to relay1Pin and relay2Pin, and limit switches to limitSwitch1Pin and limitSwitch2Pin.
The web server serves a simple HTML page with two buttons to toggle the relays.
The state of the relays is updated based on the states of the limit switches.
Upload this sketch to your ESP32 board using the Arduino IDE, and you should be able to control the relays via a web interface served by the ESP32.