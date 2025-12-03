#pragma once
#include "List.h"
#include "Lexem.h"
#include "Stack.h"
#include <string>

struct variable {
    std::string name;
    double value;
    bool isSet;

    variable() : name(""), value(0.0), isSet(false) {}
    variable(const std::string& n) : name(n), value(0.0), isSet(false) {}
    variable(const std::string& n, double v) : name(n), value(v), isSet(true) {}

    bool operator==(const std::string& otherName) const {
        return name == otherName;
    }

    bool operator==(const variable& other) const {
        return name == other.name;
    }
};

class Expression {
private:
    int id;
    std::string original;
    List<Lexem> infix;
    List<Lexem> postfix;
    TVector<variable> vars;

public:
    Expression(int _id, const std::string& expr);

    void setVariable(const std::string& name, double value);
    void setVariables(const TVector<variable>& vars);
    bool allVariablesSet() const;

    double evaluate();

    int getId() const { return id; }
    std::string getOriginal() const { return original; }
    TVector<variable> getVariables() const { return vars; }

private:
    void toPostfix();
    double calculatePostfix();
    double getVariableValue(const std::string& name) const;
    void extractVariables();
    const variable* findVariable(const std::string& name) const;
};