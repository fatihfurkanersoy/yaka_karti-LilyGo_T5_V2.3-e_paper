// include library, include base class, make path known
#include <GxEPD.h>
#include "SD.h"
#include "SPI.h"
#include <ArduinoOTA.h>
#include <WiFi.h>
#include "sys/time.h"
#include "BLEDevice.h"
#include "BLEUtils.h"
#include "BLEBeacon.h"
#include "esp_sleep.h"
//! There are three versions of the 2.13 screen,
//  if you are not sure which version, please test each one,
//  if it is successful then it belongs to the model of the file name

//#include <GxGDE0213B1/GxGDE0213B1.h>      // 2.13" b/w
//#include <GxGDEH0213B72/GxGDEH0213B72.h>  // 2.13" b/w new panel
#include <GxGDEH0213B73/GxGDEH0213B73.h>  // 2.13" b/w newer panel

int bmpWidth = 214, bmpHeight = 86;
//width:150,height:39

const unsigned char Microzerr[] ={0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0x7e, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0x7e, 0xf9, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0x3e, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xbe, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0x9f, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xdf, 0xc0, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xe7, 0xf0, 0x0f, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xe3, 0xe0, 0x3f, 0xc7, 0xff, 0xfe, 0x0f, 0xf8, 0x01, 0xff, 0xff, 0x83, 0xff, 0x8f, 0xf8, 0x00, 0xf9, 0xfe, 0x7c, 0xfc, 0x3f, 0xff, 0x0f, 0xff, 0xff, 0x81, 0xfc, 
0xf1, 0xc0, 0x7f, 0xe3, 0xff, 0xf8, 0x03, 0xf8, 0x01, 0xff, 0xfc, 0x00, 0xff, 0x8f, 0xf8, 0x00, 0xf9, 0xfc, 0x7c, 0xfc, 0x1f, 0xfe, 0x0f, 0xff, 0xfe, 0x00, 0xfc, 
0xf9, 0x80, 0xff, 0xf3, 0xff, 0xf1, 0xe1, 0xf9, 0xff, 0xff, 0xf8, 0x7c, 0x7f, 0x8f, 0xf9, 0xff, 0xf9, 0xf8, 0xfc, 0xfc, 0x1f, 0xfe, 0x0f, 0xff, 0xfc, 0x3c, 0x7c, 
0xff, 0x80, 0xff, 0xf1, 0xff, 0xf7, 0xf1, 0xf9, 0xff, 0xff, 0xf0, 0xff, 0x7f, 0x8f, 0xf9, 0xff, 0xf9, 0xf1, 0xfc, 0xfc, 0x8f, 0xfc, 0x0f, 0xff, 0xfc, 0x7e, 0x3c, 
0xff, 0x01, 0xff, 0xf9, 0xff, 0xff, 0xf0, 0xf9, 0xff, 0xff, 0xf1, 0xff, 0xff, 0x8f, 0xf9, 0xff, 0xf9, 0xe3, 0xfc, 0xfc, 0x8f, 0xfc, 0x8f, 0xff, 0xfc, 0xfe, 0x3c, 
0xff, 0x03, 0xff, 0xfc, 0xff, 0xff, 0xf8, 0xf9, 0xff, 0xff, 0xe3, 0xff, 0xff, 0x8f, 0xf9, 0xff, 0xf9, 0xe3, 0xfc, 0xfc, 0xcf, 0xf8, 0x8f, 0xff, 0xf8, 0xff, 0x3c, 
0xfe, 0x03, 0xff, 0xfc, 0x0f, 0xff, 0xf8, 0xf9, 0xff, 0xff, 0xe3, 0xff, 0xff, 0x8f, 0xf9, 0xff, 0xf9, 0xc7, 0xfc, 0xfc, 0xc7, 0xf9, 0x8f, 0xff, 0xf8, 0xff, 0x1c, 
0xfe, 0x03, 0xff, 0xfc, 0x03, 0xff, 0xf1, 0xf9, 0xff, 0xff, 0xe3, 0xff, 0xff, 0x8f, 0xf9, 0xff, 0xf9, 0x8f, 0xfc, 0xfc, 0xe7, 0xf1, 0x8f, 0xff, 0xf8, 0xff, 0x1c, 
0x06, 0x03, 0xff, 0xfc, 0x01, 0xff, 0xf1, 0xf8, 0x07, 0xff, 0xe3, 0xff, 0xff, 0x8f, 0xf9, 0xff, 0xf9, 0x1f, 0xfc, 0xfc, 0xe3, 0xf3, 0x8f, 0xff, 0xfc, 0x7f, 0x1c, 
0x06, 0x03, 0xff, 0xfc, 0xf1, 0xff, 0xe3, 0xf8, 0x01, 0xff, 0xe3, 0xff, 0xff, 0x8f, 0xf8, 0x01, 0xf8, 0x1f, 0xfc, 0xfc, 0xe3, 0xf3, 0x8f, 0xff, 0xfc, 0x3e, 0x1c, 
0xfe, 0x03, 0xff, 0xff, 0xf8, 0xff, 0xe3, 0xff, 0xf0, 0xff, 0xe3, 0xff, 0xff, 0x8f, 0xf8, 0x01, 0xf9, 0x1f, 0xfc, 0xfc, 0xf3, 0xe3, 0x8f, 0xff, 0xfe, 0x00, 0x1c, 
0xfe, 0x3f, 0xff, 0xff, 0xfe, 0x3f, 0xc7, 0xff, 0xf8, 0xff, 0xe3, 0xff, 0xff, 0x8f, 0xf9, 0xff, 0xf9, 0x8f, 0xfc, 0xfc, 0xf1, 0xe7, 0x8f, 0xff, 0xff, 0x03, 0x1c, 
0xfe, 0x7f, 0xff, 0xff, 0xfe, 0x3f, 0x8f, 0xff, 0xf8, 0xff, 0xe3, 0xff, 0xff, 0x8f, 0xf9, 0xff, 0xf9, 0xc7, 0xfc, 0xfc, 0xf1, 0xc7, 0x8f, 0xff, 0xff, 0xff, 0x3c, 
0xfc, 0x7f, 0xff, 0xff, 0xff, 0x3f, 0x1f, 0xff, 0xfc, 0xff, 0xe3, 0xff, 0xff, 0x8f, 0xf9, 0xff, 0xf9, 0xc3, 0xfc, 0xfc, 0xf8, 0xcf, 0x8f, 0xff, 0xff, 0xff, 0x3c, 
0xf0, 0x7f, 0xff, 0xff, 0xff, 0x3e, 0x3f, 0xff, 0xfc, 0xff, 0xe3, 0xff, 0xff, 0x8f, 0xf9, 0xff, 0xf9, 0xe3, 0xfc, 0xfc, 0xf8, 0x8f, 0x8f, 0xff, 0xff, 0xfe, 0x3c, 
0xe0, 0xff, 0xff, 0xff, 0xff, 0x3c, 0x7f, 0xff, 0xf8, 0xff, 0xf1, 0xff, 0xff, 0x8f, 0xf9, 0xff, 0xf9, 0xf1, 0xfc, 0xfc, 0xfc, 0x8f, 0x8f, 0xff, 0xff, 0xfe, 0x3c, 
0xc0, 0xff, 0xff, 0xff, 0xff, 0x38, 0xff, 0xff, 0xf8, 0xff, 0xf0, 0xff, 0x7f, 0x8f, 0xf9, 0xff, 0xf9, 0xf8, 0xfc, 0xfc, 0xfc, 0x1f, 0x8f, 0xff, 0xff, 0xfc, 0x7c, 
0x8e, 0xff, 0xff, 0xff, 0xff, 0x31, 0xff, 0xf3, 0xe1, 0xff, 0xf8, 0x7c, 0x7f, 0x8f, 0xf9, 0xff, 0xf9, 0xf8, 0x7c, 0xfc, 0xfc, 0x1f, 0x8f, 0xff, 0xfc, 0xf0, 0xfc, 
0x9f, 0xff, 0xff, 0xff, 0xff, 0x30, 0x00, 0xf0, 0x03, 0xff, 0xfc, 0x00, 0xff, 0x8f, 0xf8, 0x00, 0xf9, 0xfc, 0x7c, 0xfc, 0xfe, 0x3f, 0x8f, 0xff, 0xfc, 0x01, 0xfc, 
0x9f, 0xff, 0xff, 0xff, 0xff, 0x30, 0x00, 0xf8, 0x0f, 0xff, 0xff, 0x03, 0xff, 0x8f, 0xf8, 0x00, 0xf9, 0xfe, 0x3c, 0xfc, 0xfe, 0x3f, 0x8f, 0xff, 0xfe, 0x07, 0xfc, 
0x9f, 0xff, 0xff, 0xff, 0xfe, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0x1f, 0xff, 0xff, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0x1f, 0xff, 0xff, 0xff, 0xfc, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0x9f, 0xff, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0x80, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xe0, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xff, 0xe0, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xff, 0xf8, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x7f, 0xff, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x1f, 0xff, 0xe0, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x7f, 0xfe, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xc0, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x7f, 0xfc, 0x0f, 0x81, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x1f, 0xff, 0x81, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x7f, 0xfc, 0x3f, 0xc1, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x1f, 0xff, 0x07, 0xf0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x18, 0x7f, 0xf8, 0x7f, 0xe1, 0xff, 0xff, 0xff, 0xff, 0xff, 0x06, 0x1f, 0xfe, 0x0f, 0xf8, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x78, 0x7f, 0xf8, 0x7f, 0xe1, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1e, 0x1f, 0xfe, 0x1f, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xf8, 0x7f, 0xe1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xfe, 0x1f, 0xfc, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xf8, 0x7f, 0xe1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xfc, 0x3f, 0xfc, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xf8, 0x3f, 0xe1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xfc, 0x3f, 0xfc, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xfc, 0x1f, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xfc, 0x3f, 0xfc, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xfe, 0x0f, 0x87, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xfc, 0x3f, 0xfc, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xff, 0x02, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xfc, 0x3f, 0xfe, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xff, 0x80, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xfc, 0x3f, 0xfe, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xff, 0xc0, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xfc, 0x3f, 0xfe, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xff, 0x80, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xfc, 0x3f, 0xfe, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xff, 0x06, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xfc, 0x3f, 0xfe, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xfc, 0x1f, 0x83, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xfc, 0x3f, 0xfe, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xfc, 0x3f, 0xc1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xfc, 0x3f, 0xfe, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xf8, 0x7f, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xfc, 0x3f, 0xfc, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xf0, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xfc, 0x3f, 0xfc, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xf0, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xfc, 0x3f, 0xfc, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xf0, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xfe, 0x1f, 0xfc, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xf0, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xfe, 0x1f, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xf0, 0x7f, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xfe, 0x0f, 0xf8, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xf8, 0x7f, 0xe0, 0xff, 0xff, 0x87, 0xff, 0xff, 0xfe, 0x1f, 0xff, 0x07, 0xf0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x3f, 0xf8, 0x1f, 0x81, 0xff, 0xff, 0x83, 0xff, 0xff, 0xfe, 0x0f, 0xff, 0x01, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0xfc, 0x00, 0x03, 0xff, 0xff, 0x83, 0xff, 0xff, 0x00, 0x00, 0x3f, 0x80, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0xfe, 0x00, 0x07, 0xff, 0xff, 0x83, 0xff, 0xff, 0x00, 0x00, 0x3f, 0xc0, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0xff, 0xc0, 0x3f, 0xff, 0xff, 0x87, 0xff, 0xff, 0x00, 0x00, 0x3f, 0xf0, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};



