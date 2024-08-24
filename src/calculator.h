#include <Arduino.h>
#include "stack.h"	
class Ccalculator {

    public:
        Ccalculator ();
        void process(char letter);
        const char* const getExpression();
        float getResult();

    private:
        enum state_t {idle, op, new_op};

        char expression[32];
        char tmpExpression[32];
        state_t state;
        Cstack <float> operanden;
        Cstack <char> operatoren;
        float akku;

        float calc(float op1, float op2, char _operator);
        void clearExpression();
        void expressionAdd(char c);

};