#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include "funciones.h"

extern void digitalWrite(int pin, int val);
extern void pinMode(int pin, int mode);
extern void delayMicros(int);
extern int digitalRead(int pin);

extern const char led[];

// Declaración externa del array de pines
extern const char led[];

// Función para controlar los LEDs
int leds(int num) {
    int i, numval;
    for(i = 0; i < 8; i++) {
        numval = (num >> i) & 0x01;
        digitalWrite(led[i], numval);
    }
    return 0;
}

// Variable global para mantener la velocidad entre secuencias
int velocidadGlobal = 100000;

// Declaración anticipada
int verificarEntradaUsuario();

// Retardo interactivo para permitir control inmediato en Raspberry Pi
void retardoInteractivo(int total_us)
{
    int paso = 2000; // 2 ms
    int transcurrido = 0;
    while (transcurrido < total_us)
    {
        int restante = total_us - transcurrido;
        if (restante < paso)
            paso = restante;
        usleep(paso);
        transcurrido += paso;
        int r = verificarEntradaUsuario();
        if (r == 1)
        {                         // salir
            velocidadGlobal = -1; // señal especial para salir
            break;
        }
    }
}

// Función para configurar entrada no bloqueante (compatible con Raspberry Pi)
void configurarEntradaNoBloqueante()
{
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    int oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
}

// Función para restaurar entrada normal
void restaurarEntradaNormal()
{
    struct termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    oldt.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    int oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf & ~O_NONBLOCK);
}

// Función para verificar entrada del usuario (salida y control de velocidad)
int verificarEntradaUsuario()
{
    char c;
    if (read(STDIN_FILENO, &c, 1) > 0)
    {
        if (c == 'q' || c == 'Q')
        {             // 'q' o 'Q' para salir
            return 1; // Salir
        }
        else if (c == 27)
        { // ESC - podría ser inicio de secuencia de flecha
            // Leer los siguientes caracteres para detectar flechas
            char c2, c3;
            if (read(STDIN_FILENO, &c2, 1) > 0 && c2 == '[')
            {
                if (read(STDIN_FILENO, &c3, 1) > 0)
                {
                    if (c3 == 'A')
                    { // Flecha arriba
                        velocidadGlobal = velocidadGlobal > 10000 ? velocidadGlobal - 10000 : 10000;
                        printf("\rVelocidad: %d microsegundos    ", velocidadGlobal);
                        fflush(stdout);
                        return 2; // Velocidad aumentada
                    }
                    else if (c3 == 'B')
                    { // Flecha abajo
                        velocidadGlobal = velocidadGlobal < 500000 ? velocidadGlobal + 10000 : 500000;
                        printf("\rVelocidad: %d microsegundos    ", velocidadGlobal);
                        fflush(stdout);
                        return 3; // Velocidad disminuida
                    }
                }
            }
            else
            {
                // Si no es una secuencia de flecha, es ESC para salir
                return 1; // Salir
            }
        }
    }
    return 0; // No hay entrada
}

// Función de utilidad para imprimir en binario
void print_bin(unsigned char byte)
{
    for (int i = 7; i >= 0; i--)
    {
        printf("%c", (byte & (1 << i)) ? '1' : '0');
    }
}

// Función de retardo (no se usa más en las secuencias)
void retardo(int a)
{
    usleep(a); // Pausa en microsegundos
}

// Función del menú
void mostrarMenu()
{
    printf("--- MENU DE SECUENCIAS ---\n");
    printf("1. Auto Fantástico\n");
    printf("2. El Choque\n");
    printf("3. Snake Binario\n");
    printf("4. Explosión y Contracción\n");
    printf("5. Salir\n");
    printf("Velocidad actual: %d microsegundos\n", velocidadGlobal);
    printf("Seleccione una opción: ");
}

// Función de control de acceso
void pedirPassword()
{
    const char claveCorrecta[] = "12345";
    char claveIngresada[6];
    int intentos = 0;

    while (intentos < 3)
    {
        printf("Ingrese su password de 5 dígitos: ");

        for (int i = 0; i < 5; i++)
        {
            claveIngresada[i] = getchar();
            printf("*");
        }
        claveIngresada[5] = '\0';

        while (getchar() != '\n')
            ; // Limpia buffer

        printf("\n");

        if (strcmp(claveIngresada, claveCorrecta) == 0)
        {
            printf("Bienvenido al Sistema\n");
            return;
        }
        else
        {
            printf("Password no válida\n");
            intentos++;
        }
    }

    printf("Demasiados intentos. Abortando...\n");
    exit(1);
}

