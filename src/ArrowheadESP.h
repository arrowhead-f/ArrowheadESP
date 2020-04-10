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
#include <NTPClient.h>
#include <WiFiUdp.h>

// Header Includes
#include "ArrowheadESPFS/ArrowheadESPFS.h"
#include "ArrowheadHTTPSClient/ArrowheadHTTPSClient.h"

class ArrowheadESP {
private:
    /**
     * ArrowheadESPFS instance
     */
    ArrowheadESPFS _arrowheadEspFs;

    /**
     * ArrowheadHTTPSClient instance
     */
    ArrowheadHTTPSClient _httpsClient;

    /**
     * UDP capability
     */
    WiFiUDP _ntpUDP;
    // NTPClient timeClient(ntpUDP); not possible :(

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
     *
     * @return
     */
    ArrowheadESPFS& getArrowheadESPFS();

    /**
     * Returns the instance of the ArrowheadHTTPSClient
     *
     * @return
     */
    ArrowheadHTTPSClient& getArrowheadHTTPSClient();

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
