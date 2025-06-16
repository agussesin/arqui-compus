#include <stdio.h>
#include <conio.h>

int main()
{
    printf("Programa de prueba para detectar flechas\n");
    printf("Presiona flechas arriba/abajo para cambiar velocidad\n");
    printf("Presiona 'q' para salir\n\n");

    int velocidad = 100000;

    while (1)
    {
        if (_kbhit())
        {
            char c = _getch();
            printf("Tecla presionada: %d (0x%02X)\n", c, c);

            if (c == 'q' || c == 'Q')
            {
                printf("Saliendo...\n");
                break;
            }
            else if (c == 224)
            {
                char c2 = _getch();
                printf("Segunda tecla: %d (0x%02X)\n", c2, c2);

                if (c2 == 72)
                {
                    velocidad = velocidad > 10000 ? velocidad - 10000 : 10000;
                    printf("Flecha arriba - Velocidad: %d\n", velocidad);
                }
                else if (c2 == 80)
                {
                    velocidad = velocidad < 500000 ? velocidad + 10000 : 500000;
                    printf("Flecha abajo - Velocidad: %d\n", velocidad);
                }
            }
        }
    }

    return 0;
}