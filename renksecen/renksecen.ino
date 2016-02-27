
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

//#define DEBUG
//omuz alt step

#define ileri digitalWrite(yol.dir, HIGH)   
#define geri  digitalWrite(yol.dir, LOW)

#define sag   digitalWrite(omuz.dir, HIGH)   
#define sol   digitalWrite(omuz.dir, LOW)

#define KOL_IN    170
#define KOL_KALK  400 
#define KOL_DONME 400


#define PAR1_AC    220 
#define PAR1_KAPA  320 

#define PAR2_AC    500
#define PAR2_KAPA  400 


struct StepMotor
{
  int enable;
  int dir ;
  int adim;
  int hiz;
};

//tcs pinleri
const int s0 = 12 ;
const int s1 = A1;
const int s2 = 11;
const int s3 = A0;
const int out = A2;

//led
const int led=10;

//button pinleri
const int conf_yol = 5;
const int conf_omuz = 13;
const int startButton = 9;

const int hiz = 200;


int red = 0;
int green = 0;
int blue = 0;


char renk;
char oku[7];
float x;
int pos, hedef, konum=5, gelecek=4, i=0 ,  t;


enum mystate {ogren=0,topla};

mystate durum=ogren;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();


StepMotor omuz = {8,6,7,1800};
StepMotor yol  = {4,2,3,150};



const int kol = 0 ,par1 =1 ,par2 =3;

String inputString = "";        
boolean stringComplete = false;   


void setup() {
  //sensor
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);
  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);


   //step motorlar
   pinMode(yol.dir,OUTPUT);
   pinMode(yol.adim,OUTPUT);
   pinMode(yol.enable,OUTPUT);
   digitalWrite(yol.enable,LOW);

   pinMode(omuz.dir,OUTPUT);
   pinMode(omuz.adim,OUTPUT);
   pinMode(omuz.enable,OUTPUT);
   digitalWrite(omuz.enable,LOW);
   
   //buttonlar
   pinMode(conf_yol,INPUT_PULLUP);
   pinMode(conf_omuz,INPUT_PULLUP);
   pinMode(startButton,INPUT_PULLUP);

   //led
   pinMode(led,OUTPUT);
    
   
    Serial.begin(9600);
    
    pwm.begin();
    
    pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

    yield();
   
    
    Serial.println("bismillahirrahmanirrahim");
    digitalWrite(led,HIGH);
    pwm.setPWM(kol, 0,KOL_KALK);  

    while(digitalRead(conf_omuz)){sol_adim();} //Kendini sona kadar getirir
    
    while(digitalRead(conf_yol)){geri_adim();} //Kendini sona kadar getirir
   
    Serial.println("DUVar");
    
    while(digitalRead(startButton)){} //Kendini sona kadar getirir

   
    Serial.println("basladim");
    ileri_cm(7);
    durum=ogren;   
}

void loop() {
  

switch(durum){
  case(ogren):
      
      oku[i]=renkBul();
      ileri_cm(31.8);
      i++; 
      if(i>=5){
        oku[i]=renkBul();
        Serial.println(oku);
        i=0;
        durum=topla;   
      }   
   break;
    case(topla):
      tut();
      
      Serial.println(renk);
      hedef=hedefBul(); 

      if(hedef==6)
          Serial.println("hedef taninmadi");
      Serial.print(oku);
      Serial.print("Konum:");
      Serial.print(konum);
      Serial.print("Birakilacak Yer:");
      Serial.print(hedef);
      Serial.print("Siradaki:");
      Serial.println(gelecek);
      if((hedef>konum))
        ileri_cm((hedef-konum)*31.8);
      else
        geri_cm((konum-hedef)*31.8);
      birak();
      Serial.print("biraktim");
      konum=hedef;
      if((gelecek>konum))
        ileri_cm((gelecek-konum)*31.8);
      else
        geri_cm((konum-gelecek)*31.8);
        konum=gelecek;
      
      if(gelecek==-1){
      while(1);
      }
      gelecek--;
    break;
  }
  delay(200);
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
void sol_adim(void) {

  digitalWrite(omuz.enable, LOW);
  sol; 

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

void tut(){

  sag_don();


  //parmaklar açılır  kol asagı iner --renke bakar--  parmaklar kapanır  kol kalkar 
  pwm.setPWM(par1, 0,PAR1_AC);
  pwm.setPWM(par2, 0,PAR2_AC);
  
 // delay(100);
  
    for (int pos = KOL_KALK; pos >KOL_IN; pos--) {
      pwm.setPWM(kol, 0,pos);
      delay(5);  
    }
   delay(500);
   color();

   pwm.setPWM(par1, 0,PAR1_KAPA);
   pwm.setPWM(par2, 0,PAR2_KAPA);

 //   delay(100);

      for (int pos = KOL_IN; pos < KOL_KALK; pos++) {
      pwm.setPWM(kol, 0,pos);
      delay(5);  
    }
  delay(500);
  sol_don();
}

void birak(){
  
    for (int pos = KOL_KALK; pos >KOL_IN; pos--) {
         pwm.setPWM(kol, 0,pos);
          delay(5);  
      }

      pwm.setPWM(par1, 0,PAR1_AC);
      pwm.setPWM(par2, 0,PAR2_AC);
    //  delay(100);

     for (int pos = KOL_IN; pos < KOL_KALK; pos++) {
    pwm.setPWM(kol, 0,pos);
    delay(5);  
     }
  
  }

void color()
{
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s3, HIGH);
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s2, HIGH);
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);

  if (red < blue && red < green && green > blue)
    renk = 'K';
  else if (blue < red && blue < green)
    renk = 'M';
  else if (green < red && green < blue)
    renk = 'Y';
  else if (red < blue && red < green && green < blue) 
    renk = 'S';
   Serial.print(renk);

}


char renkBul(){
    //alt servo 90
    //dirsekServo 50 - 0
    //color()
    //koldaki dirsek servoyu kibarca yere indir
     while(digitalRead(conf_omuz)){sol_adim();}
    pwm.setPWM(par1, 0,PAR1_AC);
    pwm.setPWM(par2, 0,PAR2_AC);


    //altServo.write(0);
    for (int pos = KOL_KALK; pos >KOL_IN; pos--) {
      pwm.setPWM(kol, 0,pos);
      delay(5);  
    }

    delay(200);
    color(); //rengi bul
    
    //koldaki dirsek servoyu kaldir
    for (int pos = KOL_IN; pos < KOL_KALK; pos++) {
      pwm.setPWM(kol, 0,pos);
      delay(5);  
    }
    //color ile elde ettigin rengi donder
    return renk;
}

int hedefBul(){
  for(t=5;t>=0;t--){
  if(renk==oku[t]) {
    oku[t]='0';
    return t;
    }
}
  return 6;
}
