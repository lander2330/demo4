// Sketch: demo4.ino
// Version: 2026.04.18
// Author: Larry Anderson
//
// This ESP32 microcontroller program uses an infrared receiver to read keys pressed on an infrared remote control. 
//
// It uses the following 3 hardware components:
//
// 1. Espressif Systems
//    ESP32-C6-DEVKITC-1-N8-Microcontroller
//
// 2. Digital 38khz infrared receiver module
//
// 3. Smart TV QWERTY Dual Side Keyboard Remote Control

// this statement includes the remote control infrared led receiver library
#include <IRremote.hpp>
const byte IR_RECEIVE_PIN = 10;

char msg[100];

int irCodes[256];
int irKey;
int irCode;

// these statements define the keys on frontside of remote control
const int KEYINPUT = 0x2F;
const int KEYPOWER = 0x08;
const int KEYAMAZON = 0xEA;
const int KEYNETFLIX = 0xEB;
const int KEYMGO = 0xED;
const int KEYBACKWARD = 0x35;
const int KEYPAUSE = 0x37;
const int KEYPLAY = 0x33;
const int KEYFORWARD = 0x36;
const int KEYCC = 0x39;
const int KEYRECORD = 0x34;
const int KEYSTOP = 0x30;
const int KEYINFO = 0x1B;
const int KEYEXIT = 0x49;
const int KEYMENU = 0x4F;
const int KEYOK = 0x44;
const int KEYUP = 0x45;
const int KEYDOWN = 0x46;
const int KEYLEFT = 0x47;
const int KEYRIGHT = 0x48;
const int KEYBACK = 0x4A;
const int KEYGUIDE = 0x1C;
const int KEYYELLOW = 0x52;
const int KEYBLUE = 0x53;
const int KEYRED = 0x54;
const int KEYGREEN = 0x55;
const int KEYVOLUMEUP = 0x02;
const int KEYVOLUMEDOWN = 0x03;
const int KEYMUTE = 0x09;
const int KEYVISIO = 0x2D;
const int KEYREPLAY = 0x1A;
const int KEYCHANNELUP = 0x00;
const int KEYCHANNELDOWN = 0x01;
const int KEY0 = 0x10; // 48
const int KEY1 = 0x11; // 49
const int KEY2 = 0x12; // 50
const int KEY3 = 0x13; // 51
const int KEY4 = 0x14; // 52
const int KEY5 = 0x15; // 53
const int KEY6 = 0x16; // 54
const int KEY7 = 0x17; // 55
const int KEY8 = 0x18; // 56
const int KEY9 = 0x19; // 57
const int KEYWIDE = 0x77;
const int KEYDASH = 0xFF; // treat like a period 

// these statements define the keys on backside of remote control
const int KEYBACKUP = 0xE2;
const int KEYBACKDOWN = 0xE3;
const int KEYBACKLEFT = 0xE4;
const int KEYBACKRIGHT = 0xE5;

const int KEYBLUEX = 0xE7;
const int KEYYELLOWY = 0xE6;
const int KEYREDB = 0xE8;
const int KEYGREENA = 0xE9;

const int KEYENTER = 0xFE;
const int KEYBACKSPACE = 0xCA;
const int KEYSHIFTBACKSPACE = 0xCA;
const int KEYTAB = 0xCB;
const int KEYFORWARDSLASH = 0xDE; // 47
const int KEYAT = 0xA9; // 64
const int KEYCOLON = 0xD9; // 58
const int KEYSPACE = 0xCC; // 32
const int KEYCOMMA = 0xA7; // 44
const int KEYPERIOD = 0xA8; // 46
const int KEYDOTCOM = 0xDA;

