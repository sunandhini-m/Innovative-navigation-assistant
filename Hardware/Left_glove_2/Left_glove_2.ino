#include <SoftwareSerial.h>

SoftwareSerial mySerial(1, 4); //Rx(2), Tx(3)

int i = 0;
String pieces[2] = {" ", " "};
char data;
String input = "";
int dist;
int counter = 0;
int lastIndex = 0;

void setup() {
  mySerial.begin(9600); //Bluetooth BAUD rate
  pinMode(3, OUTPUT); //Pin 6 -- Straight
}

void loop() {

  counter = 0;
  lastIndex = 0;

  if (mySerial.available() > 0) {
    data = mySerial.read();
    input = input + data;
  } else {
    mySerial.print(input);
    for (int i = 0; i < input.length(); i++) {
      if (input.substring(i, i + 1) == ",") {
        pieces[counter] = (input.substring(lastIndex, i)).trim();
        lastIndex = i + 1;
        counter++;
      }
    }
    dist = pieces[1].toInt();

    if (dist > 100) { //Far distance so both LED glow
        digitalWrite(3, HIGH);
        delay(1400);
        digitalWrite(3, LOW);
        delay(1400);
      }
    
    else if (pieces[0] == "FOL" || pieces[0] == "RAL" || pieces[0] == "SHL" || pieces[0] == "SLL" || pieces[0] == "TUL" || pieces[0] == "STR" || pieces[0] == "MER" || pieces[0] == "UTL" || pieces[0] == "ROL") {
      mySerial.println(dist);
      if (dist < 50) {
        digitalWrite(3, HIGH);
        delay(400);
        digitalWrite(3, LOW);
        delay(400);
      }

      else if (dist <= 100 && dist >= 50) {
        
        digitalWrite(3, HIGH);
        delay(800);
        digitalWrite(3, LOW);
        delay(800);
      }

    } else if (pieces[0] == "STP" || pieces[0] == "OTH") {
      pieces[0] = " ";
      dist = 0;
      input = "";
    }
    input = "";
  }
}
