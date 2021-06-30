#include "SDWriter.h"

#define SPI_SPEED SD_SCK_MHZ(50)

SDWriter::SDWriter(SystemState &state) : State{state}
{
}

void SDWriter::Init()
{
  if(!SD.begin(SD_CARD_PIN)) {
    SDavailable = false;
  } else {
    StartNewFile();
  }
}

void SDWriter::StartNewFile()
{
  if(DEBUG) Serial.println("BEGIN SDWriter::StartNewFile()");
  if (DataFile)
  {
    DataFile.close();
  }
  int n = 0;
  snprintf(Filename, sizeof(Filename), "data%03d.csv", n);
  while (SD.exists(Filename))
  {
    n++;
    snprintf(Filename, sizeof(Filename), "data%03d.csv", n);
  }
  DataFile = SD.open(Filename, O_WRITE | O_CREAT);
  CreateCsvHeadings();
  if(DEBUG) Serial.println("END SDWriter::StartNewFile()");
}

void SDWriter::Loop()
{
  if(DEBUG) Serial.println("BEGIN SDWriter::Loop()");
  if(SDavailable) {
    CreateCsvLine();
  }
  if(Counter % 20 == 0) {
    if(DEBUG) Serial.println("BEGIN SDWriter::Loop() Before Flush");
    DataFile.flush();
    if(DEBUG) Serial.println("BEGIN SDWriter::Loop() Flush");
  }

  Counter++;
  if(DEBUG) Serial.println("ENd SDWriter::Loop()");
}

void SDWriter::CreateCsvHeadings()
{
  String headings = "state;timestamp;pressure;temperature;accX;accY;accZ;gX;gY;gZ;accX;accY;accZ;gX;gY;gZ;backTemp;altitude;KalmanPressure";
  if (DataFile)
  {
    DataFile.println(headings);
    DataFile.flush();
  }
}

void SDWriter::CreateCsvLine()
{
  

  if (DataFile)
  {
    char dataString[500];
    snprintf(dataString, 400, "%u;%lu;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f",
             State.CurrentDataPoint.State,
             State.CurrentDataPoint.Timestamp,
             State.CurrentDataPoint.Pressure,
             State.CurrentDataPoint.Temperature,
             State.CurrentDataPoint.Acc_X,
             State.CurrentDataPoint.Acc_Y,
             State.CurrentDataPoint.Acc_Z,
             State.CurrentDataPoint.G_X,
             State.CurrentDataPoint.G_Y,
             State.CurrentDataPoint.G_Z,
             State.CurrentDataPoint.Back_Acc_X,
             State.CurrentDataPoint.Back_Acc_Y,
             State.CurrentDataPoint.Back_Acc_Z,
             State.CurrentDataPoint.Back_G_X,
             State.CurrentDataPoint.Back_G_Y,
             State.CurrentDataPoint.Back_G_Z,
             State.CurrentDataPoint.Back_Temperature,
             State.CurrentDataPoint.Altitude,
             State.CurrentDataPoint.KalmanPressure);
    DataFile.println(dataString);
  }
}