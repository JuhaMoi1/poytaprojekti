//web server and page appearance for master-client

void serverloop()
{
  WiFiClient client = server.available();   // Listen for incoming clients
  
  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();         
      if (client.available()) 
      { // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then

        header += c;
        if (c == '\n') 
        { // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) 
          {

            if(header.indexOf(loginInfo) >= 0)
            {
              // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
              // and a content-type so the client knows what's coming, then a blank line:
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:text/html");
              client.println("Connection: close");
              client.println();
              
              /*
               * Here we will look the header and according to that we will
               * determine UDP message to send to tables, so tables will
               * know what one has to move.
               * 
               * 2 IF's for each table, because of up and down.
               */

              //PERHAPS WISER TO USE THIS WITH SWITCH CASE? MUCH IF SENTENCES.

               // TABLE 1
              if (header.indexOf("GET /1/up") >= 0) 
              {
                Serial.println("table1 up");
                table = true;
                output = "table1 up"; //1 as in up
              }
              else if (header.indexOf("GET /1/down") >= 0) 
              {
                Serial.println("table1 down");
                table = true;
                output = "table1 down"; // 0 as in down
              }

              // TABLE 2 
              else if (header.indexOf("GET /2/up") >= 0) 
              {
                Serial.println("table2 up");
                table = true;
                output = "table2 up";
              } 
              else if (header.indexOf("GET /2/down") >= 0) 
              {
                Serial.println("table2 down");
                table = true;
                output = "table2 down";
              }
              

              // TABLE 3 
              else if (header.indexOf("GET /3/up") >= 0) 
              {
                Serial.println("table3 up");
                table = true;
                output = "table3 up";
              } 
              else if (header.indexOf("GET /3/down") >= 0) 
              {
                Serial.println("table3 down");
                table = true;
                output = "table3 down";
              }

              // TABLE 4 
              else if (header.indexOf("GET /4/up") >= 0) 
              {
                Serial.println("table4 up");
                table = true;
                output = "table4 up";
              } 
              else if (header.indexOf("GET /4/down") >= 0) 
              {
                Serial.println("table4 down");
                table = true;
                output = "table4 down";
              }

              // TABLE 5 
              else if (header.indexOf("GET /5/up") >= 0) 
              {
                Serial.println("table5 up");
                table = true;
                output = "table5 up";
              } 
              else if (header.indexOf("GET /5/down") >= 0) 
              {
                Serial.println("table5 down");
                table = true;
                output = "table5 down";
              }

              // TABLE 6 
              else if (header.indexOf("GET /6/up") >= 0) 
              {
                Serial.println("table6 up");
                table = true;
                output = "table6 up";
              } 
              else if (header.indexOf("GET /6/down") >= 0) 
              {
                Serial.println("table6 down");
                table = true;
                output = "table6 down";
              }

              // TABLE 7 
              else if (header.indexOf("GET /7/up") >= 0) 
              {
                Serial.println("table7 up");
                table = true;
                output = "table7 up";
              } 
              else if (header.indexOf("GET /7/down") >= 0) 
              {
                Serial.println("table7 down");
                table = true;
                output = "table7 down";
              }

              // TABLE 8 
              else if (header.indexOf("GET /8/up") >= 0) 
              {
                Serial.println("table8 up");
                table = true;
                output = "table8 up";
              } 
              else if (header.indexOf("GET /8/down") >= 0) 
              {
                Serial.println("table8 down");
                table = true;
                output = "table8 down";
              }
            
              // Display the HTML web page
              client.println("<!DOCTYPE html><html>");
              client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
              client.println("<link rel=\"icon\" href=\"data:,\">");
              // CSS to style the on/off buttons 
              // Feel free to change the background-color and font-size attributes to fit your preferences
              client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center; font-size: 20px}");
              client.println(".button { background-color: #195B6A; border: none; color: white; padding: 5px 20px;");
              client.println("text-decoration: none; font-size: 20px; margin: 2px; cursor: pointer;}");
              client.println(".button2 {background-color: #77878A; padding: 5px 20px;}</style></head>");
            
              // Web Page Heading, ei ääkkösiä
              client.println("<body><h1>Class 174 tables</h1>");

              /*
               *  Display current state of tables, and Up/Down buttons
               *  Perhaps wise to take state's off. because they will
               *  always go to default when restarted.
               */ 

              //TABLE 1  
              client.println("<p>Table 1");
              client.println("<a href=\"/1/up\"><button class=\"button\">YLOS</button></a>");
              client.println("<a href=\"/1/down\"><button class=\"button button2\">ALAS</button></a></p>");

               
              //TABLE 2  
              client.println("<p>Table 2");
              client.println("<a href=\"/2/up\"><button class=\"button\">YLOS</button></a>");
              client.println("<a href=\"/2/down\"><button class=\"button button2\">ALAS</button></a></p>");

              //TABLE 3  
              client.println("<p>Table 3");
              client.println("<a href=\"/3/up\"><button class=\"button\">YLOS</button></a>");
              client.println("<a href=\"/3/down\"><button class=\"button button2\">ALAS</button></a></p>");

              //TABLE 4  
              client.println("<p>Table 4");
              client.println("<a href=\"/4/up\"><button class=\"button\">YLOS</button></a>");
              client.println("<a href=\"/4/down\"><button class=\"button button2\">ALAS</button></a></p>");

              //TABLE 5  
              client.println("<p>Table 5");
              client.println("<a href=\"/5/up\"><button class=\"button\">YLOS</button></a>");
              client.println("<a href=\"/5/down\"><button class=\"button button2\">ALAS</button></a></p>");

              //TABLE 6  
              client.println("<p>Table 6");
              client.println("<a href=\"/6/up\"><button class=\"button\">YLOS</button></a>");
              client.println("<a href=\"/6/down\"><button class=\"button button2\">ALAS</button></a></p>");

              //TABLE 7  
              client.println("<p>Table 7");
              client.println("<a href=\"/7/up\"><button class=\"button\">YLOS</button></a>");
              client.println("<a href=\"/7/down\"><button class=\"button button2\">ALAS</button></a></p>");

              //TABLE 8  
              client.println("<p>Table 8");
              client.println("<a href=\"/8/up\"><button class=\"button\">YLOS</button></a>");
              client.println("<a href=\"/8/down\"><button class=\"button button2\">ALAS</button></a></p>");

              client.println("</body></html>");
              break;
            }
            else
            {
              client.println("HTTP/1.1 401 Unauthorized");
              client.println("WWW-Authenticate: Basic realm=\"Secure\"");
              client.println("Content-Type: text/html");
              client.println();
              client.println("<html>Authentication failed</html>");
              break;
            }

              // The HTTP response ends with another blank line
              client.println();
              // Break out of the while loop
              break;
            } 
            else 
            { // if you got a newline, then clear currentLine
              currentLine = "";
            }
          } 
          else if (c != '\r') 
          {  // if you got anything else but a carriage return character,
            currentLine += c;      // add it to the end of the currentLine
          }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
