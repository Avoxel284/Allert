/*Reference
    int sensor1Pin = 0; //Oxygen sensor (May skip!)
    int sensor2Pin = 2; //Temperature sensor [DIGITAL]
    int sensor3Pin = 2; //Humidity sensor    [DIGITAL]
    int sensor4Pin = 0;
    int sensor5Pin = 0;
    int dangerLevel = 0; //0:Good, 1:Uncomforting, 2:Dangerous

array level0Max = [0,25,60] // <Sensor1,Sensor2,Sensor3, so on...>
array level0Min = [0,15,30] // <Sensor1,Sensor2,Sensor3, so on...>
array level1Max = [0,30,70] // <Sensor1,Sensor2,Sensor3, so on...>
array level1Min = [0,25,60] // <Sensor1,Sensor2,Sensor3, so on...>
array level2Max = [0,100,100] // <Sensor1,Sensor2,Sensor3, so on...>
array level2Min = [0,30,70] // <Sensor1,Sensor2,Sensor3, so on...>
 */

int readDanger(){
  if(readSensor(2)>=level0Min[2] && readSensor(2)<=level0Max[2] || readSensor(3)>=level0Min[2] && readSensor(3)<=level0Max[2]){ //LEVEL 0  [Temperature,Humidity]
    dangerLevel=0;
    return(dangerLevel);
  }
  if(readSensor(2)>=level1Min[2] && readSensor(2)<=level1Max[2] || readSensor(3)>=level1Min[2] && readSensor(3)<=level1Max[2]){ //LEVEL 1  [Temperature,Humidity]
    dangerLevel=1;
    return(dangerLevel);
  }
  if(readSensor(2)>=level2Min[2] && readSensor(2)<=level2Max[2] || readSensor(3)>=level2Min[2] && readSensor(3)<=level2Max[2]){ //LEVEL 2  [Temperature,Humidity]
    dangerLevel=2;
    return(dangerLevel);
  }
  
}

int oldDangerLevel = 0;

void checkDanger(){
  if(readDanger()==0){
    if(oldDangerLevel!=dangerLevel){Blynk.notify("Level 0 Danger detected - This means everything is good and in the comfort zone");oldDangerLevel=dangerLevel;delay(40);}
    Blynk.virtualWrite(5,0);
    terminal.println("//Level 0 danger detected - All good//");
  }
  if(readDanger()==1){
    if(oldDangerLevel!=dangerLevel){Blynk.notify("Level 1 Danger detected - This just means that the conditions are a little over the comfort zone");oldDangerLevel=dangerLevel;delay(40);}
    Blynk.virtualWrite(5,100);
    terminal.println("//Level 1 Danger detected//");
  }
  if(readDanger()==2){
    if(oldDangerLevel!=dangerLevel){Blynk.notify("Level 2 Danger detected!! - Conditions are dangerous!");oldDangerLevel=dangerLevel;delay(40);}
    Blynk.virtualWrite(5,255);
    terminal.println("//Level 2 Danger detected//");
  }
}
