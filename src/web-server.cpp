/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/Ponlawat/source/particle/web-server/src/web-server.ino"
/*
 * Project web-server
 * Description: Simple Web Server
 * Author: Ponlawat W.
 * Date: 28 October 2563
 * Prototype: https://community.particle.io/t/tiny-webserver-code/3297/2
 */
#include "RdWebServer.h"
#include "RestAPIEndpoints.h"

void restAPI_QueryStatus(RestAPIEndpointMsg& apiMsg, String& responseStr);
void setup();
void loop();
#line 11 "c:/Users/Ponlawat/source/particle/web-server/src/web-server.ino"
RestAPIEndpoints restAPIEndpoints;
RdWebServer* pWebServer = NULL;

void restAPI_QueryStatus(RestAPIEndpointMsg& apiMsg, String& responseStr) {
  responseStr = "{\"msg\": \"Hello World!\"}";
}

// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.

  char ipAddress[24];
  Particle.variable("ipAddress", ipAddress, STRING);
  IPAddress ip = WiFi.localIP();
  sprintf(ipAddress, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
  // ↑ save ip address from `ip` in string format to global variable `ipAddress`

  Particle.publish(ipAddress, PRIVATE);

  restAPIEndpoints.addEndpoint("Q", RestAPIEndpointDef::ENDPOINT_CALLBACK, restAPI_QueryStatus, "", "");

  pWebServer = new RdWebServer();
  pWebServer->addRestAPIEndpoints(&restAPIEndpoints);
  pWebServer->start(80);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
  if (pWebServer) {
    pWebServer->service();
  }
}
