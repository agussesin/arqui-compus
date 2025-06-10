#include <stdio.h>
#include "retardo.h"
#include "util.h"

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
