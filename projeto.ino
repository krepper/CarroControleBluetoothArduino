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

void parar() // PARA O CARRINHO
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  d_luzB();
}

void a_farol() // LIGA O FAROL
{
  analogWrite(FAROL, 100);
}

void ligar_b() // LIGA A BUZINA
{
  tone(BUZINA, 1500);
}

void desligar_b() // DESLIGA A BUZINA
{
  noTone(BUZINA);
}

void d_farol() // DESLIGA O FORAL 
{
  analogWrite(FAROL, 0);
}

void forward() // VAI PARA FRENTE
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

}

void back(){ // VAI PARA TRÁS

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  a_luzB();  
}

void virar_e() // VIRA PARA ESQUERDA
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  
}

void virar_d() // VIRA PARA DIREITA
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void a_luzB(){ // LIGA LUZ TRASEIRA
  analogWrite(FAROLB, 100); 
}

void d_luzB(){  // DESLIGA LUZ TRASEIRA
  analogWrite(FAROLB, 0);
}

void sensorParar(){   //VERIFICA O ULTRA SONICO, SE DISTANCIA FOR MENOR QUE 15, O CARRINHO PARA 
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
