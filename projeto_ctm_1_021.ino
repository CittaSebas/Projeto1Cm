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

int seconds = 9;

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
int x = 0;
int vidas = 1;


String perguntas[] = {
  "1","Baleias sao repteis?","F",
  "1","Latvia significa Letonia?","V",
  "2","Um byte sao 8 bits?","V",
  "2","Este LCD tem RGB?","F",
  "3","Orcas sao golfinhos?","V",
  "3","AMD compete com a Intel?","V",
  "4","Dentes sao ossos?","F",
  "4","Buzzer emite som?","V",
  "5","Polvos tem 3 coracoes?","V",
  "5","Luz tem massa?","F",
  "6","3 eh um numero primo?","V",
  "7","3>(5**0.2)","V"
};




void setup()
{
  
  Serial.begin(9600);
  lcd.begin(16, 2); // Set up do LCD 16 x 2
  attachInterrupt(digitalPinToInterrupt(2), jogoluz,FALLING); // Botao de interrupcao
  pinMode(bvermelho, INPUT_PULLUP); // Botao para luz vermelha
  pinMode(bverde, INPUT_PULLUP); // Botao para luz verde
  pinMode(2, INPUT_PULLUP); // Botao de Reset / Inicio
  
  pinMode(10, OUTPUT); // BUZZER
  pinMode(9, OUTPUT); // Luz vermelha
  pinMode(8, OUTPUT); // Luz verde
  randomSeed(analogRead(2));
  
}

void scrollTexto(String pergunta) {
  //Recebe uma String, que se necessario ativara um scroll
  lcd.clear();
  int len = pergunta.length();
  
  // Se a pergunta couber no display, apenas mostre
  if (len <= 16) {
    lcd.print(pergunta);
    delay(1000); 
  } else {
    //Scroll da pergunta, iterando sobre a len
    for (int i = 0; i < len - 15; i++) {
      lcd.setCursor(0,0);
      lcd.print(pergunta.substring(i, i + 16)); 
      delay(300); 
    } 
    delay(700);
}
}
//Diversas melodias com uso do RESET -----------
void melodia_derrota(){
  tone(buzzer, siNota, 500);
  delay(500); 
  tone(buzzer, solNota, 500);
  delay(500);	
  tone(buzzer, miNota, 500);
  delay(500);
  tone(buzzer, doNota, 500);
  delay(500); 
  noTone(10);
  RESET;
}
void melodia_errou(){
  tone(buzzer, siNota, 500);
  delay(500); 
  tone(buzzer, solNota, 500);
  delay(500);	
}
void melodia_correto(){
  tone(10, doNota, 300); 
  delay(300);
  tone(10, miNota, 200);  
  delay(200);
  noTone(10);
}
void som_tempo(){
  tone(10, doNota, 200);  
  delay(100);                
  tone(10, siNota, 100);  
  delay(100);
  noTone(10);
}
void som_tempo_esgotado(){
  tone(10, siNota, 200);  
  delay(100);                
  tone(10, doNota, 100);  
  delay(100);
  noTone(10);
}


void melodia_vitoria(){
  tone(10, doNota, 500);
  delay(500);            
  tone(10, miNota, 500);
  delay(500);
  tone(10, solNota, 500);
  delay(500);
  tone(10, siNota, 500); 
  delay(500);
  noTone(10);
}
void melodia_vitoria2(){
  tone(10, doNota, 500);
  delay(500);            
  tone(10, doNota, 200);
  delay(200);
  tone(10, reNota, 500);
  delay(500);
  tone(10, solNota, 500); 
  delay(500);
  tone(10, faNota, 200); 
  delay(200);
  tone(10, faNota, 200); 
  delay(200);
  tone(10, faNota, 200); 
  delay(200);
  noTone(10);
}

// ----------  Fim das melodias

// Funcoes para facilitar a escrita e leitura do codigo -------
void pisca(int pin){
  //Recebe o pin de um LED, liga ele e faz um som respectivo
	digitalWrite(pin, HIGH);
  if(pin == 1){
  	tone(10, tom_verde, 300);
    
  }
  else{
  	tone(10, tom_vermelho, 300);
  }
  delay(350); 
  noTone(10);
  digitalWrite(pin, LOW);
  delay(400);
}

int cria_sequencia(){
	return random(1,3); 
}

