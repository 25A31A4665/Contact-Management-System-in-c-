#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Contact {
    char name[50];
    char phone[15];
    char email[50];

public:
    void createContact() {
        cout << "Enter Name: ";
        cin.ignore();
        cin.getline(name, 50);

        cout << "Enter Phone: ";
        cin.getline(phone, 15);

        cout << "Enter Email: ";
        cin.getline(email, 50);
    }

    void showContact() const {
        cout << "\nName: " << name;
        cout << "\nPhone: " << phone;
        cout << "\nEmail: " << email << endl;
    }

    char* getName() {
        return name;
    }

    void updateContact() {
        cout << "Update Phone: ";
        cin.getline(phone, 15);

        cout << "Update Email: ";
        cin.getline(email, 50);
    }
};

// Function to add contact
void addContact() {
    Contact c;
    ofstream file("contacts.dat", ios::binary | ios::app);

    c.createContact();
    file.write((char*)&c, sizeof(c));

    file.close();
    cout << "Contact Added Successfully!\n";
}

// Function to display all contacts
void displayContacts() {
    Contact c;
    ifstream file("contacts.dat", ios::binary);

    while (file.read((char*)&c, sizeof(c))) {
        c.showContact();
        cout << "-------------------";
    }

    file.close();
}

// Function to search contact
void searchContact() {
    Contact c;
    char searchName[50];
    bool found = false;

    cout << "Enter Name to Search: ";
    cin.ignore();
    cin.getline(searchName, 50);

    ifstream file("contacts.dat", ios::binary);

    while (file.read((char*)&c, sizeof(c))) {
        if (strcmp(c.getName(), searchName) == 0) {
            c.showContact();
            found = true;
        }
    }

    file.close();

    if (!found)
        cout << "Contact Not Found!\n";
}

// Function to delete contact
void deleteContact() {
    Contact c;
    char searchName[50];
    bool found = false;

    cout << "Enter Name to Delete: ";
    cin.ignore();
    cin.getline(searchName, 50);

    ifstream file("contacts.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    while (file.read((char*)&c, sizeof(c))) {
        if (strcmp(c.getName(), searchName) != 0) {
            temp.write((char*)&c, sizeof(c));
        } else {
            found = true;
        }
    }

    file.close();
    temp.close();

    remove("contacts.dat");
    rename("temp.dat", "contacts.dat");

    if (found)
        cout << "Contact Deleted!\n";
    else
        cout << "Contact Not Found!\n";
}

// Function to update contact
void updateContact() {
    Contact c;
    char searchName[50];
    bool found = false;

    cout << "Enter Name to Update: ";
    cin.ignore();
    cin.getline(searchName, 50);

    fstream file("contacts.dat", ios::binary | ios::in | ios::out);

    while (file.read((char*)&c, sizeof(c))) {
        if (strcmp(c.getName(), searchName) == 0) {
            cout << "Existing Details:";
            c.showContact();

            cout << "\nEnter New Details:\n";
            cin.ignore();
            c.updateContact();

            int pos = -1 * sizeof(c);
            file.seekp(pos, ios::cur);
            file.write((char*)&c, sizeof(c));

            cout << "Contact Updated!\n";
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "Contact Not Found!\n";
}

// Main Menu
int main() {
    int choice;

    do {
        cout << "\n==== Contact Management System ====\n";
        cout << "1. Add Contact\n";
        cout << "2. View Contacts\n";
        cout << "3. Search Contact\n";
        cout << "4. Update Contact\n";
        cout << "5. Delete Contact\n";
        cout << "6. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addContact(); break;
            case 2: displayContacts(); break;
            case 3: searchContact(); break;
            case 4: updateContact(); break;
            case 5: deleteContact(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid Choice!\n";
        }
    } while (choice != 6);

    return 0;
}
