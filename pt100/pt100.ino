#include <math.h>
#include <stdio.h>

const int AnalogPin = 0;
const float Rknown = 10000.0; // or 10000; R1 or R2 in a voltage divider? TBA. 
const float Vin = 5.0;

double Thermister(int RawADC) { //Best place to put the function: before or after setup()? TBA. 
  double A = 0.0008395; // constant A, B and C from Steinhart–Hart equation
  double B = 0.00025942;
  double C = 0.00000016082;
  double Temp1, Temp2, Vout, Runknown1, logRunknown1, Runknown2, logRunknown2, Temp1C;
  Vout = (5.0 / 1023.0) * RawADC;
  Runknown1 = Rknown * (1 / ((Vin / Vout) - 1));
  //Runknown2 = Rknown * ((Vin / Vout) - 1);
  logRunknown1 = log(Runknown1);
  //logRunknown2 =  log(Runknown2);
  Temp1 = 1 / (A + (B + (C * logRunknown1 * logRunknown1 ))* logRunknown1);
  return Temp1 - 273.15;
}
void setup() {
  Serial.begin(9600);

}
void loop() {
  //Serial.println(analogRead(AnalogPin));
  Serial.print(Thermister(analogRead(AnalogPin)));
  Serial.println(" deg Cel");
  delay(1000);
}
