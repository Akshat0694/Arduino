#include <math.h>
#include <stdio.h>

const int AnalogPin = 0;
const float Rknown = 10000.0;
const float Vin = 5.0;

double Thermister(int RawADC) { //Best place to put the function: before or after setup()? TBA. 
  double A = 0.0008395; // constant A, B and C from Steinhart–Hart equation
  double B = 0.00025942;
  double C = 0.00000016082;
  double Temp, Vout, Runknown1;
  Vout = (5.0 / 1023.0) * RawADC;
  Runknown1 = Rknown * (1 / ((Vin / Vout) - 1));
  //Runknown1 = Rknown * ((Vin / Vout) - 1);
  Temp = 2.596 * Runknown1 - 264.827;
  //return Runknown1;
  return Temp;
}
void setup() {
  Serial.begin(9600);

}
void loop() {
  //Serial.println(analogRead(AnalogPin));
  Serial.print(Thermister(analogRead(AnalogPin)));
  Serial.println(" C");
  delay(1000);
}
