/*
 One Time Password
 
 */

#include "sha1.h" 
#include <stdarg.h>


void printHash(uint8_t* hash, int length) {
  int i;
  for (i=0; i<length; i++) {
    Serial.print("0123456789abcdef"[hash[i]>>4]);
    Serial.print("0123456789abcdef"[hash[i]&0xf]);
  }
  Serial.println();
}


void setup()  { 
   
  uint8_t* hash;
  uint8_t otp[4];
  uint32_t a;
  
  Serial.begin(9600);
  
  uint8_t hmacKey1[]={
   0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x21, 0xde, 0xad, 0xbe, 0xef 
};

uint8_t time[]={
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 
};

//5eed967e4fc91e989612e84f44e5b7984ecf059e

  Serial.print("Secret : ");
  printHash(hmacKey1, 10);
  
  long epoch = 1326025119 / 30;
  time[4] =  (byte )((epoch >> 24) & 0xff);
  time[5] = (byte )((epoch >> 16) & 0xff);
  time[6] = (byte )((epoch >> 8) & 0xff);
  time[7] = (byte )((epoch ) & 0xff);
  
  Serial.print("Time : ");
  printHash(time, 8);

  Sha1.initHmac(hmacKey1, 10);
  Sha1.writebytes(time, 8);

  hash = Sha1.resultHmac();      
  Serial.print("HMAC : ");   
  printHash(hash, 20);
  
  memset(otp,0,4);
  int offset = hash[19] & 0x0f;
  memcpy(otp, hash + offset, 4);
  
  unsigned long o=0x22000000;
  unsigned long l= 0x7FFFFFFF;
  long val = ((long )otp[0] & 0x7F) << 24;
  val |= ((long )otp[1]) << 16;
  val |= ((long )otp[2]) << 8;
  val |= otp[3];
  
  val = val % 1000000;
  
  Serial.print("Code : ");   //needs to be left padded
  Serial.println(val);
  
  
   
  
} 

void loop()  { 
 
  // wait for 30 milliseconds to see the dimming effect    
  delay(30);                            
}


