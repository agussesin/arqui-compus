.global explosionYContraccion
.text

// explosionYContraccion: Implements a fixed pattern sequence that expands and contracts
// Uses AARCH64 instructions and calling conventions
explosionYContraccion:
    // Save registers (x19-x30 are callee-saved)
    stp x29, x30, [sp, #-16]!
    stp x19, x20, [sp, #-16]!
    mov x29, sp

    // Save parameter
    mov x19, x0

    // Configure non-blocking input
    bl configurarEntradaNoBloqueante

    // Initialize pattern index
    mov x20, #0      // x20 = current pattern index

explosion_loop:
    // Check if we should exit (velocidadGlobal == -1)
    adrp x0, velocidadGlobal
    ldr x0, [x0, #:lo12:velocidadGlobal]
    cmp x0, #-1
    beq explosion_fin

    // Load current pattern
    adrp x0, patrones
    add x0, x0, #:lo12:patrones
    ldrb w0, [x0, x20]
    bl leds

    // Get delay from velocidadGlobal
    adrp x0, velocidadGlobal
    ldr x0, [x0, #:lo12:velocidadGlobal]
    bl retardoInteractivo

    // Increment pattern index
    add x20, x20, #1
    cmp x20, #7
    b.lt explosion_loop

    // Reset pattern index
    mov x20, #0
    b explosion_loop

explosion_fin:
    // Restore normal input
    bl restaurarEntradaNormal

    // Turn off all LEDs
    mov x0, #0
    bl leds

    // Restore registers and return
    ldp x19, x20, [sp], #16
    ldp x29, x30, [sp], #16
    ret

.data
.align 2
patrones:
    .byte 0x18, 0x3C, 0x7E, 0xFF, 0x7E, 0x3C, 0x18