int batWidth = 53, batHeight = 30;
const unsigned char batarya5[] ={0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 
0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 
0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 
0xf9, 0xff, 0xff, 0xff, 0xff, 0xff, 0x98, 
0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc8, 
0xf3, 0x01, 0x01, 0x81, 0x80, 0xc0, 0xc8, 
0xf3, 0x01, 0x01, 0x80, 0x80, 0x80, 0xc8, 
0xf3, 0x01, 0x01, 0x80, 0x80, 0xc0, 0xc8, 
0xf3, 0x01, 0x01, 0x80, 0x80, 0xc0, 0xc8, 
0xf3, 0x01, 0x01, 0x80, 0x80, 0xc0, 0xc8, 
0x83, 0x01, 0x01, 0x80, 0x80, 0xc0, 0xc8, 
0x83, 0x01, 0x01, 0x80, 0x80, 0xc0, 0xc8, 
0x83, 0x01, 0x01, 0x80, 0x80, 0xc0, 0xc8, 
0x83, 0x01, 0x01, 0x81, 0x80, 0xc0, 0xc8, 
0x83, 0x01, 0x01, 0x80, 0x80, 0xc0, 0xc8, 
0x83, 0x01, 0x01, 0x80, 0x80, 0xc0, 0xc8, 
0x83, 0x01, 0x01, 0x80, 0x80, 0xc0, 0xc8, 
0x83, 0x01, 0x01, 0x81, 0x80, 0xc0, 0xc8, 
0x83, 0x01, 0x01, 0x80, 0x80, 0xc0, 0xc8, 
0x83, 0x01, 0x01, 0x80, 0x80, 0xc0, 0xc8, 
0xf3, 0x01, 0x01, 0x80, 0x80, 0xc0, 0xc8, 
0xf3, 0x01, 0x01, 0x80, 0x80, 0xc0, 0xc8, 
0xf3, 0x01, 0x01, 0x80, 0x80, 0xc0, 0xc8, 
0xf3, 0x01, 0x01, 0x81, 0x80, 0xc0, 0xc8, 
0xf3, 0x03, 0x81, 0x81, 0x80, 0xc0, 0xc8, 
0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc8, 
0xf9, 0xff, 0xff, 0xff, 0xff, 0xff, 0x98, 
0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 
0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8};




