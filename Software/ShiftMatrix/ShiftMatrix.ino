int cols[] =
{//1rgb 2rgb 3rgb....
  9, 28, 1,
  10, 27, 2,
  11, 26, 3,
  12, 25, 4,
  13, 24, 5,
  14, 23, 6,
  15, 22, 7,
  16, 21, 8
}; 

int rows[] = {17, 18, 19, 20, 29, 30, 31, 32};

int pinOrder[] = {32,31,30,29,20,19,18,17, 28,27,26,25,24,23,22,21, 16,15,14,13,12,11,10,9, 8,7,6,5,4,3,2,1};

int dataOut[32];

int dataPin = 13;
int clockPin = 12;
int latchPin = 11;

// input 0-based row, column, rgb (r=0, g=1, b=2) and 1 or 0 to set
void setRow(int row, int val) {
  dataOut[rows[row]-1] = val;
}

void setCol(int col, int rgb, int val) {
  dataOut[cols[col*3+rgb]-1] = val;
}

void writeOut() {
  digitalWrite(clockPin, 0);
  digitalWrite(latchPin, 0);
  
  for (int i=0;i<32;i++) {
    digitalWrite(dataPin, dataOut[pinOrder[i]-1]);
    digitalWrite(clockPin, 1);
    digitalWrite(clockPin, 0);  
  }
  
    digitalWrite(latchPin, 1);
}

// the setup routine runs once when you press reset:
void setup() {                
  pinMode(dataPin, OUTPUT);     
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  
  for (int col=0;col<24;col++) {
    dataOut[cols[col]] = 1;
  }
  for (int row=0;row<8;row++) {
    dataOut[rows[row]] = 0;
  }
  writeOut();
}

// the loop routine runs over and over again forever:
void loop() {
  for(int row=0;row<8;row++) {
    setRow(row, 1);
    for (int col=0;col<8;col++) {
      for (int rgb=0;rgb<3;rgb++) {
        setCol(col, rgb, 0);
        
        writeOut();
        delay(100);
        
        setCol(col, rgb, 1);
      }
    }
    setRow(row, 0);
  }
}
