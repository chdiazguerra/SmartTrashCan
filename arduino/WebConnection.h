#ifndef WEBCONNECTION_H
#define WEBCONNECTION_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Client.h>

class WebConnection{
    private:
        const String _serverName;
        Client* _client;
        const String _ID;
        const bool _debug;
        const float _delaySend;
        float _lastTime;

    public:
        /*
        * Constructor
        */
        WebConnection(String serverName, Client &client, String ID, bool debug_, float delaySend);

        /*
        * Destructor
        */
        ~WebConnection();

        /*
        * Enviar dato
        */
        void sendData(int state);

};

#endif