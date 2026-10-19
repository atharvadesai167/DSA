#include <iostream>
#include <queue>
#include <string>
using namespace std;

int main() {
    queue<string> orders;
    int choice;
    string order;

    do {
        cout << "\n--- Pizza Parlor Take-away System ---\n";
        cout << "1. Accept Order\n";
        cout << "2. Deliver Order\n";
        cout << "3. Display Waiting Orders\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter pizza order: ";
                getline(cin, order);
                orders.push(order);
                cout << "Order accepted successfully!\n";
                break;

            case 2:
                if (orders.empty()) {
                    cout << "No orders to deliver!\n";
                } else {
                    cout << "Delivered Order: "
                         << orders.front() << endl;
                    orders.pop();
                }
                break;

            case 3:
                if (orders.empty()) {
                    cout << "No waiting orders.\n";
                } else {
                    queue<string> temp = orders;
                    cout << "Waiting Orders:\n";
                    while (!temp.empty()) {
                        cout << "- " << temp.front() << endl;
                        temp.pop();
                    }
                }
                break;

            case 4:
                cout << "Exiting the system.\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 4);

    return 0;
}
