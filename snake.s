.global snake
.text

// snake: Implements a snake/ascensor effect that shifts bits left and adds 1
// until reaching 0xFF, then restarts
// Uses AARCH64 instructions and calling conventions
snake:
    // Save registers (x19-x30 are callee-saved)
    stp x29, x30, [sp, #-16]!
    stp x19, x20, [sp, #-16]!
    mov x29, sp

    // Save parameter
    mov x19, x0

    // Configure non-blocking input
    bl configurarEntradaNoBloqueante

    // Initialize registers
    mov x20, #1      // x20 = current pattern (starts with 1)
    mov x21, #255    // x21 = max value (0xFF)

snake_loop:
    // Check if we should exit (velocidadGlobal == -1)
    adrp x0, velocidadGlobal
    ldr x0, [x0, #:lo12:velocidadGlobal]
    cmp x0, #-1
    beq snake_fin

    // Update LEDs with current pattern
    mov x0, x20
    bl leds

    // Get delay from velocidadGlobal
    adrp x0, velocidadGlobal
    ldr x0, [x0, #:lo12:velocidadGlobal]
    bl retardoInteractivo

    // Shift left and add 1
    lsl x20, x20, #1
    orr x20, x20, #1

    // Check if we reached max value
    cmp x20, x21
    b.ne snake_loop

    // Reset pattern to 1
    mov x20, #1
    b snake_loop

snake_fin:
    // Restore normal input
    bl restaurarEntradaNormal

    // Turn off all LEDs
    mov x0, #0
    bl leds

    // Restore registers and return
    ldp x19, x20, [sp], #16
    ldp x29, x30, [sp], #16
    ret 