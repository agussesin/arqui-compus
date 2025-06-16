#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>

// Variable global para mantener la velocidad entre secuencias
int velocidadGlobal = 100000;

// Declaración anticipada
int verificarEntradaUsuario();

// Retardo interactivo para permitir control inmediato
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

// Función para verificar entrada del usuario (salida y control de velocidad) - versión Windows
int verificarEntradaUsuario()
{
    if (_kbhit())
    {
        char c = _getch();
        // printf("DEBUG: Tecla detectada: %d (0x%02X)\n", c, c); // Debug eliminado

        if (c == 'q' || c == 'Q')
        {             // 'q' o 'Q' para salir
            return 1; // Salir
        }
        else if (c == 27)
        {             // ESC para salir
            return 1; // Salir con ESC
        }
        else if (c == 224 || c == 0)
        { // Tecla especial
            if (_kbhit())
            {
                char c2 = _getch();
                // printf("DEBUG: Segunda tecla: %d (0x%02X)\n", c2, c2); // Debug eliminado

                // Flecha arriba - múltiples códigos posibles
                if (c2 == 72 || c2 == 'H' || c2 == 'A')
                {
                    velocidadGlobal = velocidadGlobal > 10000 ? velocidadGlobal - 10000 : 10000;
                    printf("\rVelocidad: %d microsegundos    ", velocidadGlobal);
                    fflush(stdout);
                    return 2; // Velocidad aumentada
                }
                // Flecha abajo - múltiples códigos posibles
                else if (c2 == 80 || c2 == 'P' || c2 == 'B')
                {
                    velocidadGlobal = velocidadGlobal < 500000 ? velocidadGlobal + 10000 : 500000;
                    printf("\rVelocidad: %d microsegundos    ", velocidadGlobal);
                    fflush(stdout);
                    return 3; // Velocidad disminuida
                }
            }
        }
        // Códigos alternativos para flechas (algunos terminales usan estos)
        else if (c == 'H')
        { // Flecha arriba alternativa
            velocidadGlobal = velocidadGlobal > 10000 ? velocidadGlobal - 10000 : 10000;
            printf("\rVelocidad: %d microsegundos    ", velocidadGlobal);
            fflush(stdout);
            return 2;
        }
        else if (c == 'P')
        { // Flecha abajo alternativa
            velocidadGlobal = velocidadGlobal < 500000 ? velocidadGlobal + 10000 : 500000;
            printf("\rVelocidad: %d microsegundos    ", velocidadGlobal);
            fflush(stdout);
            return 3;
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
    printf("3. Ascensor\n");
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
    printf("00000000\n");
    printf("Iniciando secuencia...\n\n");

    unsigned char led = 0x01;
    int direccion = 1;

    for (int i = 0; i < 14; i++)
    {
        if (velocidadGlobal == -1)
        {
            printf("\nSecuencia interrumpida por el usuario.\n");
            printf("Apagando todas las luces...\n");
            printf("00000000\n");
            velocidadGlobal = 100000;
            return;
        }
        printf("Paso %d: ", i);
        print_bin(led);
        printf("\n");
        retardoInteractivo(velocidadGlobal);

        if (led == 0x80)
            direccion = -1;
        else if (led == 0x01)
            direccion = 1;

        led = (direccion == 1) ? (led << 1) : (led >> 1);
    }

    printf("Secuencia 'Auto Fantástico' finalizada.\n");
    printf("Apagando todas las luces...\n");
    printf("00000000\n");
    velocidadGlobal = 100000;
}

// Función El Choque
void elChoque(int velocidad)
{
    printf("\n=== EJECUTANDO: EL CHOQUE ===\n");
    printf("Presione 'q' para salir de la secuencia\n");
    printf("Flecha ↑ para aumentar velocidad, Flecha ↓ para disminuir\n");
    printf("Velocidad actual: %d microsegundos\n", velocidadGlobal);
    printf("Apagando todas las luces...\n");
    printf("00000000\n");
    printf("Iniciando secuencia...\n\n");

    unsigned char tabla[7] = {0x80, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42};
    int direccion = 1;
    int index = 0;

    for (int i = 0; i < 14; i++)
    {
        if (velocidadGlobal == -1)
        {
            printf("\nSecuencia interrumpida por el usuario.\n");
            printf("Apagando todas las luces...\n");
            printf("00000000\n");
            velocidadGlobal = 100000;
            return;
        }
        printf("Paso %d: ", i);
        print_bin(tabla[index]);
        printf("\n");
        retardoInteractivo(velocidadGlobal);

        if (index == 6)
            direccion = -1;
        else if (index == 0)
            direccion = 1;

        index += direccion;
    }

    printf("Secuencia 'El Choque' finalizada.\n");
    printf("Apagando todas las luces...\n");
    printf("00000000\n");
    velocidadGlobal = 100000;
}

// Función Ascensor
void ascensor(int velocidad)
{
    printf("\n=== EJECUTANDO: ASCENSOR ===\n");
    printf("Presione 'q' para salir de la secuencia\n");
    printf("Flecha ↑ para aumentar velocidad, Flecha ↓ para disminuir\n");
    printf("Velocidad actual: %d microsegundos\n", velocidadGlobal);
    printf("Apagando todas las luces...\n");
    printf("00000000\n");
    printf("Iniciando secuencia...\n\n");

    unsigned char pisos[4] = {0x01, 0x02, 0x04, 0x08};
    int direccion = 1;
    int piso = 0;

    for (int i = 0; i < 8; i++)
    {
        if (velocidadGlobal == -1)
        {
            printf("\nSecuencia interrumpida por el usuario.\n");
            printf("Apagando todas las luces...\n");
            printf("00000000\n");
            velocidadGlobal = 100000;
            return;
        }
        printf("Piso %d: ", piso + 1);
        print_bin(pisos[piso]);
        printf("\n");
        retardoInteractivo(velocidadGlobal);

        if (piso == 3)
            direccion = -1;
        else if (piso == 0)
            direccion = 1;
        piso += direccion;
    }

    printf("Secuencia 'Ascensor' finalizada.\n");
    printf("Apagando todas las luces...\n");
    printf("00000000\n");
    velocidadGlobal = 100000;
}

// Función Explosión y Contracción
void explosionYContraccion(int velocidad)
{
    printf("\n=== EJECUTANDO: EXPLOSIÓN Y CONTRACCIÓN ===\n");
    printf("Presione 'q' para salir de la secuencia\n");
    printf("Flecha ↑ para aumentar velocidad, Flecha ↓ para disminuir\n");
    printf("Velocidad actual: %d microsegundos\n", velocidadGlobal);
    printf("Apagando todas las luces...\n");
    printf("00000000\n");
    printf("Iniciando secuencia...\n\n");

    unsigned char secuencia[] = {
        0x18, // 00011000
        0x3C, // 00111100
        0x7E, // 01111110
        0xFF, // 11111111
        0x7E, // 01111110
        0x3C, // 00111100
        0x18  // 00011000
    };
    int pasos = sizeof(secuencia) / sizeof(secuencia[0]);

    for (int i = 0; i < pasos; i++)
    {
        if (velocidadGlobal == -1)
        {
            printf("\nSecuencia interrumpida por el usuario.\n");
            printf("Apagando todas las luces...\n");
            printf("00000000\n");
            velocidadGlobal = 100000;
            return;
        }
        printf("Paso %d: ", i + 1);
        print_bin(secuencia[i]);
        printf("\n");
        retardoInteractivo(velocidadGlobal);
    }

    printf("Secuencia 'Explosión y Contracción' finalizada.\n");
    printf("Apagando todas las luces...\n");
    printf("00000000\n");
    velocidadGlobal = 100000;
}