/*
 * JCBLedMatrixMAX7219 - main.h
 * 
 * Copyright 2020 - Juan C. Bryksa (jcbryksa@gmail.com)
 */
#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include <EEPROM.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "config.h"


// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW
#define MAX_DEVICES  5

#define CLK_PIN   14
#define DATA_PIN  13
#define CS_PIN    15

#define MSG_PARAMS_DELIMITER '`'
#define MSG_TEXT_BEGIN       '^'
#define MSG_TEXT_END         '~'

#define BEGIN_HEADER    0x01
#define BEGIN_TEXT      0x02
#define END_TEXT        0x03


const textEffect_t effects[] =
{
  PA_NO_EFFECT,         //00/< Used as a place filler, executes no operation
  PA_PRINT,             //01/< Text just appears (printed)
  PA_SCROLL_UP,         //02/< Text scrolls up through the display
  PA_SCROLL_DOWN,       //03/< Text scrolls down through the display
  PA_SCROLL_LEFT,       //04/< Text scrolls right to left on the display
  PA_SCROLL_RIGHT,      //05/< Text scrolls left to right on the display
  PA_SPRITE,            //06/< Text enters and exits using user defined sprite
  PA_SLICE,             //07/< Text enters and exits a slice (column) at a time from the right
  PA_MESH,              //08/< Text enters and exits in columns moving in alternate direction (U/D)
  PA_FADE,              //09/< Text enters and exits by fading from/to 0 and intensity setting
  PA_DISSOLVE,          //10/< Text dissolves from one display to another
  PA_BLINDS,            //11/< Text is replaced behind vertical blinds
  PA_RANDOM,            //12/< Text enters and exits as random dots
  PA_WIPE,              //13/< Text appears/disappears one column at a time, looks like it is wiped on and off
  PA_WIPE_CURSOR,       //14/< WIPE with a light bar ahead of the change
  PA_SCAN_HORIZ,        //15/< Scan the LED column one at a time then appears/disappear at end
  PA_SCAN_HORIZX,       //16/< Scan a blank column through the text one column at a time then appears/disappear at end
  PA_SCAN_VERT,         //17/< Scan the LED row one at a time then appears/disappear at end
  PA_SCAN_VERTX,        //18/< Scan a blank row through the text one row at a time then appears/disappear at end
  PA_OPENING,           //19/< Appear and disappear from the center of the display, towards the ends
  PA_OPENING_CURSOR,    //20/< OPENING with light bars ahead of the change
  PA_CLOSING,           //21/< Appear and disappear from the ends of the display, towards the middle
  PA_CLOSING_CURSOR,    //22/< CLOSING with light bars ahead of the change
  PA_SCROLL_UP_LEFT,    //23/< Text moves in/out in a diagonal path up and left (North East)
  PA_SCROLL_UP_RIGHT,   //24/< Text moves in/out in a diagonal path up and right (North West)
  PA_SCROLL_DOWN_LEFT,  //25/< Text moves in/out in a diagonal path down and left (South East)
  PA_SCROLL_DOWN_RIGHT, //26/< Text moves in/out in a diagonal path down and right (North West)
  PA_GROW_UP,           //27< Text grows from the bottom up and shrinks from the top down
  PA_GROW_DOWN,         //28/< Text grows from the top down and and shrinks from the bottom up
};

const textPosition_t alignments[] =
{
  PA_LEFT,    ///< The leftmost column for the first character will be on the left side of the display
  PA_CENTER,  ///< The text will be placed with equal number of blank display columns either side
  PA_RIGHT    ///< The rightmost column of the last character will be on the right side of the display
};

// Sprite definition
const uint8_t F_ROCKET = 2;
const uint8_t W_ROCKET = 11;
const uint8_t PROGMEM rocket[F_ROCKET * W_ROCKET] = 
{
    0x18, 0x24, 0x42, 0x81, 0x99, 0x18, 0x99, 0x18, 0xA5, 0x5A, 0x81,
    0x18, 0x24, 0x42, 0x81, 0x18, 0x99, 0x18, 0x99, 0x24, 0x42, 0x99
};

#endif
