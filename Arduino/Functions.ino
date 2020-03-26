//Functions
int readSensor(int sensorType){
  /* Sensor int list
   *  1. Oxygen sensor
   *  2. Temperature sensor
   *  3. Moisture sensor
   *  4.
   *  5.
   */

  if(sensorType>0 && sensorType<4){
  switch(sensorType){
    case 1:
        terminal.println("//Sensor 0 not available//");
        error(true);
        return 0;
      break;
    case 2: //Temperature Sensor
        return(dht.readTemperature());
      break;
    case 3: //Humidity Sensor
        return(dht.readHumidity());
  }
  }else{
    Serial.print("DEBUG: Sensor not available");
    terminal.println("ERROR: Sensor not available");
    error(true);
  }
}

void error(bool error){
  if(error==true){
    Blynk.virtualWrite(4,255);
    terminal.println("//Error detected//");
    delay(500);
    Blynk.virtualWrite(4,50);
    delay(500);
    Blynk.virtualWrite(4,255);
    terminal.println("!PLEASE RESTART ALLERT!");
  }else{
    Serial.println("Error Dismissed");
    Blynk.virtualWrite(4,false);
    terminal.println("//Error dismissed//");
  }
}
