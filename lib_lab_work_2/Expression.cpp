#include "Expression.h"
#include "Parser.h"
#include <stdexcept>

Expression::Expression(int _id, const std::string& expr) : id(_id), original(expr) {
    infix = Parser::parse(expr);
    extractVariables();
    toPostfix();
}

void Expression::extractVariables() {
    vars.clear();

    for (auto it = infix.begin(); it != infix.end(); ++it) {
        Lexem lex = *it;
        if (lex.isVar()) {
            std::string varName = lex.getName();

            bool found = false;
            for (int i = 0; i < vars.size(); i++) {
                if (vars[i].name == varName) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                vars.push_back(variable(varName));
            }
        }
    }
}

void Expression::setVariable(const std::string& name, double value) {
    for (int i = 0; i < vars.size(); i++) {
        if (vars[i].name == name) {
            vars[i].value = value;
            vars[i].isSet = true;
            return;
        }
    }

    vars.push_back(variable(name, value));
}

void Expression::setVariables(const TVector<variable>& vars) {
    for (int i = 0; i < vars.size(); i++) {
        setVariable(vars[i].name, vars[i].value);
    }
}

bool Expression::allVariablesSet() const {
    for (int i = 0; i < vars.size(); i++) {
        if (!vars[i].isSet) {
            return false;
        }
    }
    return true;
}

variable* Expression::findVariable(const std::string& name) {
    for (int i = 0; i < vars.size(); i++) {
        if (vars[i].name == name) {
            return &vars[i];
        }
    }
    return nullptr;
}

const variable* Expression::findVariable(const std::string& name) const {
    for (int i = 0; i < vars.size(); i++) {
        if (vars[i].name == name) {
            return &vars[i];
        }
    }
    return nullptr;
}

double Expression::getVariableValue(const std::string& name) const {
    const variable* var = findVariable(name);
    if (var == nullptr) {
        throw std::logic_error("Variable not found: " + name);
    }
    if (!var->isSet) {
        throw std::logic_error("Variable not set: " + name);
    }
    return var->value;
}

void Expression::toPostfix() {
    Stack<Lexem> operators;
    postfix.clear();

    for (auto it = infix.begin(); it != infix.end(); ++it) {
        Lexem lex = *it;

        if (lex.isConst() || lex.isVar()) {
            postfix.push_back(lex);
        }
        else if (lex.getType() == OpenBracket) {
            operators.push(lex);
        }
        else if (lex.isFunction()) {
            operators.push(lex);
        }
        else if (lex.getType() == ClosedBracket) {
            while (!operators.is_empty() && operators.top().getType() != OpenBracket) {
                postfix.push_back(operators.pop());
            }

            if (operators.is_empty()) {
                throw std::logic_error("Mismatched brackets");
            }

            operators.pop();

            if (!operators.is_empty() && operators.top().isFunction()) {
                postfix.push_back(operators.pop());
            }
        }
        else if (lex.isOper()) {
            while (!operators.is_empty() &&
                operators.top().isOper() &&
                operators.top().getPriority() >= lex.getPriority()) {
                postfix.push_back(operators.pop());
            }
            operators.push(lex);
        }
    }

    while (!operators.is_empty()) {
        if (operators.top().getType() == OpenBracket) {
            throw std::logic_error("Mismatched brackets");
        }
        postfix.push_back(operators.pop());
    }
}

double Expression::calculatePostfix() {
    Stack<double> values;

    for (auto it = postfix.begin(); it != postfix.end(); ++it) {
        Lexem lex = *it;

        if (lex.isConst()) {
            values.push(lex.getValue());
        }
        else if (lex.isVar()) {
            double val = getVariableValue(lex.getName());
            values.push(val);
        }
        else if (lex.isFunction()) {
            if (values.is_empty()) {
                throw std::logic_error("Calculation error: empty stack");
            }
            double arg = values.pop();
            values.push(lex.executeFun(arg));
        }
        else if (lex.isOper()) {
            if (values.is_empty()) {
                throw std::logic_error("Calculation error: empty stack");
            }
            double right = values.pop();

            if (values.is_empty()) {
                throw std::logic_error("Calculation error: not enough operands");
            }
            double left = values.pop();

            values.push(lex.executeOper(left, right));
        }
    }

    if (values.is_empty()) {
        throw std::logic_error("Calculation error: no result");
    }

    return values.pop();
}

double Expression::evaluate() {
    if (!allVariablesSet()) {
        throw std::logic_error("Not all variables are set");
    }
    return calculatePostfix();
}