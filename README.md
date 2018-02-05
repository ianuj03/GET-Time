# GET-Time

GET time from a website using GET command.

Microcontrollers greatly deals with time and interrupts. But the time here does not refer to the actual time, it is the time from which the micocontroller was powered up. So, if we want to get the real time we have to provide power continously which is not possible as of now (specially during prototyping and testing mode).

Therefore, in order to get the real time we'll fetch it from the website: www.timeanddate.com 

Through thingspeak.com I have made the API for timeanddate.com of the field time. So, when running this http://api.thingspeak.com/apps/thinghttp/send_request?api_key=0R02B0TKBD224PEE we get current time, which is then read by ESP8266. 


There are many other information apart from time which is not useful as of now. So, the Arduino program here reads and elminates all those unnecessar information and just prints the time on the Serial Monitor.

