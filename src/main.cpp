/*
 * JCBLedMatrixMAX7219 - main.cpp
 * 
 * Copyright 2020 - Juan C. Bryksa (jcbryksa@gmail.com)
 */

#include "main.h"
#include "website.h"


////////////////////
// Global variables
////////////////////

// Parola
// Hardware SPI connection
//MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
// Arbitrary output pins
MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
textEffect_t effectIn, effectOut;
textPosition_t alignment;
uint16_t speedTime, pauseTime;
char msgBuffer[512];
uint16_t msgIndex = 0;
//


// WiFi
const char *WiFissid     = WIFI_SSID;
const char *WiFipassword = WIFI_PASSWORD;
ESP8266WebServer server(WIFI_WEBSERVER_PORT);
//


void handleRoot() {

  long msgLen = 0;
  while ( EEPROM.read(msgLen) )
    msgLen++;

  server.setContentLength( (sizeof(web_part1)-1) + msgLen + (sizeof(web_part2)-1));
  server.send(200, "text/html", "" );
  server.sendContent_P(web_part1);
  for(long i = 0 ; i < msgLen ; i++)
    server.sendContent(String((char) EEPROM.read(i)));
  server.sendContent_P(web_part2);
  server.client().stop();

}


void handleSave() {

  char c;
  long i;
  
  for ( i = 0 ; (c = server.arg(0)[i]) ; i++ )
    EEPROM.write(i, c);

  EEPROM.write(i, '\0');

  EEPROM.commit();

  msgIndex = 0;

  P.displayReset();

  server.send(200, "text/html", "OK");

}


void fetchMessage() {

  char c, frameParams[6][8];
  uint8_t loadingParams = 1;
  uint8_t paramIdx = 0, textIdx = 0;

  // Inicializa en 0x00 el array de parametros
  memset(frameParams, 0x00, sizeof(frameParams));

  // Bucle principal para lectura del frame
  while ( (c = EEPROM.read(msgIndex)) ) {

    // Evalua si hay separadores de parametros o inicio de texto
    switch (c) {
      case MSG_PARAMS_DELIMITER: {
        msgIndex++;
        paramIdx++;
        textIdx= 0;
        continue;
      }
      case MSG_TEXT_BEGIN: {
        msgIndex++;
        loadingParams = 0;
        textIdx = 0;
        continue;
      }

    }

    // Carga los parametros del frame
    if ( loadingParams )
      frameParams[paramIdx][textIdx] = c;
    else // carga el texto del frame
      msgBuffer[textIdx] = c;

    // Si termina el texto del frame sale del bucle
    if ( c == MSG_TEXT_END ) {
      msgIndex++;
      msgBuffer[textIdx] = '\0';
      break;
    }

    textIdx++;
    msgIndex++;
  
  }

  // Establece los valores de parametros obtenidos
  effectIn  = effects[atoi(frameParams[0])];
  effectOut = effects[atoi(frameParams[1])];
  alignment = alignments[atoi(frameParams[2])];
  speedTime = atoi(frameParams[3]);
  pauseTime = atoi(frameParams[4]);

  // Evalua si termina el mensaje completo y
  // resetea indice para comenzar nuevamente
  if ( EEPROM.read(msgIndex) == '\0' )
    msgIndex = 0;

}


void setup(void)
{
  #ifdef DEBUG
  Serial.begin(9600);
  Serial.println();
  #endif

  WiFi.mode(WIFI_AP); // WiFi en modo Access Point
  boolean result = WiFi.softAP(WiFissid, WiFipassword);
  server.on(ROOT_ENDPOINT, handleRoot);
  server.on(SAVE_ENDPOINT, HTTP_POST, handleSave);
  server.begin();

  #ifdef DEBUG
  if(result == true)
  {
    Serial.println("Ready");
  }
  else
  {
    Serial.println("Failed!");
  }
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  Serial.println("HTTP server started");
  #endif

  // EEPROM
  EEPROM.begin(2048);
  delay(10);
   
  #ifdef WRITE_EEPROM
  // Bloque auxiliar para realizar una escritura inicial de EEPROM
  const char msgEepromStore[] = {"23`24`1`30`2000^Cartel~23`24`1`40`2000^Electronico~23`24`1`40`2000^MAX7219~5`5`1`30`1^Mensaje con desplazamiento hacia la izquierda~"};
  for ( int i = 0; i <= strlen(msgEepromStore) ; i++ )
    EEPROM.write(i, msgEepromStore[i]);
  EEPROM.commit();
  #endif

  fetchMessage();

  // Parola
  P.begin();
  P.setInvert(false);
  // Se utiliza "flip" porque la conexion realizada difiere de la establecida por defecto
  P.setZoneEffect(0, true, PA_FLIP_LR);
  P.setSpriteData(rocket, W_ROCKET, F_ROCKET, rocket, W_ROCKET, F_ROCKET);
  P.displayText(msgBuffer, alignment, speedTime, pauseTime, effectIn, effectOut);
}


void loop(void)
{
  // Verifica y atiende request realizados al servidor web
  server.handleClient();

  // Ejecuta y verifica finalizacion de una animacion
  if ( P.displayAnimate() ) {

    fetchMessage();

    P.setTextEffect(effectIn, effectOut);
    P.setTextAlignment(alignment);
    P.setSpeed(speedTime);
    P.setPause(pauseTime);

    P.displayReset();
  }
  //

}
