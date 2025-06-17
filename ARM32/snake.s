.global snake
.text

// Función principal que crea un efecto visual de "serpiente" en los LEDs
// El efecto consiste en un patrón que se mueve de derecha a izquierda
snake:
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

    // Inicializar valores para el patrón
    mov r5, #1      // patrón inicial (00000001)
    mov r6, #255    // valor máximo (11111111 o 0xFF)

// Bucle principal que controla la animación
loop_snake:
    // Verificar si se presionó 'q' (velocidadGlobal = -1)
    ldr r0, =velocidadGlobal
    ldr r1, [r0]
    cmp r1, #-1
    beq fin_snake

    // Mostrar el patrón actual en los LEDs
    mov r0, r5
    bl leds

    // Esperar el tiempo especificado por velocidadGlobal
    ldr r0, =velocidadGlobal
    ldr r0, [r0]
    bl retardoInteractivo

    // Verificar nuevamente si se presionó 'q' durante el retardo
    ldr r0, =velocidadGlobal
    ldr r0, [r0]
    cmp r0, #-1
    beq fin_snake

    // Desplazar el patrón una posición a la izquierda y agregar un 1 al final
    // Esto crea el efecto de "serpiente" moviéndose
    lsl r5, r5, #1  // Desplazar a la izquierda
    orr r5, r5, #1  // Agregar 1 al final

    // Verificar si llegamos al patrón máximo (0xFF)
    // Si no es igual, continuar el bucle
    cmp r5, r6
    bne loop_snake

    // Si llegamos al patrón máximo, reiniciar con el patrón inicial
    mov r5, #1
    b loop_snake

// Etiqueta para finalizar la animación
fin_snake:
    // Restaurar la configuración normal de entrada
    bl restaurarEntradaNormal

    // Apagar todos los LEDs
    mov r0, #0
    bl leds

    // Restaurar los registros guardados y volver a la función llamante
    pop {r4-r7, lr}
    bx lr