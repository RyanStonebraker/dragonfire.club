/*Started By Levi Purdy 3/27/2017
  Contributors -- Levi Purdy,

  DragonFire.club Iot xylaphone test

  References:   - WebServer example by David A. Mellis and
                  modified by Tom Igoe
                - SD card examples by David A. Mellis and
                  Tom Igoe
                - Ethernet library documentation:
                  http://arduino.cc/en/Reference/Ethernet
                - SD Card library documentation:
                  http://arduino.cc/en/Reference/SD
                - W.A. Smith, http://startingelectronics.org
                - zoomkat 12-08-12 http://code.google.com/p/arduino/issues/detail?id=605


*/

#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 50);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

File webFile;

String readString; 

int greenled = 2;
int blueled = 3;
int yellowled = 5;
int redled = 6;

void setup()
{
  Ethernet.begin(mac, ip);  // initialize Ethernet device
  server.begin();           // start to listen for clients
  Serial.begin(9600);       // for debugging

  // initialize SD card
  Serial.println("Initializing SD card...");
  if (!SD.begin(4)) {
    Serial.println("ERROR - SD card initialization failed!");
    return;    // init failed
  }
  Serial.println("SUCCESS - SD card initialized.");
  // check for index.htm file
  if (!SD.exists("index.htm")) {
    Serial.println("ERROR - Can't find index.htm file!");
    return;  // can't find index file
  }
  Serial.println("SUCCESS - Found index.htm file.");
  pinMode(greenled, OUTPUT);
  pinMode(blueled, OUTPUT);
  pinMode(redled, OUTPUT);
  pinMode(yellowled, OUTPUT);
}

void loop()
{
  EthernetClient client = server.available();  // try to get client

  if (client) {  // got client?
    boolean currentLineIsBlank = true;

    readString = "";
    while (client.connected()) {
      if (client.available()) {   // client data available to read
        char c = client.read(); // read 1 byte (character) from client
        //read char by char HTTP request
          //store characters to string 
          readString += c; 
          //Serial.print(c);
        
        
        // last line of client request is blank and ends with \n
        // respond to client only after last line received
        if (c == '\n' && currentLineIsBlank) {
          Serial.println(readString);
          
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          // send web page
          webFile = SD.open("index.htm");        // open web page file
          if (webFile) {
            while (webFile.available()) {
              client.write(webFile.read()); // send web page to client
            }
            webFile.close();
          }
          break;
          
        }
        // every line of text received from the client ends with \r\n
        if (c == '\n') {
          // last character on line of received text
          // starting new line with next character read
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // a text character was received from client
          currentLineIsBlank = false;
        }
      } // end if (client.available())
    } // end while (client.connected())
    delay(1);      // give the web browser time to receive the data
    client.stop(); // close the connection
    changeleds();
  } // end if (client)

}
void changeleds(){
 if(readString.indexOf("green") > 0){
  digitalWrite(greenled, HIGH);    // set pin 5 high
  Serial.println("Green led on");
 }
 else{
  digitalWrite(greenled, LOW);
 }
  if(readString.indexOf("blue") > 0){
  digitalWrite(blueled, HIGH);    // set pin 5 high
  Serial.println("blue led on");
 }
 else{
  digitalWrite(blueled, LOW);
 }
 if(readString.indexOf("red") > 0){
  digitalWrite(redled, HIGH);    // set pin 5 high
  Serial.println("red led on");
 }
 else{
  digitalWrite(redled, LOW);
 }
 if(readString.indexOf("yellow") > 0){
  digitalWrite(yellowled, HIGH);    // set pin 5 high
  Serial.println("yellow led on");
 }
 else{
  digitalWrite(yellowled, LOW);
 }
}


