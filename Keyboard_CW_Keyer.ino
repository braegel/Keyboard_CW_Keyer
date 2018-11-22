// teststring:
// ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.?/@abcdefghijklmnopqrstuvwxyz

#include <stdarg.h>

const int ledPin =  LED_BUILTIN;// the number of the LED pin
const int wpm = 13;
unsigned char incomingByte;
int ledState = LOW;             // ledState used to set the LED
String aword;
String serialstring;
String morse;

unsigned long previousMillis = 0;
unsigned long currentMillis;
float dit_ms_calc;
unsigned int dit_ms;

void setup() {
//  dit_ms_calc = ((60/(50*wpm))*1000);
  dit_ms_calc = 6000/5/wpm;
  dit_ms = (int)dit_ms_calc;
  pinMode(ledPin, OUTPUT);

// debug
  Serial.begin(9600);
/*  Serial.print("dit_ms: "); 
  Serial.println(dit_ms);
*/

}

void dit(){
  digitalWrite(ledPin, HIGH);
  delay(dit_ms);
  digitalWrite(ledPin, LOW);
  Serial.print(".");
}

void dah(){
  digitalWrite(ledPin, HIGH);
  delay(dit_ms*3);
  digitalWrite(ledPin, LOW);
  Serial.print("-");
}

void intra_char(){
  delay(dit_ms);
}

void inter_char(){
  delay(dit_ms*3);
  Serial.print("/");
}

void inter_word(){
  delay(dit_ms*4); // totals to 7 because inter_char delay is after every char
  Serial.print(" ");
}


void send_morse(){
  int i;
  for (i=0;i<morse.length();i++){
    if (morse.charAt(i)=='.'){
      dit();
    }
    if (morse.charAt(i)=='-'){
    dah();
    }
    if (i<morse.length()-1) {
    intra_char();
    }
  }
}

void send(char achar){
  morse="";
  switch(achar){
  case 'E': case 'e':
  morse=".";
  break;
  case 'I': case 'i':
  morse="..";
  break;
  case 'S': case 's':
  morse="...";
  break;
  case 'H': case 'h':
  morse="....";
  break;
  case '5':
  morse=".....";
  break;
  case '4':
  morse="....-";
  break;
  case 'V': case 'v':
  morse="...-";
  break;
  case '3':
  morse="...--";
  break;
  case 'U': case 'u':
  morse="..-";
  break;
  case 'F': case 'f':
  morse="..-.";
  break;
  case '-':
  morse="..--";
  break;
  case '2':
  morse="..---";
  break;
  case 'A': case 'a':
  morse=".-";
  break;
  case 'R': case 'r':
  morse=".-.";
  break;
  case 'L': case 'l':
  morse=".-..";
  break;
  case 'W': case 'w':
  morse=".--";
  break;
  case 'J': case 'j':
  morse=".---";
  break;
  case 'P': case 'p':
  morse=".--.";
  break;
  case '1':
  morse=".----";
  break;
  case 'T': case 't':
  morse="-";
  break;
  case 'M': case 'm':
  morse="--";
  break;
  case 'N': case 'n':
  morse="-.";
  break;
  case 'K': case 'k':
  morse="-.-";
  break;
  case 'D': case 'd':
  morse="-..";
  break;
  case 'B': case 'b':
  morse="-...";
  break;
  case '6':
  morse="-....";
  break;
  case 'X': case 'x':
  morse="-..-";
  break;
  case 'Y': case 'y':
  morse="-.--";
  break;
  case 'C': case 'c':
  morse="-.-.";
  break;
  case 'O': case 'o':
  morse="---";
  break;
  case 'G': case 'g':
  morse="--.";
  break;
  case 'Q': case 'q':
  morse="--.-";
  break;
  case 'Z': case 'z':
  morse="--..";
  break;
  case '7':
  morse="--...";
  break;
  case '0':
  morse="-----";
  break;
  case '9':
  morse="----.";
  break;
  case '8':
  morse="---..";
  break;
  case '.':
  morse=".-.-.-";
  break;
  case ',':
  morse="--..--";
  break;
  case '?':
  morse="..--..";
  break;
  case '/':
  morse="-..-.";
  break;
  case '@':
  morse=".--.-.";
  break;
  }
  send_morse();
}

void send_word(){
//  Serial.println("Sending a word");

  int i;

  for (i=0;i<aword.length();i++){
//    Serial.println(aword.charAt(i));
    send(aword.charAt(i));
//    Serial.println(aword.charAt(i));
    inter_char();
  }
  inter_word();
}

void process_string(){
  int i;
  aword="";
  for (i=0;i<serialstring.length();i++){
    if (serialstring.charAt(i)==' ' || serialstring.charAt(i)=='\n'){
      send_word();
      aword="";
    }
    else{
      aword.concat(serialstring.charAt(i));
    }
  }
  
}

void loop() {
        if (Serial.available() > 0) {
          serialstring=Serial.readString();
          process_string();
        }
}
