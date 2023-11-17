#include <vector>
#include <string>
#include <map>
#include "tape.h"

#ifndef TURING_MACHINE_H
#define TURING_MACHINE_H

/**
 * @file turing_machine.h
 * @brief Define la clase TuringMachine, que representa una máquina de Turing.
 */

/**
 * @class TuringMachine
 * @brief Representa una Máquina de Turing.
 * 
 * Esta clase gestiona las operaciones de una Máquina de Turing, incluyendo la simulación
 * de su comportamiento con una cinta dada.
 */
class TuringMachine {
public:
    /**
     * @brief Constructor de TuringMachine.
     * @param tm_file Nombre del archivo que contiene la definición de la máquina de Turing.
     */
    TuringMachine(const std::string& tm_file);

    /**
     * @brief Destructor de TuringMachine.
     */
    ~TuringMachine();
    //MUestra la tabla de transicion
    void display();
    /**
     * @brief Simula el comportamiento de la máquina de Turing.
     * @param tape_file Nombre del archivo que contiene la cinta inicial.
     */
    void simulate(const std::string& tape_file);

private:
    /**
     * @struct Tuple
     * @brief Representa una tupla en la tabla de transición de la máquina de Turing.
     */
    struct Tuple {
        int state; ///< Estado actual.
        char input; ///< Símbolo de entrada.
        char write; ///< Símbolo a escribir en la cinta.
        char movement; ///< Dirección del movimiento del cabezal.
        int nextstate; ///< Siguiente estado.
    };

    int num_states; ///< Número total de estados.
    int start_state; ///< Estado inicial.
    int num_tuples; ///< Número de tuplas en la tabla de transición.

    std::vector<std::pair<int, char> > transition_tuples; ///< Vectores de pares de estado y entrada.

    /**
     * @brief La tabla de transición de la máquina de Turing.
     */
    std::map<std::pair<int, char>, Tuple> transition_table;

    /**
     * @brief Conjunto de estados de aceptación de la máquina de Turing.
     */
    std::vector<int> accepting_states;


    /**
     * @brief Estado actual de la máquina de Turing.
     */
    int current_state;

    /**
     * @brief La cinta de la máquina de Turing.
     */
    Tape tape;

    /**
     * @brief Muestra una tupla.
     * @param tuple La tupla a mostrar.
     * No se usa, solo era para comprobar que se leian bien los datos
     */
    void display_tuple(Tuple tuple);
};

#endif // TURING_MACHINE_H
