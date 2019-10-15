 const int lan1 = 15;
const int lan2 = 19;
const int lan3 = 20;
const int lan4 = 21;
const int lan5 = 14;
const int lan6 = 13;
const int lan7 = 12;
const int lan8 = 11;
const int lan9 = 10;
const int lan10 = 9;
const int lan11 = 8;
const int lan12 = 7;
const int lan13 = 6;
const int lan14 = 5;
const int lan15 = 4;
const int lan16 = 3;
const int lan17 = 2;
const int lan18 = 1;
const int lan19 = 0;
const int lan20 = 85;
int lans[2][20] = {{lan1, lan2, lan3, lan4, lan5, lan6, lan7, lan8, lan9, lan10, lan11, lan12, lan13, lan14, lan15, lan16, lan17, lan18, lan19, lan20},
{lan20, lan19, lan18, lan17, lan16, lan15, lan14, lan13, lan12, lan11, lan10, lan9, lan8, lan7, lan6, lan5, lan4, lan3, lan2, lan1}};
int lanLedsLength = sizeof(lans[0]) / sizeof(lan1);
int buttonPushCounter = 0;

void setup() {
  // put your setup code here, to run once:
  for(int i = 0; i < lanLedsLength; i++) {
    pinMode(lans[0][i], OUTPUT);
  }

  attachInterrupt(digitalPinToInterrupt(34), decision, RISING);
}

static unsigned long last_interrupt_time = 0;
void decision() {
  
  unsigned long interrupt_time = millis();

  if (interrupt_time - last_interrupt_time > 200) {
    //digitalWrite(1, HIGH);
    buttonPushCounter++;
  }
  last_interrupt_time = interrupt_time;
}

void randomLan2Way(int delayyylmao, int isRandom) {
  int d;
  int r;

  if (isRandom) {
    d = random(delayyylmao);
    r = d % 2;
  } else {
    d = delayyylmao;
    r = random(100) % 2;
  }
  
  for(int i = 0; i < lanLedsLength; i++) {
    if (i == 0) {
      digitalWrite(lans[r][lanLedsLength - 1], LOW);
    }
  
    digitalWrite(lans[r][i], HIGH);
    delay(d);
  
    if (i < lanLedsLength - 1) {
      digitalWrite(lans[r][i+1], HIGH);
    }
    digitalWrite(lans[r][i], LOW);
  }

  delay(d);
}

void randomLan(int delayyylmao, int isRandom) {
  int d;
  int r = 0;

  if (isRandom) {
    d = random(delayyylmao);
  } else {
    d = delayyylmao;
  }
  
  for(int i = 0; i < lanLedsLength; i++) {
    if (i == 0) {
      digitalWrite(lans[r][lanLedsLength - 1], LOW);
    }
  
    digitalWrite(lans[r][i], HIGH);
    delay(d);
  
    if (i < lanLedsLength - 1) {
      digitalWrite(lans[r][i+1], HIGH);
    }
    digitalWrite(lans[r][i], LOW);
  }

  delay(d);
}

void cycle(int r, int j,  int d) {
  //int d = random(100);
  
  if(r) {
    for(int i = j; i < lanLedsLength; i++) {
      digitalWrite(lans[0][i], HIGH);
      delay(d);
    
      if (i < lanLedsLength - 1) {
        digitalWrite(lans[0][i+1], HIGH);
      }
      digitalWrite(lans[0][i], LOW);
    }
    delay(d);
    digitalWrite(lans[0][19], LOW);
  } else {
    for(int i = j; i > 0; i--) {
      digitalWrite(lans[0][i], HIGH);
      delay(d);
    
      if (i > 0) {
        digitalWrite(lans[0][i-1], HIGH);
      }
      digitalWrite(lans[0][i], LOW);
    }
    delay(d);
    digitalWrite(lans[0][0], LOW);
  }
}

