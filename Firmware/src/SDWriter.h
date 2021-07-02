/*
  SDWriter.h
*/
#pragma once
#include "SystemState/SystemState.h"
#include "Arduino.h"
#include "SystemState/SystemState.h"
#include "SdFat.h"


#define SD_FAT_TYPE 3
#define SPI_CLOCK SD_SCK_MHZ(4)
#define SD_CONFIG SdSpiConfig(SD_CS_PIN, DEDICATED_SPI, SPI_CLOCK)

const uint32_t PREALLOCATE_SIZE_MiB = 128UL;
const uint64_t PREALLOCATE_SIZE  =  (uint64_t)PREALLOCATE_SIZE_MiB << 20;

#if SD_FAT_TYPE == 0
typedef SdFat sd_t;
typedef File file_t;
#elif SD_FAT_TYPE == 1
typedef SdFat32 sd_t;
typedef File32 file_t;
#elif SD_FAT_TYPE == 2
typedef SdExFat sd_t;
typedef ExFile file_t;
#elif SD_FAT_TYPE == 3
typedef SdFs sd_t;
typedef FsFile file_t;
#else  // SD_FAT_TYPE
#error Invalid SD_FAT_TYPE
#endif  // SD_FAT_TYPE

class SDWriter
{
public:
    SDWriter(SystemState &state);
    void Init();
    void Loop();

private:
    SystemState &State;
    int Counter = 0;
    char Filename[16];
    SdFat sd;
    file_t CsvFile;
    bool SDavailable = true;
    void StartNewFile();
    void CreateCsvHeadings();
    void CreateCsvLine();

};