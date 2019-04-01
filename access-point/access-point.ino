// #include <ESP8266WiFi.h>
#include <WiFi.h>
#include <ShiftRegister74HC595.h>
#include <aREST.h>
#include <EEPROM.h>

void writeString(char add, String data);
String read_String(char add);

int passwordAddr = 10;

const char *ssid = "project-husky";
// Minimum of 8 characters

aREST rest = aREST();

#define LISTEN_PORT 80

WiFiServer server(LISTEN_PORT);

int dataPin1 = 32;
int clockPin1 = 33;
int latchPin1 = 25;
ShiftRegister74HC595 homeDigits(1, dataPin1, clockPin1, latchPin1);

int dataPin2 = 26;
int latchPin2 = 27;
int clockPin2 = 14;
ShiftRegister74HC595 awayDigits(1, dataPin2, clockPin2, latchPin2);

int dataPin3 = 17;
int latchPin3 = 16;
int clockPin3 = 4;
ShiftRegister74HC595 clockDigits(3, dataPin3, clockPin3, latchPin3);

int oneDef[] = {1, 2};
int twoDef[] = {0, 1, 3, 4, 6};
int threeDef[] = {0, 1, 2, 3, 6};
int fourDef[] = {1, 2, 5, 6};
int fiveDef[] = {0, 2, 3, 5, 6};
int sixDef[] = {0, 2, 3, 4, 5, 6};
int sevenDef[] = {0, 1, 2};
int eightDef[] = {0, 1, 2, 3, 4, 5, 6};
int nineDef[] = {0, 1, 2, 5, 6};
int zeroDef[] = {0, 1, 2, 3, 4, 5};

// int team = -1;

unsigned long previousMillis = 0;
const int interval = 1000;

int home = 0;
int away = 0;
int secTimer = 0;
int minTimer = 9;

int maxScore = 9;

int ledControl(String command);

int changePW(String command);
int scoreHome(String command);
int scoreAway(String command);
int clockHandler(String command);
void setup()
{
  EEPROM.begin(512);
  //     writeString(passwordAddr, "abcdefghijk");
  String loadPassword = read_String(passwordAddr);
  const char *password = loadPassword.c_str();
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');

  // Set SSID and Password
  WiFi.softAP(ssid, password);
  Serial.println(password);
  Serial.print("Access point [");
  Serial.print(ssid);
  Serial.println("] started");

  // Set Static IP Address
  IPAddress Ip(192, 168, 1, 1);
  IPAddress NMask(255, 255, 255, 0);
  WiFi.softAPConfig(Ip, Ip, NMask);

  // Show Static IP Address
  Serial.print("IP address: \t");
  Serial.println(WiFi.softAPIP());

  pinMode(2, OUTPUT);

  // Initialize Led Control API
  rest.function("led", ledControl);
  rest.function("changepass", changePW);
  rest.function("home", scoreHome);
  rest.function("away", scoreAway);
  rest.function("clock", clockHandler);

  server.begin();
}

void loop()
{
  WiFiClient client = server.available();

  if (!client)
  {
    timer();
    return;
  }
  while (!client.available())
  {
    delay(1);
  }
  if (client)
  {
    rest.handle(client);
  }
  // homeDigits.updateRegisters();
}
