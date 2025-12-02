#include "Parser.h"

List<Lexem> Parser::parse(const std::string& expression) {

	List<Lexem> result;
	size_t pos = 0;

	bool flag = true;

	while (pos < expression.length()) {

		char c = expression[pos];

		if (std::isspace(c)) {
			pos++;
		}

		if (std::isdigit(c) || c == '.') {

			result.push_back(parseNumber(expression, pos));
            flag = false;
		}
        else if (std::isalpha(c) || c == '_') {

            Lexem lexem = parseWord(expression, pos);
            result.push_back(lexem);

            if (lexem.isFunction()) {

                flag = true; // тут подразумевается операнд

            }
            else {

                flag = false; // а тут оператор

            }

        }
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            bool isUnary = (c == '-' && flag);
            result.push_back(parseOperator(c, isUnary));
            pos++;
            flag = true; // После оператора ждем операнд
        }
        else if (c == '(' || c == '[' || c == '{') {
            result.push_back(Lexem(std::string(1, c), OpenBracket));
            pos++;
            flag = true; // После открывающейся скобочки нужен операнд
        }
        else if (c == ')' || c == ']' || c == '}') {
            result.push_back(Lexem(std::string(1, c), ClosedBracket));
            pos++;
            flag = false; // После закрывающей скобочки оператор
        }

        else if (c == '|') {
            TypeLexem type;
            if (flag == true) {
                type = OpenedAbs;      
            }
            else {
                type = ClosedAbs;      
            }
            result.push_back(Lexem("|", type));
            pos++;
            flag = !flag; 
        }

        else {
            std::string error = "Unknown symbol '";
            error += c;
            error += " on position";
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

		if (number.empty()) {

			throw std::logic_error("Error: empty, I need number");

		}

		if (number.back() == '.') {

			throw std::logic_error("Error: A number cannot end with a dot!");

		}

		double var;

		try {
			var = std::stod(number);
		} 
		catch (...) {
			throw std::logic_error("Incorrect number: " + number);
		}

	}




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

        if (word == "sin") {
            return Lexem("sin", Function, 0.0, 2, MathFunctions::Sin);
        }
        else if (word == "cos") {
            return Lexem("cos", Function, 0.0, 2, MathFunctions::Cos);
        }
        else if (word == "tg") {
            return Lexem("tg", Function, 0.0, 2, MathFunctions::tg);
        }
        else if (word == "ln") {
            return Lexem("ln", Function, 0.0, 2, MathFunctions::ln);
        }
        else if (word == "exp") {
            return Lexem("exp", Function, 0.0, 2, MathFunctions::Exp);
        }
        else if (word == "abs") {
            return Lexem("abs", Function, 0.0, 2, MathFunctions::ABS);
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

    for (auto it = lexem.begin(); it != lexem.end(); it++) {

        Lexem& lex = *it;

        if (lex.isUnOperator()) { // тут замена минуса на 0 - что-то

            result.push_back(Lexem("0", Constant, 0.0));
            result.push_back(Lexem("-", Operator, 0.0, 1));
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
        throw std::logic_error("Expression cannot start with operator");
    }

    Lexem& last = *(lexem.end());
    if (last.isOper() || last.isFunction() || last.isBracket()) {
        throw std::runtime_error("Incorrect end of expression");
    }

    TypeLexem prevType = Constant; 

    for (auto it = lexem.begin(); it != lexem.end(); ++it) {
        const Lexem& current = *it;
        TypeLexem currType = current.getType();

        if ((prevType == Operator || prevType == UnOperator) &&
            (currType == Operator || currType == UnOperator)) {
            throw std::logic_error("Two operators on a rows");
        }

        if (prevType == Function && currType != OpenBracket) {
            throw std::logic_error("After function must be open bracket");
        }

        if ((prevType == Constant || prevType == Variable || prevType == ClosedBracket) && currType == OpenBracket) {
            throw std::logic_error("Missed operator before bracket");
        }

        prevType = currType;
    }
}

void Parser::AbsoluteBars(List<Lexem>& lexem) {
    List<Lexem> result;

    for (auto it = lexem.begin(); it != lexem.end(); it++) {
        Lexem& lex = *it;

        if (lex.getType() == OpenedAbs) {
            result.push_back(Lexem("abs", Function, 0.0, 2, MathFunctions::ABS));
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