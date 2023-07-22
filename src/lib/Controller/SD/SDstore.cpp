#include "SDStore.h"

void SDStore::initSD()
{
    if (!SD.begin(BUILTIN_SDCARD))
    {
#ifdef DEBUG
        Serial.println("Card failed, or not present");
#else
        Serial.println("Card failed, or not present");
#endif
    }
    else
    {
#ifdef DEBUG
        Serial.println("card initialized.");
#endif
    }

    generateFileName();
}

void SDStore::generateFileName()
{
    uint32_t current_time = PERSISTANCE::readCounter(EEPROM_time_base_address);
    storeFile = String(current_time);
    String originalName = String(current_time);

    char buffer[32];
    storeFile.toCharArray(buffer, 32);

    uint8_t i = 1;
    while (SD.exists(buffer))
    {
#ifdef DEBUG
        Serial.println(storeFile);
#endif
        storeFile = originalName + "." + i;

        storeFile.toCharArray(buffer, 32);
        i++;
    }
}

void SDStore::saveLine(String data)
{
    char buffer[32];
    storeFile.toCharArray(buffer, 32);
    File dataFile = SD.open(buffer, FILE_WRITE);
    if (dataFile)
    {
        dataFile.println(data);
        dataFile.close();
    }
}