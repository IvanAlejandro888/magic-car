#include <ESP8266WiFi.h>

#define PORT 9000
#define LED 4

const char* ssid = "TOTALPLAY_8C02F7";
const char* pass = "6144FZ1WTC";

IPAddress server(192,168,100,6);

void setup() {
  // Wiring
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  
  Serial.begin(115200);
  delay(10);

  // WiFi network connection
  Serial.print("\n\nConnecting to ");
  Serial.print(ssid);
  Serial.print(" ");

  // Set ESP8266 as client
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("\nWiFi connected");
  Serial.print("\nIP Address: ");
  Serial.print("\n");
  Serial.print(WiFi.localIP());
  Serial.print("\n-------------------------------");
}

void loop() {
  delay(5000);

  Serial.print("\nConnecting to ");
  Serial.print(server);

  // Create TCP connection
  WiFiClient client;
  if(!client.connect(server, PORT)) {
    Serial.print("\nConnection failed");

    digitalWrite(LED, LOW);
    
    return;
  }else{
    Serial.print("\nConnection sucessful");
    Serial.print("\n");

    digitalWrite(LED, HIGH);
    
    while(client.connected()){
      if(client.available()){
        String ln = client.readStringUntil('\r');
        Serial.print(ln);
        Serial.print("\n");

        if(ln == "CODIGO 1"){
          digitalWrite(LED, HIGH);
        } else if(ln == "CODIGO 0"){
          digitalWrite(LED, LOW);
        }
      }
    }
  }
}

