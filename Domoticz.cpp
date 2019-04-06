#include "Domoticz.h"

/*#include <ArduinoJson.h>

#include <HTTPClient.h>

#include <WiFiClient.h>
*/

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

int Domoticz::getPressure(){
	
	return _pressure;
	
}
	// getData() , return HTTP_CODE
	
int Domoticz::getData(String deviceIDX){

          _deviceIDX = deviceIDX;

          DynamicJsonDocument _doc(2048);
  
          HTTPClient http;

          http.begin(client, _server + _deviceIDX);
          http.setAuthorization(_username, _password);
    
          // start connection and send HTTP header
          int httpCode = http.GET();
      
          // httpCode will be negative on error
          if (httpCode > 0) {
            
			// HTTP header has been send and Server response header has been handled
            // file found at server
            
			if (httpCode == HTTP_CODE_OK) {
              String payload = http.getString();
              deserializeJson(_doc, payload);
              parseData(_doc);
            }
          } 
      
          http.end();
		  
		return httpCode;
  }
  
  void Domoticz::parseData(DynamicJsonDocument doc){
	  
		_temperature = doc["result"][0]["Temp"];
		_humidity = doc["result"][0]["Humidity"];
		_deviceName = doc["result"][0]["Name"].as<char *>();
		_type = doc["result"][0]["Type"].as<char *>();
		
		if (_type == "Temp + Humidity + Baro"){
			
			_forecastIdx = doc["result"][0]["Forecast"];
			_forecast = doc["result"][0]["ForecastStr"].as<char *>();
			_pressure = doc["result"][0]["Barometer"];
			
		}
		else {
			
			_forecastIdx = 0;
			_forecast = "N/A";
			_pressure = 0;
						
		}
		
  }
