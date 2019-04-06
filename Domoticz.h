#ifndef Domoticz_h
#define Domoticz_h

#include <Arduino.h>

#include <ArduinoJson.h>

#include <ESPHTTPClient.h>

#include <WiFiClient.h>

class Domoticz
{
  public:
		
		Domoticz(WiFiClient client, char* server, char* username, char* password);
	        
		int getData(String deviceIDX);
	  
		int getTemperature();
		
		int getHumidity();
		
		String getDeviceName();
		
		String getForecast();
		
		String getDeviceType();
		
		int getForecastIdx();
		
		int getPressure();
      
	  	  
  private:
      
		char* __username;

		char* _password;

		String _deviceIDX;

		char* _server;
		
		int _temperature;

		int _humidity;
		
		String _type;
		
		String _forecast;
			
		int _forecastIdx;
		
		int _pressure;
		
		String _deviceName;

		WiFiClient client;
      
		void parseData(DynamicJsonDocument doc);

		const char* apiCmd;
	  
};

// the #include statment and code go here...

#endif