const unsigned char batarya4[] ={0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 
0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 
0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 
0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc8, 
0xf3, 0xff, 0x83, 0xc1, 0xc1, 0xe0, 0xc8, 
0xf7, 0xff, 0x01, 0x80, 0x80, 0xc0, 0x68, 
0xf7, 0xff, 0x01, 0x80, 0x80, 0xc0, 0x68, 
0xf7, 0xff, 0x01, 0x80, 0x80, 0xc0, 0x68, 
0xf7, 0xff, 0x01, 0x80, 0x80, 0xc0, 0x68, 
0xe7, 0xff, 0x01, 0x80, 0x80, 0xc0, 0x68, 
0x87, 0xff, 0x01, 0x80, 0x80, 0xc0, 0x68, 
0x07, 0xff, 0x01, 0x80, 0x80, 0xc0, 0x68, 
0x07, 0xff, 0x01, 0x80, 0x80, 0xc0, 0x68, 
0x07, 0xff, 0x01, 0x80, 0x80, 0xc0, 0x68, 
0x07, 0xff, 0x01, 0x80, 0x80, 0xc0, 0x68, 
0x07, 0xff, 0x01, 0x80, 0x80, 0xc0, 0x68, 
0x07, 0xff, 0x01, 0x80, 0x80, 0xc0, 0x68, 
0x07, 0xff, 0x01, 0x80, 0x80, 0xc0, 0x68, 
0x07, 0xff, 0x01, 0x80, 0x80, 0xc0, 0x68, 
0x87, 0xff, 0x01, 0x80, 0x80, 0xc0, 0x68, 
0xc7, 0xff, 0x01, 0x80, 0x80, 0xc0, 0x68, 
0xf7, 0xff, 0x01, 0x80, 0x80, 0xc0, 0x68, 
0xf7, 0xff, 0x01, 0x80, 0x80, 0xc0, 0x68, 
0xf7, 0xff, 0x01, 0x80, 0x80, 0xc0, 0x68, 
0xf7, 0xff, 0x01, 0x80, 0x80, 0xc0, 0x68, 
0xf3, 0xff, 0x83, 0x81, 0xc1, 0xc0, 0xc8, 
0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc8, 
0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0x18, 
0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 
0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8};


