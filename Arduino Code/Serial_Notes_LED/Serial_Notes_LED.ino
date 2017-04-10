/*Started By Levi Purdy 3/27/2017
  Contributors -- Levi Purdy,

  DragonFire.club serial note player V1

*/

int greenled = 2;
int blueled = 3;
int yellowled = 5;
int redled = 6;

String readString; 

void setup() {
  // initialize serial:
  Serial.begin(9600);
  //Set pins as output:
  pinMode(greenled, OUTPUT);
  pinMode(blueled, OUTPUT);
  pinMode(redled, OUTPUT);
  pinMode(yellowled, OUTPUT);
  Serial.println("Started");
}

void loop() {
  // if there's any serial available, read it:
  while (Serial.available() > 0) {
    
    char c = Serial.read(); // read 1 byte (character) from client
    readString += c; 

    if (c == '\n'){
      Serial.println(readString);
      changeleds();
      readString = "";
    }

  }
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



