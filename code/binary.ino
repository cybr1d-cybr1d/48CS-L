const int bin1 = 74;
const int bin2 = 75;
const int bin3 = 76;
const int bin4 = 85;
const int bin5 = 67;
const int bin6 = 66;
const int bin7 = 68;
const int bin8 = 73;
const int bin9 = 65;
const int bin10 = 72;
const int bin11 = 71;
const int bin12 = 70;
const int bin13 = 53;
const int bin14 = 55;
const int bin15 = 54;
const int bin16 = 63;
const int bin17 = 64;
const int bin18 = 56;
const int bin19 = 69;
const int bin20 = 21;
const int bin21 = 46;
const int bin22 = 47;
const int bin23 = 45;
const int bin24 = 44;
const int bin25 = 52;
const int bin26 = 51;
const int bin27 = 43;
const int bin28 = 13;
const int bin29 = 50;
const int bin30 = 49;
const int bin31 = 48;
const int bin32 = 12;
const int bin33 = 15;
const int bin34 = 14;

const int afterBurnerTop1 = A15;
const int afterBurnerTop2 = A14;
const int afterBurnerTop3 = A13;
const int afterBurnerTop4 = A12;
const int afterBurnerBottom1 = A8;
const int afterBurnerBottom2 = A9;
const int afterBurnerBottom3 = A10;
const int afterBurnerBottom4 = A11;

int binLeds[] = {bin1, bin2, bin3, bin4, bin5, bin6, bin7, bin8, bin9, bin10, bin11, bin12,
            bin13, bin14, bin15, bin16, bin17, bin18, bin19, bin20, bin21, bin22, bin23,
            bin24, bin25, bin26, bin27, bin28, bin29, bin30, bin31, bin32, bin33, bin34};
int afterBurnerLeds[2][4] = {{afterBurnerTop1, afterBurnerTop2, afterBurnerTop3, afterBurnerTop4},
                       {afterBurnerBottom1, afterBurnerBottom2, afterBurnerBottom3, afterBurnerBottom4}};
int binLedsLength = sizeof(binLeds) / sizeof(bin1);
int afterBurnerLedsLength = sizeof(afterBurnerLeds[0]) / sizeof(afterBurnerTop1);
int buttonPushCounter = 0;
int twinkleLeds[17];
int count = 0;
int flag = 0;
int prevPin = 1;
int afterBurnerFlag = 0;
int arr[15] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1, -1, -1, -1, -1};

// x, y, and r values for each pin
int binCoordinates[34][4] = {{bin1, -6, -12, 13},
                             {bin32, -4, 9, 10},
                             {bin28, -4, 4, 6},
                             {bin27, -4, 2, 4},
                             {bin20, -4, -4, 6},
                             {bin2, -4, -11, 12},
                             {bin34, -3, 11, 11},
                             {bin33, -3, 10, 10},
                             {bin12, -3, -7, 8},
                             {bin11, -3, -9, 9},
                             {bin3, -3, -11, 11},
                             {bin19, -2, -5, 5},
                             {bin29, -1, 5, 5},
                             {bin24, -1, 1, 1},
                             {bin23, -1, 0, 1},
                             {bin8, -1, -10, 10},
                             {bin31, 0, 9, 9},
                             {bin30, 0, 7, 7},
                             {bin26, 0, 3, 3},
                             {bin13, 0, -6, 6},
                             {bin10, 0, -9, 9},
                             {bin25, 1, 2, 2},
                             {bin4, 1, -11, 11},
                             {bin22, 2, 0, 2},
                             {bin21, 2, -2, 3},
                             {bin14, 2, -6, 6},
                             {bin7, 2, -10, 10},
                             {bin18, 3, -5, 6},
                             {bin15, 3, -7, 8},
                             {bin5, 3, -11, 11},
                             {bin9, 4, -9, 10},
                             {bin6, 5, -10, 11},
                             {bin16, 6, -7, 9},
                             {bin17, 7, -6, 9}};

void setup() {
  for (int i = 0; i < binLedsLength; i++) {
    pinMode(binLeds[i], OUTPUT);
  }

  for (int i = 0; i < 4; i++) {
    pinMode(afterBurnerLeds[0][i], OUTPUT);
    pinMode(afterBurnerLeds[1][i], OUTPUT);
  }

  attachInterrupt(digitalPinToInterrupt(4), decision, RISING);
}

void clr() {
  for(int i = 0; i < 34; i++) {
    digitalWrite(binLeds[i], LOW);
  }
}

static unsigned long last_interrupt_time = 0;
void decision() {
  unsigned long interrupt_time = millis();

  if (interrupt_time - last_interrupt_time > 200) {
    buttonPushCounter++;
    clr();
  }
  last_interrupt_time = interrupt_time;
 
}

