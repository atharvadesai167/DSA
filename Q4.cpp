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
        cout << name << " - Rs. "
             << fixed << setprecision(2)
             << price << endl;
    }
};

struct SortStats {
    int passes;
    int comparisons;
    int swaps;
};

void displayCandies(Candy* inventory, int n) {
    cout << "\n CANDY LIST \n";

    for (int i = 0; i < n; i++) {
        cout << i + 1 << ". ";
        inventory[i].display();
    }
}

SortStats bubbleSortByName(Candy* inventory, int n, bool ascending) {
    SortStats stats = {0, 0, 0};

    for (int i = 0; i < n - 1; i++) {
        stats.passes++;
        bool swapped = false;

        for (int j = 0; j < n - 1 - i; j++) {
            stats.comparisons++;

            bool shouldSwap;

            if (ascending)
                shouldSwap = inventory[j].name > inventory[j + 1].name;
            else
                shouldSwap = inventory[j].name < inventory[j + 1].name;

            if (shouldSwap) {
                Candy temp = inventory[j];
                inventory[j] = inventory[j + 1];
                inventory[j + 1] = temp;

                stats.swaps++;
                swapped = true;
            }
        }

        if (!swapped)
            break;
    }

    return stats;
}

SortStats bubbleSortByPrice(Candy* inventory, int n, bool ascending) {
    SortStats stats = {0, 0, 0};

    for (int i = 0; i < n - 1; i++) {
        stats.passes++;
        bool swapped = false;

        for (int j = 0; j < n - 1 - i; j++) {
            stats.comparisons++;

            bool shouldSwap;

            if (ascending)
                shouldSwap = inventory[j].price > inventory[j + 1].price;
            else
                shouldSwap = inventory[j].price < inventory[j + 1].price;

            if (shouldSwap) {
                Candy temp = inventory[j];
                inventory[j] = inventory[j + 1];
                inventory[j + 1] = temp;

                stats.swaps++;
                swapped = true;
            }
        }

        if (!swapped)
            break;
    }

    return stats;
}

void displaySortStats(SortStats stats) {
    cout << "\n SORT STATISTICS \n";
    cout << "Number of passes       : " << stats.passes << endl;
    cout << "Number of comparisons  : " << stats.comparisons << endl;
    cout << "Number of swaps        : " << stats.swaps << endl;
}

void highestPriceCandy(Candy* inventory, int n) {
    double highestPrice = inventory[0].price;

    for (int i = 1; i < n; i++) {
        if (inventory[i].price > highestPrice)
            highestPrice = inventory[i].price;
    }

    cout << "\n1. HIGHEST PRICE CANDY\n";

    for (int i = 0; i < n; i++) {
        if (inventory[i].price == highestPrice)
            inventory[i].display();
    }
}

void lowestPriceCandy(Candy* inventory, int n) {
    double lowestPrice = inventory[0].price;

    for (int i = 1; i < n; i++) {
        if (inventory[i].price < lowestPrice)
            lowestPrice = inventory[i].price;
    }

    cout << "\n2. LOWEST PRICE CANDY\n";

    for (int i = 0; i < n; i++) {
        if (inventory[i].price == lowestPrice)
            inventory[i].display();
    }
}

void priceCollisions(Candy* inventory, int n) {
    cout << "\n3. PRICE COLLISIONS\n";

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

                    cout << " - " << inventory[i].name << endl;

                    printed = true;
                    collisionFound = true;
                }

                cout << " - " << inventory[j].name << endl;
            }
        }
    }

    if (!collisionFound)
        cout << "No price collisions found.\n";
}

void averagePrice(Candy* inventory, int n) {
    double totalPrice = 0;

    for (int i = 0; i < n; i++)
        totalPrice += inventory[i].price;

    double averagePrice = totalPrice / n;

    cout << "\n4. AVERAGE PRICE\n";
    cout << "Average Price: Rs. "
         << fixed << setprecision(2)
         << averagePrice << endl;
}

void distinctCandyNames(Candy* inventory, int n) {
    cout << "\n5. DISTINCT / UNIQUE CANDY NAMES\n";

    for (int i = 0; i < n; i++) {
        bool alreadyPrinted = false;

        for (int j = 0; j < i; j++) {
            if (inventory[i].name == inventory[j].name) {
                alreadyPrinted = true;
                break;
            }
        }

        if (!alreadyPrinted)
            cout << "- " << inventory[i].name << endl;
    }
}

int main() {
    int n;

    cout << "CANDY INVENTORY ANALYTICS\n";

    cout << "\nEnter number of candies: ";
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

    int choice;

    do {
        cout << "             MAIN MENU\n";
        cout << "1. Display All Candies\n";
        cout << "2. Highest Price Candy\n";
        cout << "3. Lowest Price Candy\n";
        cout << "4. Price Collisions\n";
        cout << "5. Average Price\n";
        cout << "6. Distinct / Unique Candy Names\n";
        cout << "7. Sort by Name - Ascending\n";
        cout << "8. Sort by Name - Descending\n";
        cout << "9. Sort by Price - Ascending\n";
        cout << "10. Sort by Price - Descending\n";
        cout << "11. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayCandies(inventory, n);
                break;

            case 2:
                highestPriceCandy(inventory, n);
                break;

            case 3:
                lowestPriceCandy(inventory, n);
                break;

            case 4:
                priceCollisions(inventory, n);
                break;

            case 5:
                averagePrice(inventory, n);
                break;

            case 6:
                distinctCandyNames(inventory, n);
                break;

            case 7: {
                cout << "\n SORT BY NAME \n";
                cout << "Order: Ascending\n";

                SortStats stats =
                    bubbleSortByName(inventory, n, true);

                displayCandies(inventory, n);
                displaySortStats(stats);
                break;
            }

            case 8: {
                cout << "\n SORT BY NAME \n";
                cout << "Order: Descending\n";

                SortStats stats =
                    bubbleSortByName(inventory, n, false);

                displayCandies(inventory, n);
                displaySortStats(stats);
                break;
            }

            case 9: {
                cout << "\n SORT BY PRICE \n";
                cout << "Order: Ascending\n";

                SortStats stats =
                    bubbleSortByPrice(inventory, n, true);

                displayCandies(inventory, n);
                displaySortStats(stats);
                break;
            }

            case 10: {
                cout << "\n SORT BY PRICE \n";
                cout << "Order: Descending\n";

                SortStats stats =
                    bubbleSortByPrice(inventory, n, false);

                displayCandies(inventory, n);
                displaySortStats(stats);
                break;
            }

            case 11:
                cout << "\nAnalytics completed successfully!\n";
                cout << "Exiting program...\n";
                break;

            default:
                cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 11);

    delete[] inventory;
    inventory = nullptr;

    return 0;
}