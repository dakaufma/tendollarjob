int dataPin = 8;
int clockPin = 10;
int latchPin = 12;

int board[8][24];
int pinOrder[] = {30,29,28,27,26,25,24,31, 23,22,21,20,19,28,17,16, 7,6,5,4,3,2,1,0, 14,13,12,11,10,9,8,15};
int rowPins[] = {16,17,18,19,28,29,30,31};
int colPins[] = {
  8 ,27,0,
  9 ,26,1,
  10,25,2,
  11,24,3,
  12,23,4,
  13,22,5,
  14,21,6,
  15,20,7
};

int pins[32];

void writeBoard(int boarda[][24], int enabledRow) {
  for (int row=0;row<8;row++) {
    pins[rowPins[row]] = (row==enabledRow)?1:0;
  }
  for (int col=0;col<24;col++) {
    pins[colPins[col]] = 1-boarda[enabledRow][col];
  }
  
  for (int i=0;i<4;i++) {
    byte b=0;
    for (int j=0;j<8;j++) {
      b = (b<<1) + pins[pinOrder[8*i+j]];
    }
    shiftOut(dataPin, clockPin, MSBFIRST, b);
  }
}

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  
  digitalWrite(dataPin, LOW);
  digitalWrite(clockPin, LOW);
  digitalWrite(latchPin, LOW);
  
  for (int row=0;row<8;row++)
    for (int col=0;col<24;col++)
      board[row][col]=1;
      
  Serial.begin(9600);
  
  /* Test code to turn all leds on
  byte b3 = 0b00000000;
  byte b2 = 0b00000000;
  byte b1 = 0b00000000;
  byte b0 = 0b11111111;
  
  while (1) {
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin, clockPin, MSBFIRST,b3);
    shiftOut(dataPin, clockPin, MSBFIRST,b2);
    shiftOut(dataPin, clockPin, MSBFIRST,b1);
    shiftOut(dataPin, clockPin, MSBFIRST,b0);
    digitalWrite(latchPin,HIGH);
    delay(1000);
  }*/
}

void loop() {
  for (int enabled=0;enabled<8;enabled++) {
    digitalWrite(latchPin, LOW);
    writeBoard(board, enabled);
    digitalWrite(latchPin, HIGH);
    delayMicroseconds(100);
  }
}
