float getHumidity(){
  int humidSensorValue = analogRead(humiditySensor);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  // Multiply by 1000 so that map() function can work properly. map() does not count numbers after the decimal.
  float humidvoltage = humidSensorValue * (5.0 / 1023.0) * 1000;
  // When Humidity is 20%RH Voltage is 660mV. When Humidity is 95%RH Voltage is 3135mV.
  float humidity = map(humidvoltage, 660, 3135, 20, 95);
  // print out the value of humidity:
  Serial.print("Humidity:");
  Serial.print(humidity);
  Serial.println();
  return humidity;
}
