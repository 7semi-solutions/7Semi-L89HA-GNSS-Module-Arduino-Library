/*!
 * @file 7semi_L89HA.h
 * @brief Header for L89 GNSS NMEA sentence parser library
 *
 * This library parses GNRMC and GNGGA NMEA sentences from L89 GNSS module,
 * extracting date, time, position, speed, and altitude.
 *
 * @author 7semi
 * @date July 2025
 * @license MIT
 */

#ifndef _7SEMI_L89HA_H_
#define _7SEMI_L89HA_H_

#include <Arduino.h>

// Structure to hold GNSS parsed data
struct GNSSData {
  int hour = 0, minute = 0, second = 0;
  int day = 0, month = 0, year = 0;
  float latitude = 0.0, longitude = 0.0;
  float altitude = 0.0;
  float speed_kmph = 0.0;
  bool fixStatus = false;
  bool getAltitude = false;
  bool getDate = false;
};

// GNSS parser class
class L89_GNSS_7semi {
public:
  L89_GNSS_7semi();  // Constructor

  // Parse input NMEA sentence and extract values
  bool parseSentence(const String& sentence);

  // Get last parsed GNSS data
  GNSSData getData() const;

private:
  GNSSData data;

  // Validate checksum of NMEA sentence
  bool CheckSum(const String& sentence);

  // Convert NMEA lat/lon to decimal degrees
  float convertToDecimalDegrees(const char* raw, char direction);
};

#endif
