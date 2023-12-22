#pragma once

#include <HardwareSerial.h>

enum
{
    LTM_IDLE,
    LTM_HEADER_START1,
    LTM_HEADER_START2,
    LTM_HEADER_MSGTYPE,
    LTM_HEADER_DATA
};

#define LTM_LONGEST_FRAME_LENGTH 18
#define LTM_GFRAMELENGTH 18
#define LTM_AFRAMELENGTH 10
#define LTM_SFRAMELENGTH 11
#define LTM_OFRAMELENGTH 18
#define LTM_NFRAMELENGTH 10
#define LTM_XFRAMELENGTH 10

extern const char *LTM_FLIGHT_MODES[];

struct
{
    int pitch;
    int roll;
    int heading;
    uint16_t voltage;
    uint8_t rssi;
    bool armed;
    bool failsafe;
    uint8_t flightmode;

    int32_t latitude;
    int32_t longitude;
    int32_t altitude;
    uint8_t groundSpeed;
    int16_t hdop;
    uint8_t gpsFix;
    uint8_t gpsSats;

    int32_t homeLatitude;
    int32_t homeLongitude;

    uint8_t sensorStatus;
} LTM_DATA;

uint8_t ltm_readuint8_t(uint8_t offset);
int ltm_readInt(uint8_t offset);
uint16_t ltm_readInt_u16(uint8_t offset);
int32_t ltm_readInt32(uint8_t offset);
int ltm_to_attitude(int v);
void ltm_loop(HardwareSerial ltm_serial);
