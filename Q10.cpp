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
    int shifts;
    int recursiveSplits;
    int dataCopies;
    int partitionSteps;
};

void displayCandies(Candy* inventory, int n) {
    cout << "\n CANDY LIST \n";

    for (int i = 0; i < n; i++) {
        cout << i + 1 << ". ";
        inventory[i].display();
    }
}

// ---------------- BUBBLE SORT ----------------

SortStats bubbleSortByName(Candy* inventory, int n, bool ascending) {
    SortStats stats = {0, 0, 0, 0, 0, 0, 0};

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
    SortStats stats = {0, 0, 0, 0, 0, 0, 0};

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

// ---------------- INSERTION SORT ----------------

SortStats insertionSortByName(Candy* inventory, int n, bool ascending) {
    SortStats stats = {0, 0, 0, 0, 0, 0, 0};

    for (int i = 1; i < n; i++) {
        stats.passes++;

        Candy key = inventory[i];
        int j = i - 1;

        while (j >= 0) {
            stats.comparisons++;

            bool shouldShift;

            if (ascending)
                shouldShift = inventory[j].name > key.name;
            else
                shouldShift = inventory[j].name < key.name;

            if (!shouldShift)
                break;

            inventory[j + 1] = inventory[j];
            stats.shifts++;
            j--;
        }

        inventory[j + 1] = key;
    }

    return stats;
}

SortStats insertionSortByPrice(Candy* inventory, int n, bool ascending) {
    SortStats stats = {0, 0, 0, 0, 0, 0, 0};

    for (int i = 1; i < n; i++) {
        stats.passes++;

        Candy key = inventory[i];
        int j = i - 1;

        while (j >= 0) {
            stats.comparisons++;

            bool shouldShift;

            if (ascending)
                shouldShift = inventory[j].price > key.price;
            else
                shouldShift = inventory[j].price < key.price;

            if (!shouldShift)
                break;

            inventory[j + 1] = inventory[j];
            stats.shifts++;
            j--;
        }

        inventory[j + 1] = key;
    }

    return stats;
}

// ---------------- SELECTION SORT ----------------

SortStats selectionSortByName(Candy* inventory, int n, bool ascending) {
    SortStats stats = {0, 0, 0, 0, 0, 0, 0};

    for (int i = 0; i < n - 1; i++) {
        stats.passes++;

        int selectedIndex = i;

        for (int j = i + 1; j < n; j++) {
            stats.comparisons++;

            if (ascending) {
                if (inventory[j].name < inventory[selectedIndex].name)
                    selectedIndex = j;
            }
            else {
                if (inventory[j].name > inventory[selectedIndex].name)
                    selectedIndex = j;
            }
        }

        if (selectedIndex != i) {
            Candy temp = inventory[i];
            inventory[i] = inventory[selectedIndex];
            inventory[selectedIndex] = temp;

            stats.swaps++;
        }
    }

    return stats;
}

SortStats selectionSortByPrice(Candy* inventory, int n, bool ascending) {
    SortStats stats = {0, 0, 0, 0, 0, 0, 0};

    for (int i = 0; i < n - 1; i++) {
        stats.passes++;

        int selectedIndex = i;

        for (int j = i + 1; j < n; j++) {
            stats.comparisons++;

            if (ascending) {
                if (inventory[j].price < inventory[selectedIndex].price)
                    selectedIndex = j;
            }
            else {
                if (inventory[j].price > inventory[selectedIndex].price)
                    selectedIndex = j;
            }
        }

        if (selectedIndex != i) {
            Candy temp = inventory[i];
            inventory[i] = inventory[selectedIndex];
            inventory[selectedIndex] = temp;

            stats.swaps++;
        }
    }

    return stats;
}

// ---------------- MERGE SORT ----------------

void mergeByName(Candy* inventory, Candy* temp,
                 int left, int mid, int right,
                 bool ascending, SortStats& stats) {

    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        stats.comparisons++;

        bool takeLeft;

        if (ascending)
            takeLeft = inventory[i].name <= inventory[j].name;
        else
            takeLeft = inventory[i].name >= inventory[j].name;

        if (takeLeft) {
            temp[k] = inventory[i];
            stats.dataCopies++;
            i++;
        }
        else {
            temp[k] = inventory[j];
            stats.dataCopies++;
            j++;
        }

        k++;
    }

    while (i <= mid) {
        temp[k] = inventory[i];
        stats.dataCopies++;
        i++;
        k++;
    }

    while (j <= right) {
        temp[k] = inventory[j];
        stats.dataCopies++;
        j++;
        k++;
    }

    for (int x = left; x <= right; x++) {
        inventory[x] = temp[x];
        stats.dataCopies++;
    }
}

