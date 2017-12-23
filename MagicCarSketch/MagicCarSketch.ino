#include <ESP8266WiFi.h>

/* << Some variables >> */
const char* wrd = "El servidor me ha pedido que ";

/* << Indicator led >> */

#define L1 14

/* << Motors >> */

// Left motor (Motor A)
#define IAM D1 /* D1 */
#define IBM D3 /* D3 */

// Right motor (Motor B)
#define DAM D2 /* D2 */
#define DBM D4 /* D4 */

// Speed
#define SPEI 950
#define SPED 1023

/* << Network >> */

#define PORT 9000
const char* ssid = "---";
const char* pass = "---";
IPAddress server(192,168,100,8);

void setup() {
  /* << Indicator led pin setup >> */
  pinMode(L1, OUTPUT);
  
  /* << Motor pins setup >> */
  
  pinMode(IAM, OUTPUT);
  pinMode(IBM, OUTPUT);
  pinMode(DAM, OUTPUT);
  pinMode(DBM, OUTPUT);
  reset();

  /* << Serial communication for debug >> */
  
  Serial.begin(115200);
  delay(10);
  
  /* << Network config >> */

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.print(" ");

  // Start network connection as client
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Inform about server successful connection
  Serial.println("WiFi connected");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("-------------------------");
  Serial.println();
}

void loop() {
  delay(3000);

  /* << Connection to server >> */
  Serial.println();
  Serial.print("Connecting to ");
  Serial.print(server);
  Serial.println();

  // Create TCP connection
  WiFiClient client;
  if(!client.connect(server, PORT)) {
    Serial.println("Connection failed");
    digitalWrite(L1, LOW);

    return;
  }
  // Connection successful
  else {
    Serial.println("Connection successful");
    Serial.println();
    digitalWrite(L1, HIGH);

    // Receive data from remote control program
    while(client.connected()) {
      if(client.available()){
        String ln = client.readStringUntil('\r');
        Serial.println();
        interpret(ln);
        Serial.println();
      }
    }
  }
}

/* << Interpreter >> */
void interpret(String data){
  reset();
  
  if(data == "FORWARD"){
    Serial.print(wrd);
    Serial.print("avance");

    forward();
  }
  if(data == "BACKWARD"){
    Serial.print(wrd);
    Serial.print("retroceda");

    backward();
  }
  if(data == "TURN_LEFT"){
    Serial.print(wrd);
    Serial.print("gire hacia la izquierda");

    turnLeft();
  }
  if(data == "TURN_RIGHT"){
    Serial.print(wrd);
    Serial.print("gire hacia la derecha");

    turnRight();
  }
  if(data == "STOP"){
    Serial.print(wrd);
    Serial.print("me detenga");

    estop();
  }
}

/* << Motor instructions >> */

/* Motor state
 * 
 * A -> Speed
 * B -> Forward
 * 
 * Order:
 * 1 -> IAM -> GPIO5
 * 2 -> IBM -> GPIO0
 * 3 -> DAM -> GPIO4
 * 4 -> DBM -> GPIO2
 * 
 * FORWARD  | 1023  1
 * BACKWARD | 1023  0
 * STOP     | 0  0
 */

void forward(){
  // Forward
  analogWrite(IAM, SPEI);
  digitalWrite(IBM, HIGH);

  // Forward
  analogWrite(DAM, SPED);
  digitalWrite(DBM, HIGH);
}

void backward(){
  // Backward
  analogWrite(IAM, SPEI);
  digitalWrite(IBM, LOW);

  // Backward
  analogWrite(DAM, SPED);
  digitalWrite(DBM, LOW);
}

void turnLeft(){
  // Backward
  analogWrite(IAM, SPEI);
  digitalWrite(IBM, LOW);

  // Forward
  analogWrite(DAM, SPED);
  digitalWrite(DBM, HIGH);
}

void turnRight(){
  // Forward
  analogWrite(IAM, SPEI);
  digitalWrite(IBM, HIGH);

  // Backward
  analogWrite(DAM, SPED);
  digitalWrite(DBM, LOW);
}

void estop(){
  // Stop
  analogWrite(IAM, 0);
  digitalWrite(IBM, HIGH);

  // Stop
  analogWrite(DAM, 0);
  digitalWrite(DBM, HIGH);
}

void reset(){
  estop();
}

