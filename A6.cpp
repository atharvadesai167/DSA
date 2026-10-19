#include <iostream>
#include <stack>
#include <string>
#include <cctype>
using namespace std;

// Function to define operator precedence
int precedence(char op) {
    if (op == '^')
        return 3;
    else if (op == '*' || op == '/' || op == '%')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    else
        return 0;
}

// Function to check whether a character is an operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' ||
           c == '/' || c == '%' || c == '^';
}

// Function to convert infix to postfix
string infixToPostfix(string infix) {
    stack<char> s;
    string postfix = "";

    for (int i = 0; i < infix.length(); i++) {
        char c = infix[i];

        // Ignore spaces
        if (isspace(static_cast<unsigned char>(c)))
            continue;

        // If operand, add it to postfix
        if (isalnum(static_cast<unsigned char>(c))) {
            postfix += c;
            postfix += ' ';
        }

        // If opening parenthesis, push onto stack
        else if (c == '(') {
            s.push(c);
        }

        // If closing parenthesis, pop until '('
        else if (c == ')') {
            while (!s.empty() && s.top() != '(') {
                postfix += s.top();
                postfix += ' ';
                s.pop();
            }

            if (!s.empty())
                s.pop();
        }

        // If operator
        else if (isOperator(c)) {
            while (!s.empty() && s.top() != '(' &&
                   (precedence(s.top()) > precedence(c) ||
                   (precedence(s.top()) == precedence(c) &&
                    c != '^'))) {
                postfix += s.top();
                postfix += ' ';
                s.pop();
            }

            s.push(c);
        }
    }

    // Pop remaining operators
    while (!s.empty()) {
        if (s.top() != '(') {
            postfix += s.top();
            postfix += ' ';
        }
        s.pop();
    }

    // Remove trailing space
    if (!postfix.empty() && postfix.back() == ' ')
        postfix.pop_back();

    return postfix;
}

int main() {
    string infix;

    cout << "Enter an infix expression: ";
    getline(cin, infix);

    cout << "Postfix expression: "
         << infixToPostfix(infix) << endl;

    return 0;
}
