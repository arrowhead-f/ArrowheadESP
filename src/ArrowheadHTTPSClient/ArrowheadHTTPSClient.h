//
// Created by Szvetlin Tanyi on 2020. 04. 09..
//

#ifndef ARROWHEADESP_ARROWHEADHTTPSCLIENT_H
#define ARROWHEADESP_ARROWHEADHTTPSCLIENT_H

// Library includes
#include <WiFiClientSecure.h>
#include "../Util/Util.h"

class ArrowheadHTTPSClient {
private:
    /**
     * SSL capable HTTP client
     */
    WiFiClientSecure _wiFiClientSecure;
public:
    /**
     * Default constructor of the class
     */
    ArrowheadHTTPSClient();

    /**
    * Returns the instance of the HTTP client
    *
    * @return
    */
    WiFiClientSecure& getWiFiClientSecure();
};


#endif //ARROWHEADESP_ARROWHEADHTTPSCLIENT_H
