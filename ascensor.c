#include <stdio.h>
#include "retardo.h"
#include "util.h"
#include "ascensor.h"

void ascensor(int velocidad)
{
    unsigned char pisos[4] = {0x01, 0x02, 0x04, 0x08};
    int direccion = 1;
    int piso = 0;
    for (int i = 0; i < 8; i++)
    {
        printf("Piso %d: ", piso+1);
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