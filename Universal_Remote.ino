
#include <IRremote.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//#include <RH_ASK.h>
//#include <SPI.h> // Not actualy used but needed to compile
//#include <EEPROM.h>

//RH_ASK driver;

#define BTN_UP      A1
#define BTN_DOWN    A2
#define BTN_OK      9
#define BTN_CANCEL  8
#define SEND_PIN    7
#define BTN_POW     A0

#define LED_GREEN   3
#define LED_RED     4
IRsend irsend(SEND_PIN);

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

String splash_screen[4] = {"==============", "UNIVERSAL", "TRANSMITTER", "=============="};

const int menuLen = 3;
String Menu[menuLen] = {"UNIVERSAL REMOTE", "BLUETOOTH", "433hz TRANSMITTER"}; 

int currentTargetMenu = 1, RCurrentTargetMenu = 1;
int currentIndex = 1, RCurrentIndex = 1;

const int IRMenuLen = 5;
String IRMenu[IRMenuLen] = {"NEC", "SAMSUNG", "SHARP", "LG", "PANASONIC"};

int menuDelay = 500;

String menu_name;

bool apply_draw_selected_once = false;
bool selecting_actions = false;
bool selected_main_menu = false;

void setup()
{
    Serial.begin(9600);
    Serial.println("IR Receiver ready");
    
    pinMode(BTN_POW, INPUT_PULLUP);
    pinMode(BTN_OK, INPUT_PULLUP);
    pinMode(BTN_CANCEL, INPUT_PULLUP);
    pinMode(BTN_UP, INPUT_PULLUP);
    pinMode(BTN_DOWN, INPUT_PULLUP);

    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_RED, OUTPUT);

    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
      Serial.println(F("SSD1306 allocation failed"));
      int ctr = 0;
      for(;;){
        if(ctr % 2 == 0){
          digitalWrite(LED_RED, LOW);
        }
        else {
          digitalWrite(LED_RED, HIGH);
        }
        delay(2000);
      }
    }
    
    drawSplashScreen(0, 3, splash_screen);
    delay(3000);
//    if (!driver.init())
//         Serial.println("init failed");
         
//    int codeType = 0x20DF10EF >> 16;
//    Serial.println(codeType);

//    const char *msg = "Hello World!";
//    driver.send((uint8_t *)msg, strlen(msg));
//    driver.waitPacketSent();
    drawMenuList(0, 3, true, Menu, "MENU", 1, -1);
}

