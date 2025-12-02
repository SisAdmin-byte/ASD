#include <string>
#include <stdexcept>
enum TypeLexem { Constant, Variable, OpenBracket, ClosedBracket, Function, Operator, UnOperator, OpenedAbs, ClosedAbs };


class Lexem {
private:
	std::string name;
	TypeLexem type;
	double value;
	int priority;
	double (*function)(double);

public:

	Lexem(std::string _name, TypeLexem _type, double _value = DBL_MAX, int _priority = -1, double(*_function)(double) = nullptr) : name(_name), type(_type), value(_value), priority(_priority), function(_function) {}


	bool isConst() { return type == TypeLexem::Constant; }
	bool isVar() { return type == TypeLexem::Variable; }
	bool isBracket() { return type == TypeLexem::OpenBracket || type == TypeLexem::ClosedBracket; }
	bool isFunction() { return type == TypeLexem::Function; }
	bool isUnOperator() { return type == TypeLexem::UnOperator; }
	bool isOper() { return type == TypeLexem::Operator; }
	bool isUnOper() { return type == TypeLexem::UnOperator; }
	bool isABS() { return type == TypeLexem::OpenedAbs || type == TypeLexem::ClosedAbs; }

	TypeLexem getType() const { return type; }

	double executeFun(double argument) {

		if (function != nullptr) {

			return function(argument);

		}
		throw std::logic_error("No function assigned to lexem: " + name);

	}



	double executeOper(double firstArg, double secondArg) {

		if (name == "+") return firstArg + secondArg;
		if (name == "-") return firstArg - secondArg;
		if (name == "*") return firstArg * secondArg;
		if (name == "/") {

			if (secondArg == 0) {
				throw std::logic_error("Division by zero!");
			}
			return firstArg / secondArg;
		}
		if (name == "^") return pow(firstArg, secondArg);
		throw std::logic_error("Unknown operator: " + name);

	}

};