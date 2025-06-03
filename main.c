#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void autoFantastico(int velocidad);
void elChoque(int velocidad);
void pedirPassword();

void mostrarMenu()
{
    printf("\n--- MENU DE SECUENCIAS ---\n");
    printf("1. Auto Fantástico\n");
    printf("2. El Choque\n");
    printf("3. Salir\n");
    printf("Seleccione una opción: ");
}

int main()
{
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
            printf("Saliendo...\n");
            return 0;
        default:
            printf("Opción inválida.\n");
        }
    }
}
