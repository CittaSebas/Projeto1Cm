# Projeto 1 Computação Móvel
Problema:
Criar um projeto no Arduino que simule um jogo de memória e perguntas. O jogo de memória deve funcionar com duas luzes LED, que serão acesas aleatoriamente 10 vezes. Após aparecerem todas as luzes, o usuário deve repetir a sequência corretamente.
Caso o usuário consiga replicar a sequência, ele avança para a fase de perguntas, que consiste em 5 perguntas aleatórias e uma pergunta final fixa. Se o usuário também conseguir responder corretamente ao jogo de perguntas, ele ganha.

Objetivo:


Metodo de Resolução:

Materiais:
  Arduino UNO
  1 Led Vermelho
  1 Led Verde
  3 botões
  4 Resistores
  1 Buzzer
  1 Display LCD 16x2
  1 Potenciômetro
  2 Protoboard

Imagem do Circuito no Tinkercad:
![image](https://github.com/user-attachments/assets/9697e375-2ff2-4493-8353-b050ed69bfe6)

Funcionamento do Programa:

Apertando o botão marcado com amarelo, começara a sequencia de luzes 
![image](https://github.com/user-attachments/assets/b8c6c3f4-df9f-4d3f-bc66-988cf3fc8a14) 

Os led serão ligados juntos um total de 10 vezes
![image](https://github.com/user-attachments/assets/ec2424f8-29e2-40ed-80aa-b2f4cbcf6a89)

Após esta sequencia, aperte os botões marcados para escolher. A luz vermelha representa o botão marcado com a cor Vermelho-alaranjado, e a luz verde representa o botão marcado com a cor Verde.
![image](https://github.com/user-attachments/assets/285f76bb-1a43-46a9-9879-73d1ae8cd9cf)

Caso o usuário acerte tocara uma música para celebrar sua vitória. Na sequência começara o jogo de Perguntas, o jogo não começará até o usuário apertar o botão da Luz Verde
Verdadeiro é representado pelo botão da Luz Verde, e o Falso é representado pelo botão da Luz Vermelha
![image](https://github.com/user-attachments/assets/665fcb23-bcce-4408-b6b1-b1082d91e1fd)

Após o usuário começar o jogo, ele tem 10 segundos por pergunta para responder-las.

Caso acertar as 5 perguntas, tocara uma música declarando vitória sobre o Jogo.

Em qualquer momento do programa se o usuário errar uma resposta, tocará uma música avisando da Derrota. Tente novamente!


Video:




Faltas:
Musica toca quando falta pouco tempo
Falta pergunta Final