const unsigned char batarya3[] ={0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 
0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 
0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 
0xf1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc8, 
0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 
0xf3, 0xff, 0xff, 0x80, 0xc0, 0xc0, 0x60, 
0xf7, 0xff, 0xff, 0x80, 0x80, 0xc0, 0x60, 
0xf7, 0xff, 0xff, 0x80, 0x80, 0xc0, 0x60, 
0xf7, 0xff, 0xff, 0x80, 0x80, 0xc0, 0x60, 
0xf7, 0xff, 0xff, 0x80, 0x80, 0xc0, 0x60, 
0x87, 0xff, 0xff, 0x80, 0x80, 0xc0, 0x60, 
0x07, 0xff, 0xff, 0x80, 0x80, 0xc0, 0x60, 
0x07, 0xff, 0xff, 0x80, 0x80, 0xc0, 0x60, 
0x07, 0xff, 0xff, 0x80, 0x80, 0xc0, 0x60, 
0x07, 0xff, 0xff, 0x80, 0x80, 0xc0, 0x60, 
0x07, 0xff, 0xff, 0x80, 0x80, 0xc0, 0x60, 
0x07, 0xff, 0xff, 0x80, 0x80, 0xc0, 0x60, 
0x07, 0xff, 0xff, 0x80, 0x80, 0xc0, 0x60, 
0x07, 0xff, 0xff, 0x80, 0x80, 0xc0, 0x60, 
0x87, 0xff, 0xff, 0x80, 0x80, 0xc0, 0x60, 
0xf7, 0xff, 0xff, 0x80, 0x80, 0xc0, 0x60, 
0xf7, 0xff, 0xff, 0x80, 0x80, 0xc0, 0x60, 
0xf7, 0xff, 0xff, 0x80, 0x80, 0xc0, 0x60, 
0xf7, 0xff, 0xff, 0x80, 0x80, 0xc0, 0x60, 
0xf3, 0xff, 0xff, 0x80, 0xc0, 0xc0, 0x60, 
0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 
0xf1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc8, 
0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 
0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8};

