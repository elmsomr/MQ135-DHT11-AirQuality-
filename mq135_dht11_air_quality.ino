#include <DHT11.h>

#define MQ135_PIN A0      // Analog pin for MQ-135
#define DHT_PIN 3         // Digital pin for DHT11
#define RL 20000          // Load resistance in ohms (20K)
#define CALIBRATION_SAMPLES 50

DHT11 dht11(DHT_PIN);     // Create DHT11 sensor object

float Ro = 10000.0;       // Initial Ro value (calibrated later)

// Calibrate the MQ135 sensor in clean air
float calibrateSensor() {
  float sensorValue = 0;
  for (int i = 0; i < CALIBRATION_SAMPLES; i++) {
    sensorValue += analogRead(MQ135_PIN);
    delay(50);
  }
  sensorValue /= CALIBRATION_SAMPLES;
  float sensorResistance = ((1023.0 / sensorValue) - 1) * RL;
  return sensorResistance / 30.0; // Based on 100ppm NH3 in clean air
}

// Calculate gas concentration (PPM) using MQ135
float getPPM() {
  int analogValue = analogRead(MQ135_PIN);
  float sensorResistance = ((1023.0 / analogValue) - 1) * RL;
  float ratio = sensorResistance / Ro;
  float ppm = 116.602 * pow(ratio, -2.769); // Empirical formula
  return ppm;
}

// Roughly determine gas type based on PPM range
String detectGasType(float ppm) {
  if (ppm < 50) {
    return "Likely CO2";
  } else if (ppm >= 50 && ppm < 200) {
    return "Smoke / Alcohol / Benzene / NOx";
  } else if (ppm >= 200) {
    return "High pollution or NH3";
  } else {
    return "Unknown";
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Calibrating MQ-135 sensor...");
  Ro = calibrateSensor();
  Serial.print("Calibrated Ro value: ");
  Serial.println(Ro);
}

void loop() {
  int temperature = 0;
  int humidity = 0;

  int status = dht11.read(DHT_PIN, &temperature, &humidity);
  float ppm = getPPM();
  String gasType = detectGasType(ppm);

  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print("°C | Humidity: ");
  Serial.print(humidity);
  Serial.print("% | Gas (PPM): ");
  Serial.print(ppm);
  Serial.print(" | Gas Type: ");
  Serial.println(gasType);

  delay(1000);
}
