#include "ltm.hpp"

const char *LTM_FLIGHT_MODES[] = {
    "Manual",
    "Rate",
    "Angle",
    "Horizon",
    "Acro",
    "Stabilized1",
    "Stabilized2",
    "Stabilized3",
    "Altitude Hold",
    "GPS Hold",
    "Waypoints",
    "Head free",
    "Circle",
    "RTH",
    "Follow me",
    "Land",
    "Fly by wire A",
    "Fly by wire B",
    "Cruise",
    "Unknown"};

static uint8_t ltm_buffer[LTM_LONGEST_FRAME_LENGTH];
static uint8_t ltm_state = LTM_IDLE;
static char ltm_frameType;
static uint8_t ltm_frameLength;
static uint8_t ltm_receiverIndex;

uint8_t ltm_readuint8_t(uint8_t offset)
{
    return ltm_buffer[offset];
}

int ltm_readInt(uint8_t offset)
{
    return (int)ltm_buffer[offset] + ((int)ltm_buffer[offset + 1] << 8);
}

uint16_t ltm_readInt_u16(uint8_t offset)
{
    return (uint16_t)ltm_buffer[offset] + ((uint16_t)ltm_buffer[offset + 1] << 8);
}

int32_t ltm_readInt32(uint8_t offset)
{
    return (int32_t)ltm_buffer[offset] + ((int32_t)ltm_buffer[offset + 1] << 8) + ((int32_t)ltm_buffer[offset + 2] << 16) + ((int32_t)ltm_buffer[offset + 3] << 24);
}

int ltm_to_attitude(int v)
{
    if (v > 32767)
    {
        v = -1 * (65535 - v);
    }
    return v;
}

void ltm_loop(HardwareSerial ltm_serial)
{
    if (!ltm_serial.available())
    {
        return;
    }

    char data = ltm_serial.read();

    if (ltm_state == LTM_IDLE)
    {
        if (data != '$')
        {
            return;
        }

        ltm_state = LTM_HEADER_START1;
        return;
    }

    if (ltm_state == LTM_HEADER_START1)
    {
        if (data == 'T')
        {
            ltm_state = LTM_HEADER_START2;
            return;
        }

        ltm_state = LTM_IDLE;
        return;
    }

    if (ltm_state == LTM_HEADER_START2)
    {
        ltm_frameType = data;
        ltm_state = LTM_HEADER_MSGTYPE;
        ltm_receiverIndex = 0;

        switch (data)
        {
        case 'G':
            ltm_frameLength = LTM_GFRAMELENGTH;
            break;
        case 'A':
            ltm_frameLength = LTM_AFRAMELENGTH;
            break;
        case 'S':
            ltm_frameLength = LTM_SFRAMELENGTH;
            break;
        case 'O':
            ltm_frameLength = LTM_OFRAMELENGTH;
            break;
        case 'N': // inav
            ltm_frameLength = LTM_NFRAMELENGTH;
            break;
        case 'X': // inav
            ltm_frameLength = LTM_XFRAMELENGTH;
            break;
        default:
            ltm_state = LTM_IDLE;
        }

        return;
    }

    if (ltm_state == LTM_HEADER_MSGTYPE)
    {
        if (ltm_receiverIndex != ltm_frameLength - 4)
        {
            /*
             * If no, put data into buffer
             */
            ltm_buffer[ltm_receiverIndex++] = data;
            return;
        }

        if (ltm_frameType == 'A')
        {
            LTM_DATA.pitch = ltm_to_attitude(ltm_readInt_u16(0));
            LTM_DATA.roll = ltm_to_attitude(ltm_readInt_u16(2));
            LTM_DATA.heading = ltm_to_attitude(ltm_readInt_u16(4));
        }

        if (ltm_frameType == 'S')
        {
            LTM_DATA.voltage = ltm_readInt(0);
            LTM_DATA.rssi = ltm_readuint8_t(4);

            uint8_t raw = ltm_readuint8_t(6);
            LTM_DATA.flightmode = raw >> 2;
        }

        if (ltm_frameType == 'G')
        {
            LTM_DATA.latitude = ltm_readInt32(0);
            LTM_DATA.longitude = ltm_readInt32(4);
            LTM_DATA.groundSpeed = ltm_readuint8_t(8);
            LTM_DATA.altitude = ltm_readInt32(9);

            uint8_t raw = ltm_readuint8_t(13);
            LTM_DATA.gpsSats = raw >> 2;
            LTM_DATA.gpsFix = raw & 0x03;
        }

        if (ltm_frameType == 'X')
        {
            LTM_DATA.hdop = ltm_readInt(0);
            LTM_DATA.sensorStatus = ltm_readuint8_t(2);
        }

        ltm_state = LTM_IDLE;
        memset(ltm_buffer, 0, LTM_LONGEST_FRAME_LENGTH);
    }
}