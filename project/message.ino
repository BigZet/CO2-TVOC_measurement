void publishMsg(String msg, bool telemetry){
  String topic = "";
  if (telemetry){
    topic = "v1/devices/me/telemetry";
  }
  else{
    topic = "v1/devices/me/attributes";
  }


  Serial.println(msg);
  mqttClient.beginMessage(topic);
  mqttClient.print(msg);
  mqttClient.endMessage();
}

String toJSON(String at_name, String value){
  doc.clear();
  doc[at_name]=value;
  String msg;
  serializeJson(doc, msg);
  return msg;
}

void msg_CO2(int value){
  publishMsg(toJSON("CO2", String(value)), true);
}

void msg_TVOC(int value){
  publishMsg(toJSON("TVOC", String(value)), true);
}

void msg_connect(){
  publishMsg(toJSON("alive", String(true)), false);
}

void msg_sensor_error(){
  publishMsg(toJSON("error_msg", "Can't read data from sensor"), false);
}