const unsigned char batarya2[] ={0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 
0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 
0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 
0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc8, 
0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc8, 
0xe7, 0xff, 0xff, 0xff, 0x80, 0xc0, 0x60, 
0xe7, 0xff, 0xff, 0xff, 0x80, 0xc0, 0x60, 
0xe7, 0xff, 0xff, 0xff, 0x80, 0xc0, 0x60, 
0xe7, 0xff, 0xff, 0xff, 0x80, 0xc0, 0x60, 
0xe7, 0xff, 0xff, 0xff, 0x80, 0xc0, 0x60, 
0x87, 0xff, 0xff, 0xff, 0x80, 0xc0, 0x60, 
0x07, 0xff, 0xff, 0xff, 0x80, 0xc0, 0x60, 
0x07, 0xff, 0xff, 0xff, 0x80, 0xc0, 0x60, 
0x07, 0xff, 0xff, 0xff, 0x80, 0xc0, 0x60, 
0x07, 0xff, 0xff, 0xff, 0x80, 0xc0, 0x60, 
0x07, 0xff, 0xff, 0xff, 0x80, 0xc0, 0x60, 
0x07, 0xff, 0xff, 0xff, 0x80, 0xc0, 0x60, 
0x07, 0xff, 0xff, 0xff, 0x80, 0xc0, 0x60, 
0x07, 0xff, 0xff, 0xff, 0x80, 0xc0, 0x60, 
0x07, 0xff, 0xff, 0xff, 0x80, 0xc0, 0x60, 
0xe7, 0xff, 0xff, 0xff, 0x80, 0xc0, 0x60, 
0xe7, 0xff, 0xff, 0xff, 0x80, 0xc0, 0x60, 
0xe7, 0xff, 0xff, 0xff, 0x80, 0xc0, 0x60, 
0xe7, 0xff, 0xff, 0xff, 0x80, 0xc0, 0x60, 
0xe7, 0xff, 0xff, 0xff, 0x80, 0xc0, 0x60, 
0xf7, 0xff, 0xff, 0xff, 0xc1, 0xe0, 0xe8, 
0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc8, 
0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x08, 
0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 
0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8};

const unsigned char batarya1[] ={0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 
0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 
0xf1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe4, 
0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe4, 
0xf3, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x34, 
0xf7, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x34, 
0xf7, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x34, 
0xf7, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x34, 
0xf7, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x34, 
0x87, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x34, 
0x07, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x34, 
0x07, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x34, 
0x07, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x34, 
0x07, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x34, 
0x07, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x34, 
0x07, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x34, 
0x07, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x34, 
0x07, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x34, 
0x87, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x34, 
0xf7, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x34, 
0xf7, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x34, 
0xf7, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x34, 
0xf7, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x34, 
0xf3, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x34, 
0xf3, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xe4, 
0xf1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe4, 
0xf8, 0x7f, 0xff, 0xff, 0xff, 0xff, 0x8c, 
0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 
0xff, 0x89, 0x29, 0x24, 0x92, 0x92, 0xfc};


