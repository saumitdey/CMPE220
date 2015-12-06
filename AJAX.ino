#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>
int dac = 0;
int DacPin = 8;
int DigitalPin[] = {2, 3, 4, 5, 6, 7, 8, 12, 13};
YunServer server;

//Initializes all pins and begin Server
//Pins 2,3,4 are for Doors, 5,6,7 for Windows and 8 for motion sensor
void setup() {
pinMode(2,INPUT_PULLUP);
pinMode(3,INPUT_PULLUP);
pinMode(4,INPUT_PULLUP);
pinMode(5,INPUT_PULLUP);
pinMode(6,INPUT_PULLUP);
pinMode(7,INPUT_PULLUP);
pinMode(8,INPUT);
pinMode(12,OUTPUT);
pinMode(13,OUTPUT);
digitalWrite(13, LOW);
Bridge.begin();
digitalWrite(13, HIGH);
server.listenOnLocalhost();
server.begin();
}

//Listens to requests from client.
void loop() {
YunClient client = server.accept();
if (client) {
process(client);
client.stop();
}
delay(50);
}

//Reads in request string from the client. 
//Depending on the string request, this function will process it
// "digital" will minipulate the requested pins to output high or low
// "dac" will minipulate the requested pins to output a varied ouput between 0V to 5V
// "status" will update send the status of all pins back to the client
void process(YunClient client) {
String command = client.readStringUntil('/');
if (command == "digital") {
digitalCommand(client);
}
if (command == "dac") {
dacCommand(client);
}
if (command == "status") {
statusCommand(client);
}
}

//Function will parse and reads the requested pin then minipulates it
//The status is then returned to the client
void digitalCommand(YunClient client) {
int pin, value;
pin = client.parseInt();
if (client.read() == '/') {
value = client.parseInt();
digitalWrite(pin, value);
}
else {
value = digitalRead(pin);
}
client.print(F("digital,"));
client.print(pin);
client.print(F(","));
client.println(value);
}

//Function will parse and reads the requested pin to minipulate the output between 0V to 5V (analog)
//The status is then returned to the client
void dacCommand(YunClient client) {
int pin, value;
pin = client.parseInt();
if (client.read() == '/') {
value = client.parseInt();
dac = value;
analogWrite(pin, value);
}
else {
value = dac;
}
client.print(F("dac,"));
client.print(pin);
client.print(F(","));
client.println(value);
}

//Function will return status of all pins in the array DigitalPin[] to the Client 
void statusCommand(YunClient client) {
int pin, value;
client.print(F("status"));
for (int thisPin = 0; thisPin < 8; thisPin++) 
  {
  pin = DigitalPin[thisPin];
  value = digitalRead(pin);
  client.print(F("#"));
  client.print(pin);
  client.print(F("="));
  client.print(value);
  }
  
{
pin = DacPin;
value = dac;
client.print(F("#"));
client.print(pin);
client.print(F("="));
client.print(value);
}

{
value = analogRead(0);
// convert the reading to millivolts:
      float voltage = value *  (5000/ 1024); 
      // convert the millivolts to temperature celsius:
      float temperature = (voltage - 500)/10;
client.print(F("#A0"));
client.print(F("="));
client.print(temperature);
}
client.println("");
}
