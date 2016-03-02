

void storeInt(int adress,int val) {
  EEPROM.write(adress,val);
  EEPROM.write(adress+1,val>>8);
  
  
}

int getInt(int adress) {
  int val;
  val=EEPROM.read(adress+1);
  val=val<<8;
  val=val+EEPROM.read(adress);
  return val;
}
