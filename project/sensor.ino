void sensorInit(){
  Serial.println("Init CCS811 module");
  scrPrint("Init CCS811 module");
  if(!ccs.begin()){
    Serial.println("Failed to start CCS811 module");
    scrPrint("Failed to start CCS811 module");
  }
  while(!ccs.available());
  scrPrint("CCS811 module started");
}

void measure(){
  if(ccs.available()){
    digitalWrite(readLED, 1); 
    if(!ccs.readData()){
      CO2 = ccs.geteCO2()-400;
      TVOC = ccs.getTVOC()- ((int) (CO2/6.57));
      Serial.print("CO2: ");
      Serial.print(String(CO2)+" ");
      Serial.print("TVOC: ");
      Serial.println(String(TVOC));
      msg_CO2(CO2);
      msg_TVOC(TVOC);
      showCO2TVOC(CO2, TVOC);
    }else{
      Serial.println("Can't read data from sensor");
      msg_sensor_error();
    }
    digitalWrite(readLED, 0); 
  }
}