const unsigned char bitik_batarya[] ={0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 
0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 
0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 
0xf1, 0xff, 0xff, 0xff, 0xff, 0xff, 0x88, 
0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc8, 
0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe8, 
0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe8, 
0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe8, 
0xf7, 0xff, 0xff, 0xf7, 0xff, 0xff, 0xe8, 
0xf7, 0xff, 0xff, 0xe3, 0xff, 0xff, 0xe8, 
0x87, 0xff, 0xff, 0xc3, 0xff, 0xff, 0xe8, 
0x07, 0xff, 0xff, 0xc1, 0xff, 0xff, 0xe8, 
0x07, 0xff, 0xff, 0x89, 0xff, 0xff, 0xe8, 
0x07, 0xff, 0xff, 0x88, 0xff, 0xff, 0xe8, 
0x07, 0xff, 0xff, 0x08, 0x7f, 0xff, 0xe8, 
0x07, 0xff, 0xff, 0x08, 0x7f, 0xff, 0xe8, 
0x07, 0xff, 0xfe, 0x08, 0x3f, 0xff, 0xe8, 
0x07, 0xff, 0xfc, 0x08, 0x3f, 0xff, 0xe8, 
0x07, 0xff, 0xfc, 0x00, 0x1f, 0xff, 0xe8, 
0x87, 0xff, 0xf8, 0x08, 0x1f, 0xff, 0xe8, 
0xe7, 0xff, 0xf8, 0x00, 0x0f, 0xff, 0xe8, 
0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe8, 
0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe8, 
0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe8, 
0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe8, 
0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc8, 
0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc8, 
0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0x18, 
0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 
0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8};


int sarjWidth = 11, sarjHeight = 20;
const unsigned char sarj_simsek[] ={0xff, 0xe0, 
0xf3, 0xe0, 
0xf3, 0xe0, 
0xf3, 0xe0, 
0xf1, 0xe0, 
0xf1, 0xe0, 
0xf0, 0xe0, 
0xb8, 0xe0, 
0x00, 0x60, 
0x80, 0x60, 
0xc0, 0x20, 
0xc0, 0x20, 
0xc0, 0x20, 
0xe3, 0xe0, 
0xe1, 0xe0, 
0xf3, 0xe0, 
0xf1, 0xe0, 
0xf9, 0xe0, 
0xf9, 0xe0, 
0xff, 0xe0};

int notsarjWidth = 11, notsarjHeight = 20;
const unsigned char sarj_olmuyor_beyaz[] ={0xff, 0xe0, 
0xff, 0xe0, 
0xff, 0xe0, 
0xff, 0xe0, 
0xff, 0xe0, 
0xff, 0xe0, 
0xff, 0xe0, 
0xff, 0xe0, 
0xff, 0xe0, 
0xff, 0xe0, 
0xff, 0xe0, 
0xff, 0xe0, 
0xff, 0xe0, 
0xff, 0xe0, 
0xff, 0xe0, 
0xff, 0xe0, 
0xff, 0xe0, 
0xff, 0xe0, 
0xff, 0xe0, 
0xff, 0xe0};




// FreeFonts from Adafruit_GFX
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>


#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

#define SPI_MOSI 23
#define SPI_MISO -1
#define SPI_CLK 18

#define ELINK_SS 5
#define ELINK_BUSY 4
#define ELINK_RESET 16
#define ELINK_DC 17

#define SDCARD_SS 13
#define SDCARD_CLK 14
#define SDCARD_MOSI 15
#define SDCARD_MISO 2

#define BUTTON_PIN 39

GxIO_Class io(SPI, /*CS=5*/ ELINK_SS, /*DC=*/ ELINK_DC, /*RST=*/ ELINK_RESET);
GxEPD_Class display(io, /*RST=*/ ELINK_RESET, /*BUSY=*/ ELINK_BUSY);

SPIClass sdSPI(VSPI);

const float batPin = 35;
const float SARJ_PIN = 27;
int sarj_durum = 0 ;

