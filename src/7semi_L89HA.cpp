/*!
 * @file 7semi_L89HA.cpp
 * @brief Library for parsing GNSS NMEA sentences from L89 module
 *
 * @author 7semi
 * @date July 2025
 * @license MIT
 *
 * This library extracts GPS data (RMC, GGA) from raw NMEA strings
 * such as location, time, date, altitude, and speed.
 */

#include "7semi_L89HA.h"

L89_GNSS_7semi::L89_GNSS_7semi() {}

/*
  Parse NMEA sentence and extract GNSS info
*/
bool L89_GNSS_7semi::parseSentence(const String& sentence) {
  if (!CheckSum(sentence)) return false;

  char fields[20][20] = { 0 };
  int j = 0, k = 0;

  // Split by commas
  for (int i = 0; i < sentence.length(); i++) {
    if (sentence[i] == ',') {
      fields[j][k] = '\0';
      j++;
      k = 0;
    } else if (sentence[i] == '*') {
      fields[j][k] = '\0';
      break;
    } else {
      fields[j][k++] = sentence[i];
    }
  }

  /*
     extract data from  $GNRMC sentence
     Time, latitude, longitude, Speed over the ground in kmh
  */

  if (sentence.startsWith("$GNRMC")) {
    // if (fields[2] == 'A') {  // check data validity
    if (strlen(fields[1]) >= 6) {
      data.hour = (fields[1][0] - '0') * 10 + (fields[1][1] - '0');
      data.minute = (fields[1][2] - '0') * 10 + (fields[1][3] - '0');
      data.second = (fields[1][4] - '0') * 10 + (fields[1][5] - '0');
    }
    if (strlen(fields[9]) >= 6) {
      data.day = (fields[9][0] - '0') * 10 + (fields[9][1] - '0');
      data.month = (fields[9][2] - '0') * 10 + (fields[9][3] - '0');
      data.year = (fields[9][4] - '0') * 10 + (fields[9][5] - '0');
      data.getDate = true;
    }

    data.latitude = convertToDecimalDegrees(fields[3], fields[4][0]);
    data.longitude = convertToDecimalDegrees(fields[5], fields[6][0]);
    data.longitude = atof(fields[7]) * 1.852;
    data.fixStatus = true;
    return true;
    // } else
      return false;
  }
  /*
     extract data from  $GNGGA sentence
     Time, latitude, longitude, height above from sea level
  */

  else if (sentence.startsWith("$GNGGA")) {
    // if (fields[5] != '0') {  // check data validity
    if (strlen(fields[1]) >= 6) {
      data.hour = (fields[1][0] - '0') * 10 + (fields[1][1] - '0');
      data.minute = (fields[1][2] - '0') * 10 + (fields[1][3] - '0');
      data.second = (fields[1][4] - '0') * 10 + (fields[1][5] - '0');
    }
    data.latitude = convertToDecimalDegrees(fields[2], fields[3][0]);
    data.longitude = convertToDecimalDegrees(fields[4], fields[5][0]);
    data.altitude = atof(fields[7]);
    data.getAltitude = true;
    data.fixStatus = true;
    return true;
    // } else
    //   return false;
  }
  return data.fixStatus;
}

// Return parsed data
GNSSData L89_GNSS_7semi::getData() const {
  return data;
}

// Validate checksum from *XX
bool L89_GNSS_7semi::CheckSum(const String& sentence) {
  int asterisk = sentence.indexOf('*');
  if (asterisk == -1) return false;

  uint8_t checksum = 0;
  for (int i = 1; i < asterisk; i++) {
    checksum ^= sentence[i];
  }

  String givenStr = sentence.substring(asterisk + 1);
  uint8_t sum = strtol(givenStr.c_str(), NULL, 16);

  return checksum == sum;
}

// Convert NMEA lat/lon to decimal degrees
float L89_GNSS_7semi::convertToDecimalDegrees(const char* raw, char dir) {
  if (strlen(raw) < 4) return 0.0;

  float val = atof(raw);
  int deg = int(val / 100);
  float min = val - deg * 100;
  float dec = deg + min / 60.0;

  if (dir == 'S' || dir == 'W') dec *= -1;
  return dec;
}
