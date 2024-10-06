# Jogo de Memórias e Perguntas - Projeto 1 Computação Móvel
**Introdução:**
Este projeto foi desenvolvido como parte da disciplina CC4670 - Computação Móvel. 

**Objetivo:**
Criar um projeto no Arduino que simule um jogo de memória e perguntas. O jogo de memória deve funcionar com duas luzes LED, que serão acesas aleatoriamente 10 vezes. Após aparecerem todas as luzes, o usuário deve repetir a sequência corretamente.
Caso o usuário consiga replicar a sequência, ele avança para a fase de perguntas, que consiste em 5 perguntas aleatórias e uma pergunta final fixa. Se o usuário também conseguir responder corretamente ao jogo de perguntas, ele ganha. O projeto deve incluir diversos sons de feedback para o usuário (se errar uma pergunta, por exemplo). Além de ter melodias para vitória, ou derrota.

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


Código:

O código foi escrito no Tinkercad. Para mais informações ver o código comentado.

Dos três botões, dois são analógicos e usados de input do usuário para cada LED. O outro foi usado na porta 3 e declarado como interruptor. O botão de interrupção foi usado para deixar o usuário desistir e iniciar o jogo. Essas duas funcionalidades foram feitas dentro de uma função, com o uso de um contador. Ele é iniciado no valor 0 e é incrementado cada vez que o botão for apertado. O jogo iniciará, quando esse contador valer 1 e se valer 2 significa que o usuário deseja desistir.  Dentro do loop encontram-se diferentes condicionais, que são ativadas quando o contador tiver o valor 2, para manejar a desistência do jogador, tocando o som e mostrando uma mensagem no LCD. 

O jogo começa na primeira interrupção, que gera um array de 10 inteiros, com números entre 1 e 2, que simbolizam as luzes verde e vermelho. Após as luzes serem mostradas para o usuário, um contador de botões pressionados auxilia o programa a se manter dentro do loop, enquanto o usuário repete a sequência. A verificação ocorre a cada botão pressionado pelo usuário, caso ele erre, uma mensagem aparece e o código é resetado, por meio do "asm ("jmp (0x0000)")".

As perguntas foram guardadas em um array do tipo string com três posições. A primeira é a dificuldade da questão, que foi mantida após o projeto ter sido completado com esse aspecto presente. O segundo é a pergunta e o terceiro a resposta, em formato "V" ou "F". Uma função escolhe uma pergunta, depois que o  usuário entrar na fase de perguntas com um seed aleatório (com duas opções, já que cada dificuldade conta com 2 perguntas). Uma função de chekagem verifica se a resposta for correta ou não, comparando o valor do array na posição da resposta da pergunta com o input do usuário. Caso o usuário acerte, o contador da dificuldade é incrementado e o processo se repete. Quando o contador de dificuldade valer 5, uma mensagem será mostrada no LCD e a pergunta final é mostrada e checkada pela mesma função. Nesta fase de perguntas também foi implementado um timer, com o uso de um contador de tempo, que é decrementado a cada 1.2 segundos, totalizando 10 segundos e facilitando a mostra do tempo no display, já que não é necessário chamar a função "clear"
no display. Um contador guarda as vidas (no caso o jogador tem 1 vida) do jogador e é decrementado, quando seu tempo chega a 0. Caso o usuário tenha 1 vida no momento em que o timer chega a 0, uma pergunta de dificuldade "7" é mostrada, que facilita a não repetição de perguntas.  

Para as mensagens que são mostradas indefinidamente, foram usados loops "while", que são ativados/desativados com contadores. Um é o de interrupção como explicado e o outro foi feito para entrar na fase de perguntas do jogo, que espera o usuário segurar o botão verde para iniciar a fase.


**Conclusão:**

O projeto atingiu os objetivos propostos, criando um jogo funcional que testa a memória e conhecimento do jogador. Tendo algumas dificiuldades, conseguimos resolvê-las e implementar o código corretamente.

Dificuldades Encontradas:

Código não funcionando corretamente.
- Varios erros de mensagens no LCD.
- Problemas com delay.
- Erro inicial de tentar realizar a função do jogo dentro da interrupção.
- Projeto feito com premissa equivocada de perguntas com graús de dificuldade diferente, mas que foi mantido por ajudar a assegurar uma pergunta diferente em cada etapa.
