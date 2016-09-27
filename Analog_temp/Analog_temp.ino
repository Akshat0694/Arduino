#include <math.h>
#include <stdio.h>

const int AnalogPin = 0;
const float Rknown = 10.0; // or 10000; R1 or R2 in a voltage divider? TBA. 
const float Vin = 5.0;
const double A = 0.001129148; // constant A, B and C from Steinhart–Hart equation
const double B = 0.000234125;
const double C = 0.0000000876741;

double Thermister(int RawADC) { //Best place to put the function: before or after setup()? TBA. 
  double Temp1, Temp2, Vout, Runknown1, Runknown2, Temp1C;
  Vout = (5.0 / 1023.0) * RawADC;
  //Runknown1 = Rknown * (1 / ((Vin / Vout) - 1));
  Runknown2 =  Rknown * ((Vin / Vout) - 1);
  //Temp1 = (1 / (A + (B * log(Runknown1)) + (C * pow(Runknown1, 3)))) - 273.15;
  Temp2 = (1 / (A + (B * log(Runknown2)) + (C * pow(Runknown2, 3)))) - 273.15;
  //Temp = log(((10240000/RawADC) - 10000));
  ////Temp = log(1000.0 / (1024.0/ RawADC -1));
  //Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
  //Temp = Temp - 273.15;// Convert Kelvin to Celcius
  return Temp2;
}
void setup() {
  Serial.begin(9600);

}
void loop() {
  Serial.println(analogRead(AnalogPin));
  Serial.print(Thermister(analogRead(AnalogPin)));
  Serial.println(" Celcius");
  delay(1000);
}
