#include <stdio.h>
#include "retardo.h"
#include "util.h"
#include "explosion_contraccion.h"

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
    for (int i = 0; i < pasos; i++) {
        printf("Paso %d: ", i+1);
        print_bin(secuencia[i]);
        printf("\n");
        retardo(velocidad);
    }
    printf("Secuencia 'Explosión y Contracción' finalizada.\n");
} 