bool sdOK = false;
int startX = 0, startY = 0;
// Define WIFI parameters
//------------------------------------------------------
#define WIFI_SSID "Microzerr"
#define WIFI_PASSWORD "micro2017"
long rssi = 0;
//------------------------------------------------------
BLEAdvertising *pAdvertising;
struct timeval now;
#define BEACON_UUID "6503e729-92c3-4f5d-9dbe-bb613992d465" // UUID 1 128-Bit (may use linux tool uuidgen or random numbers via https://www.uuidgenerator.net/)
RTC_DATA_ATTR static time_t last; 
RTC_DATA_ATTR static uint32_t bootcount; // remember number of boots in RTC Memory
//----------------------------------------------------------------
//Zamanlayıcı
const unsigned long bat_kontrol_time = 2000;  // milisaniye cinsinden zaman (2000 = 2 saniye)
const unsigned long beacon_time = 10000; // milisaniye cinsinden zaman (10000 = 10 saniye)
const unsigned long ekran_yenileme_time = 300000; // milisaniye cinsinden zaman (3600000 = 3600 saniye = 1 saat)
unsigned long previous_time_bat_kontrol = 0;
unsigned long previous_time_beacon = 0;
unsigned long previous_time_ekran_yenileme = 0;

void setBeacon() {

  BLEBeacon oBeacon = BLEBeacon();
  oBeacon.setManufacturerId(0x4C00); // fake Apple 0x004C LSB (ENDIAN_CHANGE_U16!)
  oBeacon.setProximityUUID(BLEUUID(BEACON_UUID));
  oBeacon.setMajor((bootcount & 0xFFFF0000) >> 16);
  oBeacon.setMinor(bootcount&0xFFFF);
  BLEAdvertisementData oAdvertisementData = BLEAdvertisementData();
  BLEAdvertisementData oScanResponseData = BLEAdvertisementData(); 
  oAdvertisementData.setFlags(0x04); // BR_EDR_NOT_SUPPORTED 0x04
  std::string strServiceData = "FURKAN"; 
  strServiceData += (char)26;     // Len
  strServiceData += (char)0xFF;   // Type
  strServiceData += oBeacon.getData(); 
  oAdvertisementData.addData(strServiceData);
  
  pAdvertising->setAdvertisementData(oAdvertisementData);
  pAdvertising->setScanResponseData(oScanResponseData);
}
//-------------------------------------------------------------------
//
void sarj_oluyor_mu(){ 
  sarj_durum = digitalRead(SARJ_PIN);
  if(sarj_durum == 1){
  Serial.println("ŞARJ OLUYOR 1");
  display.drawBitmap(sarj_simsek, 182, 95,  sarjWidth, sarjHeight, GxEPD_WHITE);
  }
  else{
  Serial.println("ŞARJ OLMUYOR  0");
  display.drawBitmap(sarj_olmuyor_beyaz, 182, 95,  notsarjWidth, notsarjHeight, GxEPD_WHITE);
  }    
display.updateWindow(0, 0, display.width(), display.height()); 
}

void Sarj_Kontrol(){
  int i;
  float value = 0;
  float numReadings = 1000;
  for (i = 0; i < numReadings; i++){
    // Read light sensor data.
    value = value + analogRead(batPin);
    // 1ms pause adds more stability between reads.
    delay(1);}
   Serial.println("DEĞİŞİM");
   value = value / numReadings;
   Serial.println(value);
  float bat = value / 1023;
  bat = bat * 2 ;
  Serial.println(bat);
  delay(1);        // delay in between reads for stability
  
  //Şarj Aralığı 
  // Gelen Voltaj - Okunan Değer
  /*  3.20          3.5   
      3.4           3.75
      3.6           4.0
      3.8           4.25 
      4.0           4.50
      4.2           4.75
      4.4           5.0
      4.6           5.25
      4.8           5.5
      5.0           5.75
 */
if ( bat >= 4.46){
  display.drawBitmap(batarya5, 195, 90,  batWidth, batHeight, GxEPD_WHITE);
  Serial.println("ŞARJ DOLU");
}
else if ( bat >= 4.24 ){
  display.drawBitmap(batarya4, 195, 90,  batWidth, batHeight, GxEPD_WHITE);
  Serial.println("ŞARJ 4");
}
else if ( bat >= 4.0 ){
  display.drawBitmap(batarya3, 195, 90,  batWidth, batHeight, GxEPD_WHITE);
  Serial.println("ŞARJ 3");
}
else if (bat >= 3.75){
  display.drawBitmap(batarya2, 195, 90,  batWidth, batHeight, GxEPD_WHITE);
  Serial.println("ŞARJ 2");
}
else if ( bat >= 3.6){
  display.drawBitmap(batarya1, 195, 90,  batWidth, batHeight, GxEPD_WHITE);
  Serial.println("ŞARJ 1");
}
else if (bat >= 2.7 ) {
  display.drawBitmap(bitik_batarya, 195, 90,  batWidth, batHeight, GxEPD_WHITE);
  Serial.println("ŞARJ BİTİK");
}
else {
  Serial.println("Problem var");
} 

display.updateWindow(0, 0, display.width(), display.height());
}

