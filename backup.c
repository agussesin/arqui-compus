// Backup de las implementaciones originales en C
// Estas funciones no se compilan, solo se mantienen como referencia

void snake(int velocidad)
{
    printf("\n=== EJECUTANDO: SNAKE BINARIO ===\n");
    printf("Presione 'q' para salir de la secuencia\n");
    printf("Flecha ↑ para aumentar velocidad, Flecha ↓ para disminuir\n");
    printf("Velocidad actual: %d microsegundos\n", velocidadGlobal);
    printf("Apagando todas las luces...\n");
    leds(0x00);
    printf("Iniciando secuencia...\n\n");

    configurarEntradaNoBloqueante();

    unsigned char led = 0x01;

    for (int i = 0; i < 14; i++)
    {
        if (velocidadGlobal == -1) break;

        printf("Paso %d: ", i);
        print_bin(led);
        printf("\n");

        leds(led);
        retardoInteractivo(velocidadGlobal);

        led = (led << 1) | 0x01;
        if (led == 0xFF) led = 0x01;
    }

    printf("Secuencia 'Snake Binario' finalizada.\n");
    leds(0x00);
    velocidadGlobal = 100000;
    restaurarEntradaNormal();
}

void explosionYContraccion(int velocidad)
{
    printf("\n=== EJECUTANDO: EXPLOSIÓN Y CONTRACCIÓN ===\n");
    printf("Presione 'q' para salir de la secuencia\n");
    printf("Flecha ↑ para aumentar velocidad, Flecha ↓ para disminuir\n");
    printf("Velocidad actual: %d microsegundos\n", velocidadGlobal);
    printf("Apagando todas las luces...\n");
    leds(0x00);
    printf("Iniciando secuencia...\n\n");

    configurarEntradaNoBloqueante();

    unsigned char patrones[] = {0x18, 0x3C, 0x7E, 0xFF, 0x7E, 0x3C, 0x18};
    int index = 0;

    for (int i = 0; i < 14; i++)
    {
        if (velocidadGlobal == -1) break;

        printf("Paso %d: ", i);
        print_bin(patrones[index]);
        printf("\n");

        leds(patrones[index]);
        retardoInteractivo(velocidadGlobal);

        index = (index + 1) % 7;
    }

    printf("Secuencia 'Explosión y Contracción' finalizada.\n");
    leds(0x00);
    velocidadGlobal = 100000;
    restaurarEntradaNormal();
} 