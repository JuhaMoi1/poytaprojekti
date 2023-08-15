#include <ESP8266WiFi.h>
#include <WiFiUdp.h>


//here replace table number with destination table. ie. for table 2 it has to be "table2 up" and "table2 down" etc.
const char *tableName = "table 8";
//important note on tablemessages. no spaces between table and number
const char *tableMessageUp = "table8 up";
const char *tableMessageDown = "table8 down";

const char *ssid = "SSID";
const char *password = "PASSWORD";

WiFiUDP UDP;
/* Switched real ip addresses to something else
 * setting static ip for the tables, so i can have them on certain ip space.
 * table1 = 127.0.0.101
 * table2 = 127.0.0.102
 * table3 = 127.0.0.103
 * table4 = 127.0.0.104
 * table5 = 127.0.0.105
 * table6 = 127.0.0.106
 * table7 = 127.0.0.107
 * table8 = 127.0.0.108
 */
IPAddress local_IP(127,0,0,108);
IPAddress gateway(127,0,0,1);
IPAddress subnet(255,255,0,0);


#define UDP_PORT 4210
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];
bool tableStatus;
bool tableUp = false;
bool tableDown = false;
char *input = "";

int up = 5;
int down = 4;

unsigned long lastTime = 0;
unsigned long previousMillis = 0;
void setup()
{
  
  delay(3000);
  
  WiFi.disconnect(true);
  delay(1);
  pinMode(up, OUTPUT);
  pinMode(down, OUTPUT);
  digitalWrite(up, HIGH);
  digitalWrite(down, HIGH);
  Serial.begin(115200);
  Serial.println();
  WiFi.config(local_IP, gateway, subnet);
    //if(!WiFi.config(local_IP, gateway, subnet))
  //{
    //Serial.println(" FAILED TO CONFIGURE WIFI");
  //}

  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA);

  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println();
  //if(!WiFi.config(local_IP, gateway,subnet))
  //{
  //  Serial.println("Failed to configure wifi");
  //}
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected. ip address: "); Serial.println(WiFi.localIP());
  Serial.print("gateway ip address: "); Serial.println(WiFi.gatewayIP());

  UDP.begin(UDP_PORT);
  Serial.print("listening on udp portt "); Serial.println(UDP_PORT);
  Serial.print("Table name is: "); Serial.println(tableName);
}

void loop()
{
  //trying to prevent table getting new command while it's already moving.
    int packetSize = UDP.parsePacket();
    if(packetSize && !tableUp && !tableDown)
    {
      UDP.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);

      if(packetBuffer)
      {
        Serial.print("saatu viesti: "); Serial.println(packetBuffer);
        if(strcmp(packetBuffer, tableMessageUp) == 0)
        {
          tableUp = true;
          tableDown = false;
        }
        if(strcmp(packetBuffer, tableMessageDown) == 0)
        {
          tableDown = true;
          tableUp = false;
        }

        if(strcmp(packetBuffer, "all tables up") == 0)
        {
          tableUp = true;
          tableDown = false;
        }
        if(strcmp(packetBuffer, "all tables down") == 0)
        {
          tableDown = true;
          tableUp = false;
        }
        lastTime = millis();
        
      }
      memset(packetBuffer, 0, UDP_TX_PACKET_MAX_SIZE);
      UDP.endPacket();
    
    }
  if(tableUp)
  {
      
    if((millis() - lastTime) < 10000)
    {
      Serial.print("Poyta ylos  "); Serial.println(millis() - lastTime);
      digitalWrite(up, LOW);
    }
    else
    {
      Serial.println("nyt menny 10s? poyta ylhaal");
      digitalWrite(up, HIGH);
      tableUp = false;
    }
  }
  if(tableDown)
  {
    
    if(millis() - lastTime < 10000)
    {
      Serial.print("Poyta alas  "); Serial.println(millis() - lastTime);
      digitalWrite(down, LOW);
    }
    else
    {
      Serial.println("nyt mennyt 10 sek, ja poyta alhaalla");
      digitalWrite(down, HIGH);
      tableDown = false;
      
    }
  }
}
