/* Kütüphaneler */
#define BLYNK_PRINT Serial
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <dht11.h>

/* Pin Tanımlamaları */
#define CHANNEL0 D0
#define CHANNEL1 D1
#define CHANNEL2 D2
#define CHANNEL3 D3
#define SENSOR D8

/* Blynk Uygulaması için gerekli olan tanımlamalar*/
char auth[] = "32bxA6kRp3ACAa7dEgZZVxA6VT1Ldem9"; // Token

/* Wifi ayarları için gerekli olan tanımlamalar*/
char ssid[] = "Redmi"; // Wifi Adı
char pass[] = "mertcan123"; // Wifi Şifresi

/* Nesne Tanımlamaları*/
BlynkTimer timer; // Senkronizasyon Nesnesi
dht11 DHT_SENSOR;

/*************************************************************************************/

BLYNK_WRITE(V0) // Sanal V1 
{
  int pinValue = param.asInt(); // Sanal V1 'den gelen veriyi değişkene ata.
 
  if (pinValue==1){
    Serial.println(" 0.CHANNEL : ON");
    digitalWrite(CHANNEL0,HIGH);
    }
  else {
      Serial.println(" 0.CHANNEL : OFF");
      digitalWrite(CHANNEL0,LOW);
    }
}

/*************************************************************************************/

BLYNK_WRITE(V1) // Sanal V1 
{
  int pinValue = param.asInt(); // Sanal V1 'den gelen veriyi değişkene ata.
 
  if (pinValue==1){
    Serial.println(" 1.CHANNEL : ON");
    digitalWrite(CHANNEL1,HIGH);
    }
  else {
      Serial.println(" 1.CHANNEL : OFF");
      digitalWrite(CHANNEL1,LOW);
    }
}

/*************************************************************************************/

BLYNK_WRITE(V2) // Sanal V1 
{
  int pinValue = param.asInt(); // Sanal V1 'den gelen veriyi değişkene ata.
 
  if (pinValue==1){
    Serial.println(" 2.CHANNEL : ON");
    digitalWrite(CHANNEL2,HIGH);
    }
  else {
      Serial.println(" 0.CHANNEL : OFF");
      digitalWrite(CHANNEL2,LOW);
    }
}

/*************************************************************************************/

BLYNK_WRITE(V3) // Sanal V1 
{
  int pinValue = param.asInt(); // Sanal V1 'den gelen veriyi değişkene ata.
 
  if (pinValue==1){
    Serial.println(" 3.CHANNEL : ON");
    digitalWrite(CHANNEL3,HIGH);
    }
  else {
      Serial.println(" 3.CHANNEL : OFF");
      digitalWrite(CHANNEL3,LOW);
    }
}

/*************************************************************************************/

void SendData()
{
  String Sicaklik="";
  String Nem="";
  String SicaklikYaziOn="SICAKLIK : ";
  String SicaklikYaziArka=" °C";
  String NemYaziOn="NEM : % ";
  int Control = DHT_SENSOR.read(SENSOR);

  Sicaklik=(String)DHT_SENSOR.temperature;
  Nem=(String)DHT_SENSOR.humidity;


  Blynk.virtualWrite(V4, SicaklikYaziOn+Sicaklik+SicaklikYaziArka);
  Blynk.virtualWrite(V5, NemYaziOn+Nem);

}


void setup() 
{
  /* GPIO Ayarları */
 pinMode(CHANNEL0, OUTPUT);
 pinMode(CHANNEL1, OUTPUT);
 pinMode(CHANNEL2, OUTPUT);
 pinMode(CHANNEL3, OUTPUT);
 pinMode(SENSOR,INPUT);

 digitalWrite(CHANNEL0,LOW);
 digitalWrite(CHANNEL1,LOW);
 digitalWrite(CHANNEL2,LOW);
 digitalWrite(CHANNEL3,LOW);

 /* Seri Haberleşme Ayarları */
 Serial.begin(115200);

 /* Blynk Ayarları*/
 Blynk.begin(auth, ssid, pass); // Blynk'e bağlan.

 /* Timer Nesnesinin Veri Gönderme Ayarları*/
 timer.setInterval(1000L, SendData); // Saniyede bir veri gönderilir.
}

void loop() 
{
  Blynk.run(); // Blynk Fonksyionları Çalıştırılır
  timer.run(); // Zamanlamayı Kontrol Eder
}
