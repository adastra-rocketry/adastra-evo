/*
  SDWriter.h
*/
#pragma once
#include "SystemState/SystemState.h"
#include "Arduino.h"
#include "SystemState/SystemState.h"
#include <SPI.h>
#include <SD.h>

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
    File DataFile;
    bool SDavailable = true;
    void StartNewFile();
    void CreateCsvHeadings();
    void CreateCsvLine();

};