  
String tempStr;
int tempInt;


void updateServer() {  
  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
  
    
    client.print("GET /coffee/coffeestate.php");
    client.print("?s=");
    tempStr=String(state);
    client.print(tempStr);
    
    client.print("&l=");
    
    tempInt=coffieLeft();
    tempStr=String(tempInt);
    client.print(tempStr);
    
    client.print("&t=");
    
    tempInt=getTimer();
    tempStr=String(tempInt);
    client.print(tempStr);
    
    client.print("&u=");
    
    tempInt=millis();
    tempStr=String(tempInt);
    client.print(tempStr);
    
    client.println(" HTTP/1.1");
    
    client.println("Host: 212.97.141.141");
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  
    // if there are incoming bytes available
  // from the server, read them and print them:
 /* if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }
  */
   // if the server's disconnected, stop the client:
 
   if (client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    }
}
