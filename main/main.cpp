// Copyright 2024 Marina Usova

#include "Calculator.h"
#include "Expression.h"
#include <iostream>
#include <string>
#include <sstream>

void printMenu() {
    std::cout << "\n=== CALCULATOR MENU ===\n";
    std::cout << "1. Create new expression\n";
    std::cout << "2. Delete expression\n";
    std::cout << "3. Set variables\n";
    std::cout << "4. Evaluate expression\n";
    std::cout << "0. Exit\n";
    std::cout << "Your choice: ";
}

int main() {
    Calculator calc;
    int choice;
    std::string input;

    while (true) {
        printMenu();

        std::string input;
        std::getline(std::cin, input);

        if (input.length() != 1 || !std::isdigit(input[0])) {
            std::cout << "Invalid input. Please enter a number (0-4).\n";
            continue;
        }

        choice = input[0] - '0';

        if (choice == 0) {
            std::cout << "Exiting...\n";
            break;
        }

        try {
            switch (choice) {
            case 1: {
                std::cout << "Enter expression: ";
                std::string expr;
                std::getline(std::cin, expr);

                int id = calc.createExpression(expr);
                std::cout << "Expression created with ID = " << id << std::endl;
                break;
            }

            case 2: {
                std::cout << "Enter expression ID: ";
                std::string idStr;
                std::getline(std::cin, idStr);

                try {
                    int id = std::stoi(idStr);
                    if (calc.deleteExpression(id)) {
                        std::cout << "Expression deleted\n";
                    }
                    else {
                        std::cout << "Expression not found\n";
                    }
                }
                catch (...) {
                    std::cout << "Invalid ID format\n";
                }
                break;
            }

            case 3: {
                std::cout << "Enter expression ID: ";
                std::string idStr;
                std::getline(std::cin, idStr);

                try {
                    int id = std::stoi(idStr);

                    if (!calc.expressionExists(id)) {
                        std::cout << "Expression not found\n";
                        break;
                    }

                    Expression* expr = calc.getExpression(id);
                    TVector<variable> vars = expr->getVariables();

                    if (vars.size() == 0) {
                        std::cout << "Expression has no variables\n";
                        break;
                    }

                    std::cout << "Expression variables:\n";
                    for (int i = 0; i < vars.size(); i++) {
                        std::cout << "  " << vars[i].name << " = ";
                        if (vars[i].isSet) {
                            std::cout << vars[i].value;
                        }
                        else {
                            std::cout << "?";
                        }
                        std::cout << std::endl;
                    }

                    std::cout << "Enter variable values (format: name=value):\n";
                    std::cout << "Enter empty line to finish\n";

                    TVector<variable> newVars;
                    std::string line;

                    while (true) {
                        std::cout << "> ";
                        std::getline(std::cin, line);
                        if (line.empty()) break;

                        size_t eqPos = line.find('=');
                        if (eqPos != std::string::npos) {
                            std::string name = line.substr(0, eqPos);
                            std::string valueStr = line.substr(eqPos + 1);

                            double value;
                            try {
                                value = std::stod(valueStr);
                            }
                            catch (...) {
                                std::cout << "Invalid number: " << valueStr << std::endl;
                                continue;
                            }

                            newVars.push_back(variable(name, value));
                        }
                        else {
                            std::cout << "Invalid format. Use: name=value\n";
                        }
                    }

                    if (newVars.size() > 0) {
                        calc.setVariables(id, newVars);
                        std::cout << "Variables set\n";
                    }
                }
                catch (...) {
                    std::cout << "Invalid ID format\n";
                }
                break;
            }

            case 4: {
                std::cout << "Enter expression ID: ";
                std::string idStr;
                std::getline(std::cin, idStr);

                try {
                    int id = std::stoi(idStr);

                    if (!calc.expressionExists(id)) {
                        std::cout << "Expression not found\n";
                        break;
                    }

                    double result = calc.evaluateExpression(id);
                    std::cout << "Result: " << result << std::endl;
                }
                catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << std::endl;
                }
                catch (...) {
                    std::cout << "Invalid ID format or unknown error\n";
                }
                break;
            }

            default:
                std::cout << "Invalid choice. Please enter a number between 0 and 4.\n";
            }
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
        catch (...) {
            std::cout << "Unknown error occurred\n";
        }
    }

    return 0;
}