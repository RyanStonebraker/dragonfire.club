/*Started By Levi Purdy 3/27/2017
  Contributors -- Levi Purdy,

  DragonFire.club serial note player V1

*/

int greenSolenoid = 3;
int blueSolenoid = 2;
int yellowSolenoid = 6;
int redSolenoid = 5;

float greenElapsed = 0;
float blueElapsed = 0;
float yellowElapsed = 0;
float redElapsed = 0;

#define ONTIME 50

String readString;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  //Set pins as output:
  pinMode(greenSolenoid, OUTPUT);
  pinMode(blueSolenoid, OUTPUT);
  pinMode(redSolenoid, OUTPUT);
  pinMode(yellowSolenoid, OUTPUT);
  Serial.println("Started");
}

void loop() {
  // if there's any serial available, read it:
  while (Serial.available() > 0) {

    char c = Serial.read(); // read 1 byte (character) from client
    readString += c;

    if (c == '\n'){
      Serial.println(readString);
      changeSolenoids();
      readString = "";
      break;
    }
  }

  resetSolenoids();
}

void resetSolenoids() {
  if (millis() >= greenElapsed + ONTIME)
    digitalWrite(greenSolenoid, LOW);

  if (millis() >= redElapsed + ONTIME)
    digitalWrite(redSolenoid, LOW);

  if (millis() >= blueElapsed + ONTIME)
    digitalWrite(blueSolenoid, LOW);

  if (millis() >= yellowElapsed + ONTIME)
    digitalWrite(yellowSolenoid, LOW);
}

void changeSolenoids(){
 if(readString.indexOf("green") > 0){
  digitalWrite(greenSolenoid, HIGH);    // set pin 5 high
  greenElapsed = millis();
  Serial.println("Green Solenoid on");
 }
 else{
  digitalWrite(greenSolenoid, LOW);
 }
  if(readString.indexOf("blue") > 0){
  digitalWrite(blueSolenoid, HIGH);    // set pin 5 high
  blueElapsed = millis();
  Serial.println("Blue Solenoid on");
 }
 else{
  digitalWrite(blueSolenoid, LOW);
 }
 if(readString.indexOf("red") > 0){
  digitalWrite(redSolenoid, HIGH);    // set pin 5 high
  redElapsed = millis();
  Serial.println("Red Solenoid on");
 }
 else{
  digitalWrite(redSolenoid, LOW);
 }
 if(readString.indexOf("yellow") > 0){
  digitalWrite(yellowSolenoid, HIGH);    // set pin 5 high
  yellowElapsed = millis();
  Serial.println("Yellow Solenoid on");
 }
 else{
  digitalWrite(yellowSolenoid, LOW);
 }
}
