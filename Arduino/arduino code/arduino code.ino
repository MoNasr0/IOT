#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>

WebSocketsClient wsc;

const char *ssid = "M & R & N & R";
const char *pass = "hackpasswordman";

#define SERVER  "192.168.0.105"
#define PORT    200
#define URL     "/"

void websocketEvent(WStype_t type, uint8_t *data, size_t length) {
  switch (type) {
    case (WStype_CONNECTED):
      Serial.printf("Connected!\n");
      break;

    case (WStype_DISCONNECTED):
      Serial.printf("Disconnected!\n");
      break;

    case (WStype_TEXT):
      int power;
      String x = (char*)data;
      power = x.toInt();
      power = map(power, 0, 255, 0, 1023);
      analogWrite(LED_BUILTIN, power); // LED_BUILTIN
      Serial.printf("value: %d\n", power);
      break;
  }
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println(".");
    delay(500);
  }
  Serial.println("Connected");
  Serial.println(WiFi.SSID());
  Serial.println(WiFi.localIP());

  wsc.begin(SERVER, PORT, URL);
  wsc.onEvent(websocketEvent);
  // try ever 1000 again if connection has failed
  wsc.setReconnectInterval(1000);
}

void loop() {
  wsc.loop();
}