// Función Auto Fantástico
void autoFantastico(int velocidad)
{
    printf("\n=== EJECUTANDO: AUTO FANTÁSTICO ===\n");
    printf("Presione 'q' para salir de la secuencia\n");
    printf("Flecha ↑ para aumentar velocidad, Flecha ↓ para disminuir\n");
    printf("Velocidad actual: %d microsegundos\n", velocidadGlobal);
    printf("Apagando todas las luces...\n");
    leds(0x00);
    printf("Iniciando secuencia...\n\n");

    configurarEntradaNoBloqueante();

    unsigned char led = 0x01;
    int direccion = 1;

    for (int i = 0; i < 14; i++)
    {
        if (velocidadGlobal == -1) break;

        printf("Paso %d: ", i);
        print_bin(led);
        printf("\n");

        leds(led); // <-- Enciende LEDs reales
        retardoInteractivo(velocidadGlobal);

        direccion = (led == 0x80) ? -1 : (led == 0x01 ? 1 : direccion);
        led = (direccion == 1) ? (led << 1) : (led >> 1);
    }

    printf("Secuencia 'Auto Fantástico' finalizada.\n");
    leds(0x00);
    velocidadGlobal = 100000;
    restaurarEntradaNormal();
}


// Función El Choque
void elChoque(int velocidad)
{
    printf("\n=== EJECUTANDO: EL CHOQUE ===\n");
    printf("Presione 'q' para salir de la secuencia\n");
    printf("Flecha ↑ para aumentar velocidad, Flecha ↓ para disminuir\n");
    printf("Velocidad actual: %d microsegundos\n", velocidadGlobal);
    printf("Apagando todas las luces...\n");
    leds(0x00);
    printf("Iniciando secuencia...\n\n");

    configurarEntradaNoBloqueante();

    unsigned char tabla[7] = {0x80, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42};
    int direccion = 1;
    int index = 0;

    for (int i = 0; i < 14; i++)
    {
        if (velocidadGlobal == -1) break;

        printf("Paso %d: ", i);
        print_bin(tabla[index]);
        printf("\n");

        leds(tabla[index]); // <-- Enciende LEDs reales
        retardoInteractivo(velocidadGlobal);

        direccion = (index == 6) ? -1 : (index == 0 ? 1 : direccion);
        index += direccion;
    }

    printf("Secuencia 'El Choque' finalizada.\n");
    leds(0x00);
    velocidadGlobal = 100000;
    restaurarEntradaNormal();
}

// Las funciones snake y explosionYContraccion han sido movidas a assembly
// Ver snake.s y explosion.s para las implementaciones actuales
/*
void snake(int velocidad)
{
    printf("\n=== EJECUTANDO: SNAKE BINARIO ===\n");
    printf("Presione 'q' para salir de la secuencia\n");
    printf("Flecha ↑ para aumentar velocidad, Flecha ↓ para disminuir\n");
    printf("Velocidad actual: %d microsegundos\n", velocidadGlobal);
    printf("Apagando todas las luces...\n");
    leds(0x00);
    printf("Iniciando secuencia...\n\n");

    configurarEntradaNoBloqueante();

    unsigned char led = 0x01;

    for (int i = 0; i < 14; i++)
    {
        if (velocidadGlobal == -1) break;

        printf("Paso %d: ", i);
        print_bin(led);
        printf("\n");

        leds(led);
        retardoInteractivo(velocidadGlobal);

        led = (led << 1) | 0x01;
        if (led == 0xFF) led = 0x01;
    }

    printf("Secuencia 'Snake Binario' finalizada.\n");
    leds(0x00);
    velocidadGlobal = 100000;
    restaurarEntradaNormal();
}

void explosionYContraccion(int velocidad)
{
    printf("\n=== EJECUTANDO: EXPLOSIÓN Y CONTRACCIÓN ===\n");
    printf("Presione 'q' para salir de la secuencia\n");
    printf("Flecha ↑ para aumentar velocidad, Flecha ↓ para disminuir\n");
    printf("Velocidad actual: %d microsegundos\n", velocidadGlobal);
    printf("Apagando todas las luces...\n");
    leds(0x00);
    printf("Iniciando secuencia...\n\n");

    configurarEntradaNoBloqueante();

    unsigned char patrones[] = {0x18, 0x3C, 0x7E, 0xFF, 0x7E, 0x3C, 0x18};
    int index = 0;

    for (int i = 0; i < 14; i++)
    {
        if (velocidadGlobal == -1) break;

        printf("Paso %d: ", i);
        print_bin(patrones[index]);
        printf("\n");

        leds(patrones[index]);
        retardoInteractivo(velocidadGlobal);

        index = (index + 1) % 7;
    }

    printf("Secuencia 'Explosión y Contracción' finalizada.\n");
    leds(0x00);
    velocidadGlobal = 100000;
    restaurarEntradaNormal();
}
*/