const int KEYALTPERCENT = 0xAD; // 37
const int KEYALTPOUND = 0xAB; // 35
const int KEYALTDOLLAR = 0xAC; // 36
const int KEYALTEQUAL = 0xA5; // 61
const int KEYALTPLUS = 0xC4; // 43
const int KEYALTMINUS = 0xD4; // 45
const int KEYALTQUESTION = 0xD3; // 63
const int KEYALTLEFTBRACKET = 0xD8; // 91
const int KEYALTRIGHTBRACKET = 0xC0; // 93
const int KEYALTBACKSLASH = 0xC3; // 92
const int KEYALTASTERISK = 0xD1; // 42
const int KEYALTAMPERSAND = 0xAF; // 38
const int KEYALTEXCLAMATION = 0xAA; // 33
const int KEYALTBACKSPACE = 0xCD; // 127
const int KEYALTLESSTHAN = 0xD5; // 60
const int KEYALTGREATERTHAN = 0xD7; // 62
const int KEYALTUNDERSCORE = 0xC9; // 95
const int KEYALTLEFTPAREN = 0xC1; // 40
const int KEYALTRIGHTPAREN = 0xC2; // 41
const int KEYALTTILDE = 0xD2; // 126
const int KEYALTSEMICOLON = 0xA6; // 59
const int KEYALTSINGLEQUOTE = 0xC7; // 39
const int KEYALTDOUBLEQUOTE = 0xC8; // 34

const int KEYALT0 = 0xF1; // 48
const int KEYALT1 = 0xF2; // 49
const int KEYALT2 = 0xF3; // 50
const int KEYALT3 = 0xF4; // 51
const int KEYALT4 = 0xF5; // 52
const int KEYALT5 = 0xF6; // 53
const int KEYALT6 = 0xF7; // 54
const int KEYALT7 = 0xF8; // 55
const int KEYALT8 = 0xF9; // 56
const int KEYALT9 = 0xFA; // 57

const int KEYa = 0x5B; // 97
const int KEYb = 0x75; // 98
const int KEYc = 0x6E; // 99
const int KEYd = 0x5D; // 100
const int KEYe = 0x06; // 101
const int KEYf = 0x5E; // 102
const int KEYg = 0x5F; // 103
const int KEYh = 0x68; // 104
const int KEYi = 0x57; // 105
const int KEYj = 0x69; // 106
const int KEYk = 0x6A; // 107
const int KEYl = 0x6B; // 108
const int KEYm = 0x78; // 109
const int KEYn = 0x76; // 110
const int KEYo = 0x58; // 111
const int KEYp = 0x59; // 112
const int KEYq = 0x04; // 113
const int KEYr = 0x0C; // 114
const int KEYs = 0x5C; // 115
const int KEYt = 0x0D; // 116
const int KEYu = 0x29; // 117
const int KEYv = 0x70; // 118
const int KEYw = 0x05; // 119
const int KEYx = 0x6D; // 120
const int KEYy = 0x0F; // 121
const int KEYz = 0x6C; // 122

const int KEYA = 0x8C; // 65
const int KEYB = 0x9D; // 66
const int KEYC = 0x9B; // 67
const int KEYD = 0x8E; // 68
const int KEYE = 0x7B; // 69
const int KEYF = 0x8F; // 70
const int KEYG = 0x93; // 71
const int KEYH = 0x94; // 72
const int KEYI = 0x89; // 73
const int KEYJ = 0x95; // 74
const int KEYK = 0x96; // 75
const int KEYL = 0x97; // 76
const int KEYM = 0x9F; // 77
const int KEYN = 0x9E; // 78
const int KEYO = 0x8A; // 79
const int KEYP = 0x8B; // 80
const int KEYQ = 0x79; // 81
const int KEYR = 0x7C; // 82
const int KEYS = 0x8D; // 83
const int KEYT = 0x7D; // 84
const int KEYU = 0x7F; // 85
const int KEYV = 0x9C; // 86
const int KEYW = 0x7A; // 87
const int KEYX = 0x9A; // 88
const int KEYY = 0x7E; // 89
const int KEYZ = 0x99; // 90

