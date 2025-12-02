#pragma once
#include "Expression.h"
#include "List.h"
#include <string>
#include <iostream>

class Calculator {
private:
    TVector<Expression*> expressions;
    int nextId;

public:
    Calculator() : nextId(1) {}

    ~Calculator() {
        for (int i = 0; i < expressions.size(); i++) {
            delete expressions[i];
        }
    }

    int createExpression(const std::string& expr) {
        try {
            Expression* newExpr = new Expression(nextId, expr);
            expressions.push_back(newExpr);
            return nextId++;
        }
        catch (const std::exception& e) {
            throw std::logic_error("Failed to create expression: " + std::string(e.what()));
        }
    }

    bool deleteExpression(int id) {
        for (int i = 0; i < expressions.size(); i++) {
            if (expressions[i]->getId() == id) {
                delete expressions[i];
                expressions.erase(i);
                return true;
            }
        }
        return false;
    }

    bool setVariables(int id, const TVector<variable>& vars) {
        for (int i = 0; i < expressions.size(); i++) {
            if (expressions[i]->getId() == id) {
                expressions[i]->setVariables(vars);
                return true;
            }
        }
        return false;
    }

    double evaluateExpression(int id) {
        for (int i = 0; i < expressions.size(); i++) {
            if (expressions[i]->getId() == id) {
                return expressions[i]->evaluate();
            }
        }
        throw std::logic_error("Expression not found");
    }

    bool expressionExists(int id) const {
        for (int i = 0; i < expressions.size(); i++) {
            if (expressions[i]->getId() == id) {
                return true;
            }
        }
        return false;
    }

    Expression* getExpression(int id) {
        for (int i = 0; i < expressions.size(); i++) {
            if (expressions[i]->getId() == id) {
                return expressions[i];
            }
        }
        return nullptr;
    }

    void printAllExpressions() const {
        if (expressions.empty()) {
            std::cout << "No expressions\n";
            return;
        }

        std::cout << "\n=== ALL EXPRESSIONS ===\n";
        for (int i = 0; i < expressions.size(); i++) {
            Expression* expr = expressions[i];
            std::cout << "ID " << expr->getId() << ": " << expr->getOriginal() << "\n";

            TVector<variable> vars = expr->getVariables();
            if (!vars.empty()) {
                std::cout << "  Variables: ";
                for (int j = 0; j < vars.size(); j++) {
                    std::cout << vars[j].name << "=";
                    if (vars[j].isSet) {
                        std::cout << vars[j].value;
                    }
                    else {
                        std::cout << "?";
                    }
                    if (j < vars.size() - 1) std::cout << ", ";
                }
                std::cout << "\n";
            }
            std::cout << "-------------------\n";
        }
    }
};