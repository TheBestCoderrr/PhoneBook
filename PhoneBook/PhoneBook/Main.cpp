#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Class.h"
#include "ContactsManipulation.h"

using namespace std;

int main() {
	FILE* ContactsFile;
	Contacts contacts;
	Contact contact;
	char* FirstName = new char[PIBSIZE];
	char* LastName = new char[PIBSIZE];
	char* SurName = new char[PIBSIZE];
	int UserVariant = -1;
	cout << "0 - Exit\n1 - Add Contact\n2 - Delete contact\n3 - Find contact\n4 - Show contacts\n5 - download file\n6 - save file\n";
	while (UserVariant != 0) {
		cout << "Choose variant: ";
		cin >> UserVariant;
		switch (UserVariant) {
		case 0:
			break;
		case 1:
			contact.EnteringContact();
			contacts.AddContact(contact);
			break;
		case 2:
			EnteringPIB(FirstName, LastName, SurName);
			contacts.DeleteContact(contacts.FindContact(FirstName, LastName, SurName));
			break;
		case 3:
			EnteringPIB(FirstName, LastName, SurName);
			contacts.PrintOneContact(contacts.FindContact(FirstName, LastName, SurName));
			break;
		case 4:
			contacts.Show();
			break;
		case 5:
			ContactsFile = fopen("C:\\Users\\User\\Downloads\\Contacts.txt", "r");
			if (ContactsFile != NULL) {
				GetContactsFromFile(ContactsFile, contacts);
				fclose(ContactsFile);
			}
			break;
		case 6:
			ContactsFile = fopen("C:\\Users\\User\\Downloads\\Contacts.txt", "a");
			if (ContactsFile != NULL) {
				SaveContactsInFile(ContactsFile, contacts);
				fclose(ContactsFile);
			}
			break;
		default:
			cout << "Invalid variant!" << endl;
			break;
		}
	}
	delete[] FirstName, LastName, SurName;
}