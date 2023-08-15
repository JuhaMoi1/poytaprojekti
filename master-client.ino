#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

// Has ict labrax login credentials
const char *ssid     = "SSID";
const char *password = "PASSWORD";

/*
 * Base64encode encrypted username and password stored
 * in this variable.
 * Visit https://www.base64encode.org/ to get new info.
 * Encrypting is in format username:password
 */
 const char *loginInfo = "TEFCUkE6PE3ND8=";

WiFiUDP UDP;
IPAddress local_IP(127,0,0,100);
IPAddress gateway(127,0,0,1);
IPAddress subnet(255,255,0,0);
//should broadcast be changed to 127.0.0.255?
IPAddress broadcast_IP(127,0,255,255);

#define UDP_PORT 4210


// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Variables for button pressing to send the message over.
int tableDown = 5;
int tableUp = 4;
bool buttonPressed = false;

// message to send the tables. for now it's just 1 or 0. Numbers come from binary "high" 'n "low".
char *output = "";

/*bool that sets true when webpage requests the table to move. and after move command it goes to false. 
 * So this won't spamm the move commands all the time, just once.
 */
bool table;

//client stuff, not sure if neccessary
unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;

void setup() {
  delay(3000);
  Serial.begin(115200);
  Serial.println("wifi disconnected");
  WiFi.disconnect(true);
  
  // Initialize correct pins to input for buttons
  pinMode(tableDown, INPUT);
  pinMode(tableUp, INPUT);

  table = false;


  if(!WiFi.config(local_IP, gateway, subnet))
  {
    Serial.println(" FAILED TO CONFIGURE WIFI");
  }
   //Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    delay(500);
    Serial.println(WiFi.status());
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();


  server.begin();

 // UDP.begin(UDP_PORT);
  Serial.print("Listening on UDP port: ");
  Serial.println(UDP_PORT);
}

void loop()
{
  if(table) //might need own table for everyone. who knows how the code will evolve.
  { 
    Serial.println();
    Serial.println(output);
    
    UDP.beginPacket(broadcast_IP, UDP_PORT);
    UDP.write(output, strlen(output)+1);
    UDP.endPacket();
    
    Serial.println();
    
    table = false;    
  }

  if(buttonPressed && !digitalRead(tableDown) && !digitalRead(tableUp))
  {
    buttonPressed = false;
  }

/*
 * These two next if sentences gets output message that includes all tables,
 * and then tables will regonize by the output message that it was meant for all.
 */
  if(digitalRead(tableDown) && !buttonPressed)
  {
    buttonPressed = true;
    output = "all tables down";
    table = true;
  }
  if(digitalRead(tableUp) && !buttonPressed)
  {
    buttonPressed = true;
    output = "all tables up";
    table = true;
  }
  
  serverloop();
  
}
