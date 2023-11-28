
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <MQ135.h>
#include <DHT.h>
#include <BH1750.h>
#include <Wire.h>
#include <SoftwareSerial.h>

//#define SERVER_IP "10.0.1.7:9080" // PC address with emulation on host
#define SERVER_IP "http://10.44.14.17:8000/form"

#ifndef STASSID
#define STASSID "WIFI_service"
#define STAPSK "bablo$$$"
#endif

#define PIN_MQ135 A0 // MQ135 Analog Input Pin
#define DHTPIN 2 // DHT Digital Input Pin
#define DHTTYPE DHT11 // DHT11 or DHT22, depends on your sensor

MQ135 mq135_sensor(PIN_MQ135);
DHT dht(DHTPIN, DHTTYPE);
BH1750 lightMeter;

float Temperature, Humidity; // Temp and Humid floats, will be measured by the DHT
//int8_t conPin = 13;
String payload = "";
String str_temp = "";
String str_hum = "";
String str_idcode = "";
String str_ppm = "";
String str_massa = "";
String str_luxin = "";
String str_microcog = "";
//String str_str_microcog = "";
String str_microcock = "";
byte incomingByte;
String incomingString = "";
byte arrgh[10];
int c = 0;
int trimmer;
int flag;

const int IdCode = 1;

//int Luxin = 130;

float Luxin;
float Massa = 200;

SoftwareSerial nano(12,14);


void setup() {

  Serial.begin(115200);

  //pinMode(14, OUTPUT);
  //pinMode(12, INPUT);

  //digitalWrite(12, 1);
  //digitalWrite(14, 0);

  nano.begin(115200);

  Serial.println();
  Serial.println();
  Serial.println();

  WiFi.begin(STASSID, STAPSK);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  dht.begin();

  Serial.print("DHT begin!...");

  Wire.begin();

  lightMeter.begin(BH1750::ONE_TIME_HIGH_RES_MODE);

  Serial.println(F("BH1750 One-Time Test"));
}

void loop() {

  Humidity = dht.readHumidity();
  Temperature = dht.readTemperature();

  while (!lightMeter.measurementReady(true)) {
    yield();
  }
  float lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.print(" lx");
  lightMeter.configure(BH1750::ONE_TIME_HIGH_RES_MODE);

    // Check if any reads failed and exit early (to try again).
  if (isnan(Humidity) || isnan(Temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  float ppm = mq135_sensor.getPPM();
  Serial.print("\t Humidity: ");
  Serial.print(Humidity);
  Serial.print("\t Temperature: ");
  Serial.print(Temperature);
  Serial.print("\t PPM: ");
  Serial.print(ppm);
  Serial.println(" ppm");

  delay(100);

  //Serial.print("Value = ");             // Выводим в монитор порта текст 
  //Serial.println(digitalRead(conPin));
  
  str_microcock = "{"; //obnulyaem stroku
  flag = 0;
  nano.println(1984);
  while (!nano.available()) {
    nano.flush();
    delay(500);
    nano.println(1984);
    Serial.println("ia zlomalciy");
    flag++;
    if (flag > 50) goto savve;
  }
  delay(50);
  /*тестовая хуета Ебануть не должно*/
  nano.println(228);
  str_microcock = "{";
  while (!nano.available()){
    nano.flush();
    nano.println(228);
    delay(500);
    Serial.println(228);
    flag++;
    if (flag > 50) goto savve;
  }
  delay(1000);
  incomingString = nano.readString();
  Serial.println(incomingString);
  if (incomingString == "!")
  {
    nano.flush();
    incomingString = "";
    while (incomingString != "!"){
      nano.println(993);
      while (!nano.available()){
        nano.flush();
        nano.println(993);
        delay(500);
        Serial.println(993);
        flag++;
        if (flag > 70) goto savve;
      }
      incomingString = nano.readString();
      Serial.println(incomingString);
      str_microcock = str_microcock + incomingString;
    }
    while (!nano.available()){
      nano.flush();
      nano.println(99);
      delay(500);
      Serial.println(99);
      flag++;
      if (flag > 70) goto savve;
    }
    incomingString = nano.readString();
    str_microcog = incomingString;
    trimmer = str_microcock.length();
    trimmer = trimmer - 2;
    str_microcock = str_microcock.substring(0,trimmer);
    str_microcock = str_microcock + "}";
    str_microcock.replace("\n",",");
    Serial.println(str_microcock);
    Serial.println(str_microcog);
  }
  else
  {
    savve:
    str_microcog = "-1";
  }

  /*nano.println(228);
  delay(100);
  for (int i = 0; i <63; i++){
    nano.println(228);
    delay(70);
    incomingStr = nano.readString();
    /*if (i == 0){
      incomingStr = nano.readString();
    }*/
      /*while (incomingByte!= 0x0A || incomingByte!= 0x0D){
        incomingByte = nano.read();
      }
      incomingByte = nano.read();
    }
    while (incomingByte!= 0x0A || incomingByte!= 0x0D){
      c = 0;
      for (int g = 0; g<10; g++){
        arrgh[g] = 0x00;
      }
      while(incomingByte!= 0x20 || incomingByte!= 0x0A || incomingByte!= 0x0D){
        arrgh[c] = incomingByte;
        c++;
        incomingByte = nano.read();
      }
      for (char ch : arrgh) str_microcock += ch;
      str_microcock += ": ";
      incomingByte = nano.read();
    }
    str_microcock.substring(0,-2);
    incomingByte = nano.read();
    Serial.println(incomingStr);
    str_microcock += incomingStr + ", ";
    
  }
  str_microcock.substring(0,-2);
  str_microcock += "}";

  Serial.println(str_microcock);*/
  /*str_microcog = nano.readString();
  Serial.println(str_microcog);*/
  nano.println(3); //hren znaet
  delay(500);

  str_microcog.trim();
  Serial.print(str_microcog);
  str_temp = "";
  str_hum = "";
  str_idcode = "";
  str_ppm = "";
  str_massa = "";
  str_luxin = "";

  str_temp = String(Temperature);
  str_hum = String(Humidity);
  str_idcode = String(IdCode);
  str_ppm = String(ppm);
  str_massa = String(Massa);
  str_luxin = String(lux);
  // wait for WiFi connection
  if ((WiFi.status() == WL_CONNECTED)) {

    WiFiClient client;
    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    // configure traged server and url
    http.begin(client, /*"http://"*/ SERVER_IP /*"/postplain/"*/);  // HTTP
    http.addHeader("Content-Type", "application/json");

    Serial.print("[HTTP] POST...\n");
    // start connection and send HTTP header and body
    payload = "{\"temperature\":\"" + str_temp +"\",\"humidity\":\"" + str_hum +"\",\"IdCode\":\"" + str_idcode +"\",\"Massa\":\"" + str_massa + "\",\"co2\":\"" + str_ppm + "\",\"luxin\":\"" + str_luxin + "\",\"Micro\":\"" + str_microcog + "\"}";

    int httpCode = http.POST(payload);

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        const String& payload = http.getString();
        Serial.println("received payload:\n<<");
        Serial.println(payload);
        Serial.println(">>");
      }
    } else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }

  delay(8000);
}
