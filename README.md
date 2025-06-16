
# Tarefa: Roteiro de FreeRTOS #1 - EmbarcaTech 2025

Autor: **Pedro Henrique Dias Avelar**

Curso: Residência Tecnológica em Sistemas Embarcados

Instituição: EmbarcaTech - HBr

Brasília, Junho de 2025

---

## Objetivo
O objetivo do presente projeto foi demonstrar o uso básico do FreeRTOS.
Para isto foram criadas 4 tasks:
* Oscilar o led RGB entre as cores vermelho, verde e azul
* Ativar o buzzer a cada 2 segundos
* Ler os botões A e B para ativar/desativar as duas tarefas anteriores
* Exibir o status das tarefas, do led e do buzzer no display OLED

##Lista de periféricos utilizados
|Periférico    | Conexão na BitDogLab|
|--------------|---------------------|
| Botões A e B | GP5 e GP6           |
| Buzzers A e B| GP21 e GP10         |
|LED RGB       | GP13(R),GP11(G),GP12(B)|
|Display OLED  | GP14(SDA), GP15(SCL)|

##Lógica
O código envolve a criação de 4 funções, display_task(), led_task(), buzzer_task() e button_task(), responsável por cada um dos quatro periféricos.
* led_task(): Oscila o led RGB entre as cores vermelho, verde e azul a cada execução
* buzzer_task(): Emite um beep de 250ms com os dois buzzers da BitDogLab e então espera 2 segundos antes de tocar novamente
* button_task(): Faz a leitura dos botões A e B. O botão A faz alterar o estado de funcionamento do led RGB; já o botão B faz alternar o estado de funcionamento do buzzer.
* display_task(): Exibe no display OLED qual led está aceso, se os buzzers estão ativados ou desativados e o estado das respectivas tarefas, se estão ativadas ou desativadas.

Ao iniciar o programa, é mostrada uma tela de apresentação, e o programa inicia após detectar um acionamento de botão:
![Imagem do WhatsApp de 2025-06-16 à(s) 00 05 41_57556ea9](https://github.com/user-attachments/assets/8dddc4d4-1ad9-43a3-b17e-ca4162ca867f)

Após esse acionamento, o programa irá executar as tasks ativadas, exibindo no display OLED o status:
![image](https://github.com/user-attachments/assets/aedac04f-b380-4e3a-99b0-464d9d923fd3)

Video: https://www.youtube.com/shorts/j6pyCCiNvGw

##Reflexões

1)O que acontece se todas as tarefas tiverem a mesma prioridade?

Manter as tarefas com a mesma prioridade poderia causar falhas de comunicação com o display OLED. Como o display é o periférico que mais consome CPU, foi dada a sua tarefa uma prioridade maior.
Para a leitura dos botões, não foi observada uma necessidade de maior prioridade, mas isso pode mudar com o aumento da quantidade e complexidade de outras tarefas.

2) Qual tarefa consome mais tempo da CPU?

O display OLED e sua tarefa são os maiores consumidores de CPU

3) Quais seriam os riscos de usar polling sem prioridades?

O uso de polling sem prioridades poderia causar problemas na comunicação com o display OLED. Na primeira versão do programa, usando vTaskSuspend e vTaskResume, havia uma falha ao suspender a task
do buzzer durante sua execução, causando uma toca ininterrupta do mesmo; ao alterar o programa para o uso de semáforos, este erro deixou de ocorrer.

---

## 📜 Licença
GNU GPL-3.0.