void mergeSortByName(Candy* inventory, Candy* temp,
                     int left, int right,
                     bool ascending, SortStats& stats) {

    stats.recursiveSplits++;

    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    mergeSortByName(inventory, temp, left, mid, ascending, stats);
    mergeSortByName(inventory, temp, mid + 1, right, ascending, stats);

    mergeByName(inventory, temp, left, mid, right, ascending, stats);
}

SortStats mergeSortName(Candy* inventory, int n, bool ascending) {
    SortStats stats = {0, 0, 0, 0, 0, 0, 0};

    Candy* temp = new Candy[n];

    mergeSortByName(inventory, temp, 0, n - 1, ascending, stats);

    delete[] temp;

    return stats;
}

void mergeByPrice(Candy* inventory, Candy* temp,
                  int left, int mid, int right,
                  bool ascending, SortStats& stats) {

    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        stats.comparisons++;

        bool takeLeft;

        if (ascending)
            takeLeft = inventory[i].price <= inventory[j].price;
        else
            takeLeft = inventory[i].price >= inventory[j].price;

        if (takeLeft) {
            temp[k] = inventory[i];
            stats.dataCopies++;
            i++;
        }
        else {
            temp[k] = inventory[j];
            stats.dataCopies++;
            j++;
        }

        k++;
    }

    while (i <= mid) {
        temp[k] = inventory[i];
        stats.dataCopies++;
        i++;
        k++;
    }

    while (j <= right) {
        temp[k] = inventory[j];
        stats.dataCopies++;
        j++;
        k++;
    }

    for (int x = left; x <= right; x++) {
        inventory[x] = temp[x];
        stats.dataCopies++;
    }
}

void mergeSortByPrice(Candy* inventory, Candy* temp,
                      int left, int right,
                      bool ascending, SortStats& stats) {

    stats.recursiveSplits++;

    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    mergeSortByPrice(inventory, temp, left, mid, ascending, stats);
    mergeSortByPrice(inventory, temp, mid + 1, right, ascending, stats);

    mergeByPrice(inventory, temp, left, mid, right, ascending, stats);
}

SortStats mergeSortPrice(Candy* inventory, int n, bool ascending) {
    SortStats stats = {0, 0, 0, 0, 0, 0, 0};

    Candy* temp = new Candy[n];

    mergeSortByPrice(inventory, temp, 0, n - 1, ascending, stats);

    delete[] temp;

    return stats;
}

// ---------------- QUICK SORT ----------------