bool isDuplicate2(int num, int arrEnd) {
  for (int i = 0; i < arrEnd; i++) {
    if (arr[i] == num) {
      return true;
    }
  }
  return false;
}

void matrix2() {
  int arrEnd = 0;
  int row = random(-5, 7);
  int yMax[2] = {-1, -15};
  int flag;

  do {
    flag = 0;
    yMax[0] = -1;
    yMax[1] = -15;
    
    for (int i = 0; i < 34; i++) {
      if (binCoordinates[i][1] == row || binCoordinates[i][1] == row+1 || binCoordinates[i][1] == row-1) {
        if (!isDuplicate2(i, arrEnd) && binCoordinates[i][2] > yMax[1]) {
          yMax[0] = i;
          yMax[1] = binCoordinates[i][2];
          flag = 1;
        }
      }
    }
    if (flag == 1) {
      arr[arrEnd++] = yMax[0];
    }
  } while (flag != 0);

  for (int i = 0; i < arrEnd; i++) {
    digitalWrite(binCoordinates[arr[i]][0], HIGH);
    delay(150);
    if (i < arrEnd-1) {
      digitalWrite(binCoordinates[arr[i+1]][0], HIGH);
    }
    digitalWrite(binCoordinates[arr[i]][0], LOW);
    }
}

void matrix() {
  int row = random(-5, 6);
  
  for (int j = 0; j < 34; j++) {
    int pin = binCoordinates[j][0];
    int x = binCoordinates[j][1];
    int y = binCoordinates[j][2];

    if (x == row || x == row+1) {
      digitalWrite(pin, HIGH);
      if (prevPin != 1) {
        digitalWrite(prevPin, LOW);
      }
      delay(200);
      prevPin = pin;
    }
  }
}

void initTwinkleLeds() {
  for (int i = 0; i < 17; i++) {
    int led = random(34);

    while (isDuplicate(led)) {
      led = random(34);
    }

    twinkleLeds[i] = led;

    digitalWrite(binLeds[twinkleLeds[i]], HIGH);
  }
  //delay(10000);
}

void shiftLeft() {
  
  for (int i = 0; i < 17; i++) {
    twinkleLeds[i] = twinkleLeds[i+1];
  }
  twinkleLeds[16] = 0;
}

bool isDuplicate(int num) {
  for (int i = 1; i < 17; i++) {
    if (twinkleLeds[i] == num) {
      return true;
    }
  }
  return false;
}

void indicator() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(binLeds[0], HIGH);
    delay(100);
    digitalWrite(binLeds[0], LOW);
  }
}

void twinkle() {
  
  digitalWrite(binLeds[twinkleLeds[0]], LOW);
  shiftLeft();
  
  int newLed = random(34);
  
  while (isDuplicate(newLed)) {
    newLed = random(34);
  }
  
  twinkleLeds[16] = newLed;
  
  digitalWrite(binLeds[twinkleLeds[16]], HIGH);
  
  delay(1000);
}

void afterBurnerOn() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(afterBurnerLeds[0][i], HIGH);
    digitalWrite(afterBurnerLeds[1][i], HIGH);
    delay(75);
  }
}

void afterBurnerOff() {
  for (int i = 3; i >= 0; i--) {
    digitalWrite(afterBurnerLeds[0][i], LOW);
    digitalWrite(afterBurnerLeds[1][i], LOW);
    delay(75);
  }
}

void binTopDown() {
  int d = 200;

  for (int i = 33; i >= 0; i--) {
//    if (i == binLedsLength-1) {
//      digitalWrite(binLeds[0], LOW);
//    }

    digitalWrite(binLeds[i], HIGH);
    delay(d);

//    if (i > 0) {
//      digitalWrite(binLeds[i-1], HIGH);
//    }
    digitalWrite(binLeds[i], LOW);
  }

  delay(d);
}

void binBottomUp() {
  int d = 200;
  
  for(int i = 0; i < binLedsLength; i++) {
    if (i == 0) {
      digitalWrite(binLeds[binLedsLength - 1], LOW);
    }
  
    digitalWrite(binLeds[i], HIGH);
    delay(d);
  
    if (i < binLedsLength - 1) {
      digitalWrite(binLeds[i+1], HIGH);
    }
    digitalWrite(binLeds[i], LOW);
  }

  delay(d);
}

void ripple(int delayyylmao) {
  int d = delayyylmao;
  
  for (int i = 1; i < 14; i++) {
    if (i == 1) {
      for (int j = 0; j < 34; j++) {
        if (binCoordinates[j][3] == 13) {
          digitalWrite(binCoordinates[j][0], LOW);
        }
      }
    }

    for (int j = 0; j < 34; j++) {
      if (binCoordinates[j][3] == i) {
        digitalWrite(binCoordinates[j][0], HIGH);
      }
    }
    delay(d);

    if (i < 13) {
      for (int j = 0; j < 34; j++) {
        if (binCoordinates[j][3] == i+1) {
          digitalWrite(binCoordinates[j][0], HIGH);
        }
      }
    }

    for (int j = 0; j < 34; j++) {
      if (binCoordinates[j][3] == i) {
        digitalWrite(binCoordinates[j][0], LOW);
      }
    }

    delay(d);
  }
}

