#pragma once
#include <Arduino.h>

template <class T>
class Cstack {
    public:
        Cstack() {
            lenght = 0;
        };

        void push(const T value){
            data[lenght] = value;
            lenght ++;
        };
        T pop(){
            lenght --;
            return data[lenght];
        };
        bool isEmpty() {
            return lenght == 0;
        };
    private:
        T data[8];
        uint8_t lenght;
};

