#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include "turing_machine.h"
#include "tape.h"

/**
 * @brief Constructor de la clase TuringMachine.
 * @param tm_file Nombre del archivo que contiene la definición de la máquina de Turing.
 * @throw runtime_error Si el archivo no tiene la extensión correcta o no se puede abrir.
 */
TuringMachine::TuringMachine(const std::string& tm_file) {
    if (tm_file.find(".tm") == std::string::npos) {
        throw std::runtime_error("El fichero no tiene la extension correcta, debería ser: <filename>.tm");
    }

    std::ifstream file(tm_file);
    if (!file.is_open()) {
        throw std::runtime_error("Error: No se puede abrir el fichero " + tm_file);
    }

    std::string line;

    // Leer y validar el número de estados
    if (!getline(file, line) || !(std::istringstream(line) >> num_states)) {
        throw std::runtime_error("Error: Fallo al leer el número de estados - el formato no es correcto");
    }

    // Leer y validar el estado inicial
    if (!getline(file, line) || !(std::istringstream(line) >> start_state)) {
        throw std::runtime_error("Error: Fallo al leer el estado inicial - el formato no es correcto");
    }
    current_state = start_state;

    // Leer y validar los estados de aceptación
    getline(file, line);
    std::stringstream ss(line);
    std::string state_str;
    while (ss >> state_str) {
        try {
            int state = std::stoi(state_str);
            accepting_states.push_back(state);
        } catch (const std::invalid_argument&) {
            throw std::runtime_error("Error: Uno de los estados de aceptación no es un número válido");
        }
    }

    // Leer y validar el número de tuplas
    if (!getline(file, line) || !(std::istringstream(line) >> num_tuples)) {
        throw std::runtime_error("Error: Fallo al leer el número de tuplas - el formato no es correcto");
    }

    // Leer y construir las tuplas para la tabla de transición
    for (int i = 0; i < num_tuples; i++) {
        Tuple tuple;
        if (!(file >> tuple.state >> tuple.input >> tuple.write >> tuple.movement >> tuple.nextstate)) {
            throw std::runtime_error("Error: Fallo al leer una tupla en el input - el formato no es correcto");
        }
        transition_table[std::make_pair(tuple.state, tuple.input)] = tuple;
        transition_tuples.push_back(std::make_pair(tuple.state, tuple.input));
    }

    file.close();
}

/**
 * @brief Destructor de la clase TuringMachine.
 */
TuringMachine::~TuringMachine() {}

/**
 * @brief Muestra la información de la Máquina de Turing.
 * 
 * Esta función imprime el número de estados, el estado inicial, los estados de aceptación,
 * y la tabla de transición de la Máquina de Turing.
 */

void TuringMachine::display() {
    std::cout << "\n- Número de estados: " << num_states << std::endl;
    std::cout << "- Estado inicial: " << start_state << std::endl;

    std::cout << "- Estados de aceptación:";
    for (int accepting_state : accepting_states) {
        std::cout << " " << accepting_state;
    }
    std::cout << std::endl;

    std::cout << "\nTabla de transición:\n" << std::endl;
    for (auto item : transition_tuples) {
        Tuple tuple = transition_table[item];
        display_tuple(tuple);
    }

    std::cout << std::endl;
}


/**
 * @brief Simula el comportamiento de la máquina de Turing.
 * @param tape_file Nombre del archivo que contiene la cinta inicial.
 */
void TuringMachine::simulate(const std::string& tape_file) {
    tape = Tape(tape_file);
    tape.display(current_state);

    // Bucle principal de la simulación
    while (true) {
        char symbol = tape.read();
        std::pair<int, char> key(current_state, symbol);
        std::map<std::pair<int, char>, Tuple>::iterator it = transition_table.find(key);

        if (it == transition_table.end()) {
            break;
        }
        Tuple tuple = it->second;

        tape.write(tuple.write);

        if (tuple.movement == 'L') {
            tape.move_left();
        } else if (tuple.movement == 'R') {
            tape.move_right();
        } else if (tuple.movement == 'S') {
            tape.stay();
        } else {
            throw std::runtime_error("El carácter del movimento '" + std::string(1, tuple.movement) + "' no es válido. Debe ser 'R', 'L', o 'S'.");
        }

        current_state = tuple.nextstate;
        tape.display(current_state);
    }

    // Comprobación del estado de aceptación
    bool is_accepted = false;
    for (size_t i = 0; i < accepting_states.size(); i++) {
        if (current_state == accepting_states[i]) {
            is_accepted = true;
            break;
        }
    }

    // Impresión del resultado de la simulación
    if (is_accepted) {
        std::cout << "\nCadena ACEPTADA" << std::endl;
    } else {
        std::cout << "\nCadena RECHAZADA" << std::endl;
    }
}

/**
 * @brief Muestra una tupla de la tabla de transición.
 * @param tuple La tupla a mostrar.
 * @note Método utilizado solo para comprobación durante el desarrollo.
 */
void TuringMachine::display_tuple(TuringMachine::Tuple tuple) {
    std::cout << tuple.state << " " << tuple.input << " " << tuple.write << " " << tuple.movement << " " << tuple.nextstate << std::endl;
}
