#include "TVC.h"

TVC::TVC(SystemState &state) : State{ state } {
  
}

void TVC::Init() {
  pinMode(A3, OUTPUT);
  digitalWrite(A3, HIGH);
  ServoX.attach(9); // servo on digital pin 10
  ServoY.attach(10); // servo on digital pin 10
}

void TVC::Loop() {
    
}