// these statements comment out keys that are not found on the infrared remote 
//const int KEYMISSINGCARET = 0x00; // 94
//const int KEYMISSINGSINGLEBACKQUOTE = 0x00; // 96
//const int KEYMISSINGLEFTBRACE = 0x00; // 123
//const int KEYMISSINGORBAR = 0x00; // 124
//const int KEYMISSINGRIGHTBRACE = 0x00; // 125

void setup()
    {
    // these statements initialize the arduino IDE serial monitor  
    Serial.begin(9600);
    while(!Serial)
      {
      delay(100);
      }
    Serial.println("demo4 executing");
    Serial.println("press a remote control key");    

    // this statement initialize the infrared receiver
    IrReceiver.begin(IR_RECEIVE_PIN, 0);

    // this statement initializes the array that contains remote control ascii display characters
    loadCodes();
    }

// this is the main loop that runs about 10 times every second 
void loop()
    {
    if (getIR())
      {
      // if remote control display character A-Z a-z numeric and other typewriter display characters like ~!@#$%^&*()-=_+[]\{}|;':",./<>?`  
      if (irCode !=  0)
        Serial.println((char)irCode);
      // else it must be a non-display character such as input, power, exit, menu, back, guide, vol+, vol- ch+, ch-, rewind, pause, play, forward, record, etc.
      else if (irKey == KEYMENU)
        Serial.println("Menu key pressed"); 
      else if (irKey == KEYOK)
        Serial.println("OK key pressed");
      else
        Serial.println("other non-display character remote key pressed");         
      }
    delay(100);
    }

// these statement attempt to retrieve infrared receiver data
boolean getIR()
  {
  boolean rc = (IrReceiver.decode());
  // if an infrared key code was received
  if (rc)
    {
    // ignore repeat key codes to avoid multiple actions for a single button press
    if ((IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT))
      {
      IrReceiver.resume(); // resume receiving the next signal
      return false;
      }    

    // extract the command (key code) from the decoded data
    unsigned long cmd = IrReceiver.decodedIRData.command;
    irKey = (int)cmd;
    irCode = irCodes[irKey];
    
    Serial.print("Command = ");
    Serial.println(cmd, HEX);     // print
    Serial.println(irCode);       // print decimal
    Serial.println(char(irCode)); // print character  
    Serial.print("Address = ");
    Serial.println(IrReceiver.decodedIRData.address, HEX);
    Serial.print("Raw data = ");
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    Serial.println();
    IrReceiver.printIRSendUsage(&Serial);    

    IrReceiver.resume(); // resume receiving the next signal
    }
  return rc;
  }  

