#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Term {
public:
    int coefficient;
    int exponent;

    Term(int c = 0, int e = 0) {
        coefficient = c;
        exponent = e;
    }
};

class Polynomial {
private:
    vector<Term> terms;

public:
    void addTerm(int coefficient, int exponent) {
        if (coefficient == 0)
            return;

        for (int i = 0; i < terms.size(); i++) {
            if (terms[i].exponent == exponent) {
                terms[i].coefficient += coefficient;

                if (terms[i].coefficient == 0)
                    terms.erase(terms.begin() + i);

                return;
            }
        }

        terms.push_back(Term(coefficient, exponent));
    }

    void display() {
        if (terms.empty()) {
            cout << "0";
            return;
        }

        for (int i = 0; i < terms.size(); i++) {
            int c = terms[i].coefficient;
            int e = terms[i].exponent;

            if (i > 0 && c > 0)
                cout << " + ";
            else if (i > 0 && c < 0)
                cout << " - ";

            if (c < 0)
                c = -c;

            if (e == 0)
                cout << c;
            else if (e == 1)
                cout << c << "x";
            else
                cout << c << "x^" << e;
        }

        cout << endl;
    }

    double evaluate(double x) {
        double result = 0;

        for (Term t : terms)
            result += t.coefficient * pow(x, t.exponent);

        return result;
    }

    int degree() {
        if (terms.empty())
            return 0;

        int maxDegree = terms[0].exponent;

        for (Term t : terms) {
            if (t.exponent > maxDegree)
                maxDegree = t.exponent;
        }

        return maxDegree;
    }

    Polynomial add(Polynomial p) {
        Polynomial result = *this;

        for (Term t : p.terms)
            result.addTerm(t.coefficient, t.exponent);

        return result;
    }

    Polynomial subtract(Polynomial p) {
        Polynomial result = *this;

        for (Term t : p.terms)
            result.addTerm(-t.coefficient, t.exponent);

        return result;
    }

    Polynomial multiply(Polynomial p) {
        Polynomial result;

        for (Term a : terms) {
            for (Term b : p.terms) {
                result.addTerm(
                    a.coefficient * b.coefficient,
                    a.exponent + b.exponent
                );
            }
        }

        return result;
    }
};

int main() {
    Polynomial p1, p2;

    p1.addTerm(3, 2);
    p1.addTerm(2, 1);
    p1.addTerm(5, 0);

    p2.addTerm(4, 2);
    p2.addTerm(3, 1);
    p2.addTerm(2, 0);

    cout << "Polynomial 1: ";
    p1.display();

    cout << "Polynomial 2: ";
    p2.display();

    cout << "\nDegree of Polynomial 1: "
         << p1.degree() << endl;

    double x = 2;
    cout << "P1(" << x << ") = "
         << p1.evaluate(x) << endl;

    Polynomial sum = p1.add(p2);
    cout << "\nAddition: ";
    sum.display();

    Polynomial difference = p1.subtract(p2);
    cout << "Subtraction: ";
    difference.display();

    Polynomial product = p1.multiply(p2);
    cout << "Multiplication: ";
    product.display();

    return 0;
}
