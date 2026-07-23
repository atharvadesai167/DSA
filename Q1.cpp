#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main()
{
    double testCases[] = {10, 100, 1000, 100000, 1000000, 10000000};

    cout << fixed << setprecision(10);

    cout << "-------------------------------------------------------------\n";
    cout << "Number\t\tSquare Root\t\tIterations\n";
    cout << "-------------------------------------------------------------\n";

    for (double n : testCases)
    {
        double guess = n / 2.0;

        // Handle n = 0 separately (not required here but good practice)
        if (n == 0)
        {
            cout << n << "\t\t0\t\t\t0\n";
            continue;
        }

        int iterations = 0;

        while (fabs(guess * guess - n) >= 0.000001)
        {
            guess = 0.5 * (guess + n / guess);
            iterations++;
        }

        cout << n << "\t\t"
             << guess << "\t\t"
             << iterations << endl;
    }

    return 0;
}