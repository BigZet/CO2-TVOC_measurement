void connectWiFi() {
  Serial.print("Attempting to connect to SSID: ");
  Serial.print(ssid);
  Serial.print(" ");
  scrPrint("Connect to: "+String(ssid));


  //Пока не подключимся к сети по SSID и паролю
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    //При неудаче
    Serial.print(".");
    //Ждем 5 сек
    delay(5000);
  }
  Serial.println();

  //При удаче
  Serial.println("You're connected to the network");
  scrPrint("You're connected to the network");
  Serial.println();
}

void connectMQTT() {
  Serial.print("Attempting to connect to MQTT broker: ");
  scrPrint("Connect to: "+String(broker));
  Serial.print(broker);
  Serial.println(" ");

  if (!mqttClient.connect(broker, 1883)) {
      // Неудача
    Serial.print(".");
      //Спим 5 сек
  }
  Serial.println();
  Serial.println("You're connected to the MQTT broker");
  scrPrint("You're connected to the MQTT broker");
  Serial.println();

  mqttClient.subscribe("v1/devices/me/rpc/request/+", 1);
}

void reConnect(){

  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }

  if (!mqttClient.connected()) {
    connectMQTT();
  }
  mqttClient.poll();
  msg_connect();
  
}

void networkInit(){
  mqttClient.setId(deviceID);
  mqttClient.setUsernamePassword(accessToken, "");
  reConnect();
  Serial.println("Successful connection");
  scrPrint("Successful connection");
}
