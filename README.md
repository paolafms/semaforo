# Semáforo utilizando microcontrolador Raspberry Pi Pico W:
- O semáforo alterna entre três estados: vermelho, amarelo e verde com cada estado durando 3 segundos.
- O código foi projetado para funcionar tanto no simulador Wokwi quanto na placa BitDogLab, com ajustes específicos para cada plataforma.

# São simulados os seguintes componentes:
- Microcontrolador Raspberry Pi Pico W.
- 03 LEDs (vermelho, amarelo e verde).
- 03 Resistores de 330 Ω.

# Observação importante!
- PARA O LED AMARELO ACENDER NO WOKWI, BASTA TIRAR O COMENTÁRIO (//) DO #define WOKWI.
- PARA O LED AMARELO ACENDER NA PLACA BITDOGLAB, BASTA COMENTAR (//) NO #define WOKWI.
- O #define WOKWI garante que o semáforo funcione corretamente, independentemente de estar sendo simulado no Wokwi ou na BitDogLab.
- BitDogLab: Não existe LED amarelo, para que ele apareça, precisa acender os LEDS verde e vermelho ao mesmo tempo.
- Simulação no Wokwi: Foi adicionado o LED amarelo, e para não acender os LEDS verde e vermelho ao mesmo tempo, foi criado o #define WOKWI.

# Funcionalidades do Semáforo:
- LED Vermelho (GPIO 13): Indica o estado "PARE".
- LED Amarelo (GPIO 12): Indica o estado "ATENÇÃO".
- LED Verde (GPIO 11): Indica o estado "PROSSEGUIR".
- O semáforo alterna entre os estados vermelho, amarelo e verde a cada 3 segundos.
- Mensagens indicando o estado atual do semáforo são exibidas no console durante as transições.
- No Wokwi, o LED amarelo é utilizado, enquanto na BitDogLab, o LED amarelo é substituído por uma combinação de LEDs vermelho e verde.
