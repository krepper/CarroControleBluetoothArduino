#include <Ultrasonic.h>

//Definicoes pinos Arduino ligados a entrada da Ponte H
int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;
int FAROL = 10;
int BUZINA = 11;
int FAROLB = 3;

#define pino_trigger 9
#define pino_echo 8


Ultrasonic ultrasonico(pino_trigger, pino_echo);



void setup()
{
  //Define os pinos como saida
 pinMode(IN1, OUTPUT);
 pinMode(IN2, OUTPUT);
 pinMode(IN3, OUTPUT);
 pinMode(IN4, OUTPUT);
 pinMode(FAROL, OUTPUT);
 pinMode(FAROLB, OUTPUT);
 pinMode(BUZINA, OUTPUT);

 Serial.begin(9600);  //Inicializa porta serial.
}

void parar()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  d_luzB();
}

void a_farol()
{
  analogWrite(FAROL, 100);
}

void ligar_b()
{
  tone(BUZINA, 1500);
}

void desligar_b()
{
  noTone(BUZINA);
}

void d_farol()
{
  analogWrite(FAROL, 0);
}

void forward()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

}

void back(){

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  a_luzB();  
}

void virar_e()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  
}

void virar_d()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void a_luzB(){
  analogWrite(FAROLB, 100); 
}

void d_luzB(){
  analogWrite(FAROLB, 0);
}

void sensorParar(){  
  long msec = ultrasonico.timing();
  
  float dCM;
  dCM = ultrasonico.convert(msec, Ultrasonic::CM);
  
  Serial.println(dCM);
  
  if (dCM < 15) { 
    parar();
  }  
  
}

void loop()
{
   sensorParar();
  
   if(Serial.available() > 0){ 
     char input = Serial.read(); 
     //Serial.println(input);
     switch(input){
       case 'F':  
         forward();
         break;
       case 'B':  
         back();
         break;
       case 'L':
         virar_e();
         break;
       case 'R':
         virar_d();
         break;
       case 'W':
         a_farol();
         break;
       case 'w':
         d_farol();
         break;
       case 'U':
         a_luzB();
         break;
       case 'u':
         d_luzB();
         break;
       case 'V':
         ligar_b();
         break;
       case 'v':
         desligar_b();
         break;
       case 'S':
         parar();
         break;
       default: break;
     }
   }
}
