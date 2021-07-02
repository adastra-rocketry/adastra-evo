#include "SDWriter.h"

SDWriter::SDWriter(SystemState &state) : State{state}
{
}

void SDWriter::Init()
{
  
  pinMode(SD_CS_PIN, OUTPUT);
  if (!sd.begin(SD_CONFIG)) {
    sd.initErrorHalt(&Serial);
    SDavailable = false;
  } else {
    StartNewFile();
  }
}

void SDWriter::StartNewFile()
{
  if(DEBUG) Serial.println("BEGIN SDWriter::StartNewFile()");
  if (CsvFile.isOpen())
  {
    CsvFile.close();
  }

  int n = 0;
  do 
  {
    snprintf(Filename, sizeof(Filename), "data%03d.csv", n);
    n++;
  } while (sd.exists(Filename));

  Serial.print("Using filename: ");
  Serial.println(Filename);


  if(!CsvFile.open(Filename, O_WRONLY | O_CREAT | O_TRUNC)) {
    Serial.println("open CSV File failed");
  }

  // if (!CsvFile.preAllocate(PREALLOCATE_SIZE)) {
  //   Serial.println("preAllocate failed");
  // }
  CreateCsvHeadings();
  if(DEBUG) Serial.println("END SDWriter::StartNewFile()");
}

void SDWriter::Loop()
{
  if(DEBUG) Serial.println("BEGIN SDWriter::Loop()");
  if(SDavailable) {
    CreateCsvLine();
  }

  if(Counter % 50 == 0) {
    if(DEBUG) Serial.println("BEGIN SDWriter::Loop() Before Flush");
    CsvFile.flush();
    if(DEBUG) Serial.println("BEGIN SDWriter::Loop() Flush");
  }

  Counter++;
  if(DEBUG) Serial.println("ENd SDWriter::Loop()");
}

void SDWriter::CreateCsvHeadings()
{
  String headings = "state;timestamp;pressure;temperature;accX;accY;accZ;gX;gY;gZ;accX;accY;accZ;gX;gY;gZ;backTemp;altitude;KalmanPressure";
  if (CsvFile.isOpen())
  {
    CsvFile.println(headings);
    CsvFile.flush();
  }
}

void SDWriter::CreateCsvLine()
{
  

  if (CsvFile.isOpen())
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
    CsvFile.println(dataString);
  }
}