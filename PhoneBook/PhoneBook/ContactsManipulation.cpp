#include <iostream>
#include "Class.h"
#include "Consts.h"
using namespace std;

void EnteringPIB(PIB& otherpib) {
	cin.ignore();
	cout << "Enter first name: ";
	cin.getline(otherpib.FirstName, PIBSIZE);
	cout << "Enter last name: ";
	cin.getline(otherpib.LastName, PIBSIZE);
	cout << "Enter surname: ";
	cin.getline(otherpib.SurName, PIBSIZE);
}

int GetIntNum(char* Buffer) {
	int num = 0;
	for (int i = 0; i < strlen(Buffer); i++) {
		num += Buffer[i] - '0';
		num *= 10;
	}
	num /= 10;
}

void GetContactsFromFile(FILE* ContactsFile, Contacts contacts) {
	size_t CountContactsInFile = 0;
	char letter;
	do{
		letter = fgetc(ContactsFile);
		if (letter == '\n')
			CountContactsInFile++;
	} while (letter != EOF);
	CountContactsInFile /= 3;

	Contact* NewContacts = new Contact[contacts.GetCountContacts() + CountContactsInFile];
	NewContacts = contacts.GetContacts();
	PIB pib;
	char* str = new char[TEXTSIZE];
	char* Buffer = NULL, * NextBuffer = NULL;
	for (int i = contacts.GetCountContacts() - 1; i < CountContactsInFile + contacts.GetCountContacts(); i++) {
		fseek(ContactsFile, 5, SEEK_CUR);
		fgets(str, TEXTSIZE, ContactsFile);
		Buffer = strtok_s(str, " ", &NextBuffer);
		pib.FirstName = Buffer;
		Buffer = strtok_s(NULL, " ", &NextBuffer);
		pib.LastName = Buffer;
		Buffer = strtok_s(NULL, " ", &NextBuffer);
		pib.SurName = Buffer;
		NewContacts[i].SetPIB(pib);
		fgets(str, TEXTSIZE, ContactsFile);
		Buffer = strtok_s(str, " ", &NextBuffer);
		Buffer = strtok_s(NULL, " ", &NextBuffer);
		GetIntNum(Buffer);

		fgets(str, TEXTSIZE, ContactsFile);
		Buffer = strtok_s(str, " ", &NextBuffer);
		Buffer = strtok_s(NULL, " ", &NextBuffer);
		Buffer = strtok_s(NULL, " ", &NextBuffer);
		NewContacts[i].SetContactInfo(Buffer);
	}

	delete[] contacts.GetContacts();
	contacts.SetContacts(NewContacts);
	delete[] str;
	contacts.SetCountContacts(contacts.GetCountContacts() + CountContactsInFile);
}

void SaveContactsInFile(FILE* ContactsFile,Contacts contacts) {
	Contact* copycontacts = contacts.GetContacts();
	PIB copyPIB;
	for (int i = 0; i < contacts.GetCountContacts(); i++) {
		copyPIB = copycontacts[i].GetPIB();
		fprintf(ContactsFile, "PIB: %s %s %s\nHomePhone: %i\nWorkPhone: %i\nMobilePhone: %i\nAdditional info: %s", copyPIB.FirstName, copyPIB.LastName, 
			copyPIB.SurName, int(copycontacts[i].GetHomePhone()), int(copycontacts[i].GetWorkPhone()), int(copycontacts[i].GetMobilePhone()), 
			copycontacts[i].GetContactInfo());
	}
}