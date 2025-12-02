#include "Algorithms.h"

bool check_balanced_brackets(const std::string& expression) {
    Stack<char> stack;

    for (char ch : expression) {
        if (ch == '(' || ch == '{' || ch == '[') {
            stack.push(ch);
        }
        else if (ch == ')' || ch == '}' || ch == ']') {

            if (stack.is_empty()) {
                return false; 
            }

            char top_char = stack.pop();

            if ((ch == ')' && top_char != '(') ||
                (ch == '}' && top_char != '{') ||
                (ch == ']' && top_char != '[')) {
                return false;
            }
        }
    }
    return stack.is_empty();
}