// C++ code
//
/*
  LiquidCrystal Library - Hello World

   Demonstrates the use of a 16x2 LCD display.
  The LiquidCrystal library works with all LCD
  displays that are compatible with the  Hitachi
  HD44780 driver. There are many of them out
  there, and you  can usually tell them by the
  16-pin interface.

  This sketch prints "Hello World!" to the LCD
  and shows the time.

  The circuit:
  * LCD RS pin to digital pin 12
  * LCD Enable pin to digital pin 11
  * LCD D4 pin to digital pin 5
  * LCD D5 pin to digital pin 4
  * LCD D6 pin to digital pin 3
  * LCD D7 pin to digital pin 2
  * LCD R/W pin to ground
  * LCD VSS pin to ground
  * LCD VCC pin to 5V
  * 10K resistor:
  * ends to +5V and ground
  * wiper to LCD VO pin (pin 3)

  Library originally added 18 Apr 2008  by David
  A. Mellis
  library modified 5 Jul 2009  by Limor Fried
  (http://www.ladyada.net)
  example added 9 Jul 2009  by Tom Igoe
  modified 22 Nov 2010  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/LiquidCrystal
*/

#include <LiquidCrystal.h>

int seconds = 10;

LiquidCrystal lcd(12, 11, 7, 6, 5, 4);
#define bvermelho A0
#define bverde A1
#define verde 8
#define vermelho 9
#define buzzer 10
#define RESET asm ("jmp (0x0000)")
int seqluz[10];
int tom_vermelho = 440;
int tom_verde = 523;
int doNota = 262;
int reNota = 294;
int miNota = 330;
int faNota = 349;
int solNota = 392;
int laNota = 440;
int siNota = 494;
int bpressionado = 0;
int contador = 0;
int vitoria=0;
int pospergunta=0;
int dif=1;
String s="";
String respusu="";
int perg;
int tempo = 10000;
int x = 0;


String perguntas[] = {
  "1","3<5?","V",
  "1","5>4?","V",
  "2","5x5=10?","F",
  "2","2x3=6?","V",
  "3","Sol>Terra","V",
  "3","Pedra>Tesoura","V",
  "4","Leao>Sol","F",
  "4","Full dima>Couro","V",
  "5","Peixes voam?","F",
  "5","luz tem massa?","F",  
};




void setup()
{
  
  Serial.begin(9600);
  lcd.begin(16, 2); // Set up the number of columns and rows on the LCD.
  // Print a message to the LCD.
  attachInterrupt(digitalPinToInterrupt(2), jogoluz,FALLING);
  pinMode(bvermelho, INPUT_PULLUP); // Botao para luz vermelha
  pinMode(bverde, INPUT_PULLUP); // Botao para luz verde
  pinMode(2, INPUT_PULLUP); // Botao de Reset / Inicio
  
  pinMode(10, OUTPUT); // BUZZER
  pinMode(9, OUTPUT); // Luz vermelha
  pinMode(8, OUTPUT); // Luz verde
  randomSeed(analogRead(A0));
  
}

void melodia_derrota(){
  lcd.clear();
  lcd.print("Voce perdeu");
  tone(buzzer, siNota, 500);  // Toca Fá por 500ms
  delay(500); 
  tone(buzzer, solNota, 500);  // Toca Mi por 500ms
  delay(500);	
  tone(buzzer, miNota, 500);  // Toca Ré por 500ms
  delay(500);
  tone(buzzer, doNota, 500);  // Toca Dó por 500ms
  delay(500); 
  noTone(10);
  lcd.clear();
  RESET;
}

void melodia_correto(){
  lcd.clear();
  lcd.print("Correto");
  tone(10, doNota, 500);  // Toca Dó por 500ms
  delay(500);                 // Pausa por 500ms
  tone(10, miNota, 500);  // Toca Ré por 500ms
  delay(500);
  noTone(10);
  lcd.clear();
}

void melodia_vitoria(){
  tone(10, doNota, 500);  // Toca Dó por 500ms
  delay(500);                 // Pausa por 500ms
  tone(10, miNota, 500);  // Toca Ré por 500ms
  delay(500);
  tone(10, solNota, 500);  // Toca Mi por 500ms
  delay(500);
  tone(10, siNota, 500);  // Toca Fá por 500ms
  delay(500);
  noTone(10);
}

void pisca(int pin){
	digitalWrite(pin, HIGH);
  	delay(500); 
  	digitalWrite(pin, LOW);
  delay(500);
}

