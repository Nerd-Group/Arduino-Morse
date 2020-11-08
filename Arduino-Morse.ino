// the pin where the LED should be driven
#define LedPin 13

// optional serial debugging
#define serial true

// define all delays in milliseconds
#define shortDelay 500
#define longDelay 2*shortDelay
#define spaceDelay 3*shortDelay
#define wordEndDelay 5*longDelay

// change the text to whatever you want and dont forget to adjust the 'TextLength'
const char Text[] = "Wish You Were Here";
const char TextLength = 18;

const char MorseTable[][5] = {
  // A to I
  ".-   ", "-... ", "-.-. ", "-..  ", ".    ", "..-. ", "--.  ", ".... ", "..   ",
  // J to R
  ".--- ", "-.-  ", ".-.. ", "--   ", "-.   ", "---  ", ".--. ", "--.- ", ".-.  ",
  // S to Z
  "...  ", "-    ", "..-  ", "...- ", ".--  ", "-..- ", "-.-- ", "--.. ",
  // 0 to 9
  "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."
};

void setup() {
  // All unused pins as High-Ohm Pull-down
  for (int i = 0; i < 8; i++) {
    pinMode(i, INPUT);
    digitalWrite(i, LOW);
  }

  // Pin where the LED should be driven
  pinMode(LedPin, OUTPUT);
  digitalWrite(LedPin, LOW);

  if (serial) {
    Serial.begin(9600);
  }

}



void Blink(bool state) {
  digitalWrite(LedPin, HIGH);

  if (state) { // long caracter
    delay(longDelay);
  }
  else { // short caracter
    delay(shortDelay);
  }

  digitalWrite(LedPin, LOW);
  delay(shortDelay);
}



void loop() {

  // output all letters of the text sequentially
  for (int i = 0; i < TextLength; i++) {

    // select the letter that is going to be displayed
    char Letter =  Text[i];

    if (serial) {
      Serial.print(Letter);
      Serial.print("  ");
    }

    // get the Morse Translation of that letter

    // space
    if (Letter == 32) {
      if (serial) {
        Serial.println(" ");
      }
      delay(spaceDelay);

      continue;
    }

    // uppercase letters
    if (Letter > 64 && Letter < 91)
      Letter -= 65;

    // lowercase letters
    if (Letter > 96 && Letter < 123)
      Letter -= 97;

    // numbers
    if (Letter > 47 && Letter < 58)
      Letter -= 21; // numbers begin at Array-index 27 after the letters.

    // error
    if (Letter > 36) {
      for (int j = 0; j < 6; j++) {
        Blink(false);
      }
      break;
    }

    // convert the letter using the implemented morse table
    char Word[5] = {""};
    for (int j = 0; j < 5; j++) {
      Word[j] = MorseTable[Letter][j];
    }

    // now display the word on the LED
    for (int j = 0; j < 5 && Word[j] != 32; j++) {

      if (serial) {
        Serial.print(Word[j]);
      }

      if (Word[j] == 46) {
        Blink(false);
      }
      else {
        Blink(true);
      }
    }

    // end of the word
    if (serial) {
      Serial.println("");
    }
    delay(longDelay);
  }

  // end of the whole Text
  if (serial) {
    Serial.println("\n");
  }
  delay(wordEndDelay);

}
