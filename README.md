# Jogo de Memórias e Perguntas - Projeto 1 Computação Móvel
**Introdução:**
Este projeto foi desenvolvido como parte da disciplina CC4670 - Computação Móvel. Para 

**Objetivo:**
Criar um projeto no Arduino que simule um jogo de memória e perguntas. O jogo de memória deve funcionar com duas luzes LED, que serão acesas aleatoriamente 10 vezes. Após aparecerem todas as luzes, o usuário deve repetir a sequência corretamente.
Caso o usuário consiga replicar a sequência, ele avança para a fase de perguntas, que consiste em 5 perguntas aleatórias e uma pergunta final fixa. Se o usuário também conseguir responder corretamente ao jogo de perguntas, ele ganha.

**Metodologia:**

Materiais:
-  Arduino UNO
-  1 Led Vermelho
-  1 Led Verde
-  3 botões
-  4 Resistores
-  1 Buzzer
-  1 Display LCD 16x2
-  1 Potenciômetro
-  2 Protoboards

Circuito no Tinkercad:
![image](https://github.com/user-attachments/assets/9697e375-2ff2-4493-8353-b050ed69bfe6)

Funcionamento do Programa:

O jogo apenas começa quando o usuário apertar o botão (na foto marcado com amarelo).

![image](https://github.com/user-attachments/assets/b8c6c3f4-df9f-4d3f-bc66-988cf3fc8a14) 


Uma vez que o botão de início for apertado, começará a sequência de luzes. Os LEDs serão acesos um total de 10 vezes. O usuário deve esperar sequência completa antes de começar a pressionar os botões.
![image](https://github.com/user-attachments/assets/ec2424f8-29e2-40ed-80aa-b2f4cbcf6a89)

O usuário deve replicar a sequência usando os botões ressaltados na Imagem. A luz vermelha representa o botão marcado com a cor Vermelho-alaranjado, e a luz verde representa o botão marcado com a cor Verde.
![image](https://github.com/user-attachments/assets/b739bb09-64c6-4dfe-a481-a95611532275)




Caso o usuário acertar, tocará uma música para celebrar sua vitória. Na sequência começará o jogo de Perguntas, o jogo não começará até o usuário segurar o botão da Luz Verde
Verdadeiro é representado pelo botão da Luz Verde, e o Falso é representado pelo botão da Luz Vermelha.

![image](https://github.com/user-attachments/assets/665fcb23-bcce-4408-b6b1-b1082d91e1fd)


Após o usuário começar o jogo, ele tem 10 segundos por pergunta para respondê-las. O usuário tambêm tem a opção de pular uma pergunta, para isto ele deve deixar o tempo acabar.
![image](https://github.com/user-attachments/assets/987dd165-44cf-4e14-a294-52279f824888)



Caso acertar as 6 perguntas, tocará uma música declarando vitória sobre o Jogo.
Em qualquer momento do programa se o usuário errar uma resposta, tocará uma música avisando da Derrota. Tente novamente!




Video:

Código:

O código foi escrito no Tinkercad e inclui funções para geração aleatória de perguntas e de sequências de LEDs, além da lógica de controle de tempo e feedback sonoro. O código completo e comenteado está disponível neste repositório.

**Conclusão:**

O projeto atingiu os objetivos propostos, criando um jogo funcional que testa a memória e conhecimento do jogador. Tendo algumas dificiuldades, conseguimos resolve-las e implementar o código corretamente.

Dificuldades Encontradas:

Código não funcionando corretamente.
- Varios erros de mostra no lcd.
- Problemas com delay.
