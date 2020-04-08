//
// Created by Szvetlin Tanyi on 2020. 04. 07..
//

#ifndef ARROWHEADESP_DATASTRUCTURES_H
#define ARROWHEADESP_DATASTRUCTURES_H

enum connStatus { NO_CONNECTION, WIFI };

struct netInfo {
    const char* ssid;
    const char* pass;

    netInfo() {}

    netInfo(const char* _ssid,
            const char* _pass) :
            ssid(_ssid),
            pass(_pass) {}
};

struct sslInfo {
    int insecure; // used to disable CA verification
    const char* filenameCa;
    const char* filenamePk;
    const char* filenameCl;

    sslInfo() {}

    sslInfo(int _insecure,
            const char* _filenameCa,
            const char* _filenamePk,
            const char* _filenameCl) :
            insecure(_insecure),
            filenameCa(_filenameCa),
            filenamePk(_filenamePk),
            filenameCl(_filenameCl) {}
};


#endif //ARROWHEADESP_DATASTRUCTURES_H
