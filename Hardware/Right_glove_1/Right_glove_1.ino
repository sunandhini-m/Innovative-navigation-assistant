#include <SoftwareSerial.h>

SoftwareSerial mySerial_1(1, 2); //Bluetooth connecting to mobile.
SoftwareSerial mySerial_2(0, 4); //Bluetooth pairing with left glove.

int i = 0;
String pieces[2] = {" "," "};
char data;
String input = "";
bool isSerial = false;
int dist;
int counter = 0;
int lastIndex = 0;

void setup() {
  mySerial_1.begin(9600); //Bluetooth BAUD rate
  pinMode(3, OUTPUT);
}

void loop() {

  counter = 0;
  lastIndex = 0;

  if (mySerial_1.available() > 0) { //Enter if any data is available in bluetooth serial.
    data = mySerial_1.read(); //Read the data available in serial.
    input = input + data; // Make the available data into a string. 
    isSerial = true;
  } else {
    mySerial_1.print(input);
    if (isSerial) { //Stop serial_1 and start serial_2 for comunicating with Left glove.
      mySerial_2.begin(9600);
      mySerial_2.print(" " + input);
      mySerial_2.end();
      mySerial_1.begin(9600);
      isSerial = false;
    }
    //The data is availablein the format direction_of_turn,distance_from_turn.
    for (int i = 0; i < input.length(); i++) {
      if (input.substring(i, i + 1) == ",") {
        pieces[counter] = (input.substring(lastIndex, i)).trim();
        lastIndex = i + 1;
        counter++;
      }
    }
    dist = pieces[1].toInt();

    if (dist > 100) {
        digitalWrite(3, HIGH);
        delay(1400);
        digitalWrite(3, LOW);
        delay(1400);
      }

    else if (pieces[0] == "FOR" || pieces[0] == "RAR" || pieces[0] == "SHR" || pieces[0] == "SLR" || pieces[0] == "TUR" || pieces[0] == "STR" || pieces[0] == "MER" || pieces[0] == "UTR"|| pieces[0] == "ROR") {
      mySerial_1.println(pieces[1]);
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
