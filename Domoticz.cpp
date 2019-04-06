#include "Domoticz.h"

char* _username;

char* _password;

char* _deviceIDX;

char* _server;

int _temperature;

int _humidity;

String _deviceName;

String _type;
		
String _forecast;
			
int _forecastIdx;

const char* apiCommand = "/json.htm?type=devices&rid=";


Domoticz::Domoticz(WiFiClient client, char* server, char* username, char* password){

      _username = username;
      _password = password;
      _server =  server;
  }
  
  
int Domoticz::getTemperature(){
	
	return _temperature;
}
		
int Domoticz::getHumidity(){
	
	return _humidity;
	
}
	
String Domoticz::getDeviceName(){
	
	return _deviceName;
}

String Domoticz::getForecast(){
	
	return _forecast;
	
}

String Domoticz::getDeviceType(){
	
	return _type;
	
}

int Domoticz::getForecastIdx(){
	
	return _forecastIdx;
	
}

void Domoticz::getData(String deviceIDX){

          _deviceIDX = deviceIDX;

          DynamicJsonDocument _doc(2048);
  
          HTTPClient http;

          http.begin(client, _server + apiCommand + _deviceIDX);
          http.setAuthorization(_username, _password);
    
          Serial.print("[HTTP] GET...\n");
          // start connection and send HTTP header
          int httpCode = http.GET();
      
          // httpCode will be negative on error
          if (httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTP] GET... code: %d\n\n", httpCode);
      
            // file found at server
            if (httpCode == HTTP_CODE_OK) {
              String payload = http.getString();
              deserializeJson(_doc, payload);
              http.end();
              parseData(_doc);
            }
          } else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
          }
      
          http.end();
  
  }
  
  void Domoticz::parseData(DynamicJsonDocument doc){
	  
		_temperature = doc["result"][0]["Temp"];
		_humidity = doc["result"][0]["Humidity"];
		_deviceName = doc["result"][0]["Name"].as<char *>();
		_type = doc["result"][0]["Type"].as<char *>();
		
		if (_type == "Temp + Humidity + Baro"){
			
			_forecastIdx = doc["result"][0]["Forecast"];
			_forecast = doc["result"][0]["ForecastStr"].as<char *>();
			
		}
		
  }
