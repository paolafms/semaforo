#define WOKWI // !!!!!! LEIA O README.md !!!!!!
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

// Pinos dos LEDs
#define LED_VERMELHO 13  // Pino do LED vermelho (GPIO 13)
#define LED_AMARELO 12   // Pino do LED amarelo (GPIO 12) - Só no Wokwi
#define LED_VERDE 11     // Pino do LED verde (GPIO 11)

// Estado inicial do semáforo
int estado_semaforo = 0;  // Variável que armazena o estado atual do semáforo (0: verde, 1: vermelho, 2: amarelo)
uint64_t tempo_total = 0; // Variável para armazenar o tempo total decorrido

// Função para mudar o estado do semáforo
void mudar_estado_semaforo() {
    switch (estado_semaforo) {
        case 0:
            // Desliga o LED verde e, dependendo da plataforma, ajusta os LEDs vermelho e amarelo
            gpio_put(LED_VERDE, 0);
#ifdef WOKWI
            gpio_put(LED_AMARELO, 0);
#else
            gpio_put(LED_VERMELHO, 1);
            gpio_put(LED_VERDE, 0);
#endif
            gpio_put(LED_VERMELHO, 1);  // Liga o LED vermelho
            printf("VERMELHO - PARE\n"); // Exibe mensagem no console
            estado_semaforo = 1;  // Muda o estado para vermelho
            break;
        case 1:
            // Desliga o LED vermelho e verde, e ajusta o LED amarelo ou vermelho/verde dependendo da plataforma
            gpio_put(LED_VERMELHO, 0);
            gpio_put(LED_VERDE, 0);
#ifdef WOKWI
            gpio_put(LED_AMARELO, 1);  // Liga o LED amarelo no Wokwi
#else
            gpio_put(LED_VERMELHO, 1);
            gpio_put(LED_VERDE, 1);
#endif
            printf("AMARELO - ATENÇÃO\n"); // Exibe mensagem no console
            estado_semaforo = 2;  // Muda o estado para amarelo
            break;
        case 2:
            // Desliga o LED vermelho e amarelo, e liga o LED verde
            gpio_put(LED_VERMELHO, 0);
#ifdef WOKWI
            gpio_put(LED_AMARELO, 0);
#else
            gpio_put(LED_VERMELHO, 0);
            gpio_put(LED_VERDE, 0);
#endif
            gpio_put(LED_VERDE, 1);  // Liga o LED verde
            printf("VERDE - PROSSEGUIR\n"); // Exibe mensagem no console
            estado_semaforo = 0;  // Muda o estado para verde
            break;
    }
}

// Função de callback para o temporizador
bool timer_callback(struct repeating_timer *t) {
    static int contador = 0;  // Contador para controlar a mudança de estado do semáforo
    tempo_total++;  // Incrementa o tempo total decorrido
    printf("Tempo: %llu segundos\n", tempo_total);  // Exibe o tempo total no console
    contador++;
    if (contador >= 3) {  // A cada 3 segundos, muda o estado do semáforo
        mudar_estado_semaforo();
        contador = 0;  // Reinicia o contador
    }
    return true;  // Retorna true para continuar o temporizador
}

int main() {
    stdio_init_all();  // Inicializa a comunicação serial (para o console)
    sleep_ms(300);  // Aguarda 300ms para estabilização

    // Inicializa os pinos dos LEDs
    gpio_init(LED_VERMELHO);
    gpio_init(LED_VERDE);
#ifdef WOKWI
    gpio_init(LED_AMARELO);  // Inicializa o pino do LED amarelo apenas no Wokwi
    gpio_set_dir(LED_AMARELO, GPIO_OUT);  // Configura o pino do LED amarelo como saída
#endif
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);  // Configura o pino do LED vermelho como saída
    gpio_set_dir(LED_VERDE, GPIO_OUT);  // Configura o pino do LED verde como saída

    mudar_estado_semaforo();  // Define o estado inicial do semáforo

    // Configura um temporizador repetitivo para chamar a função timer_callback
    struct repeating_timer timer;
    add_repeating_timer_ms(1000, timer_callback, NULL, &timer);

    // Loop infinito para manter o programa em execução
    while (true) {
        tight_loop_contents();  // Mantém o loop ocupado sem consumir muita CPU
    }
    return 0;  // Retorno padrão
}