// these statements associate infrared received remote control keycodes with ascii display characters
// these are the keycodes delivered by the Smart TV QWERTY Dual Side Keyboard Remote Control
void loadCodes()
  {
  for (int i = 0; i <= 255; i++)
    {
    irCodes[i] = 0;
    }  
  irCodes[KEYSPACE]=32;
  irCodes[KEYALTEXCLAMATION]=33;
  irCodes[KEYALTDOUBLEQUOTE]=34;
  irCodes[KEYALTPOUND]=35;
  irCodes[KEYALTDOLLAR]=36;
  irCodes[KEYALTPERCENT]=37;
  irCodes[KEYALTAMPERSAND]=38;
  irCodes[KEYALTSINGLEQUOTE]=39;
  irCodes[KEYALTLEFTPAREN]=40;
  irCodes[KEYALTRIGHTPAREN]=41;
  irCodes[KEYALTASTERISK]=42;
  irCodes[KEYALTPLUS]=43;
  irCodes[KEYCOMMA]=44;
  irCodes[KEYALTMINUS]=45;
  irCodes[KEYPERIOD]=46;
  irCodes[KEYDASH]=46;
  irCodes[KEYFORWARDSLASH]=47;
  irCodes[KEY0]=48;
  irCodes[KEY1]=49;
  irCodes[KEY2]=50;
  irCodes[KEY3]=51;
  irCodes[KEY4]=52;
  irCodes[KEY5]=53;
  irCodes[KEY6]=54;
  irCodes[KEY7]=55;
  irCodes[KEY8]=56;
  irCodes[KEY9]=57;
  irCodes[KEYALT0]=48;
  irCodes[KEYALT1]=49;
  irCodes[KEYALT2]=50;
  irCodes[KEYALT3]=51;
  irCodes[KEYALT4]=52;
  irCodes[KEYALT5]=53;
  irCodes[KEYALT6]=54;
  irCodes[KEYALT7]=55;
  irCodes[KEYALT8]=56;
  irCodes[KEYALT9]=57;
  irCodes[KEYCOLON]=58;
  irCodes[KEYALTSEMICOLON]=59;
  irCodes[KEYALTLESSTHAN]=60;
  irCodes[KEYALTEQUAL]=61;
  irCodes[KEYALTGREATERTHAN]=62;
  irCodes[KEYALTQUESTION]=63;
  irCodes[KEYAT]=64;
  irCodes[KEYA]=65;
  irCodes[KEYB]=66;
  irCodes[KEYC]=67;
  irCodes[KEYD]=68;
  irCodes[KEYE]=69;
  irCodes[KEYF]=70;
  irCodes[KEYG]=71;
  irCodes[KEYH]=72;
  irCodes[KEYI]=73;
  irCodes[KEYJ]=74;
  irCodes[KEYK]=75;
  irCodes[KEYL]=76;
  irCodes[KEYM]=77;
  irCodes[KEYN]=78;
  irCodes[KEYO]=79;
  irCodes[KEYP]=80;
  irCodes[KEYQ]=81;
  irCodes[KEYR]=82;
  irCodes[KEYS]=83;
  irCodes[KEYT]=84;
  irCodes[KEYU]=85;
  irCodes[KEYV]=86;
  irCodes[KEYW]=87;
  irCodes[KEYX]=88;
  irCodes[KEYY]=89;
  irCodes[KEYZ]=90;
  irCodes[KEYALTLEFTBRACKET]=91;
  irCodes[KEYALTBACKSLASH]=92;
  irCodes[KEYALTRIGHTBRACKET]=93;
  irCodes[KEYALTUNDERSCORE]=95;
  irCodes[KEYa]=97;
  irCodes[KEYb]=98;
  irCodes[KEYc]=99;
  irCodes[KEYd]=100;
  irCodes[KEYe]=101;
  irCodes[KEYf]=102;
  irCodes[KEYg]=103;
  irCodes[KEYh]=104;
  irCodes[KEYi]=105;
  irCodes[KEYj]=106;
  irCodes[KEYk]=107;
  irCodes[KEYl]=108;
  irCodes[KEYm]=109;
  irCodes[KEYn]=110;
  irCodes[KEYo]=111;
  irCodes[KEYp]=112;
  irCodes[KEYq]=113;
  irCodes[KEYr]=114;
  irCodes[KEYs]=115;
  irCodes[KEYt]=116;
  irCodes[KEYu]=117;
  irCodes[KEYv]=118;
  irCodes[KEYw]=119;
  irCodes[KEYx]=120;
  irCodes[KEYy]=121;
  irCodes[KEYz]=122;
  irCodes[KEYALTTILDE]=126;
  irCodes[KEYALTBACKSPACE]=127;
  } 

// these statements show my software development environment
// Microsoft Windows 10 
// Arduino IDE 2.3.6
// Board: ESP32C6 Dev Module (specifically Espressif Systems ESP32-C6-DEVKITC-1-N8 Microcontroller)
// Flash Size: 8MB(64Mb)
// Partition Scheme: 8M with spiffs (3MB APP/1.5MB SPIFFS)
// Using library IRremote at version 4.5.0 in folder: C:\Users\larry\OneDrive\Documents\Arduino\libraries\IRremote
