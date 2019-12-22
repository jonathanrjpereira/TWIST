float getTemperature(){
  float tempSensorValue = analogRead(temperatureSensor);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = tempSensorValue * (5.0 / 1023.0);
  // print out the value you read:
  //Serial.print("Voltage(V)=  ");
  //Serial.print(voltage);
  //Serial.println();
  int Temperature;
  if ((voltage > 2.521) && (voltage < 2.585))
    Temperature = 0;
  if ((voltage > 2.585) && (voltage < 2.648))
    Temperature = 1 ;
  if ((voltage > 2.648) && (voltage < 2.711))
    Temperature = 2;
  if ((voltage > 2.711) && (voltage < 2.773))
      Temperature = 3;
  if ((voltage > 2.773) && (voltage < 2.834))
    Temperature = 4;
  if ((voltage > 2.834) && (voltage < 2.894))
    Temperature = 5;
  if ((voltage > 2.894) && (voltage < 2.95))
    Temperature = 6;
  if ((voltage > 2.95) && (voltage < 3.01))
    Temperature = 7;
  if ((voltage > 3.01) && (voltage < 3.07))
    Temperature = 8;
  if ((voltage > 3.07) && (voltage < 3.13))
    Temperature = 9;
  if ((voltage > 3.13) && (voltage < 3.18))
    Temperature = 10;
  if ((voltage > 3.18) && (voltage < 3.24))
    Temperature = 11;
  if ((voltage > 3.24) && (voltage < 3.29))
    Temperature = 12;
  if ((voltage > 3.29) && (voltage < 3.34))
    Temperature = 13;
  if ((voltage > 3.34) && (voltage < 3.40))
    Temperature = 14;
  if ((voltage > 3.40) && (voltage < 3.45))
    Temperature = 15;
  if ((voltage > 3.45) && (voltage < 3.5))
    Temperature = 16;
  if ((voltage > 3.5) && (voltage < 3.54))
    Temperature = 17;
  if ((voltage > 3.54) && (voltage < 3.59))
    Temperature = 18;
  if ((voltage > 3.59) && (voltage < 3.64))
    Temperature = 19;
  if ((voltage > 3.64) && (voltage < 3.68))
    Temperature = 20;
  if ((voltage > 3.68) && (voltage < 3.72))
    Temperature = 21;
  if ((voltage > 3.72) && (voltage < 3.76))
    Temperature = 22;
  if ((voltage > 3.76) && (voltage < 3.81))
    Temperature = 23;
  if ((voltage > 3.81) && (voltage < 3.85))
    Temperature = 24;
  if ((voltage > 3.85) && (voltage < 3.88))
    Temperature = 25;
  if ((voltage > 3.88) && (voltage < 3.92))
    Temperature = 26;
  if ((voltage > 3.92) && (voltage < 3.96))
    Temperature = 27;
  if ((voltage > 3.96) && (voltage < 3.99))
    Temperature = 28;
  if ((voltage > 3.99) && (voltage < 4.03))
    Temperature = 29;
  if ((voltage > 4.03) && (voltage < 4.06))
    Temperature = 30;
  if ((voltage > 4.06) && (voltage < 4.09))
    Temperature = 31;
  if ((voltage > 4.09) && (voltage < 4.12))
    Temperature = 32;
  if ((voltage > 4.12) && (voltage < 4.15))
    Temperature = 33;
  if ((voltage > 4.15) && (voltage < 4.18))
    Temperature = 34;
  if ((voltage > 4.18) && (voltage < 4.21))
    Temperature = 35;
  if ((voltage > 4.21) && (voltage < 4.24))
    Temperature = 36;
  if ((voltage > 4.24) && (voltage < 4.26))
    Temperature = 37;
  if ((voltage > 4.26) && (voltage < 4.29))
    Temperature = 38;
  if ((voltage > 4.29) && (voltage < 4.31))
    Temperature = 39;
  if ((voltage > 4.31) && (voltage < 4.34))
    Temperature = 40;
  if ((voltage > 4.34) && (voltage < 4.36))
    Temperature = 41;
  if ((voltage > 4.36) && (voltage < 4.38))
    Temperature = 42;
  if ((voltage > 4.38) && (voltage < 4.4))
    Temperature = 43;
  if ((voltage > 4.4) && (voltage < 4.42))
    Temperature = 44;
  if ((voltage > 4.42) && (voltage < 4.44))
    Temperature = 45;
  if ((voltage > 4.44) && (voltage < 4.46))
    Temperature = 46;
  if ((voltage > 4.46) && (voltage < 4.48))
    Temperature = 47;
  if ((voltage > 4.48) && (voltage < 4.5))
    Temperature = 48;
  if ((voltage > 4.5) && (voltage < 4.51))
    Temperature = 49;
  if ((voltage > 4.51) && (voltage < 4.52))
    Temperature = 50;

  Serial.print("Temperature:");
  Serial.print(Temperature);
  Serial.println();
  return Temperature;
}
