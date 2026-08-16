#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Candy {
public:
    string name;
    double price;

    void input() {
        cout << "Enter candy name: ";
        getline(cin >> ws, name);

        cout << "Enter candy price: ";
        cin >> price;
    }

    void display() const {
        cout << name << " - Rs. " << fixed << setprecision(2) << price << endl;
    }
};

int main() {
    int n;

    cout << "       CANDY INVENTORY ANALYTICS\n";

    cout << "Enter number of candies: ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid number of candies.\n";
        return 0;
    }

    Candy* inventory = new Candy[n];

    cout << "\n ENTER CANDY DETAILS \n";

    for (int i = 0; i < n; i++) {
        cout << "\nCandy " << i + 1 << ":\n";
        inventory[i].input();
    }

    double highestPrice = inventory[0].price;

    for (int i = 1; i < n; i++) {
        if (inventory[i].price > highestPrice) {
            highestPrice = inventory[i].price;
        }
    }

    cout << "1. HIGHEST PRICE CANDY\n";


    for (int i = 0; i < n; i++) {
        if (inventory[i].price == highestPrice) {
            inventory[i].display();
        }
    }


    double lowestPrice = inventory[0].price;

    for (int i = 1; i < n; i++) {
        if (inventory[i].price < lowestPrice) {
            lowestPrice = inventory[i].price;
        }
    }

    cout << "2. LOWEST PRICE CANDY\n";


    for (int i = 0; i < n; i++) {
        if (inventory[i].price == lowestPrice) {
            inventory[i].display();
        }
    }


    cout << "3. PRICE COLLISIONS\n";


    bool collisionFound = false;

    for (int i = 0; i < n; i++) {
        bool printed = false;

        for (int j = i + 1; j < n; j++) {

       
            if (inventory[i].price == inventory[j].price &&
                inventory[i].name != inventory[j].name) {

                if (!printed) {
                    cout << "Price Rs. "
                         << fixed << setprecision(2)
                         << inventory[i].price << ":\n";

                    cout << "  - " << inventory[i].name << endl;

                    printed = true;
                    collisionFound = true;
                }

                cout << "  - " << inventory[j].name << endl;
            }
        }
    }

    if (!collisionFound) {
        cout << "No price collisions found.\n";
    }

    double totalPrice = 0;

    for (int i = 0; i < n; i++) {
        totalPrice += inventory[i].price;
    }

    double averagePrice = totalPrice / n;

    cout << "4. AVERAGE PRICE\n";


    cout << "Average Price: Rs. "
         << fixed << setprecision(2)
         << averagePrice << endl;


    cout << "5. DISTINCT / UNIQUE CANDY NAMES\n";


    for (int i = 0; i < n; i++) {

        bool alreadyPrinted = false;

        for (int j = 0; j < i; j++) {
            if (inventory[i].name == inventory[j].name) {
                alreadyPrinted = true;
                break;
            }
        }

        if (!alreadyPrinted) {
            cout << "- " << inventory[i].name << endl;
        }
    }

    delete[] inventory;
    inventory = nullptr;

    cout << "Analytics completed successfully!\n";

    return 0;
}