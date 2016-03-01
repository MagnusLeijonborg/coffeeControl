double brewingTimer=0; // timer in seconds
long startms=0;

double timer2=0;
long startms2=0;


void setTimer(int sec) {
  brewingTimer=sec;
  startms=millis();  
}

void updateTimer() {
  double delta=millis()-startms;
  brewingTimer=brewingTimer-delta/1000;
  startms=millis();
  if (brewingTimer<0)
    brewingTimer=0;
  
}

int getTimer() {
  return brewingTimer;
}



void setTimer2(int sec) {
  timer2=sec;
  startms2=millis();  
}

void updateTimer2() {
  double delta=millis()-startms2;
  timer2=timer2-delta/1000;
  startms2=millis();
  if (timer2<0)
    timer2=0;
  
}

int getTimer2() {
  return timer2;
}