void loop()
{
    if(analogRead(BTN_POW) <= 15){
      irsend.sendNEC(0x20DF10EF, 32); //AnalysIR Batch Export (IRremote) // AnalysIR IR Protocol: NEC, 
      Serial.println("POWER");
      delay(500);
    }
    else if(digitalRead(BTN_OK) == LOW){
//      if(digitalRead(LED_GREEN) == HIGH){
//        digitalWrite(LED_GREEN, LOW);
//        display.clearDisplay();
//        drawCentered(1, "LED GREEN", false);
//        drawCentered(2, "LOW", false);
//        display.display();
//      }
//      else {
//        digitalWrite(LED_GREEN, HIGH);
//        display.clearDisplay();
//        drawCentered(1, "LED GREEN", false);
//        drawCentered(2, "HIGH", false);
//        display.display();
//      }
//      
//      irsend.sendNEC(0x20DF10EF, 32); //AnalysIR Batch Export (IRremote) // AnalysIR IR Protocol: NEC, 
//      Serial.println("OK");

        selected_main_menu = true;
        /*
         *  DISPLAY THE MENU ONCE PUSH BUTTON IS TRIGGERED.
         */
        if(!apply_draw_selected_once){
              apply_draw_selected_once = true;
              switch(currentIndex - 1){
                case 0: menu_name = IRMenu[RCurrentIndex - 1];
                        drawMenuList(0, 3, true, IRMenu, "REMOTE BRAND", RCurrentTargetMenu, currentIndex - 1); 
                  break;
              }
        }
        
        delay(menuDelay);
    }
    else if(digitalRead(BTN_CANCEL) == LOW){
        if(currentIndex == menuLen) {
          drawMenuList(currentIndex - 3, currentIndex, true, Menu, "MENU", 3, -1);
          selected_main_menu = false;
          apply_draw_selected_once = false;
        }
        else if(currentIndex == 1)  {
          drawMenuList(currentIndex-1, currentIndex + 2, true, Menu, "MENU", 1, -1);
          selected_main_menu = false;
          apply_draw_selected_once = false;
        }
        else {
          drawMenuList(currentIndex - 2, currentIndex + 1, true, Menu, "MENU", 2, -1);
          selected_main_menu = false;
          apply_draw_selected_once = false;
        }

        delay(menuDelay);
//      if(digitalRead(LED_RED) == HIGH){
//        digitalWrite(LED_RED, LOW);
//        display.clearDisplay();
//        drawCentered(1, "LED RED", false);
//        drawCentered(2, "HIGH", false);
//        display.display();
//      }
//      else {
//        digitalWrite(LED_RED, HIGH);
//        display.clearDisplay();
//        drawCentered(1, "LED RED", false);
//        drawCentered(2, "LOW", false);
//        display.display();
//      }
//      
//      irsend.sendNEC(0x20DF10EF, 32); //AnalysIR Batch Export (IRremote) // AnalysIR IR Protocol: NEC, 
//      Serial.println("CANCEL");
//      delay(500);
    }
    else if(analogRead(BTN_UP) <= 15){
//      irsend.sendNEC(0x20df40bf, 32); //AnalysIR Batch Export (IRremote) // AnalysIR IR Protocol: NEC, 
//      Serial.println("UP");
//      const char *msg = "UP!";
//      driver.send((uint8_t *)msg, strlen(msg));
//      driver.waitPacketSent();
//      delay(500);
      if(selected_main_menu && !selecting_actions){
            switch(currentIndex - 1){
              case 0: Menu_BTN_UP(RCurrentTargetMenu, RCurrentIndex, true, IRMenu, IRMenuLen, "REMOTE BRAND", 0, currentIndex - 1);
                break;
            }
        }
        else {
          Menu_BTN_UP(currentTargetMenu, currentIndex, true, Menu, menuLen, "MENU", -1, -1);
        }
    }
    else if(analogRead(BTN_DOWN) <= 15){
//      irsend.sendNEC(0x20dfc03f, 32); //AnalysIR Batch Export (IRremote) // AnalysIR IR Protocol: NEC, 
//      Serial.println("DOWN");
//      const char *msg = "DOWN!";
//      driver.send((uint8_t *)msg, strlen(msg));
//      driver.waitPacketSent();
//      delay(500);
        if(selected_main_menu && !selecting_actions){
            switch(currentIndex - 1){
              case 0: Menu_BTN_DOWN(RCurrentTargetMenu, RCurrentIndex, true, IRMenu, IRMenuLen, "INFRARED MENU", 0, currentIndex - 1);
                break;
            }
        }
        else {
          Menu_BTN_DOWN(currentTargetMenu, currentIndex, true, Menu, menuLen, "MENU", -1, -1);
        }
    }  
}


void drawCentered(int lin, const char* str, bool inverted) { /* function drawCentered */

  String text = String(str);
  int strlen_ = String(str).length();
  int col = int((20 - strlen_) / 2);

  for(int i = 0; i < col; i++){
    text = " " + text + " ";
  }
  if(inverted) display.setTextColor(BLACK, WHITE);
  
  display.setCursor(0, lin * 8);
  display.println(text);
  
  display.setTextColor(WHITE);

}

