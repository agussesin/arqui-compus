#include <stdio.h>
#include "retardo.h"

void retardo(int ciclos);

void print_bin(unsigned char byte)
{
    for (int i = 7; i >= 0; i--)
    {
        printf("%c", (byte & (1 << i)) ? '1' : '0');
    }
}

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

// ver si es igual al fel profe
// secuencia de luces ida y vuelta programada dinámicamente sin tabla de datos, usando operaciones bit a bit y control de dirección.