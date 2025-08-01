/*!
 * @file L89HA_GNSS_Example.ino
 * @brief Example code to read and parse GNSS data from L89 module using 7semi_L89HA library
 *
 * This example reads NMEA sentences from the L89 module using SoftwareSerial,
 * parses GNRMC and GNGGA data, and prints location, time, speed, altitude, and date to Serial Monitor.
 */

#include <SoftwareSerial.h>
#include <7semi_L89HA.h>

// Create SoftwareSerial on pins RX, TX
SoftwareSerial gnssSerial(8, 9);  // RX, TX

// Create GNSS parser instance
L89_GNSS_7semi gnss;

void setup() {
  Serial.begin(115200);    // Start Serial Monitor
  gnssSerial.begin(9600);  // Start GNSS module serial communication
  Serial.println(" 7semi L89 GNSS Library.");
}

void loop() {
  static String sentence = "";

  // Read characters from GNSS module
  while (gnssSerial.available()) {
    char c = gnssSerial.read();
    // Serial.print(c);
    sentence += c;  // Build sentence line-by-line
    // End of NMEA sentence
    if (c == '\n') {
      sentence.trim();  // Remove trailing \r or spaces

      // Try to parse sentence
      if (gnss.parseSentence(sentence)) {
        GNSSData data = gnss.getData();  // Get parsed data

        // Print time
        Serial.print("Time: ");
        Serial.print(data.hour);
        Serial.print(":");
        Serial.print(data.minute);
        Serial.print(":");
        Serial.println(data.second);

        // Print location
        Serial.print("Lat: ");
        Serial.print(data.latitude, 6);
        Serial.print("  Lon: ");
        Serial.println(data.longitude, 6);

        // Print altitude if available
        if (data.getAltitude) {
          Serial.print("Alt: ");
          Serial.print(data.altitude);
          Serial.println(" M");
        }

        // Print date if available
        if (data.getDate) {
          Serial.print("Date: ");
          Serial.print(data.day);
          Serial.print("/");
          Serial.print(data.month);
          Serial.print("/");
          Serial.println(data.year);
        }
      }
      // Reset sentence for next line
      sentence = "";
    }
  }
}
