#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"

MAX30105 particleSensor;

const byte RATE_SIZE = 4;
byte rates[RATE_SIZE];

byte rateSpot = 0;
byte validRates = 0;

long lastBeat = 0;

float beatsPerMinute = 0;
int beatAvg = 0;

void setup()
{
  Serial.begin(115200);
  Wire.begin();

  Serial.println("Starting MAX30102...");

  // Try to connect to the sensor
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST))
  {
    Serial.println("MAX30102 NOT FOUND!");
    Serial.println("Check VCC, GND, SDA, and SCL.");
    while (1);
  }

  Serial.println("MAX30102 detected!");
  Serial.println("Place your finger flat over the sensor.");
  Serial.println();

  // Configure the MAX30102
  particleSensor.setup();

  // Red LED brightness
  particleSensor.setPulseAmplitudeRed(0x0A);

  // Turn off green LED
  particleSensor.setPulseAmplitudeGreen(0);
}

void loop()
{
  long irValue = particleSensor.getIR();

  // No finger / poor finger placement
  if (irValue < 50000)
  {
    Serial.print("No finger detected | IR: ");
    Serial.println(irValue);

    delay(250);
    return;
  }

  // Check the IR signal for a heartbeat
  if (checkForBeat(irValue))
  {
    long currentTime = millis();

    // Don't calculate BPM on the very first detected beat
    if (lastBeat != 0)
    {
      long delta = currentTime - lastBeat;

      beatsPerMinute = 60000.0 / delta;

      // Only accept reasonable values
      if (beatsPerMinute > 20 && beatsPerMinute < 255)
      {
        rates[rateSpot] = (byte)beatsPerMinute;

        rateSpot++;
        rateSpot %= RATE_SIZE;

        if (validRates < RATE_SIZE)
        {
          validRates++;
        }

        // Calculate average BPM
        int total = 0;

        for (byte i = 0; i < validRates; i++)
        {
          total += rates[i];
        }

        beatAvg = total / validRates;

        Serial.print("IR: ");
        Serial.print(irValue);

        Serial.print(" | Beat! | BPM: ");
        Serial.print(beatsPerMinute, 1);

        Serial.print(" | Average BPM: ");
        Serial.println(beatAvg);
      }
    }

    lastBeat = currentTime;
  }
}