void mostrar_luzes(){
  lcd.setCursor(0,0);
  lcd.print("Memorize a ");
  lcd.setCursor(0,1);
  lcd.print("sequencia!");
  //Mostra a combinacao de luzes a ser seguida
  for(int i = 0; i <=9; i++){
    if(seqluz[i] == 1){
    	pisca(verde);
    }
    else if(seqluz[i] == 2){
    	pisca(vermelho);
    }
  }
  scrollTexto("Sua vez!");
  lcd.setCursor(0,1);
  delay(600);
  lcd.clear();
}
void mensagem_luz(){ 
  //Escreve a mensagem a ser repetida no loop
  lcd.clear();
  lcd.print("Teste de");
  lcd.setCursor(0,1);
  lcd.print("Memoria");
  delay(1000);
  lcd.clear();
  lcd.print("Aperte o botao");
  lcd.setCursor(0,1);
  lcd.print("para iniciar");
  delay(1000);
  lcd.clear();
}

void mensagem_pergunta(){
  //Escreve a mensagem a ser repetida no loop
  lcd.clear();
  lcd.print("Teste de");
  lcd.setCursor(0,1);
  lcd.print("Conhecimento");
  delay(1000);
  lcd.clear();
  lcd.print("Responda com");
  lcd.setCursor(0,1);
  lcd.print("V / F");
  delay(1000);
  lcd.clear();
  lcd.print("Segure o botao");
  lcd.setCursor(0,1);
  lcd.print("Verde p/ seguir");
  delay(1500);
  lcd.clear();
}

int escolhepergunta(int dif){
  // Recebe a quantidade de perguntas respondidas e retorna uma
  // posicao no array com a pergunta aleatoriamente escolhida
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
  if(dif == 6){
  	return pospergunta=3*random(10,11);
  }
}


void mostrapergunta(int perg){
  // Recebe a posicao de uma pergunta e a mostra
  lcd.clear();
  lcd.print("Pergunta ");
  lcd.setCursor(9,0);
  lcd.print(dif);
  lcd.setCursor(11,0);
  lcd.print(" / 5");
  delay(1000);
  lcd.clear();
  String s = perguntas[perg+1];
  lcd.setCursor(0,0);
  scrollTexto(s);
  delay(1500);
  lcd.clear();
}

void mostra_tempo(int tempo){
  // Recebe e mostra o tempo que o usuario tem
  //caso tiver metade do tempo toca um som
  lcd.setCursor(3,0);
  lcd.print("Tempo: ");
  lcd.setCursor(12, 0);
  lcd.print(tempo);
  lcd.setCursor(2,1);
  lcd.print("Sim  ou");
  lcd.setCursor(12,1);
  lcd.print("Nao");
   if(tempo <6){
     som_tempo();
        }
}
void respondepergunta(int perg, String respusu) {
  // Recebe a posicao de uma pergunta e a resposta do usuario
  // e compara as respostas para verificar o resultado
  lcd.clear();
  if (perguntas[perg + 2].equals("V")) {
 		//Mostram a resposta correta da pergunta
    lcd.setCursor(1, 1);
    lcd.print("*Sim  ou");
    lcd.setCursor(12, 1);
    lcd.print("Nao");
    delay(500);
  } else {
    lcd.setCursor(2, 1);
    lcd.print("Sim  ou");
    lcd.setCursor(11, 1);
    lcd.print("*Nao");
    delay(500);
  }
  
  // Verificacao da resposta com base na posicao do array
  if (respusu.equals(perguntas[perg + 2])) {
    lcd.setCursor(0, 0);
    lcd.print("Resposta Correta!");
    melodia_correto();
    if(dif == 6){
      //Maneja o caso de vitoria do usuario
      lcd.clear();
      lcd.print("Voce ganhou!!");
      delay(500);
      melodia_vitoria2();
    }

  } else { 
    //Maneja resposta errada e toca o seu som
    lcd.setCursor(0,0);
    lcd.print("Voce errou!");
    melodia_errou();
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Fim de Jogo!");
    delay(1000);
    RESET;  // Reinicia o jogo
  }
}

  
void jogoluz(){
  //Incrementa um contador para manejar o desistir
  // e iniciar o jogo das luzes
  contador++;
	for(int i= 0; i<=9;i++){
  	seqluz[i] = cria_sequencia();
      Serial.println(seqluz[i]);
  }
}

void check_luz(int pos, int luz){
  // Recebe a quantidade de inputs do usuario e o input atual
  // e verifica se a resposta esta correta, utilizando o array 
  // da sequencia gerada aleatoriamente
  if(seqluz[pos] != luz){
    //Caso o usuario errar, toca a melodia de derrota
    // e mostra o quanto o usuario acertou
    lcd.clear();
    scrollTexto("Sequencia errada");
    lcd.setCursor(0,1);
    lcd.print(bpressionado);
    lcd.setCursor(3, 1);
    lcd.print("de 10");
    lcd.setCursor(7, 1);
    melodia_derrota();
  }
  else{
    //Faz a respectiva luz piscar e mostra os acertos do usuario
  	if(luz == 1){
      lcd.setCursor(0,0);
      lcd.print("Sequencia:");
      lcd.setCursor(11,0);
      lcd.print(bpressionado+1);
      lcd.setCursor(0,1);
      lcd.print("Correto");
      pisca(verde);
      }
    if(luz == 2){
      lcd.setCursor(0,0);
      lcd.print("Sequencia:");
      lcd.setCursor(11,0);
      lcd.print(bpressionado+1);
      lcd.setCursor(0,1);
      lcd.print("Correto");
      pisca(vermelho);
    }
  }
}

