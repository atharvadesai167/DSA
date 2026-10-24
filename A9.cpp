
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
using namespace std;

int main()
{
    int choice;
    string record, filename = "records.txt";
    string deleteRecord;
    string line;

    do
    {
        cout << "\n===== FILE HANDLING MENU =====\n";
        cout << "1. Create File\n";
        cout << "2. Add Record\n";
        cout << "3. Display Records\n";
        cout << "4. Delete Specific Record\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(10000, '\n');

        switch (choice)
        {
            case 1:
            {
                ofstream file(filename);

                if (file.is_open())
                {
                    cout << "File created successfully.\n";
                    file.close();
                }
                else
                {
                    cout << "Unable to create file.\n";
                }
                break;
            }

            case 2:
            {
                ofstream file(filename, ios::app);

                if (file.is_open())
                {
                    cout << "Enter record: ";
                    getline(cin, record);

                    file << record << '\n';

                    if (file.good())
                        cout << "Record added successfully.\n";
                    else
                        cout << "Error writing record.\n";

                    file.close();
                }
                else
                {
                    cout << "Unable to open file.\n";
                }
                break;
            }

            case 3:
            {
                ifstream file(filename);

                if (file.is_open())
                {
                    cout << "\nStored Records:\n";
                    bool found = false;

                    while (getline(file, line))
                    {
                        cout << line << '\n';
                        found = true;
                    }

                    if (!found)
                        cout << "No records found.\n";

                    file.close();
                }
                else
                {
                    cout << "File does not exist or cannot be opened.\n";
                }
                break;
            }

            case 4:
            {
                cout << "Enter record to delete: ";
                getline(cin, deleteRecord);

                ifstream file(filename);

                if (!file.is_open())
                {
                    cout << "File does not exist or cannot be opened.\n";
                    break;
                }

                ofstream temp("temp.txt");

                if (!temp.is_open())
                {
                    cout << "Unable to create temporary file.\n";
                    file.close();
                    break;
                }

                bool deleted = false;

                while (getline(file, line))
                {
                    if (line == deleteRecord)
                    {
                        deleted = true;
                    }
                    else
                    {
                        temp << line << '\n';
                    }
                }

                file.close();
                temp.close();

                if (deleted)
                {
                    if (remove(filename.c_str()) == 0 &&
                        rename("temp.txt", filename.c_str()) == 0)
                    {
                        cout << "Record deleted successfully.\n";
                    }
                    else
                    {
                        cout << "Error updating file.\n";
                    }
                }
                else
                {
                    remove("temp.txt");
                    cout << "Record not found.\n";
                }
                break;
            }

            case 5:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}
