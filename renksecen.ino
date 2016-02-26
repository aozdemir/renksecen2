 
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


#define ileri digitalWrite(yol.dir, HIGH)   
#define geri  digitalWrite(yol.dir, LOW)

#define sag   digitalWrite(omuz.dir, HIGH)   
#define sol   digitalWrite(omuz.dir, LOW)

#define KOL_IN    170
#define KOL_KALK  400 
#define KOL_DONME 200

#define PAR1_AC    200 
#define PAR1_KAPA  320 

#define PAR2_AC    550 
#define PAR2_KAPA  500 


struct StepMotor
{
  int enable;
  int dir ;
  int adim;
  int hiz;
};

const int conf_yol = 5;
const int conf_omuz = 12;

const int startButton = 9;

const int hiz = 200;


enum mystate {ogren=0,topla};

mystate durum=ogren;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();


StepMotor omuz = {8,6,7,1200};
StepMotor yol  = {4,2,3,200};

int  hedef, konum=5, gelecek=4 ;

const int kol = 0 ,par1 =1 ,par2 =3;

String inputString = "";        
boolean stringComplete = false;   


void setup() {
 
 pinMode(yol.dir,OUTPUT);
 pinMode(yol.adim,OUTPUT);
 pinMode(yol.enable,OUTPUT);

 pinMode(omuz.dir,OUTPUT);
 pinMode(omuz.adim,OUTPUT);
 pinMode(omuz.enable,OUTPUT);

 pinMode(conf_yol,INPUT_PULLUP);
  pinMode(conf_omuz,INPUT_PULLUP);
 pinMode(startButton,INPUT_PULLUP);
  
 digitalWrite(yol.enable,LOW);
 digitalWrite(omuz.enable,LOW);
  
  Serial.begin(9600);
  
  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  yield();
 
  
  Serial.println("bismillahirrahmanirrahim");
  
  pwm.setPWM(kol, 0,KOL_KALK);  
while(digitalRead(conf_omuz)){sol_adim();} //Kendini sona kadar getirir
/*  
while(digitalRead(conf_yol)){geri_adim();} //Kendini sona kadar getirir
 Serial.println("DUVar");
  while(digitalRead(startButton)){} //Kendini sona kadar getirir

 
  Serial.println("basladim");
  ileri_cm(7);*/
}

void loop() {
  

switch(durum){
  case(ogren):
    durum=topla;
   break;
    case(topla):
    // sol_don();
 //   pwm.setPWM(kol, 0,KOL_IN
  //  );  
     
    /* delay(5000);
       tut();
       delay(1000);
       
        ileri_cm(31.8);
         sol_don();
        
        
        //sag_don();
     /*   sol_don();
        
        sag_don();
        delay(5000);
     /*    sag_don();
       delay(2000);
       
  
   /*  pwm.setPWM(kol, 0,KOL_KALK);
       pwm.setPWM(par1, 0,PAR1_KAPA);
        pwm.setPWM(par2, 0,PAR2_KAPA);

       
 /*   for (int pos = KOL_KALK; pos >KOL_IN; pos--) {
      pwm.setPWM(kol, 0,pos);
      delay(10);  
    }
      pwm.setPWM(kol, 0,KOL_IN);
       pwm.setPWM(par1, 0,PAR1_KAPA);
         pwm.setPWM(par2, 0,PAR2_KAPA);

     /*  Serial.println("aldım");
       ileri_cm(10);*/

       

    break;
  }

}

void geri_cm(float cm) {
  digitalWrite(yol.enable, LOW);
  geri; 
  //yol.adim motor 200 adimi 1 cm eder 6000 adim 15 esit olur.
  for (int x = 0; x < cm*200; x++) 
  {
    digitalWrite(yol.adim, HIGH); // Output high
    delayMicroseconds(yol.hiz); 
    digitalWrite(yol.adim, LOW); // Output low
    delayMicroseconds(yol.hiz); 
  }
  digitalWrite(yol.enable, HIGH);
}
void ileri_cm(float cm) {
//yol.adim motor yonunu belirle
  digitalWrite(yol.enable, LOW);
  ileri; 
  for (int x = 0; x < cm*200; x++) 
  {
    digitalWrite(yol.adim, HIGH); // Output high
    delayMicroseconds(yol.hiz); 
    digitalWrite(yol.adim, LOW); // Output low
    delayMicroseconds(yol.hiz); 
  }
   digitalWrite(yol.enable, HIGH);

}

void geri_adim(void) {
  digitalWrite(yol.enable, LOW);
  geri; 

    digitalWrite(yol.adim, HIGH); // Output high
    delayMicroseconds(yol.hiz); 
    digitalWrite(yol.adim, LOW); // Output low
    delayMicroseconds(yol.hiz); 

}

void sag_don(void) {

  digitalWrite(omuz.enable, LOW);
  sag; 
  for (int x = 0; x < KOL_DONME; x++) 
  {
    digitalWrite(omuz.adim, HIGH); // Output high
    delayMicroseconds(omuz.hiz); 
    digitalWrite(omuz.adim, LOW); // Output low
    delayMicroseconds(omuz.hiz); 
  }

}
void sag_adim(void) {

  digitalWrite(omuz.enable, LOW);
  sag; 

    digitalWrite(omuz.adim, HIGH); // Output high
    delayMicroseconds(omuz.hiz); 
    digitalWrite(omuz.adim, LOW); // Output low
    delayMicroseconds(omuz.hiz); 
  

}

void sol_don(void) {

  digitalWrite(omuz.enable, LOW);
  sol; 
  for (int x = 0; x < KOL_DONME; x++) 
  {
    digitalWrite(omuz.adim, HIGH); // Output high
    delayMicroseconds(omuz.hiz); 
    digitalWrite(omuz.adim, LOW); // Output low
    delayMicroseconds(omuz.hiz);
  }
}

void sol_adim(void) {

  digitalWrite(omuz.enable, LOW);
  sol; 

    digitalWrite(omuz.adim, HIGH); // Output high
    delayMicroseconds(omuz.hiz); 
    digitalWrite(omuz.adim, LOW); // Output low
    delayMicroseconds(omuz.hiz);
  
}
void tut(){

  //parmaklar açılır  kol asagı iner --renke bakar--  parmaklar kapanır  kol kalkar 
  pwm.setPWM(par1, 0,PAR1_AC);
  pwm.setPWM(par2, 0,PAR2_AC);
  delay(100);
  
    for (int pos = KOL_KALK; pos >KOL_IN; pos--) {
      pwm.setPWM(kol, 0,pos);
      delay(10);  
    }
   delay(1000);
   pwm.setPWM(par1, 0,PAR1_KAPA);
   pwm.setPWM(par2, 0,PAR2_KAPA);

    delay(100);

      for (int pos = KOL_IN; pos < KOL_KALK; pos++) {
      pwm.setPWM(kol, 0,pos);
      delay(10);  
    }
  delay(1000);
}
void birak(){
  
    for (int pos = KOL_KALK; pos >KOL_IN; pos--) {
         pwm.setPWM(kol, 0,pos);
          delay(10);  
      }

      pwm.setPWM(par1, 0,PAR1_AC);
      pwm.setPWM(par2, 0,PAR2_AC);
      delay(100);

     for (int pos = KOL_IN; pos < KOL_KALK; pos++) {
    pwm.setPWM(kol, 0,pos);
    delay(10);  
     }
  
  }

