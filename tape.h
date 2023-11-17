// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 9: Simulador de máquina de Turing
// Autor: Eduardo José Barrios García
// Correo: alu01013410190@ull.edu.es

#include <iostream>
#include <vector>
#include <string>
#include <map>

#ifndef TAPE_H
#define TAPE_H

/**
 * @file Tape.h
 * @brief Define la clase Tape, que representa la cinta de una Máquina de Turing.
 */

/**
 * @class Tape
 * @brief Representa la cinta utilizada en una Máquina de Turing.
 * 
 * Esta clase gestiona las operaciones básicas que se pueden realizar sobre la cinta,
 * como leer, escribir y mover el cabezal de lectura/escritura.
 */
class Tape
{
public:
    /**
     * @brief Constructor por defecto de Tape.
     */
    Tape();

    /**
     * @brief Constructor de Tape que inicializa la cinta con el contenido de un archivo.
     * @param tape_file Nombre del archivo que contiene la cinta inicial.
     */
    Tape(const std::string& tape_file);

    /**
     * @brief Destructor de Tape.
     */
    ~Tape();

    /**
     * @brief Muestra el contenido actual de la cinta.
     * @param current_state Posición actual del cabezal de lectura/escritura.
     */
    void display(int current_state);

    /**
     * @brief Lee el símbolo bajo el cabezal de lectura/escritura.
     * @return char El símbolo leído.
     */
    char read();

    /**
     * @brief Escribe un símbolo bajo el cabezal de lectura/escritura.
     * @param symbol El símbolo a escribir.
     */
    void write(char symbol);

    /**
     * @brief Mueve el cabezal de lectura/escritura hacia la izquierda.
     */
    void move_left();

    /**
     * @brief Mueve el cabezal de lectura/escritura hacia la derecha.
     */
    void move_right();

    /**
     * @brief Mantiene el cabezal de lectura/escritura en la posición actual.
     */
    void stay();

private:
    // El contenido de la cinta
    std::string content;

    // La posición del cabezal de lectura/escritura
    int position;
};

#endif // TAPE_H
