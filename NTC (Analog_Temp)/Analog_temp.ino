#include <math.h>
#include <stdio.h>

const int AnalogPin = 0;
const float Rknown = 10000.0; // or 10000; R1 or R2 in a voltage divider? TBA. 
const float Vin = 5.0;

double Thermister(int RawADC) { //Best place to put the function: before or after setup()? TBA. 
  double Temp1, Temp2, Vout, Runknown1, logRunknown1, Runknown2, logRunknown2, Temp1C;
  double A = 0.0008395; // constant A, B and C from Steinhart–Hart equation
  double B = 0.00025942;
  double C = 0.00000016082;
  Vout = (5.0 / 1023.0) * RawADC;
  Runknown1 = Rknown * (1 / ((Vin / Vout) - 1));
  //Runknown2 = Rknown * ((Vin / Vout) - 1);
  logRunknown1 = log(Runknown1);
  //logRunknown2 =  log(Runknown2);
  Temp1 = 1 / (A + (B + (C * logRunknown1 * logRunknown1)) * logRunknown1);  //gives correct value as temperature rises on touch of figure to the sensor
  //Temp2 = 1 / (A + (B + (C * logRunknown2 * logRunknown2)) * logRunknown2);  //temp decreases when toched by fingures
  //Temp = log(((10240000/RawADC) - 10000));
  ////Temp = log(1000.0 / (1024.0/ RawADC -1));
  //Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
  //Temp = Temp - 273.15;// Convert Kelvin to Celcius
  return Temp1 - 273.15;
}
void setup() {
  Serial.begin(9600);

}
void loop() {
  Serial.println(analogRead(AnalogPin));
  Serial.print(Thermister(analogRead(AnalogPin)));
  Serial.println(" C");
  delay(1000);
}