void horizontalScan() {
  for (int i = -6; i  < 8; i++) {
    for (int j = 0; j < 34; j++) {
      if (binCoordinates[j][1] == i) {
        digitalWrite(binCoordinates[j][0], HIGH);
      }
    }
    delay(100);
    for (int j = 0; j < 34; j++) {
      if (binCoordinates[j][1] == i) {
        digitalWrite(binCoordinates[j][0], LOW);
      }
    }
  }
}

void horizontalCylon() {
  for (int i = -6; i  < 8; i++) {
    for (int j = 0; j < 34; j++) {
      if (binCoordinates[j][1] == i) {
        digitalWrite(binCoordinates[j][0], HIGH);
      }
    }
    delay(100);
    for (int j = 0; j < 34; j++) {
      if (binCoordinates[j][1] == i) {
        digitalWrite(binCoordinates[j][0], LOW);
      }
    }
  }

  for (int i = 7; i > -6; i--) {
    for (int j = 0; j < 34; j++) {
      if (binCoordinates[j][1] == i) {
        digitalWrite(binCoordinates[j][0], HIGH);
      }
    }
    delay(100);
    for (int j = 0; j < 34; j++) {
      if (binCoordinates[j][1] == i) {
        digitalWrite(binCoordinates[j][0], LOW);
      }
    }
  }
}

void verticalScan() {
  for (int i = -12; i < 12; i++) {
    for (int j = 0; j < 34; j++) {
      if (binCoordinates[j][2] == i) {
        digitalWrite(binCoordinates[j][0], HIGH);
      }
    }
    delay(100);
    for (int j = 0; j < 34; j++) {
      if (binCoordinates[j][2] == i) {
        digitalWrite(binCoordinates[j][0], LOW);
      }
    }
  }
}

void verticalCylon() {
  for (int i = -12; i < 12; i++) {
    for (int j = 0; j < 34; j++) {
      if (binCoordinates[j][2] == i) {
        digitalWrite(binCoordinates[j][0], HIGH);
      }
    }
    delay(100);
    for (int j = 0; j < 34; j++) {
      if (binCoordinates[j][2] == i) {
        digitalWrite(binCoordinates[j][0], LOW);
      }
    }
  }

  for (int i = 12; i > -12; i--) {
    for (int j = 0; j < 34; j++) {
      if (binCoordinates[j][2] == i) {
        digitalWrite(binCoordinates[j][0], HIGH);
      }
    }
    delay(100);
    for (int j = 0; j < 34; j++) {
      if (binCoordinates[j][2] == i) {
        digitalWrite(binCoordinates[j][0], LOW);
      }
    }
  }
}

void sparkle() {
  int r1 = random(34);
  int r2 = random(34);
  int r3 = random(34);
  int r4 = random(34);
  int r5 = random(34);
  int r6 = random(34);
  int r7 = random(34);
  int r8 = random(34);
  int r9 = random(34);
  int r10 = random(34);
  
  digitalWrite(binLeds[r1], HIGH);
  digitalWrite(binLeds[r2], HIGH);
  digitalWrite(binLeds[r3], HIGH);
  digitalWrite(binLeds[r4], HIGH);
  digitalWrite(binLeds[r5], HIGH);
  digitalWrite(binLeds[r6], HIGH);
  digitalWrite(binLeds[r7], HIGH);
  digitalWrite(binLeds[r8], HIGH);
  digitalWrite(binLeds[r9], HIGH);
  digitalWrite(binLeds[r10], HIGH);
  delay(500);
  digitalWrite(binLeds[r1], LOW);
  digitalWrite(binLeds[r2], LOW);
  digitalWrite(binLeds[r3], LOW);
  digitalWrite(binLeds[r4], LOW);
  digitalWrite(binLeds[r5], LOW);
  digitalWrite(binLeds[r6], LOW);
  digitalWrite(binLeds[r7], LOW);
  digitalWrite(binLeds[r8], LOW);
  digitalWrite(binLeds[r9], LOW);
  digitalWrite(binLeds[r10], LOW);
}

void allOn() {
  for (int i = 0; i < 34; i++) {
    digitalWrite(binLeds[i], HIGH);
  }
}

