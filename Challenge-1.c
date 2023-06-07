// Challenge-1
#include <stdio.h>
#include <stdint.h>

#define MAX_PACKET_DATA_LENGTH (50)

typedef struct data_packet_t {
    uint8_t id;
    uint8_t data_length;
    uint8_t data[MAX_PACKET_DATA_LENGTH];
    uint16_t crc;
} data_packet_t;

uint16_t calculateCRC(const uint8_t* data, uint8_t length) {
    uint16_t crc = 0xFFFF;

    for (int i = 0; i < length; i++) {
        crc ^= (uint16_t)data[i] << 8;

        for (int j = 0; j < 8; j++) {
            if (crc & 0x8000) {
                crc = (crc << 1) ^ 0x1021;
            }
            else {
                crc = crc << 1;
            }
        }
    }

    return crc;
}

int isPacketCorrupted(const data_packet_t* packet) {
    uint16_t calculatedCRC = calculateCRC(packet->data, packet->data_length);
    return (calculatedCRC == packet->crc) ? 0 : 1;
}

int main() {
    data_packet_t packet;

    printf("Enter packet ID: ");
    scanf("%hhu", &packet.id);

    printf("Enter data length: ");
    scanf("%hhu", &packet.data_length);

    printf("Enter data (up to %d bytes): ", MAX_PACKET_DATA_LENGTH);
    for (int i = 0; i < packet.data_length; i++) {
        scanf("%hhu", &packet.data[i]);
    }

    packet.crc = calculateCRC(packet.data, packet.data_length);

    int isCorrupted = isPacketCorrupted(&packet);
    printf("Packet is %s.\n", (isCorrupted ? "corrupted" : "not corrupted"));

    return 0;
}