void middleOut(int delayyylmao, int isRandom) {
  int d;
  int mid = lanLedsLength / 2;
  int j = 9;

  if (isRandom) {
    d = random(delayyylmao);
  } else {
    d = delayyylmao;
  }
  
  for(int i = mid; i < lanLedsLength; i++) {
      digitalWrite(lans[0][i], HIGH);
      digitalWrite(lans[0][j], HIGH);
      delay(d);
    
      if (i < lanLedsLength - 1) {
        digitalWrite(lans[0][i+1], HIGH);
      } else if(j > 0) {
        digitalWrite(lans[0][j-1], HIGH);
      }
      digitalWrite(lans[0][i], LOW);
      digitalWrite(lans[0][j], LOW);
      j--;
    }
    delay(d);
    digitalWrite(lans[0][lanLedsLength -1], LOW);
    digitalWrite(lans[0][0], LOW);
}

void cylon(int reverse) {
  int d = 37;
  int r = reverse;
  
  for(int i = 0; i < lanLedsLength; i++) {
    if (i == 0) {
      digitalWrite(lans[r][lanLedsLength - 1], LOW);
    }
  
    digitalWrite(lans[r][i], HIGH);
    delay(d);
  
    if (i < lanLedsLength - 1) {
      digitalWrite(lans[r][i+1], HIGH);
    }
    digitalWrite(lans[r][i], LOW);
  }
}

void fiveAtATime(int delayyylmao, int isRandom) {
  int d;
  int r = 0;
  int j = -1;
  int k = -2;
  int l = -3;
  int m = -4;

  if (isRandom) {
    d = random(delayyylmao);
  } else {
    d = delayyylmao;
  }
  
  for(int i = 0; i < lanLedsLength+4; i++) {
    if (i < lanLedsLength) {
      digitalWrite(lans[r][i], HIGH);
    } if (i > 0 && j < lanLedsLength) {
      digitalWrite(lans[r][j], HIGH);
    } if (i > 1 && k < lanLedsLength) {
      digitalWrite(lans[r][k], HIGH);
    } if (i > 2 && l < lanLedsLength) {
      digitalWrite(lans[r][l], HIGH);
    } if (i > 3 && m < lanLedsLength) {
      digitalWrite(lans[r][m], HIGH);
    }
    delay(d);
  
    if (i < lanLedsLength - 1) {
      digitalWrite(lans[r][i+1], HIGH);
    } if (j >= 0 && j < (lanLedsLength - 1)) {
      digitalWrite(lans[r][j+1], HIGH);
    } if (k >= 0 && l < (lanLedsLength - 1)) {
      digitalWrite(lans[r][k+1], HIGH);
    } if (l >= 0 && l < (lanLedsLength - 1)) {
      digitalWrite(lans[r][l+1], HIGH);
    } if (m >= 0 && m < (lanLedsLength - 1)) {
      digitalWrite(lans[r][m+1], HIGH);
    }

    if (i < lanLedsLength) {
      digitalWrite(lans[r][i], LOW);
    } if (j >= 0 && j < lanLedsLength) {
      digitalWrite(lans[r][j], LOW);
    } if (k >= 0 && k < lanLedsLength) {
      digitalWrite(lans[r][k], LOW);
    } if (l >= 0 && l < lanLedsLength) {
      digitalWrite(lans[r][l], LOW);
    } if (m >= 0 && m < lanLedsLength) {
      digitalWrite(lans[r][m], LOW);
    }

    j++;
    k++;
    l++;
    m++;
  }

  if (isRandom) {
    delay(random(d*50));
  } else {
    delay(315);
  }
}

void loop() {
  
  switch(buttonPushCounter % 10) {
    case 0:
      randomLan(63, 0);
      break;
    case 1:
      randomLan(63, 1);
      break;  
    case 2:
      randomLan2Way(50, 0);
      break;
    case 3:
      randomLan2Way(50, 1);
      break;
    case 4:
      middleOut(100, 0);
      break;
    case 5:
      middleOut(100, 1); 
      break; 
    case 6:
      cylon(0);
      cylon(1);
      break;
    case 7:
      fiveAtATime(63, 0);
      break;
    case 8:
      fiveAtATime(63, 1);
      break;
    case 9:
      delay(100);
      break;    
  }
}
