#include "WebConnection.h"

WebConnection::WebConnection(String serverName, Client &client, String ID, bool debug_, float delaySend) : _serverName(serverName), _ID(ID), _debug(debug_), _delaySend(delaySend){
    _lastTime = 0;
    _client = &client;
}

WebConnection::~WebConnection(){
    _client = NULL;
}

void WebConnection::sendData(int state){
    float currentTime = millis();
    if (currentTime - _lastTime < _delaySend){
        return;
    }
    if (_client->connect(_serverName.c_str(), 443)){
        if (_debug){
            Serial.println("Connected to server!");
        }
        // Make a HTTP request:
        _client->print("GET /php/postdata.php?id=");
        _client->print(_ID);
        _client->print("&estado=");
        _client->print(state);
        _client->print(" HTTP/1.1\r\n");
        _client->print("Host: ");
        _client->println(_serverName);
        _client->println("Connection: close");
        _client->println();

        while (_client->connected()) {
            String line = _client->readStringUntil('\n');
            if (line == "\r") {
                if (_debug){
                    Serial.println("headers received");
                }
                break;
            }
        }

        while (_client->available()) {
            char c = _client->read();
            if (_debug){
                Serial.write(c);
            }
        }

        _client->stop();
    } else {
        if (_debug){
            Serial.println("connection failed");
        }
    }
    _lastTime = millis();
}