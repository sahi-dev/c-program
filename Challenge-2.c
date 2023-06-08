#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    uint8_t day;
    uint8_t month;
    uint16_t year;
} Date;

typedef enum {
    CONVERSION_SUCCESS,
    NULL_POINTER_ERROR,
    INCORRECT_FORMAT_ERROR
} ConversionStatus;

ConversionStatus convertStringToDate(const char* dateString, Date* result) {
    if (dateString == NULL || result == NULL) {
        return NULL_POINTER_ERROR;
    }

    int day, month, year;
    if (sscanf(dateString, "%d/%d/%d", &day, &month, &year) != 3) {
        return INCORRECT_FORMAT_ERROR;
    }

    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 0) {
        return INCORRECT_FORMAT_ERROR;
    }

    result->day = (uint8_t)day;
    result->month = (uint8_t)month;
    result->year = (uint16_t)year;

    return CONVERSION_SUCCESS;
}

int main() {
    char dateString[11];
    Date result;

    printf("Enter the date in dd/mm/yyyy format: ");
    scanf("%10s", dateString);

    ConversionStatus status = convertStringToDate(dateString, &result);

    if (status == CONVERSION_SUCCESS) {
        printf("Conversion successful\n");
        printf("Date: %d\n", result.day);
        printf("Month: %d\n", result.month);
        printf("Year: %d\n", result.year);
    } else if (status == NULL_POINTER_ERROR) {
        printf("Error: NULL pointers\n");
    } else if (status == INCORRECT_FORMAT_ERROR) {
        printf("Error: Incorrect date format\n");
    }

    return 0;
}