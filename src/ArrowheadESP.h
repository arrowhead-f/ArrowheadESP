//
// Created by Szvetlin Tanyi <szvetlin@aitia.ai> on 2020. 04. 06.
//

#ifndef ARROWHEADESP_ARROWHEADESP_H
#define ARROWHEADESP_ARROWHEADESP_H

#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#endif

#ifdef ESP32
// TODO
#endif

// Library includes
#include <WiFiClientSecure.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// Header Includes
#include "ArrowheadESPFS.h"

class ArrowheadESP {
private:
    /**
     * ArrowheadESPFS instance
     */
    ArrowheadESPFS arrowheadEspFs;

    /**
     * UDP capability
     */
    WiFiUDP ntpUDP;
    // NTPClient timeClient(ntpUDP); not possible :(

    /**
     * SSL capable HTTP client
     */
    WiFiClientSecure _wiFiClientSecure;

    /**
     * Returns the instance of the HTTP client
     *
     * @return
     */
    WiFiClientSecure& getWiFiClientSecure();

    /**
     * Sets up the connection to the WiFi network
     *
     * @return success of the connection attempt
     */
    bool setupWiFi();
    /**
     * Sets up the certificates to the HTTP client
     *
     * @return
     */
    bool setupCertificates();
public:
    /**
     * Default constructor of the library
     */
    ArrowheadESP();

    /**
     * Returns the instance of the ArrowheadESPFS
     * @return
     */
    ArrowheadESPFS& getArrowheadESPFS();

    /**
     * Starts the operation of the library
     *
     * @return
     */
    bool begin();

    /**
     * Keeps all connection alive
     *
     * @return
     */
    int loop();
};


#endif //ARROWHEADESP_ARROWHEADESP_H
