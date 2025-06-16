# Sistema de Secuencias de LEDs para Raspberry Pi

## Descripción
Este programa implementa un sistema de control de acceso con múltiples secuencias de LEDs que se pueden ejecutar en una Raspberry Pi.

## Características
- **Control de acceso**: Sistema de password con 3 intentos
- **4 secuencias de LEDs**:
  - Auto Fantástico
  - El Choque
  - Ascensor
  - Explosión y Contracción
- **Interrupción de secuencias**: Presiona 'q' para salir de cualquier secuencia
- **Control de velocidad en tiempo real**: Usa flechas ↑ y ↓ para ajustar la velocidad
- **Apagado automático**: Todas las luces se apagan al salir de una secuencia
- **Velocidad persistente**: La velocidad se mantiene entre diferentes secuencias

## Compilación en Raspberry Pi

### Prerrequisitos
Asegúrate de tener instalado el compilador GCC:
```bash
sudo apt update
sudo apt install build-essential
```

### Compilar el programa
```bash
gcc -o programa main.c
```

### Ejecutar el programa
```bash
./programa
```

## Uso del programa

### 1. Control de Acceso
- Password por defecto: `12345`
- Máximo 3 intentos antes de que el programa aborte

### 2. Menú Principal
```
--- MENU DE SECUENCIAS ---
1. Auto Fantástico
2. El Choque
3. Ascensor
4. Explosión y Contracción
5. Salir
Velocidad actual: 100000 microsegundos
Seleccione una opción:
```

### 3. Durante la ejecución de secuencias
- Cada secuencia muestra información sobre cómo salir y controlar velocidad
- **Controles disponibles**:
  - `q`, `Q` o `ESC`: Salir de la secuencia
  - `Flecha ↑`: Aumentar velocidad (más rápido)
  - `Flecha ↓`: Disminuir velocidad (más lento)
- **Rango de velocidad**: 10,000 a 500,000 microsegundos
- **Feedback visual**: La velocidad actual se muestra en tiempo real
- Al salir, todas las luces se apagan automáticamente (00000000)

### 4. Control de Velocidad
- **Velocidad inicial**: 100,000 microsegundos
- **Incremento/Decremento**: 10,000 microsegundos por flecha
- **Límites**:
  - Mínimo: 10,000 microsegundos (muy rápido)
  - Máximo: 500,000 microsegundos (muy lento)
- **Persistencia**: La velocidad se mantiene al cambiar entre secuencias

## Estructura de archivos
- `main.c` - Archivo principal del programa
- `funciones.c` - Todas las funciones del sistema (Raspberry Pi)
- `main_windows.c` - Versión para Windows
- `funciones_windows.c` - Funciones para Windows
- `programa` - Ejecutable compilado

## Compatibilidad
Este código está diseñado específicamente para sistemas Linux/Unix como Raspberry Pi OS, utilizando:
- `termios.h` - Para configuración de terminal
- `fcntl.h` - Para control de archivos
- `unistd.h` - Para funciones del sistema

## Notas importantes
- El programa requiere acceso al terminal para la entrada no bloqueante
- Funciona mejor en terminales que soporten entrada de caracteres especiales
- Las secuencias se pueden interrumpir en cualquier momento
- El control de velocidad es inmediato y se aplica al siguiente paso de la secuencia
- La velocidad ajustada se conserva entre llamadas a diferentes secuencias 