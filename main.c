#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "EasyPIO.h"
#include "funciones.h"

// Definición de pines GPIO para los LEDs
const char led[] = {17, 18, 27, 22, 23, 24, 25, 4}; // Pines GPIO

int main()
{
    // Inicialización de GPIO
    pioInit();

    // Configurar los pines como salida
    for(int i = 0; i < 8; i++) {
        pinMode(led[i], OUTPUT);
    }

    // Apagar todos los LEDs (active low)
    leds(0xFF);

    pedirPassword();

    int opcion = 0;
    int velocidad = 100000;

    while (1)
    {
        mostrarMenu();
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            autoFantastico(velocidad);
            break;
        case 2:
            elChoque(velocidad);
            break;
        case 3:
            snake(velocidad);
            break;
        case 4:
            explosionYContraccion(velocidad);
            break;
        case 5:
            printf("Saliendo...\n");
            return 0;
        default:
            printf("Opción inválida.\n");
        }
    }
}
