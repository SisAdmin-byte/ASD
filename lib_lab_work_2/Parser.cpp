#include "Parser.h"
#include "Lexem.h"
#include <cctype>
#include <stdexcept>

List<Lexem> Parser::parse(const std::string& expression) {
    List<Lexem> result;
    size_t pos = 0;
    bool flag = true;

    while (pos < expression.length()) {
        char c = expression[pos];

        if (std::isspace(c)) {
            pos++;
            continue;
        }

        if (std::isdigit(c) || c == '.') {
            result.push_back(parseNumber(expression, pos));
            flag = false;
        }
        else if (std::isalpha(c) || c == '_') {
            Lexem lexem = parseWord(expression, pos);
            result.push_back(lexem);

            if (lexem.isFunction()) {
                flag = true;
            }
            else {
                flag = false;
            }
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            bool isUnary = (c == '-' && flag);
            result.push_back(parseOperator(c, isUnary));
            pos++;
            flag = true;
        }
        else if (c == '(' || c == '[' || c == '{') {
            result.push_back(Lexem(std::string(1, c), OpenBracket));
            pos++;
            flag = true;
        }
        else if (c == ')' || c == ']' || c == '}') {
            result.push_back(Lexem(std::string(1, c), ClosedBracket));
            pos++;
            flag = false;
        }
        else if (c == '|') {
            TypeLexem type = (flag ? OpenedAbs : ClosedAbs);
            result.push_back(Lexem("|", type));
            pos++;
            flag = !flag;
        }
        else {
            std::string error = "Unknown symbol '";
            error += c;
            error += "' on position ";
            error += std::to_string(pos);
            throw std::logic_error(error);
        }
    }

    processUnaryMinus(result);
    AbsoluteBars(result);
    checkSyntax(result);

    return result;
}

Lexem Parser::parseNumber(const std::string& expr, std::size_t& pos) {
    std::string number;
    bool flagForDot = false;

    while (pos < expr.length() && (std::isdigit(expr[pos]) || expr[pos] == '.')) {
        if (expr[pos] == '.') {
            if (flagForDot) {
                throw std::logic_error("Error: two dots");
            }
            flagForDot = true;
        }
        number += expr[pos];
        pos++;
    }

    if (number.empty()) {
        throw std::logic_error("Error: empty number");
    }

    if (number.back() == '.') {
        throw std::logic_error("Error: A number cannot end with a dot!");
    }

    double value;
    try {
        value = std::stod(number);
    }
    catch (...) {
        throw std::logic_error("Incorrect number: " + number);
    }

    return Lexem(number, Constant, value);
}

Lexem Parser::parseWord(const std::string& expr, std::size_t& pos) {
    std::string word;
    while (pos < expr.length() && (std::isalnum(expr[pos]) || expr[pos] == '_')) {
        word += expr[pos];
        pos++;
    }

    if (word.empty()) {
        throw std::logic_error("Empty name");
    }

    if (std::isdigit(word[0])) {
        throw std::logic_error("Name variable cannot start from number: " + word);
    }

    if (isFunction(word)) {
        // Функции должны иметь высокий приоритет (например, 4)
        if (word == "sin") {
            return Lexem("sin", Function, 0.0, 4, MathFunctions::Sin);
        }
        else if (word == "cos") {
            return Lexem("cos", Function, 0.0, 4, MathFunctions::Cos);
        }
        else if (word == "tg") {
            return Lexem("tg", Function, 0.0, 4, MathFunctions::tg);
        }
        else if (word == "ln") {
            return Lexem("ln", Function, 0.0, 4, MathFunctions::ln);
        }
        else if (word == "exp") {
            return Lexem("exp", Function, 0.0, 4, MathFunctions::Exp);
        }
        else if (word == "abs") {
            return Lexem("abs", Function, 0.0, 4, MathFunctions::ABS);
        }
        else {
            throw std::logic_error("Unknown function: " + word);
        }
    }
    return Lexem(word, Variable);
}

bool Parser::isFunction(const std::string& str) {
    return (str == "sin" || str == "cos" || str == "tg" || str == "ln" || str == "exp" || str == "abs");
}

Lexem Parser::parseOperator(char oper, bool isUnary) {
    if (isUnary) {
        return Lexem("-", UnOperator, 0.0, 3);
    }

    switch (oper) {
    case '+': return Lexem("+", Operator, 0.0, 1);
    case '-': return Lexem("-", Operator, 0.0, 1);
    case '*': return Lexem("*", Operator, 0.0, 2);
    case '/': return Lexem("/", Operator, 0.0, 2);
    case '^': return Lexem("^", Operator, 0.0, 3);
    default:
        std::string error = "Unknown operator: ";
        error += oper;
        throw std::logic_error(error);
    }
}

void Parser::processUnaryMinus(List<Lexem>& lexem) {
    List<Lexem> result;

    for (auto it = lexem.begin(); it != lexem.end(); ++it) {
        Lexem& lex = *it;

        if (lex.isUnOperator()) {
            // Для унарного минуса добавляем "0" и бинарный "-"
            result.push_back(Lexem("0", Constant, 0.0));
            result.push_back(Lexem("-", Operator, 0.0, 1));
            // НЕ добавляем исходный унарный оператор!
        }
        else {
            result.push_back(lex);
        }
    }

    lexem = result;
}

void Parser::checkSyntax(List<Lexem>& lexem) {
    if (lexem.is_empty()) {
        throw std::logic_error("Empty expression");
    }

    Lexem& first = *lexem.begin();
    if (first.isOper() && !first.isUnOperator()) {
        throw std::logic_error("Expression cannot start with binary operator");
    }

    auto it_end = lexem.end();
    --it_end;
    Lexem& last = *it_end;

    if (last.isOper() || last.isFunction() || last.isBracket()) {
        throw std::logic_error("Incorrect end of expression");
    }

    // Используем специальное значение для начала
    enum { None, Operand, OperatorType } prev = None;

    for (auto it = lexem.begin(); it != lexem.end(); ++it) {
        const Lexem& current = *it;

        if (prev != None) {
            bool currentIsOperand = current.isConst() || current.isVar() || current.isBracket();
            bool currentIsOperator = current.isOper() || current.isUnOperator();

            bool prevIsOperand = (prev == Operand);
            bool prevIsOperator = (prev == OperatorType);

            if (prevIsOperator && currentIsOperator) {
                throw std::logic_error("Two operators in a row");
            }

            if (prevIsOperand && current.isBracket()) {
                throw std::logic_error("Missed operator before bracket");
            }

            if (current.isFunction() && !current.isBracket()) {
                throw std::logic_error("After function must be open bracket");
            }
        }

        // Обновляем состояние для следующей итерации
        if (current.isConst() || current.isVar() || current.isBracket()) {
            prev = Operand;
        }
        else if (current.isOper() || current.isUnOperator()) {
            prev = OperatorType;
        }
        else if (current.isFunction() || current.isBracket()) {
            // Функции и открывающие скобки - это начало операнда
            prev = None; // Сброс, чтобы не проверять
        }
    }
}

void Parser::AbsoluteBars(List<Lexem>& lexem) {
    List<Lexem> result;

    for (auto it = lexem.begin(); it != lexem.end(); ++it) {
        Lexem& lex = *it;

        if (lex.getType() == OpenedAbs) {
            result.push_back(Lexem("abs", Function, 0.0, 4, MathFunctions::ABS));
            result.push_back(Lexem("(", OpenBracket));
        }
        else if (lex.getType() == ClosedAbs) {
            result.push_back(Lexem(")", ClosedBracket));
        }
        else {
            result.push_back(lex);
        }
    }

    lexem = result;
}