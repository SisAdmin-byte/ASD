#pragma once
#include <string>
#include <cmath>
#include <stdexcept>

enum TypeLexem {
    Constant,
    Variable,
    OpenBracket,
    ClosedBracket,
    Function,
    Operator,
    UnOperator,
    OpenedAbs,
    ClosedAbs
};

struct Lexem {
    std::string name;
    TypeLexem type;
    double value;
    int priority;
    double (*function)(double);
    Lexem(std::string _name, TypeLexem _type, double _value = 0.0,
        int _priority = -1, double(*_function)(double) = nullptr)
        : name(_name), type(_type), value(_value),
        priority(_priority), function(_function) {
    }

    bool isConst() const { return type == Constant; }
    bool isVar() const { return type == Variable; }
    bool isBracket() const { return type == OpenBracket || type == ClosedBracket;; }
    bool isFunction() const { return type == Function; }
    bool isOper() const { return type == Operator; }
    bool isUnOperator() const { return type == UnOperator; }
    bool isOpenedAbs() const { return type == OpenedAbs; }
    bool isClosedAbs() const { return type == ClosedAbs; }

    std::string getName() const { return name; }
    int getPriority() const { return priority; }
    double getValue() const { return value; }
    TypeLexem getType() const { return type; }

    void setValue(double val) { value = val; }

    double executeFun(double arg) const {
        if (type == Function) {
            if (function != nullptr) {
                return function(arg);
            }
            throw std::logic_error("No function assigned to lexem: " + name);
        }
        else if (type == UnOperator) {
            if (name == "-") {
                return -arg;
            }
            throw std::logic_error("Unknown unary operator: " + name);
        }
        throw std::logic_error("Lexem is not a function or unary operator: " + name);
    }

    double executeOper(double left, double right) const {
        if (type != Operator) {
            throw std::logic_error("Lexem is not an operator: " + name);
        }

        if (name == "+") return left + right;
        if (name == "-") return left - right;
        if (name == "*") return left * right;
        if (name == "/") {
            if (right == 0) {
                throw std::logic_error("Division by zero");
            }
            return left / right;
        }
        if (name == "^") {
            return pow(left, right);
        }
        throw std::logic_error("Unknown operator: " + name);
    }
};