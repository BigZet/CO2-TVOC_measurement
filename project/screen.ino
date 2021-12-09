void screenInit(){
  screen.begin(SSD1306_SWITCHCAPVCC);
  screen.clearDisplay();
  screen.setTextSize(1.5);
  screen.setTextColor(WHITE);
  screen.setCursor(0,0);
  screen.println("Starting screen");
  screen.display();
}

void scrPrint(String text){
  screen.clearDisplay();
  screen.setCursor(0,0);
  screen.println(text);
  screen.display();
}

void showCO2TVOC(int CO2, int TVOC){
  screen.clearDisplay();
  screen.setCursor(0,0);
  screen.println("CO2: " + String(CO2));
  screen.setCursor(0,10);
  screen.println("TVOC: " + String(TVOC));
  if(CO2<500){
    screen.setCursor(0,20);
    screen.println("CO2 LEVEL: LOW");
  } else if (CO2<1000){
    screen.setCursor(0,20);
    screen.println("CO2 LEVEL: MIDDLE");
  } else if (CO2<2000){
    screen.setCursor(0,20);
    screen.println("CO2 LEVEL: HIGH");
  }else{
    screen.setCursor(0,20);
    screen.println("CO2 LEVEL: TOO HIGH!");
  }
  screen.display();
}