int partitionByName(Candy* inventory, int low, int high,
                     bool ascending, SortStats& stats) {

    stats.partitionSteps++;

    Candy pivot = inventory[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {

        stats.comparisons++;

        bool condition;

        if (ascending)
            condition = inventory[j].name <= pivot.name;
        else
            condition = inventory[j].name >= pivot.name;

        if (condition) {
            i++;

            Candy temp = inventory[i];
            inventory[i] = inventory[j];
            inventory[j] = temp;

            stats.swaps++;
        }
    }

    Candy temp = inventory[i + 1];
    inventory[i + 1] = inventory[high];
    inventory[high] = temp;

    stats.swaps++;

    return i + 1;
}

void quickSortByName(Candy* inventory, int low, int high,
                     bool ascending, SortStats& stats) {

    if (low < high) {

        int pivotIndex =
            partitionByName(inventory, low, high, ascending, stats);

        quickSortByName(inventory, low, pivotIndex - 1,
                        ascending, stats);

        quickSortByName(inventory, pivotIndex + 1, high,
                        ascending, stats);
    }
}

SortStats quickSortName(Candy* inventory, int n, bool ascending) {

    SortStats stats = {0, 0, 0, 0, 0, 0, 0};

    quickSortByName(inventory, 0, n - 1, ascending, stats);

    return stats;
}

int partitionByPrice(Candy* inventory, int low, int high,
                     bool ascending, SortStats& stats) {

    stats.partitionSteps++;

    Candy pivot = inventory[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {

        stats.comparisons++;

        bool condition;

        if (ascending)
            condition = inventory[j].price <= pivot.price;
        else
            condition = inventory[j].price >= pivot.price;

        if (condition) {
            i++;

            Candy temp = inventory[i];
            inventory[i] = inventory[j];
            inventory[j] = temp;

            stats.swaps++;
        }
    }

    Candy temp = inventory[i + 1];
    inventory[i + 1] = inventory[high];
    inventory[high] = temp;

    stats.swaps++;

    return i + 1;
}

void quickSortByPrice(Candy* inventory, int low, int high,
                      bool ascending, SortStats& stats) {

    if (low < high) {

        int pivotIndex =
            partitionByPrice(inventory, low, high, ascending, stats);

        quickSortByPrice(inventory, low, pivotIndex - 1,
                         ascending, stats);

        quickSortByPrice(inventory, pivotIndex + 1, high,
                         ascending, stats);
    }
}

SortStats quickSortPrice(Candy* inventory, int n, bool ascending) {

    SortStats stats = {0, 0, 0, 0, 0, 0, 0};

    quickSortByPrice(inventory, 0, n - 1, ascending, stats);

    return stats;
}

// ---------------- STATISTICS ----------------

void displaySortStats(SortStats stats) {

    cout << "\n SORT STATISTICS \n";

    cout << "Number of passes        : "
         << stats.passes << endl;

    cout << "Number of comparisons   : "
         << stats.comparisons << endl;

    cout << "Number of swaps         : "
         << stats.swaps << endl;

    cout << "Number of shifts        : "
         << stats.shifts << endl;

    cout << "Recursive splits        : "
         << stats.recursiveSplits << endl;

    cout << "Data copy operations    : "
         << stats.dataCopies << endl;

    cout << "Partitioning steps      : "
         << stats.partitionSteps << endl;
}

// ---------------- ANALYTICS ----------------

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

                    cout << " - "
                         << inventory[i].name << endl;

                    printed = true;
                    collisionFound = true;
                }

                cout << " - "
                     << inventory[j].name << endl;
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

// ---------------- LINEAR SEARCH ----------------

void linearSearchByName(Candy* inventory, int n) {

    string searchName;
    int comparisons = 0;
    bool found = false;

    cout << "\n LINEAR SEARCH BY NAME \n";

    cout << "Enter candy name to search: ";
    getline(cin >> ws, searchName);

    for (int i = 0; i < n; i++) {

        comparisons++;

        if (inventory[i].name == searchName) {

            cout << "\nSearch Result: FOUND\n";
            cout << "Index: " << i << endl;
            cout << "Position: " << i + 1 << endl;

            cout << "Candy: ";
            inventory[i].display();

            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nSearch Result: NOT FOUND\n";
        cout << "Candy \"" << searchName
             << "\" does not exist in the inventory.\n";
    }

    cout << "Number of comparisons: "
         << comparisons << endl;
}

void linearSearchByPrice(Candy* inventory, int n) {

    double searchPrice;
    int comparisons = 0;
    bool found = false;

    cout << "\n LINEAR SEARCH BY PRICE \n";

    cout << "Enter candy price to search: ";
    cin >> searchPrice;

    for (int i = 0; i < n; i++) {

        comparisons++;

        if (inventory[i].price == searchPrice) {

            if (!found)
                cout << "\nSearch Result: FOUND\n";

            cout << "Index: " << i << endl;
            cout << "Position: " << i + 1 << endl;

            cout << "Candy: ";
            inventory[i].display();

            found = true;
        }
    }

    if (!found) {

        cout << "\nSearch Result: NOT FOUND\n";

        cout << "No candy found with price Rs. "
             << fixed << setprecision(2)
             << searchPrice << endl;
    }

    cout << "Number of comparisons: "
         << comparisons << endl;
}

// ---------------- BINARY SEARCH ----------------

// Binary Search by Name
void binarySearchByName(Candy* inventory, int n) {

    string target;

    int low = 0;
    int high = n - 1;

    int divideSteps = 0;
    int comparisons = 0;

    bool found = false;
    int foundIndex = -1;

    cout << "\n BINARY SEARCH BY NAME \n";

    // Binary Search requires sorted data
    cout << "\nSorting inventory by name in ascending order...\n";

    bubbleSortByName(inventory, n, true);

    displayCandies(inventory, n);

    cout << "\nEnter candy name to search: ";
    getline(cin >> ws, target);

    while (low <= high) {

        int mid = low + (high - low) / 2;

        // Compare target with middle element
        comparisons++;

        if (inventory[mid].name == target) {

            found = true;
            foundIndex = mid;
            break;
        }

        comparisons++;

        if (target < inventory[mid].name) {

            high = mid - 1;
            divideSteps++;
        }
        else {

            low = mid + 1;
            divideSteps++;
        }
    }

    cout << "\n BINARY SEARCH RESULT \n";

    if (found) {

        cout << "Search Result: FOUND\n";
        cout << "Index: " << foundIndex << endl;
        cout << "Position: " << foundIndex + 1 << endl;

        cout << "Candy: ";
        inventory[foundIndex].display();
    }
    else {

        cout << "Search Result: NOT FOUND\n";

        cout << "Candy \"" << target
             << "\" does not exist in the inventory.\n";
    }

    cout << "\nNumber of iterations / divide steps: "
         << divideSteps << endl;

    cout << "Number of key comparisons: "
         << comparisons << endl;
}

// Binary Search by Price
void binarySearchByPrice(Candy* inventory, int n) {

    double target;

    int low = 0;
    int high = n - 1;

    int divideSteps = 0;
    int comparisons = 0;

    bool found = false;
    int foundIndex = -1;

    cout << "\n BINARY SEARCH BY PRICE \n";

    // Binary Search requires sorted data
    cout << "\nSorting inventory by price in ascending order...\n";

    bubbleSortByPrice(inventory, n, true);

    displayCandies(inventory, n);

    cout << "\nEnter candy price to search: ";
    cin >> target;

    while (low <= high) {

        int mid = low + (high - low) / 2;

        // Compare target with middle element
        comparisons++;

        if (inventory[mid].price == target) {

            found = true;
            foundIndex = mid;
            break;
        }

        comparisons++;

        if (target < inventory[mid].price) {

            high = mid - 1;
            divideSteps++;
        }
        else {

            low = mid + 1;
            divideSteps++;
        }
    }

    cout << "\n BINARY SEARCH RESULT \n";

    if (found) {

        cout << "Search Result: FOUND\n";
        cout << "Index: " << foundIndex << endl;
        cout << "Position: " << foundIndex + 1 << endl;

        cout << "Candy: ";
        inventory[foundIndex].display();
    }
    else {

        cout << "Search Result: NOT FOUND\n";

        cout << "No candy found with price Rs. "
             << fixed << setprecision(2)
             << target << endl;
    }

    cout << "\nNumber of iterations / divide steps: "
         << divideSteps << endl;

    cout << "Number of key comparisons: "
         << comparisons << endl;
}

// ---------------- MAIN ----------------

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

        cout << "\n             MAIN MENU\n";

        cout << "1. Display All Candies\n";
        cout << "2. Highest Price Candy\n";
        cout << "3. Lowest Price Candy\n";
        cout << "4. Price Collisions\n";
        cout << "5. Average Price\n";
        cout << "6. Distinct / Unique Candy Names\n";

        cout << "7. Bubble Sort by Name - Ascending\n";
        cout << "8. Bubble Sort by Name - Descending\n";
        cout << "9. Bubble Sort by Price - Ascending\n";
        cout << "10. Bubble Sort by Price - Descending\n";

        cout << "11. Insertion Sort by Name - Ascending\n";
        cout << "12. Insertion Sort by Name - Descending\n";
        cout << "13. Insertion Sort by Price - Ascending\n";
        cout << "14. Insertion Sort by Price - Descending\n";

        cout << "15. Selection Sort by Name - Ascending\n";
        cout << "16. Selection Sort by Name - Descending\n";
        cout << "17. Selection Sort by Price - Ascending\n";
        cout << "18. Selection Sort by Price - Descending\n";

        cout << "19. Merge Sort by Name - Ascending\n";
        cout << "20. Merge Sort by Name - Descending\n";
        cout << "21. Merge Sort by Price - Ascending\n";
        cout << "22. Merge Sort by Price - Descending\n";

        cout << "23. Quick Sort by Name - Ascending\n";
        cout << "24. Quick Sort by Name - Descending\n";
        cout << "25. Quick Sort by Price - Ascending\n";
        cout << "26. Quick Sort by Price - Descending\n";

        cout << "27. Linear Search by Name\n";
        cout << "28. Linear Search by Price\n";

        cout << "29. Binary Search by Name\n";
        cout << "30. Binary Search by Price\n";

        cout << "31. Exit\n";

        cout << "\nEnter your choice: ";
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
                cout << "\n BUBBLE SORT BY NAME \n";
                cout << "Order: Ascending\n";

                SortStats stats =
                    bubbleSortByName(inventory, n, true);

                displayCandies(inventory, n);
                displaySortStats(stats);
                break;
            }

            case 8: {
                cout << "\n BUBBLE SORT BY NAME \n";
                cout << "Order: Descending\n";

                SortStats stats =
                    bubbleSortByName(inventory, n, false);

                displayCandies(inventory, n);
                displaySortStats(stats);
                break;
            }

            case 9: {
                cout << "\n BUBBLE SORT BY PRICE \n";
                cout << "Order: Ascending\n";

                SortStats stats =
                    bubbleSortByPrice(inventory, n, true);

                displayCandies(inventory, n);
                displaySortStats(stats);
                break;
            }

            case 10: {
                cout << "\n BUBBLE SORT BY PRICE \n";
                cout << "Order: Descending\n";

                SortStats stats =
                    bubbleSortByPrice(inventory, n, false);

                displayCandies(inventory, n);
                displaySortStats(stats);
                break;
            }

            case 11: {
                cout << "\n INSERTION SORT BY NAME \n";
                cout << "Order: Ascending\n";

                SortStats stats =
                    insertionSortByName(inventory, n, true);

                displayCandies(inventory, n);
                displaySortStats(stats);
                break;
            }

            case 12: {
                cout << "\n INSERTION SORT BY NAME \n";
                cout << "Order: Descending\n";

                SortStats stats =
                    insertionSortByName(inventory, n, false);

                displayCandies(inventory, n);
                displaySortStats(stats);
                break;
            }

            case 13: {
                cout << "\n INSERTION SORT BY PRICE \n";
                cout << "Order: Ascending\n";

                SortStats stats =
                    insertionSortByPrice(inventory, n, true);

                displayCandies(inventory, n);
                displaySortStats(stats);
                break;
            }

            case 14: {
                cout << "\n INSERTION SORT BY PRICE \n";
                cout << "Order: Descending\n";

                SortStats stats =
                    insertionSortByPrice(inventory, n, false);

                displayCandies(inventory, n);
                displaySortStats(stats);
                break;
            }

            case 15: {
                cout << "\n SELECTION SORT BY NAME \n";
                cout << "Order: Ascending\n";

                SortStats stats =
                    selectionSortByName(inventory, n, true);

                displayCandies(inventory, n);
                displaySortStats(stats);
                break;
            }

            case 16: {
                cout << "\n SELECTION SORT BY NAME \n";
                cout << "Order: Descending\n";

                SortStats stats =
                    selectionSortByName(inventory, n, false);

                displayCandies(inventory, n);
                displaySortStats(stats);
                break;
            }

            case 17: {
                cout << "\n SELECTION SORT BY PRICE \n";
                cout << "Order: Ascending\n";

                SortStats stats =
                    selectionSortByPrice(inventory, n, true);

                displayCandies(inventory, n);
                displaySortStats(stats);
                break;
            }

            case 18: {
                cout << "\n SELECTION SORT BY PRICE \n";
                cout << "Order: Descending\n";

                SortStats stats =
                    selectionSortByPrice(inventory, n, false);

                displayCandies(inventory, n);
                displaySortStats(stats);
                break;
            }

            case 19: {
                cout << "\n MERGE SORT BY NAME \n";
                cout << "Order: Ascending\n";

                SortStats stats =
                    mergeSortName(inventory, n, true);

                displayCandies(inventory, n);
                displaySortStats(stats);
                break;
            }

            case 20: {
                cout << "\n MERGE SORT BY NAME \n";
                cout << "Order: Descending\n";

                SortStats stats =
                    mergeSortName(inventory, n, false);

                displayCandies(inventory, n);
                displaySortStats(stats);
                break;
            }

            case 21: {
                cout << "\n MERGE SORT BY PRICE \n";
                cout << "Order: Ascending\n";

                SortStats stats =
                    mergeSortPrice(inventory, n, true);

                displayCandies(inventory, n);
                displaySortStats(stats);
                break;
            }

            case 22: {
                cout << "\n MERGE SORT BY PRICE \n";
                cout << "Order: Descending\n";

                SortStats stats =
                    mergeSortPrice(inventory, n, false);

                displayCandies(inventory, n);
                displaySortStats(stats);
                break;
            }

            case 23: {
                cout << "\n QUICK SORT BY NAME \n";
                cout << "Order: Ascending\n";

                SortStats stats =
                    quickSortName(inventory, n, true);

                displayCandies(inventory, n);
                displaySortStats(stats);
                break;
            }

            case 24: {
                cout << "\n QUICK SORT BY NAME \n";
                cout << "Order: Descending\n";

                SortStats stats =
                    quickSortName(inventory, n, false);

                displayCandies(inventory, n);
                displaySortStats(stats);
                break;
            }

            case 25: {
                cout << "\n QUICK SORT BY PRICE \n";
                cout << "Order: Ascending\n";

                SortStats stats =
                    quickSortPrice(inventory, n, true);

                displayCandies(inventory, n);
                displaySortStats(stats);
                break;
            }

            case 26: {
                cout << "\n QUICK SORT BY PRICE \n";
                cout << "Order: Descending\n";

                SortStats stats =
                    quickSortPrice(inventory, n, false);

                displayCandies(inventory, n);
                displaySortStats(stats);
                break;
            }

            case 27:
                linearSearchByName(inventory, n);
                break;

            case 28:
                linearSearchByPrice(inventory, n);
                break;

            case 29:
                binarySearchByName(inventory, n);
                break;

            case 30:
                binarySearchByPrice(inventory, n);
                break;

            case 31:
                cout << "\nAnalytics completed successfully!\n";
                cout << "Exiting program...\n";
                break;

            default:
                cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 31);

    delete[] inventory;
    inventory = nullptr;

    return 0;
}