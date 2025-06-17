.global ascensor
.text

ascensor:
    push {r4-r7, lr}
    mov r4, r0

    bl configurarEntradaNoBloqueante

    mov r5, #1
    mov r6, #0
    mov r7, #255

loop:
    ldr r0, =velocidadGlobal
    ldr r0, [r0]
    cmp r0, #-1
    beq fin

    mov r0, r5
    bl leds

    ldr r0, =velocidadGlobal
    ldr r0, [r0]
    bl retardoInteractivo

    lsl r5, r5, #1
    orr r5, r5, #1

    cmp r5, r7
    bne loop

    mov r5, #1
    b loop

fin:
    bl restaurarEntradaNormal
    mov r0, #0
    bl leds
    pop {r4-r7, lr}
    bx lr

