#pragma once
#include "List.h"
#include "Lexem.h"
#include <string>
#include <cctype>
#include <stdexcept>
#include "MathFunction.h"

class Parser {

public:

    List<Lexem> parse(const std::string& expression);
    bool isFunction(const std::string& str);
    Lexem parseNumber(const std::string& expr, std::size_t& pos);
    Lexem parseWord(const std::string& expr, std::size_t& pos);
    Lexem parseOperator(char oper, bool isUnary);
    void processUnaryMinus(List<Lexem>& lexems);
    void checkSyntax(List<Lexem>& lexems);
    void AbsoluteBars(List<Lexem>& lexem);
};