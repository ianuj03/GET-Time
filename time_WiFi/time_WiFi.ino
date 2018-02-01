/*
 * The program here, reads the data from a website and prints it on the Serial monitor.
 * The data is Current Time.
 * The Internet connectivity for the Arduino board is through the ESP8266 WiFi module.
 * Author: Anuj Jain
 * @ianuj03
 */
#include<SoftwareSerial.h>
SoftwareSerial wifi(7,8);
#define ssid "ANUJ"
#define pswd "password"
#define ip "52.1.229.129"
String Time="";
String time1;
String GET="GET /apps/thinghttp/send_request?api_key=0R02B0TKBD224PEE\r\n";
void getTime();
bool wifi_connect(){
  delay(2000);
  //wifi.println("AT+CIPSTATUS\r\n");
  //if(!wifi.find("2")||!wifi.find("3")){
 wifi.println("AT+RST\r\n");
 delay(2000);
  String cmd="AT+CWJAP=\"";
  cmd+=ssid;
  cmd+="\",\"";
  cmd+=pswd;
  cmd+="\"\r\n";
  wifi.println(cmd);
  delay(2000);
  if(wifi.find("OK")){
    Serial.println("Connect Wifi : RECEIVED: OK");
    return true;
  }
  else{
    Serial.println("Connect Wifi RECEIVED: Error");
    return false;
  }
  //}
}
void setup(){
  wifi.begin(9600);
  Serial.begin(9600);
  delay(5000);
  //bool ch=wifi_connect();
  //if(ch==false)
    //  wifi_connect();
}
void loop(){
  //bool ch=wifi_connect();
  //if(ch==false)
    //wifi_connect();
    getTime();
  Serial.println(Time);
  delay(5000);
}
void getTime(){
  char inv='"';
  String cmd="AT+CIPSTART=";
  cmd+=inv;
  cmd+="TCP";
  cmd+=inv;
  cmd+=",";
  cmd+=inv;
  cmd+="api.thingspeak.com";
  cmd+=inv;
  cmd+=",80\r\n";
  //String cmd="AT+CIPSTART=\"TCP\",\"52.1.229.129\",80\r\n";
  wifi.println(cmd);
  delay(500);
  if(wifi.find("Error")){
    Serial.println("CIPSTART:Recieved Error");
    return;
  }
  cmd="AT+CIPSEND=";
  cmd+=GET.length();
  cmd+="\r\n";
  //wifi.print("AT+CIPSEND=63");
  wifi.println(cmd);
  delay(1000);
  //GET+="Host:api.thingspeak.com";
  //GET+="\r\n\r\n\r\n\r\n\r\n";
  wifi.println(GET);
  delay(100);
  
  //Serial.println(wifi.println(GET));
  //if(wifi.find("Error"))
    //Serial.println("CIPSTART:Recieved Error");
  if(wifi.find("+IPD"))
      Serial.println("got time");
  Serial.println(Time);
  int i=0;
  while(wifi.available()){
    char c=wifi.read();
    time1+=c;
  }
  Serial.print(time1);
  Serial.println(".");
  Time=time1;
  if(!wifi.find("+IPD"))
    Serial.println("\nError Found");
  else{
  while(Time.charAt(i)!=':')
    i++;
  i++;
  Time=Time.substring(i);
  int j=0;
  while(Time.charAt(j)!='C')
    j++;
  Time=Time.substring(0,j);
  //return Time;
  }
}