int cria_sequencia(){
	return random(1,3); 
}

void mostrar_luzes(){
  for(int i = 0; i <5; i++){
    if(seqluz[i] == 1){
    	pisca(verde);
    }
    else if(seqluz[i] == 2){
    	pisca(vermelho);
    }
  }
}

void mensagem_luz(){
  lcd.clear();
  lcd.print("Teste de");
  lcd.setCursor(0,1);
  lcd.print("Memoria");
  delay(1500);
  lcd.clear();
  lcd.print("Memorize a");
  lcd.setCursor(0,1);
  lcd.print("Sequencia");
  delay(1500);
  lcd.clear();
  lcd.print("Aperte o botao");
  lcd.setCursor(0,1);
  lcd.print("para iniciar");
  delay(1500);
  lcd.clear();
  
  
}

void mensagem_pergunta(){
  lcd.clear();
  lcd.print("Teste de");
  lcd.setCursor(0,1);
  lcd.print("Conhecimento");
  delay(1500);
  lcd.clear();
  lcd.print("Responda com");
  lcd.setCursor(0,1);
  lcd.print("V / F");
  delay(1500);
  lcd.clear();
  lcd.print("Aperte o botao");
  lcd.setCursor(0,1);
  lcd.print("Verde para seguir");
  delay(1500);
  lcd.clear();
}

int escolhepergunta(int dif){
  if(dif == 1){
    return pospergunta=3*random(0,2);
  }
  if(dif == 2){
    return pospergunta=3*random(2,4);
  }
  if(dif == 3){
    return pospergunta=3*random(4,6);
  }
  if(dif == 4){
    return pospergunta=3*random(6,8);
  }
  if(dif == 5){
    return pospergunta=3*random(8,10);
  }
}

void apresentapergunta(int perg){
  lcd.clear();
  lcd.print("Pergunta de");
  lcd.setCursor(0,1);
  lcd.print("Dificuldade:");
  lcd.setCursor(12,1);
  lcd.print(dif);
  delay(2000);
}

void mostrapergunta(int perg){
  
  lcd.clear();
  String s = perguntas[perg+1];
  lcd.print(s);
  lcd.setCursor(0,1);
}

void respondepergunta(int perg, String respusu){
  if(respusu == perguntas[perg+2]){
    Serial.println(dif);
    
    tempo = 10000;
    seconds = 10;
    perg = escolhepergunta(dif);
  } 
  else{
    melodia_derrota();
  }
}
  
void jogoluz(){
	for(int i= 0; i<5;i++){
  	seqluz[i] = cria_sequencia();
  }
  Serial.println("PRENDIO");
  for(int i = 0; i <5; i++){
  	Serial.println(seqluz[i]);
  }
  contador++;
  
}

void check_luz(int pos, int luz){
  Serial.println(pos);
  Serial.println(luz);
  if(luz == 1){
    	pisca(verde);
    }
    if(luz == 2){
    	pisca(vermelho);
    }
  if(seqluz[pos] != luz){
    melodia_derrota();
  }
}




void loop()
{
  mensagem_luz();
  lcd.clear();
  
  
  if(contador == 1){
  	mostrar_luzes();
    while(bpressionado <=4){
    
      if(digitalRead(bvermelho) == LOW){
          check_luz(bpressionado, 2);
          bpressionado++;
      }
    else if(digitalRead(bverde) == LOW){
          check_luz(bpressionado,1);
        bpressionado++;
       }
    }
    melodia_vitoria();
   
      while(x==0){
        
        mensagem_pergunta();
        
        if(digitalRead(bverde)==LOW){
          x=1;
          apresentapergunta(dif);
          }
        
      }
      perg = escolhepergunta(dif);
      while(dif <=5 && tempo >0){
        
       
        
  		mostrapergunta(perg);
        lcd.print(seconds);
        delay(1000);
        seconds--;
        tempo -= 1000;
        if(tempo == 0){
        	melodia_derrota();
        }	
        
        
        
        if(digitalRead(bvermelho) == LOW){
          pisca(vermelho);
          respondepergunta(perg,"F");
          dif++;
          perg = escolhepergunta(dif);
          Serial.println(perg);
          apresentapergunta(dif);
          
      } else if(digitalRead(bverde) == LOW){
          pisca(verde);
          respondepergunta(perg,"V");
          dif++;
          perg = escolhepergunta(dif);
          Serial.println(perg);
          apresentapergunta(dif);
          
       
      }
    }
  }
   
}

