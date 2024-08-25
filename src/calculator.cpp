#include <Arduino.h>
#include "calculator.h"
#include "stack.h"

const char * const version = "FinnCalc V1.01";

Ccalculator::Ccalculator () : operanden(), operatoren() {
    state = idle;
    akku = 0;
    clearExpression();
    strcpy(expression,version);
}

bool isDigit(char letter) {
    return (letter >= '0') && (letter <= '9');
}

bool isOperator(char letter) {
    return letter == '+' || letter == '-' || letter == '*' || letter == '/';
}

uint32_t digit(char letter) {
    return (((int) letter) - 48);
}

char decodeOperator(char c)
{
    switch (c) {
        case 'A': return '+'; break;
        case 'B': return '-'; break;
        case 'C': return '*'; break;
        case 'D': return '/'; break;
        case '#': return '='; break;
        default: return c; break;
    }
}

void Ccalculator::process(char letter)
{
    letter = decodeOperator(letter);

    // update expresion string
    if ((state == idle) && isDigit(letter)) {
        clearExpression();
    }

    // update calculation logic
    switch(state) {
        case idle:
            if(isDigit(letter)) {
                akku = digit(letter);
                state = op;
                expressionAdd(letter);
           }
            break;
        case op:
            if(isDigit(letter)) {
                akku = (akku * 10) + digit(letter);
            }
            else if (isOperator(letter) || (letter == '=')) {
                operanden.push(akku);
                if (!operatoren.isEmpty()) {
                    float right = operanden.pop();
                    float left = operanden.pop();
                    char op = operatoren.pop();
                    akku = calc(left, right, op);
                    operanden.push(akku);
                }
                if (isOperator(letter)) {
                    operatoren.push(letter);
                    state = new_op;
                }
                else {
                    state = idle;
                    akku = operanden.pop();
                }
            }
            expressionAdd(letter);
            break;
        case new_op:
            if(isDigit(letter)) {
                akku = digit(letter);
                state = op;
                expressionAdd(letter);
            }
            break;

    }
    Serial.printf("state=%d, akku=%f, expression=%s tmpExpression=%s\n", state, akku, expression, tmpExpression);
}

const char* const Ccalculator::getExpression(){
    return expression;
}

float Ccalculator::getResult() {
    return akku;
}

float Ccalculator::calc(float op1, float op2, char _operator){
    switch (_operator) {
        case '+':
            return op1 + op2;
            break;
        case '-':
            return op1 - op2;
            break;
        case '*':
            return op1 * op2;
            break;
        case '/':
// Todo: handle op2 = 0
            return op1 / op2;
            break;
    }
    return 0;
}

void Ccalculator::clearExpression()
{
    *expression = 0;
    *tmpExpression = 0;
};

void Ccalculator::expressionAdd(char c)
{
    if (isDigit(c)) {
        strncat(tmpExpression, &c, 1);
    }
    else {
        strcat(expression, tmpExpression);
        *tmpExpression = 0; // clear tmpExpression
        strncat(expression, &c, 1);
    }
};
