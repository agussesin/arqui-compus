
#include <iostream> 
#include <stdio.h>
using namespace std; 


void autoFantastico();
void elChoque();
void secuenciaPropia1();
void secuenciaPropia2();

void mostrarMenu() {
    cout<<"--- MENU DE SECUENCIAS ---";
    cout<<"1. Auto Fantástico\n";
    cout<<"2. El Choque";
    cout<<"3. Secuencia Propia 1";
    cout<<"4. Secuencia Propia 2";
    cout<<"5. Salir";
    cout<<"Seleccione una opción: ";
}

int main() {
    int opcion = 0;

    while (1) {
        mostrarMenu();
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                autoFantastico();
                break;
            case 2:
                elChoque();
                break;
            case 3:
                secuenciaPropia1();
                break;
            case 4:
                secuenciaPropia2();
                break;
            case 5:
                cout<< "Saliendo del programa...";
                return 0;
            default:
                cout<< "Opción inválida. Intente de nuevo";
        }
    }

    return 0;
}

// FUNCIONES DE EJEMPLO
void autoFantastico() {
    cout<<"[Auto Fantástico ejecutándose...]";
}

void elChoque() {
    cout<< "[El Choque ejecutándose...]";
}

void secuenciaPropia1() {
    cout<< "[Secuencia Propia 1 ejecutándose...]";
}

void secuenciaPropia2() {
    cout<< "[Secuencia Propia 2 ejecutándose...]";
}
