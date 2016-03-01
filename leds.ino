


void setLeds(int r, int g, int b, int percent) {
  int i=round((NUMPIXELS*percent)/100)+1;
  if (i>(NUMPIXELS-1)) {
    i=NUMPIXELS-1;
  }
  int j=0;
  for (int j=0; j<NUMPIXELS;j++) {
       pixels.setPixelColor(j, pixels.Color(0,0,0)); 
       pixels.show(); // This sends the updated pixel color to the hardware.
  }
  for (int j=0; j<i;j++) {
       pixels.setPixelColor(j, pixels.Color(r,g,b)); 
       pixels.show(); // This sends the updated pixel color to the hardware.
  }
}

void updateLeds(int state, int coffeeLeft, int timeLeft, int brewingTime) {
  int i=0;
  float brewPercent=0;
  switch(state) {
   case 0 : // Empty
      for( i=0;i<NUMPIXELS;i++){
        // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
        pixels.setPixelColor(i, pixels.Color(16,0,0)); // Moderately bright red color.
     }
     pixels.show(); // This sends the updated pixel color to the hardware.
     break;
   case 1: // Brewing
       brewPercent=round((float(timeLeft)/float(brewingTime))*100);
       setLeds(0,0,16,int(brewPercent));
     break;
   case 2: // Coffee
     setLeds(0,16,00,coffeeLeft);
     break;
   case 3: // overweight
      setLeds(32,0,0,100);
     break;
     
  } 
  
}

