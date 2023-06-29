#include "StateChange.h"
#include "States.h"

StateChange::StateChange(int n_change, int green, int yellow, int red){
    _current = States::INIT;
    _n_change = n_change;
    _green = green;
    _yellow = yellow;
    _red = red;
}

int StateChange::getCurrent(){
    return _current;
}

bool StateChange::medicion(int input){
    bool result = false;
    if (_current == States::INIT){
        _current = input;
        result = true;
    }
    if (input == _input){
        _count++;
    } else {
        _count = 0;
        _input = input;
    }
    if (_count == _n_change){
        _current = _input;
        result = true;
    }
    return result;
}

void StateChange::changeState(bool hasChanged){
    if (hasChanged){
        if (_current == States::GREEN){
            digitalWrite(_green, HIGH);
            digitalWrite(_yellow, LOW);
            digitalWrite(_red, LOW);
        } else if (_current == States::YELLOW){
            digitalWrite(_green, LOW);
            digitalWrite(_yellow, HIGH);
            digitalWrite(_red, LOW);
        } else if (_current == States::RED){
            digitalWrite(_green, LOW);
            digitalWrite(_yellow, LOW);
            digitalWrite(_red, HIGH);
        }
    }
}
