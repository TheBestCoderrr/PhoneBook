#include <iostream>
#include "Class.h"
#include "Consts.h"
using namespace std;

void EnteringPIB(char* FirstName, char* LastName, char* SurName) {
	cin.ignore();
	cout << "Enter first name: ";
	cin.getline(FirstName, PIBSIZE);
	cout << "Enter last name: ";
	cin.getline(LastName, PIBSIZE);
	cout << "Enter surname: ";
	cin.getline(SurName, PIBSIZE);
}

size_t GetSize_tNum(char* Buffer) {
	size_t num = 0;
	for (size_t i = 0; i < strlen(Buffer); i++) {
		num += Buffer[i] - '0';
		num *= 10;
	}
	num /= 10;
	return num;
}

void GetContactsFromFile(FILE* ContactsFile, Contacts contacts) {
	size_t CountContactsInFile = 0;
	char letter;
	do{
		letter = fgetc(ContactsFile);
		if (letter == '\n')
			CountContactsInFile++;
	} while (letter != EOF);
	++CountContactsInFile /= 3;

	Contact* NewContacts = new Contact[contacts.GetCountContacts() + CountContactsInFile];
	NewContacts = contacts.GetContacts();
	char* str = new char[TEXTSIZE];
	char* Buffer = NULL, * NextBuffer = NULL;
	fseek(ContactsFile, 0, SEEK_SET);
	for (int i = contacts.GetCountContacts(); i < CountContactsInFile + contacts.GetCountContacts(); i++) {
		fseek(ContactsFile, 5, SEEK_CUR);
		fgets(str, TEXTSIZE, ContactsFile);
		Buffer = strtok_s(str, " ", &NextBuffer);
		NewContacts[i].SetFirstName(Buffer);
		Buffer = strtok_s(NULL, " ", &NextBuffer);
		NewContacts[i].SetLastName(Buffer);
		Buffer = strtok_s(NULL, " ", &NextBuffer);
		NewContacts[i].SetSurName(Buffer);
		fgets(str, TEXTSIZE, ContactsFile);
		Buffer = strtok_s(str, " \t", &NextBuffer);
		Buffer = strtok_s(NULL, " \t\n", &NextBuffer);
		NewContacts[i].SetHomePhone(GetSize_tNum(Buffer));
		fgets(str, TEXTSIZE, ContactsFile);
		Buffer = strtok_s(str, " \t", &NextBuffer);
		Buffer = strtok_s(NULL, " \t\n", &NextBuffer);
		NewContacts[i].SetWorkPhone(GetSize_tNum(Buffer));
		fgets(str, TEXTSIZE, ContactsFile);
		Buffer = strtok_s(str, " \t", &NextBuffer);
		Buffer = strtok_s(NULL, " \t\n", &NextBuffer);
		NewContacts[i].SetMobilePhone(GetSize_tNum(Buffer));
		fgets(str, TEXTSIZE, ContactsFile);
		Buffer = strtok_s(str, " \t", &NextBuffer);
		Buffer = strtok_s(NULL, " \t", &NextBuffer);
		Buffer = strtok_s(NULL, " \t\n", &NextBuffer);
		NewContacts[i].SetContactInfo(Buffer);
	}

	delete[] contacts.GetContacts();
	contacts.SetContacts(NewContacts);
	delete[] str;
	contacts.SetCountContacts(contacts.GetCountContacts() + CountContactsInFile);
}

void SaveContactsInFile(FILE* ContactsFile,Contacts contacts) {
	Contact* copycontacts = contacts.GetContacts();
	for (int i = 0; i < contacts.GetCountContacts(); i++) {
		fprintf(ContactsFile, "PIB: %s %s %s\nHomePhone: %i\nWorkPhone: %i\nMobilePhone: %i\nAdditional info: %s", copycontacts[i].GetFirstName() , copycontacts[i].GetLastName(),
			copycontacts[i].GetSurName(), int(copycontacts[i].GetHomePhone()), int(copycontacts[i].GetWorkPhone()), int(copycontacts[i].GetMobilePhone()),
			copycontacts[i].GetContactInfo());
	}
}