int oldState=0;


int setState() {
 if (weight<=(empty+margin)) { // detect empty
    state=0;
 }
 else // not empty 
 {
   if (weight>=full+margin*1000) {  // overful
     state=3;
   } 
   else // not overful
   {  
     if ((weight>=full-margin) & (state==0)) { // detect brewing and reset brewing timer
        setTimer(brewingTime);
        state=1; 
     }
     else {
       if ((state==1) & (getTimer()==0)) { // detect finnished brewing
         state=2;
       }
     }
   } 
 }
 if (oldState!=state) {
   updateServer();
   oldState=state;
 }
}



