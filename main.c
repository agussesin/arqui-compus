#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "retardo.h"
#include "auto_fantastico.h"
#include "choque.h"
#include "ascensor.h"
#include "explosion_contraccion.h"

void autoFantastico(int velocidad);
void elChoque(int velocidad);
void ascensor(int velocidad);
// void pedirPassword();

int main()
{
    // pedirPassword();

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
            ascensor(velocidad);
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