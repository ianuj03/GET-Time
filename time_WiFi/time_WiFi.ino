/*
 * The program here, reads the data from a website and prints it on the Serial monitor.
 * The data is Current Time.
 * The Internet connectivity for the Arduino board is through the ESP8266 WiFi module.
 * Author: Anuj Jain
 * @ianuj03
 */
#include<SoftwareSerial.h>
SoftwareSerial wifi(7,8);//Tx,Rx
#define ssid "ANUJ"//Change SSID
#define pswd "password"//Change Password
#define ip "184.106.153.149"//Static IP of thingspeak.com 
//Can try with this IP also 52.1.229.129

String Time="";
String GET="GET /apps/thinghttp/send_request?api_key=0R02B0TKBD224PEE\r\n";
void getTime();

//--------------WiFi CONNECTION---------------
bool wifi_connect(){
  delay(1000);
  //wifi.println("AT+CIPSTATUS\r\n");
  //if(!wifi.find("2")||!wifi.find("3")){
   wifi.println("AT+RST\r\n");//RESET the module
   delay(2000);
   String cmd="AT+CWJAP=\"";//To join an access point
   cmd+=ssid;
   cmd+="\",\"";
   cmd+=pswd;
  cmd+="\"\r\n";
  wifi.println(cmd);//AT+CWJAP="<ssid>","<password>"
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
  wifi.begin(115200);//Standard  Baud rate of the module
  Serial.begin(9600);
  delay(3000);
  bool ch=wifi_connect();
  if(ch==false)
     wifi_connect();
}

void loop(){
  //bool ch=wifi_connect();
  //if(ch==false)
    //wifi_connect();
    getTime();
  Serial.println(Time);//Time is decleared as a global variable
  delay(5000);
}
//------------------GET TIME function-----------------
void getTime(){
  char inv='"';
  String time1;
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
  wifi.println(cmd);
  delay(1000);
  //GET+="Host:api.thingspeak.com";
  //GET+="\r\n\r\n\r\n\r\n\r\n";
  wifi.println(GET);
  delay(100);
  
  //Serial.println(wifi.println(GET));
  //if(wifi.find("Error"))
    //Serial.println("CIPSTART:Recieved Error");
  //--------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //----------------------------Before doing this just print the data as it is on the serial monitor to understand the output of ESP8266--------------------------------
  //--------------------------------------------------------------------------------------------------------------------------------------------------------------------
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