void setup()
{
    Serial.begin(115200);
    Serial.println();
    Serial.println("setup");
    pinMode(SARJ_PIN,INPUT);
    
    SPI.begin(SPI_CLK, SPI_MISO, SPI_MOSI, ELINK_SS);
    display.init(); // enable diagnostic output on Serial
    display.setRotation(1);
    display.fillScreen(GxEPD_BLACK);
    display.setTextColor(GxEPD_WHITE);
    display.setFont(&FreeMonoBold12pt7b);
    display.setCursor(0, 0);  
    sdSPI.begin(SDCARD_CLK, SDCARD_MISO, SDCARD_MOSI, SDCARD_SS);
    if (!SD.begin(SDCARD_SS, sdSPI)) {
        sdOK = false;
    } else {
        sdOK = true;
    }
    display.fillScreen(GxEPD_WHITE);
    display.drawBitmap(Microzerr, startX, startY,  bmpWidth, bmpHeight, GxEPD_WHITE);
    Sarj_Kontrol();
    sarj_oluyor_mu();
    display.updateWindow(0, 0, display.width(), display.height()); 
    display.update();
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
      Serial.println("Connection Failed! ");
    } 
    // goto sleep
    //esp_sleep_enable_ext0_wakeup((gpio_num_t)BUTTON_PIN, LOW);
    //esp_deep_sleep_start();
    //----------------------------------
    // Port defaults to 3232
    ArduinoOTA.setPort(5050);
  
    // Hostname defaults to esp3232-[MAC]
    ArduinoOTA.setHostname("zerrgate");
  
    // No authentication by default
    ArduinoOTA.setPassword("micro2017");
    
    // Password can be set with it's md5 value as well
    // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
    // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");
    //----------------------------------
    //----------------------------------
    ArduinoOTA
      .onStart([]() {
        String type;
        if (ArduinoOTA.getCommand() == U_FLASH)
          type = "sketch";
        else // U_SPIFFS
          type = "filesystem";
  
        // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
        Serial.println("Start updating " + type);
      })
      .onEnd([]() {
        Serial.println("\nEnd");
      })
      .onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
      })
      .onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR) Serial.println("End Failed");
      });
    ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void loop()
{
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("ESP Yeniden Başlatılıyor...");
     ESP.restart();
  }
  ArduinoOTA.handle();
  
  unsigned long current_time = millis();
  if(current_time - previous_time_bat_kontrol >= bat_kontrol_time) {
    Serial.println("");
    Serial.println("Şu anda şarj durumu ve şarj olup/olmama durumu alınıyor");
    sarj_oluyor_mu();
    Sarj_Kontrol();
   display.updateWindow(0, 0, display.width(), display.height());
    previous_time_bat_kontrol = current_time;  
  }
  if(current_time - previous_time_ekran_yenileme >= ekran_yenileme_time) {
    Serial.println("");
    Serial.println("Ekran Yenileme");
    Sarj_Kontrol();
    sarj_oluyor_mu();
    display.update();
    previous_time_ekran_yenileme = current_time;  
  }
  if(current_time - previous_time_beacon >= beacon_time){
    Serial.println("");
    Serial.println("reate the BLE Device...");
    // Create the BLE Device
    BLEDevice::init("FURKAN");  
    // Create the BLE Server
    BLEServer *pServer = BLEDevice::createServer(); // <-- no longer required to instantiate BLEServer, less flash and ram usage
    pAdvertising = BLEDevice::getAdvertising();    
    BLEDevice::startAdvertising();
    setBeacon();  
    // Start advertising
    pAdvertising->start();
    Serial.println("Advertizing started...");
    pAdvertising->stop();
    previous_time_beacon = current_time; 
  }
}
