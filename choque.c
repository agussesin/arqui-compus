#include <stdio.h>

void retardo(int ciclos);

void print_bin(unsigned char byte)
{
    for (int i = 7; i >= 0; i--)
    {
        printf("%c", (byte & (1 << i)) ? '1' : '0');
    }
}

void elChoque(int velocidad)
{
    unsigned char tabla[7] = {0x80, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42};

    for (int i = 0; i < 7; i++)
    {
        printf("Paso %d: ", i);
        print_bin(tabla[i]);
        printf("\n");
        retardo(velocidad);
    }

    printf("Secuencia 'El Choque' finalizada.\n");
}
