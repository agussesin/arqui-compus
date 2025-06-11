#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Función de utilidad para imprimir en binario
void print_bin(unsigned char byte)
{
    for (int i = 7; i >= 0; i--)
    {
        printf("%c", (byte & (1 << i)) ? '1' : '0');
    }
}

// Función de retardo
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
    unsigned char led = 0x01;
    int direccion = 1;

    for (int i = 0; i < 14; i++)
    {
        printf("Paso %d: ", i);
        print_bin(led);
        printf("\n");
        retardo(velocidad);

        if (led == 0x80)
            direccion = -1;
        else if (led == 0x01)
            direccion = 1;

        led = (direccion == 1) ? (led << 1) : (led >> 1);
    }

    printf("Secuencia 'Auto Fantástico' finalizada.\n");
}

// Función El Choque
void elChoque(int velocidad)
{
    unsigned char tabla[7] = {0x80, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42};
    int direccion = 1;
    int index = 0;

    for (int i = 0; i < 14; i++)
    {
        printf("Paso %d: ", i);
        print_bin(tabla[index]);
        printf("\n");
        retardo(velocidad);

        if (index == 6)
            direccion = -1;
        else if (index == 0)
            direccion = 1;

        index += direccion;
    }

    printf("Secuencia 'El Choque' finalizada.\n");
}

// Función Ascensor
void ascensor(int velocidad)
{
    unsigned char pisos[4] = {0x01, 0x02, 0x04, 0x08};
    int direccion = 1;
    int piso = 0;
    for (int i = 0; i < 8; i++)
    {
        printf("Piso %d: ", piso + 1);
        print_bin(pisos[piso]);
        printf("\n");
        retardo(velocidad);
        if (piso == 3)
            direccion = -1;
        else if (piso == 0)
            direccion = 1;
        piso += direccion;
    }
    printf("Secuencia 'Ascensor' finalizada.\n");
}

// Función Explosión y Contracción
void explosionYContraccion(int velocidad)
{
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
        printf("Paso %d: ", i + 1);
        print_bin(secuencia[i]);
        printf("\n");
        retardo(velocidad);
    }
    printf("Secuencia 'Explosión y Contracción' finalizada.\n");
}