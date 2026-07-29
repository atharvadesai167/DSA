#include <iostream>
#include <string>
using namespace std;

// ===================== Base Class =====================
class Candy
{
protected:
    string name;
    float price;
    int weightInGrams;

public:
    // Default Constructor
    Candy()
    {
        name = "Unknown";
        price = 0.0;
        weightInGrams = 0;
    }

    // Parameterized Constructor
    Candy(string n, float p, int w)
    {
        name = n;
        price = p;
        weightInGrams = w;
    }

    // Function Overloading
    void applyDiscount(float percentage)
    {
        float discount = price * (percentage / 100);
        price -= discount;
    }

    void applyDiscount(float percentage, float flatCap)
    {
        float discount = price * (percentage / 100);

        if (discount > flatCap)
            discount = flatCap;

        price -= discount;
    }

    // Operator Overloading
    bool operator<(const Candy &other)
    {
        return price < other.price;
    }

    bool operator==(const Candy &other)
    {
        return name == other.name;
    }

    // Virtual Function
    virtual float getFinalPrice()
    {
        return price;
    }

    void display()
    {
        cout << "\nCandy Name : " << name << endl;
        cout << "Price      : $" << price << endl;
        cout << "Weight     : " << weightInGrams << " g" << endl;
    }

    virtual ~Candy() {}
};

// ===================== Derived Class =====================
class ImportedCandy : public Candy
{
private:
    float importTax;

public:
    ImportedCandy(string n, float p, int w, float tax)
        : Candy(n, p, w)
    {
        importTax = tax;
    }

    float getFinalPrice() override
    {
        return price + importTax;
    }
};

// ===================== Main =====================
int main()
{
    int choice;

    cout << "=========================================\n";
    cout << "      CANDY INVENTORY SYSTEM\n";
    cout << "=========================================\n";
    cout << "1. Buy Chocolate (Apply Discount)\n";
    cout << "2. Compare Two Candies\n";
    cout << "3. View Imported Candy Price\n";
    cout << "4. View Candy Inventory\n";
    cout << "5. Exit\n";
    cout << "=========================================\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
    {
        Candy chocolate("Chocolate", 100, 200);

        cout << "\nChocolate Details:\n";
        chocolate.display();

        cout << "\nApplying 10% Discount...\n";
        chocolate.applyDiscount(10);
        cout << "Price After Discount: $" << chocolate.getFinalPrice() << endl;

        cout << "\nApplying 20% Discount (Maximum $10)...\n";
        chocolate.applyDiscount(20, 10);
        cout << "Final Price: $" << chocolate.getFinalPrice() << endl;

        break;
    }

    case 2:
    {
        Candy candy1("ChocoBar", 50, 100);
        Candy candy2("GummyBear", 20, 80);

        cout << "\nComparing Candies...\n";

        if (candy1 < candy2)
            cout << "ChocoBar is cheaper than GummyBear.\n";
        else
            cout << "GummyBear is cheaper than ChocoBar.\n";

        if (candy1 == candy2)
            cout << "Both candies have the same name.\n";
        else
            cout << "Both candies have different names.\n";

        break;
    }

    case 3:
    {
        Candy *candy;

        ImportedCandy imported("Swiss Chocolate", 100, 150, 50);

        candy = &imported;

        cout << "\nImported Candy Details\n";
        cout << "Candy Name : Swiss Chocolate\n";
        cout << "Base Price : $100\n";
        cout << "Import Tax : $50\n";
        cout << "Final Price: $" << candy->getFinalPrice() << endl;

        break;
    }

    case 4:
    {
        Candy normalCandy("Lollipop", 30, 50);
        ImportedCandy importedCandy("Swiss Chocolate", 100, 150, 50);

        Candy *inventory[2];

        inventory[0] = &normalCandy;
        inventory[1] = &importedCandy;

        cout << "\nCandy Inventory\n";
        cout << "-----------------------------\n";

        for (int i = 0; i < 2; i++)
        {
            cout << "Candy " << i + 1
                 << " Final Price = $"
                 << inventory[i]->getFinalPrice() << endl;
        }

        break;
    }

    case 5:
    {
        cout << "\nThank You for Visiting the Candy Store!\n";
        break;
    }

    default:
        cout << "\nInvalid Choice!\n";
    }

    return 0;
}