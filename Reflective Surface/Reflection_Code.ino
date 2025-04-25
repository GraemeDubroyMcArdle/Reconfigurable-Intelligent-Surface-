//Circuit settings
//Serial >> PB15 (MOSI)
//LATCH >> PB14 (CS)
//CLK >?> PB13 (SCK)


//#include <SPI.h>       //SPI library for STM32
#define latchPin PB14  //Chip Select Pin
#define Clock PB13
#define SER PB15

//Turns all Registers On
int all[7] = { 0b11111111,
               0b11111111,
               0b11111111,
               0b11111111,
               0b11111111,
               0b11111111,
               0b11111111 };

//Turns all Registers Off
int off[7] = { 0b00000000,
               0b00000000,
               0b00000000,
               0b00000000,
               0b00000000,
               0b00000000,
               0b00000000 };

//Configuration for 0 degree
int pos0[7] = { 0b01111100,
                0b01111100,
                0b00000000,
                0b10000010,
                0b11111110,
                0b01111100,
                0b10000011 };

//Configuration for +15
int pos15[7] = { 0b11111000,
                 0b11111000,
                 0b00000010,
                 0b00000110,
                 0b11011110,
                 0b11111000,
                 0b00000010 };

//Configuration for -15
int neg15[7] = { 0b00111110,
                 0b00111110,
                 0b10000000,
                 0b11000000,
                 0b11110110,
                 0b00111110,
                 0b00000001 };

//Configuration of +30
int pos30[7] = { 0b11110000,
                 0b11110010,
                 0b11100010,
                 0b00000110,
                 0b00011100,
                 0b11111000,
                 0b00000110 };

//Configuration for -30
int neg30[7] = { 0b00011110,
                 0b10011110,
                 0b10001110,
                 0b11000000,
                 0b01110000,
                 0b00111110,
                 0b00000110 };
//Configuration for +45
int pos45[7] = { 0b11110010,
                 0b11100010,
                 0b11100110,
                 0b10000100,
                 0b00001100,
                 0b00111010,
                 0b11100111 };

//Configure -45
int neg45[7] = { 0b10011110,
                 0b10001110,
                 0b11001110,
                 0b01000010,
                 0b01100000,
                 0b10111000,
                 0b01001111 };

//Confugure +60
int pos60[7] = { 0b11100100,
                 0b11100100,
                 0b11100100,
                 0b11001100,
                 0b00001100,
                 0b00011010,
                 0b01110010 };

//Configure -60
int neg60[7] = { 0b01001110,
                 0b01001110,
                 0b01001110,
                 0b01100110,
                 0b01100000,
                 0b10110000,
                 0b00011101 };

//Sets the shift registers according to the Array entered into terminal
void setShift(int vals[]) {
  //Sets the latch low to accept oncoming signals
  digitalWrite(latchPin, LOW);
  Serial.println("Initiated");

  //Loops through the array in reverse order to shift down the arrays
  for (int i = 6; i >= 0; i--)
    shift595(SER, Clock, MSBFIRST, vals[i]);

  //ends the write and updates the Shift Registers
  digitalWrite(latchPin, HIGH);
}



void setup() {
  //Opens Terminal
  Serial.begin(115200);
  //Sets the Digital pins for shifting communications
  pinMode(SER, OUTPUT);
  pinMode(Clock, OUTPUT);
  pinMode(latchPin, OUTPUT);


  Serial.println("Initiated");
  setShift(pos0);
}

//Acts as a standin for shiftOut function, with the same input data, however allows manual
//delays for testing purposes
void shift595(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val) {
  uint8_t i;

  //sets the signal to on or off depending on depending on the entered bits
  for (i = 0; i < 8; i++) {
    if (bitOrder == LSBFIRST)
      digitalWrite(dataPin, !!(val & (1 << i)));
    else
      digitalWrite(dataPin, !!(val & (1 << (7 - i))));

    //Updates the clock
    digitalWrite(clockPin, HIGH);
    delay(5);
    digitalWrite(clockPin, LOW);
    delay(5);
  }
}


void loop() {
  // Runs when a new signal is entered into the terminal
  if (Serial.available() > 0) {
    Serial.println("in New Input");
    String input = Serial.readStringUntil('\n');
    input.trim();

    Serial.println(input);

    //If 0 is entered, sets pins to 0 degree reflection
    if (input == "0") {
      Serial.println("In 0");
      setShift(pos0);
    }
    //Sets pins to 15 degree reflection
    else if (input == "pos15")
      setShift(pos15);
    else if (input == "neg15")
      setShift(neg15);
    else if (input == "pos30")
      setShift(pos30);
    else if (input == "neg30")
      setShift(neg30);
    else if (input == "pos45")
      setShift(pos45);
    else if (input == "neg45")
      setShift(neg45);
    else if (input == "pos60")
      setShift(pos60);
    else if (input == "neg60")
      setShift(neg60);
    else if (input == "all")
      setShift(all);
    else if (input == "off")
      setShift(off);
  }
}
