#define BLYNK_TEMPLATE_ID "TMPL6_IgB46ri"
#define BLYNK_TEMPLATE_NAME "Simulasi Blynk"
#define BLYNK_AUTH_TOKEN "QRJgO8GqBX3IKKbS3fF9kyCOErLYI993"

// Aktifkan Serial Monitor untuk debugging
#define BLYNK_PRINT Serial 

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "Wokwi-GUEST";
char pass[] = "";

const int zone_1_pin = 34; 
const int dry = 2700;
const int wet = 0;

BlynkTimer timer;

// Fungsi Kirim Data (Dijalankan setiap 1 detik)
void sendSensorData()
{
  // Baca Sensor
  int raw_value = analogRead(zone_1_pin);
  
  // Mapping
  int percent_value = map(raw_value, wet, dry, 100, 0); 
  
  // Clamping (Agar tidak minus atau lebih dari 100)
  if (percent_value < 0) percent_value = 0;
  if (percent_value > 100) percent_value = 100;

  Serial.print("Raw: "); Serial.print(raw_value);
  Serial.print(" | Percent: "); Serial.print(percent_value);
  Serial.println("%");

  // Kirim ke Blynk
  Blynk.virtualWrite(V0, percent_value); 
  
  // (Opsional) Kirim raw data ke V1
  Blynk.virtualWrite(V1, raw_value);
}

void setup()
{
  Serial.begin(115200);
  pinMode(zone_1_pin, INPUT);

  Serial.println("Menghubungkan ke Blynk...");
  
  // Fungsi ini otomatis menangani WiFi dan Login Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Set timer kirim data setiap 1 detik (1000L)
  timer.setInterval(1000L, sendSensorData);
}

void loop()
{
  Blynk.run(); // untuk menjaga koneksi
  timer.run(); // untuk menjalankan timer
}