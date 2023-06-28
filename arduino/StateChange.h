#ifndef STATECHANGE_H
#define STATECHANGE_H

#include <Arduino.h>

class StateChange{
  private:
    //Valor actual
    int _current;
    //Valor ingresado
    int _input;
    //Cantidad de repeticiones consecutivas
    int _count = 0;
    //Cantidad necesaria para cambiar
    int _n_change;
    //Pins
    int _green, _yellow, _red;

  public:
    //Constructor
    StateChange(int n_change, int green, int yellow, int red);
    //Getters
    int getCurrent();
    //Funciones

    /*
    * Recibe una medicion y la compara con las anteriores
    */
    bool medicion(int input);

    /*
    * Cambia el estado del semaforo segun _current
    */
    void changeState(bool hasChanged);

};

#endif
