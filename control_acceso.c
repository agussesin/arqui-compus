#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