void loop() {

  switch(buttonPushCounter % 14) {

    case 0:
      if (flag == 0) {
        initTwinkleLeds();
        flag = 1;
      }
      twinkle();
      count++;
      if (afterBurnerFlag == 0 && count > 10) {
        afterBurnerOn();
        afterBurnerFlag = 1;
      } if (afterBurnerFlag == 1 && count > 50) {
        afterBurnerOff();
        count = 0;
        afterBurnerFlag = 0;
      }
      break;
    case 1:
      binBottomUp();
      count++;
      if (afterBurnerFlag == 0 && count > 1) {
        afterBurnerOn();
        afterBurnerFlag = 1;
      } if (afterBurnerFlag == 1 && count > 3) {
        afterBurnerOff();
        count = 0;
        afterBurnerFlag = 0;
      }
      flag = 0;
      break;
    case 2:
      binTopDown();
      count++;
      if (afterBurnerFlag == 0 && count > 1) {
        afterBurnerOn();
        afterBurnerFlag = 1;
      } if (afterBurnerFlag == 1 && count > 3) {
        afterBurnerOff();
        count = 0;
        afterBurnerFlag = 0;
      }
      flag = 0;
      break;
    case 3:
      matrix2();
      count++;
      if (afterBurnerFlag == 0 && count > 10) {
        afterBurnerOn();
        afterBurnerFlag = 1;
      } if (afterBurnerFlag == 1 && count > 20) {
        afterBurnerOff();
        count = 0;
        afterBurnerFlag = 0;
      }
      flag = 0;
      break;
    case 4:
      ripple(25);
      count++;
      if (afterBurnerFlag == 0 && count > 5) {
        afterBurnerOn();
        afterBurnerFlag = 1;
      } if (afterBurnerFlag == 1 && count > 10) {
        afterBurnerOff();
        count = 0;
        afterBurnerFlag = 0;
      }
      delay(100);
      flag = 0;
      break;
    case 5:
      ripple(300);
      count++;
      if (afterBurnerFlag == 0 && count > 5) {
        afterBurnerOn();
        afterBurnerFlag = 1;
      } if (afterBurnerFlag == 1 && count > 20) {
        afterBurnerOff();
        count = 0;
        afterBurnerFlag = 0;
      }
      delay(100);
      flag = 0;
      break;
    case 6:
      horizontalScan();
      count++;
      if (afterBurnerFlag == 0 && count > 3) {
        afterBurnerOn();
        afterBurnerFlag = 1;
      } if (afterBurnerFlag == 1 && count > 7) {
        afterBurnerOff();
        count = 0;
        afterBurnerFlag = 0;
      }
      flag = 0;
      break;
    case 7:
      verticalScan();
      count++;
      if (afterBurnerFlag == 0 && count > 3) {
        afterBurnerOn();
        afterBurnerFlag = 1;
      } if (afterBurnerFlag == 1 && count > 7) {
        afterBurnerOff();
        count = 0;
        afterBurnerFlag = 0;
      }
      flag = 0;
      break;
    case 8:
      sparkle();
      count++;
      if (afterBurnerFlag == 0 && count > 15) {
        afterBurnerOn();
        afterBurnerFlag = 1;
      } if (afterBurnerFlag == 1 && count > 30) {
        afterBurnerOff();
        count = 0;
        afterBurnerFlag = 0;
      }
      flag = 0;
      break;
    case 9:
      horizontalCylon();
      count++;
      if (afterBurnerFlag == 0 && count > 3) {
        afterBurnerOn();
        afterBurnerFlag = 1;
      } if (afterBurnerFlag == 1 && count > 7) {
        afterBurnerOff();
        count = 0;
        afterBurnerFlag = 0;
      }
      flag = 0;
      break;
    case 10:
      verticalCylon();
      count++;
      if (afterBurnerFlag == 0 && count > 3) {
        afterBurnerOn();
        afterBurnerFlag = 1;
      } if (afterBurnerFlag == 1 && count > 7) {
        afterBurnerOff();
        count = 0;
        afterBurnerFlag = 0;
      }
      flag = 0;
      break;
    case 11:
      horizontalScan();
      verticalScan();
      count++;
      if (afterBurnerFlag == 0 && count > 3) {
        afterBurnerOn();
        afterBurnerFlag = 1;
      } if (afterBurnerFlag == 1 && count > 7) {
        afterBurnerOff();
        count = 0;
        afterBurnerFlag = 0;
      }
      flag = 0;
      break;
    case 12:
      allOn();
      afterBurnerOn();
      delay(10000);
      afterBurnerOff();
      delay(10000);
      break;
    case 13:
      count++;
      if (afterBurnerFlag == 0 && count > 5) {
        afterBurnerOn();
        afterBurnerFlag = 1;
      } if (afterBurnerFlag == 1 && count > 15) {
        afterBurnerOff();
        count = 0;
        afterBurnerFlag = 0;
      }
      flag = 0;
      delay(1000);
      break;                         
  }
}
