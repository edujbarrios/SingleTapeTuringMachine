#include "tape.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

/**
 * @file tape.cc
 * @brief Implementación de la clase Tape para la Máquina de Turing.
 */

/**
 * @brief Constructor por defecto de Tape.
 * Inicializa el contenido de la cinta y la posición a valores por defecto.
 */
Tape::Tape() {
    // Inicializa el contenido de la cinta y la posición a valores por defecto
    content = "$$";
    position = 1;
}

/**
 * @brief Constructor de Tape que inicializa la cinta con el contenido de un archivo.
 * @param tape_file Nombre del archivo que contiene la cinta inicial.
 * @exception runtime_error Excepción lanzada si hay problemas al abrir o leer el archivo.
 */
Tape::Tape(const std::string& tape_file) {
    // Comprobar si el archivo es un archivo de cinta válido
    if (tape_file.find(".tape") == std::string::npos) {
        throw std::runtime_error("El archivo no tiene el tipo/extensión correcto, debería ser <nombre_archivo>.tape");
    }

    // Abrir el archivo .tape
    std::ifstream file(tape_file);
    if (!file.is_open()) {
        throw std::runtime_error("Error: No se puede abrir el archivo " + tape_file);
    }

    // Leer el contenido inicial de la cinta
    file >> content;
    content = "$" + content + "$";
    position = 1;

    // Cerrar el archivo .tape
    file.close();
}

/**
 * @brief Destructor de Tape.
 */
Tape::~Tape() {}

/**
 * @brief Muestra el contenido actual de la cinta.
 * @param current_state Posición actual del cabezal de lectura/escritura.
 */
void Tape::display(int current_state) {
    // Imprime la parte de la cinta antes de la posición actual
    for (int positionBeforeHead = 0; positionBeforeHead < position; positionBeforeHead++) {
        std::cout << content[positionBeforeHead];
    }

    std::cout << " " << "q" << current_state << " ";

    // Imprime la parte de la cinta desde la posición actual en adelante
    for (int positionAfterHead = position; positionAfterHead < static_cast<int>(content.size()); positionAfterHead++) {
        std::cout << content[positionAfterHead];
    }

    std::cout << std::endl;
}


/**
 * @brief Lee el símbolo bajo el cabezal de lectura/escritura.
 * @return char El símbolo leído.
 */
char Tape::read() {
    return content[position];
}

/**
 * @brief Escribe un símbolo bajo el cabezal de lectura/escritura.
 * @param symbol El símbolo a escribir.
 */
void Tape::write(char symbol) {
    content[position] = symbol;
}

/**
 * @brief Mueve el cabezal de lectura/escritura hacia la izquierda.
 */
void Tape::move_left() {
    position--;
}

/**
 * @brief Mueve el cabezal de lectura/escritura hacia la derecha.
 */
void Tape::move_right() {
    position++;
}

/**
 * @brief Mantiene el cabezal de lectura/escritura en la posición actual.
 * La función stay no realiza ninguna acción.
 */
void Tape::stay() {
    // No hace nada, se queda en el mismo lugar
}