void loop()
{
  int uperg;
  if(contador == 2){
    //Desiste (reseta) caso o contador for incrementado 2x
    // e toca o seu som respectivo
    lcd.clear();
    lcd.print("Voce desistiu!");
    delay(1000);
    tone(10, solNota, 200);
    delay(200);
    tone(10, doNota, 200);
    delay(200);
    tone(10, solNota, 200);
    delay(200);
    tone(10, solNota, 200);
    delay(200);
    delay(1000);
    RESET;
  }
  //Chama a mensagem e limpa caso terminar de mostrar a mensagem
  mensagem_luz();
  lcd.clear();
  if(contador == 1){
    //Quando o botao (2) ser pressionado mostra a sequencia gerada
    mostrar_luzes();
    delay(1000);
    while(bpressionado <=9 && contador ==1){
      //Mantem o codigo nessa parte ate o usuario apertar pelo
      // menos 1x vez
    if(digitalRead(bvermelho) == LOW){
      //Verifica e incrementa o input e seu contador
      check_luz(bpressionado, 2);
      bpressionado++;
      }
    else if(digitalRead(bverde) == LOW){
      check_luz(bpressionado,1);
      bpressionado++;
       }
    }
    if(contador == 1){
      //Toca musica de vitoria da primeira fase
      melodia_vitoria();
    }
    while(x==0 && contador == 1){
      
      //Mantem o codigo no loop ate o usuario segurar o botao
      mensagem_pergunta();
      if(digitalRead(bverde)==LOW){
        // Incrementa o contador e sai do loop while
        x=1;
      }
    }
    if(contador ==1){
      //Escolhe e mostra a primeira pergunta
      //checkando se o usuario nao desistiu
      perg = escolhepergunta(dif);
      mostrapergunta(perg);
    }
    while(dif <=6 && seconds >0 && contador == 1){ 
      
      
      //Mantem o codigo no loop while e mostra/atualiza o tempo
      mostra_tempo(seconds);
      delay(1200);
      seconds--;
      if(seconds == 0 && vidas == 1){
        //Maneja o caso do usuario pular uma questao com uso
        // de um contador de vidas e um som respectivo
        seconds = 9;
        lcd.clear();
        lcd.print("Pergunta pulada");
        delay(600);
        som_tempo_esgotado();
        vidas--;
        perg = 33;
        mostrapergunta(perg);
        }
      if(seconds == 0 && vidas == 0){
        //Maneja o caso do usuario esgotar o tempo e a vida
        lcd.clear();
        lcd.print("Tempo esgotado!");
        melodia_derrota();
        }	
      if(digitalRead(bvermelho) == LOW){
        //Pisca a resposta F e chama a funcao de resposta
        // Tambem atualiza contadores e variaveis 
        pisca(vermelho);
        respondepergunta(perg,"F");
        dif++;
        seconds = 9;
        if(dif == 6){
          //Maneja o caso da pergunta final que tem local fixo
          lcd.clear();
          lcd.print("Pergunta Final!");
          delay(1000);
          lcd.clear();
          perg = escolhepergunta(dif);
          scrollTexto(perguntas[perg+1]);
        }
        else if(dif <6){
          //Maneja os casos das perguntas normais (1 a 5)
        perg = escolhepergunta(dif);
     	mostrapergunta(perg);
          seconds = 9;
        }
      } 
      else if(digitalRead(bverde) == LOW){
        // Maneja a resposta V e chama a funcao de resposta
        // Tambem atualiza contadores e variaveis
        pisca(verde);
        respondepergunta(perg,"V");
        dif++;
        seconds = 9;
        if(dif == 6){
          //Maneja o caso da pergunta final
          lcd.clear();
          lcd.print("Pergunta Final!");
          delay(1000);
          lcd.clear();
          perg = escolhepergunta(dif);
          scrollTexto(perguntas[perg+1]);
          lcd.clear();
        }
        else if(dif <6){
          //Maneja os casos das perguntas normais (1 a 5)
        perg = escolhepergunta(dif);
      	mostrapergunta(perg);
        }
      }
  
    }
  }
}

