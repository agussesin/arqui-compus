.global explosionYContraccion
.text

// Función principal que crea un efecto visual de explosión y contracción en los LEDs
explosionYContraccion:
    // Guardar registros que vamos a usar (r4-r7 son callee-saved, es decir, deben preservarse)
    push {r4-r7, lr}

    // Guardar el parámetro x0 en r4 (aunque no se usa en esta implementación)
    mov r4, r0  // x0 → r4

    // Establecer la velocidad inicial del efecto
    ldr r0, =velocidadGlobal
    ldr r1, =100000
    str r1, [r0]

    // Configurar la entrada del teclado en modo no bloqueante
    // Esto permite que el programa siga ejecutándose mientras espera entrada
    bl configurarEntradaNoBloqueante

    // Inicializar el índice para recorrer el patrón de LEDs
    mov r5, #0

// Bucle principal que controla la animación
loop_explosion:
    // Verificar si se presionó 'q' (velocidadGlobal = -1)
    ldr r0, =velocidadGlobal
    ldr r1, [r0]
    cmp r1, #-1
    beq fin_explosion

    // Cargar el patrón actual de la tabla de patrones
    // r5 es el índice que se usa para recorrer la tabla
    ldr r0, =patrones
    add r0, r0, r5
    ldrb r0, [r0]
    bl leds

    // Esperar el tiempo especificado por velocidadGlobal
    ldr r0, =velocidadGlobal
    ldr r0, [r0]
    bl retardoInteractivo

    // Verificar nuevamente si se presionó 'q' durante el retardo
    ldr r0, =velocidadGlobal
    ldr r0, [r0]
    cmp r0, #-1
    beq fin_explosion

    // Incrementar el índice y verificar si llegamos al final del patrón
    add r5, r5, #1
    cmp r5, #7
    blt loop_explosion

    // Si llegamos al final del patrón, reiniciar el índice
    mov r5, #0
    b loop_explosion

// Etiqueta para finalizar la animación
fin_explosion:
    // Restaurar la configuración normal de entrada
    bl restaurarEntradaNormal

    // Apagar todos los LEDs
    mov r0, #0
    bl leds

    // Restaurar los registros guardados y volver a la función llamante
    pop {r4-r7, lr}
    bx lr

.data
.align 2
// Tabla de patrones para la animación
// Cada byte representa un patrón de LEDs (1 = encendido, 0 = apagado)
// Los patrones crean un efecto de expansión y contracción
patrones:
    .byte 0x18, 0x3C, 0x7E, 0xFF, 0x7E, 0x3C, 0x18
    // 0x18 = 00011000 (2 LEDs centrales)
    // 0x3C = 00111100 (4 LEDs centrales)
    // 0x7E = 01111110 (6 LEDs centrales)
    // 0xFF = 11111111 (todos los LEDs)
    // Luego se contrae de nuevo al centro