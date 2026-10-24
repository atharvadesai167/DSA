
#include <iostream>
using namespace std;

struct Node
{
    int id, age;
    string name, mobile;
    Node *prev, *next;
};

Node *head = NULL;

void addPlayer()
{
    Node *n = new Node;

    cout << "Enter Player ID: ";
    cin >> n->id;
    cout << "Enter Player Name: ";
    cin >> n->name;
    cout << "Enter Mobile Number: ";
    cin >> n->mobile;
    cout << "Enter Age: ";
    cin >> n->age;

    n->prev = NULL;
    n->next = NULL;

    if (head == NULL)
        head = n;
    else
    {
        Node *t = head;
        while (t->next != NULL)
            t = t->next;

        t->next = n;
        n->prev = t;
    }

    cout << "Player added successfully!\n";
}

void deletePlayer()
{
    int id;
    cout << "Enter Player ID to delete: ";
    cin >> id;

    Node *t = head;

    while (t != NULL && t->id != id)
        t = t->next;

    if (t == NULL)
    {
        cout << "Player not found!\n";
        return;
    }

    if (t->prev != NULL)
        t->prev->next = t->next;
    else
        head = t->next;

    if (t->next != NULL)
        t->next->prev = t->prev;

    delete t;
    cout << "Player deleted successfully!\n";
}

void displayPlayers()
{
    Node *t = head;

    if (t == NULL)
    {
        cout << "No player records found!\n";
        return;
    }

    while (t != NULL)
    {
        cout << "\nID: " << t->id;
        cout << "\nName: " << t->name;
        cout << "\nMobile: " << t->mobile;
        cout << "\nAge: " << t->age << "\n";
        t = t->next;
    }
}

void searchPlayer()
{
    string name;
    cout << "Enter Player Name to search: ";
    cin >> name;

    Node *t = head;

    while (t != NULL)
    {
        if (t->name == name)
        {
            cout << "Player found!\n";
            cout << "ID: " << t->id;
            cout << "\nName: " << t->name;
            cout << "\nMobile: " << t->mobile;
            cout << "\nAge: " << t->age << "\n";
            return;
        }

        t = t->next;
    }

    cout << "Player not found!\n";
}

void updateMobile()
{
    int id;
    string mobile;

    cout << "Enter Player ID: ";
    cin >> id;

    Node *t = head;

    while (t != NULL && t->id != id)
        t = t->next;

    if (t == NULL)
    {
        cout << "Player not found!\n";
        return;
    }

    cout << "Enter new Mobile Number: ";
    cin >> mobile;

    t->mobile = mobile;
    cout << "Mobile number updated successfully!\n";
}

int main()
{
    int choice;

    do
    {
        cout << "\n--- Cricket Player Management ---\n";
        cout << "1. Add Player\n";
        cout << "2. Delete Player\n";
        cout << "3. Display Players\n";
        cout << "4. Search Player by Name\n";
        cout << "5. Update Mobile Number\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1: addPlayer(); break;
            case 2: deletePlayer(); break;
            case 3: displayPlayers(); break;
            case 4: searchPlayer(); break;
            case 5: updateMobile(); break;
            case 6: cout << "Program ended.\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}
