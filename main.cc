#include <iostream>
#include "turing_machine.h"

/**
 * @brief Punto de entrada principal para la simulación de la Máquina de Turing.
 *
 * @param argc Número de argumentos de línea de comandos.
 * @param argv Array de argumentos de línea de comandos.
 * @return int Código de retorno del programa.
 */
int main(int argc, char* argv[]) {
    // Verifica los argumentos de la línea de comandos
    if (argc != 3) {
        std::cout << "Uso: " << argv[0] << " <archivo_tm> <archivo_cinta>" << std::endl;
        return 1;
    }

    try {
        // Crea la Máquina de Turing
        TuringMachine tm(argv[1]);

        char option;
        std::cout << "¿Desea mostrar la tabla de transición? (S)i/(N)o: ";
        std::cin >> option;

        // Muestra la tabla de transición si el usuario lo solicita
        if (option == 's' || option == 'S')
            tm.display();

        std::cout << "Simulando la máquina de Turing con la cinta dada" << std::endl;

        // Simula el comportamiento de la Máquina de Turing
        tm.simulate(argv[2]);
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