void drawSplashScreen(int startIndex, int lastIndex, String list[]){
  display.clearDisplay();
  
  display.setTextColor(WHITE);
  for(int ctr = 0; ctr <= lastIndex; ctr++){
    display.setCursor(0, ctr * 8);

    String text = list[ctr];
    int strlen_ = list[ctr].length();
    int col = int((20 - strlen_) / 2);
  
    for(int x = 0; x < col; x++){
      text = " " + text + " ";
    }
    
    display.println(text);  
  }
  display.display(); 
}

void drawMenuList(int startIndex, int lastIndex, boolean draw_menu, String list[], const char* header, int targetMenu, int focusIndex){
  display.clearDisplay();
  if(draw_menu) {
    display.setTextColor(BLACK, WHITE); // Draw 'inverse' text
    
    if(header != NULL) drawCentered(0,header, false);
    else drawCentered(0,"MENU", false);
    
    display.display(); 
    display.setTextColor(WHITE);
  }
  
  int ctr = 1;
  for(int i = startIndex; i < lastIndex; i++){
    display.setCursor(0, ctr * 8);
    String target = list[i];
    int spaces = 0;
    int str_len = target.length();
    
    if(targetMenu == ctr){
        target = ">"+target;
    }
    else { 
        target = " "+target;
    } 
    display.println(target);  
    ctr++;
  }
  display.display(); 
}


void Menu_BTN_UP(int CTM, int CI, boolean draw_menu, String list[], int list_len, const char* header, int targetMenu, int focusIndex){
    if(CTM <= 1){
              if(CI <= 1){
                CTM = 3;
                CI = list_len;
                drawMenuList(list_len - 3, list_len, draw_menu, list, header, CTM, focusIndex); 
              }
              else{
                CI --;
                if(CTM > 1) CTM--;
                drawMenuList(CI - 1, CI + 2, draw_menu, list, header, CTM, focusIndex); 
              }
    }
    else {
            if(CTM == 3){
              CTM--;
              CI --;
              drawMenuList(CI - 2, CI + 1, draw_menu, list, header, CTM, focusIndex);  
            }
            else{
              CI --;
              
              if(CTM > 1) CTM--;
              drawMenuList(CI - 1, CI + 2, draw_menu, list, header, CTM, focusIndex);  
            } 
    }
    menu_name = list[CI - 1];
    delay(menuDelay);
    Menu_Variable(targetMenu, true, CTM);
    Menu_Variable(targetMenu, false, CI);
}



void Menu_BTN_DOWN(int CTM, int CI, boolean draw_menu, String list[], int list_len, const char* header, int targetMenu, int focusIndex){
    if(CTM >= 3) {
        if(CI >= list_len){
          CI = 1;
          CTM = 1;
          drawMenuList(0, 3, draw_menu, list, header, CTM, focusIndex); 
        }
        else{
          CI ++;
          CTM = 3;
          drawMenuList(CI - 3, CI, draw_menu, list, header, CTM, focusIndex); 
        }
    }
    else {
      if(CTM == 1){
        CTM++;
        CI ++;
        drawMenuList(CI - 2, CI + 1, draw_menu, list, header, CTM, focusIndex);  
      }
      else{      
        CI ++;
        if(CTM < 3) CTM++;
        drawMenuList(CI - 3, CI, draw_menu, list, header, CTM, focusIndex); 
      } 
    }

    menu_name = list[CI - 1];
    delay(menuDelay);

    Menu_Variable(targetMenu, true, CTM);
    Menu_Variable(targetMenu, false, CI);
}

void Menu_Variable(int index, bool target, int val){
  if(target){
    switch(index){
      case 0: RCurrentTargetMenu = val;
        break;
      default: currentTargetMenu = val;
    }
  }
  else {
    switch(index){
      case 0: RCurrentIndex = val;
        break;
      default: currentIndex = val;
    }
  }
}

void displayMenu(int index){
  switch(index - 1){
      case 0: 
              menu_name = IRMenu[RCurrentIndex - 1];
              drawMenuList(0, 3, true, IRMenu, "REMOTE BRAND", RCurrentTargetMenu, currentIndex - 1); 
        break;
    }
}
