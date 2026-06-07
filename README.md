# 💡 Sistema de Iluminação Assistida com MSP430

![Status](https://img.shields.io/badge/Status-Em%20Desenvolvimento-yellow)
![Plataforma](https://img.shields.io/badge/Microcontrolador-MSP430-red)
![Disciplina](https://img.shields.io/badge/Disciplina-SISMIC-blue)

## 🎯 Sobre o Projeto

Este projeto consiste em um sistema de automação residencial focado em acessibilidade e segurança. O objetivo principal é auxiliar a mobilidade noturna de pessoas idosas que moram sozinhas, utilizando sensores de presença para criar um "caminho de luz". As lâmpadas são acionadas de forma automática e com uma transição suave de intensidade, evitando ofuscamento repentino e prevenindo quedas no escuro.

Projeto desenvolvido no escopo da disciplina de **Laboratório de Sistemas Microprocessados (Lab. Sismic)** da **Universidade de Brasília (UnB)**.

## 🛠️ Hardware Utilizado

* **Microcontrolador:** Placa de desenvolvimento Texas Instruments MSP430F5529LP (Launchpad)
* **Sensores:** Sensor de presença/movimento (PIR HC-SR501)
* **Interface e Controle:** Display LCD (16x2) e Kit Controle Remoto + Receptor Infravermelho (IR)
* **Atuadores:** LEDs e/ou Módulo Relé/MOSFET (para as luzes do caminho)
* **Outros componentes:** Protoboard, resistores e jumpers

## 💻 Software e Ferramentas

* **IDE:** Code Composer Studio 20.5.0
* **Linguagem:** C

## ⚙️ Lógica de Funcionamento e Arquitetura

O sistema opera com base na seguinte lógica principal:

1.  **Configuração de Limite (IR):** Utilizando o controle remoto infravermelho, é possível ajustar o teto máximo de luminosidade que o sistema deve atingir. O receptor IR capta o comando e o MSP430 salva esse novo limite.
2.  **Detecção:** O sensor de presença identifica movimento no ambiente.
3.  **Processamento e Acionamento Suave (Fade-in):** O MSP430 registra o sinal e, através de PWM (*Pulse Width Modulation*), aumenta o *duty cycle* gradativamente, acendendo a luz de forma suave até atingir o limite (teto) previamente configurado pelo controle IR.
4.  **Monitoramento (Display LCD):** Em tempo real, o microcontrolador envia os dados para o display LCD, que exibe a porcentagem atual de iluminação do ambiente (de 0% até o limite estabelecido).
5.  **Timer e Desligamento (Fade-out):** Após um tempo predeterminado sem detecção de novos movimentos, o PWM atua novamente para reduzir a intensidade da luz gradativamente até apagá-la completamente, atualizando a queda de porcentagem no LCD.

<img width="700" height="500" alt="image1" src="https://github.com/user-attachments/assets/48f63a16-8e1d-4b6f-b289-9d80823a6ea5" />
