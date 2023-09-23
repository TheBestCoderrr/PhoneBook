#pragma once
#include <iostream>
#include "Consts.h"
using namespace std;




class Contact {
private:
	char* FirstName;
	char* LastName;
	char* SurName;
	size_t HomePhone;
	size_t WorkPhone;
	size_t MobilePhone;
	char* ContactInfo;
public:
	void SetFirstName(char* FirstName);
	char* GetFirstName() { return FirstName;  }
	
	void SetLastName(char* LastName);
	char* GetLastName() { return LastName;  }
	
	void SetSurName(char* SurName);
	char* GetSurName() { return SurName;  }

	void SetHomePhone(size_t HomePhone);
	size_t GetHomePhone() { return HomePhone; }
	
	void SetWorkPhone(size_t WorkPhone);
	size_t GetWorkPhone() { return WorkPhone; }
	
	void SetMobilePhone(size_t MobilePhone);
	size_t GetMobilePhone() { return MobilePhone; }
	
	void SetContactInfo(char* ContactInfo);
	char* GetContactInfo() { return ContactInfo; }

	Contact();
	~Contact();
	Contact(const Contact& other) noexcept;

	Contact& operator=(const Contact& other) noexcept;

	void EnteringContact();
	void Show();
};

inline void Contact::SetFirstName(char* FirstName) {
	this->FirstName = _strdup(FirstName);
}

inline void Contact::SetLastName(char* LastName) {
	this->LastName = _strdup(LastName);
}

inline void Contact::SetSurName(char* SurName) {
	this->SurName = _strdup(SurName);
}

inline void Contact::SetHomePhone(size_t HomePhone) {
	this->HomePhone = HomePhone;
}

inline void Contact::SetWorkPhone(size_t WorkPhone) {
	this->WorkPhone = WorkPhone;
}

inline void Contact::SetMobilePhone(size_t MobilePhone) {
	this->MobilePhone = MobilePhone;
}

inline void Contact::SetContactInfo(char* ContactInfo) {
	this->ContactInfo = ContactInfo;
}

inline Contact::Contact() {
	FirstName = nullptr;
	LastName = nullptr;
	SurName = nullptr;
	HomePhone = NULL;
	WorkPhone = NULL;
	MobilePhone = NULL;
	ContactInfo = nullptr;
}

inline Contact::~Contact() {
	delete[] FirstName, LastName, SurName;
	delete[] ContactInfo;
}

inline Contact::Contact(const Contact& other) noexcept {
	FirstName = _strdup(other.FirstName);
	LastName = _strdup(other.LastName);
	SurName = _strdup(other.SurName);
	HomePhone = other.HomePhone;
	WorkPhone = other.WorkPhone;
	MobilePhone = other.MobilePhone;
	ContactInfo = _strdup(other.ContactInfo);
}

inline Contact& Contact::operator=(const Contact& other) noexcept {
	if (this != &other) {
		delete[] FirstName, LastName, SurName;
		FirstName = _strdup(other.FirstName);
		LastName = _strdup(other.LastName);
		SurName = _strdup(other.SurName);
		HomePhone = other.HomePhone;
		WorkPhone = other.WorkPhone;
		MobilePhone = other.MobilePhone;
		delete[] ContactInfo;
		ContactInfo = _strdup(other.ContactInfo);
	}
	return *this;
}

inline void Contact::EnteringContact() {
	FirstName = new char[PIBSIZE];
	LastName = new char[PIBSIZE];
	SurName = new char[PIBSIZE];
	cin.ignore();
	cout << "Enter first name: ";
	cin.getline(FirstName, PIBSIZE);
	cout << "Enter last name: ";
	cin.getline(LastName, PIBSIZE);
	cout << "Enter surname: ";
	cin.getline(SurName, PIBSIZE);
	cout << "Enter home phone: ";
	cin >> HomePhone;
	cout << "Enter work phone: ";
	cin >> WorkPhone;
	cout << "Enter mobile phone: ";
	cin >> MobilePhone;
	ContactInfo = new char[TEXTSIZE];
	cout << "Enter additional information: ";
	cin.ignore();
	cin.getline(ContactInfo, TEXTSIZE);
}

inline void Contact::Show() {
	cout << "PIB: " << FirstName << ' ' << LastName << ' ' << SurName << endl;
	cout << "HomePhone: " << HomePhone << "\tWorkPhone: " << WorkPhone << "\tMobilePhone: " << MobilePhone << endl;
	cout << "Additional info: " << ContactInfo << endl;
}






class Contacts {
private:
	Contact* contacts = NULL;
	size_t CountContacts = 0;
public:
	~Contacts();

	void SetContacts(Contact* contacts);
	Contact* GetContacts() { return  contacts;  }
	void SetCountContacts(size_t CountContacts);
	size_t GetCountContacts() { return  CountContacts;  }

	int FindContact(char* FirstName, char*LastName, char* SurName);
	void AddContact(const Contact& contact);
	void DeleteContact(int index);
	void PrintOneContact(int index);
	void Show();
};
	
inline Contacts::~Contacts() {
	delete[] contacts;
}

inline void Contacts::SetContacts(Contact* contacts) {
	this->contacts = contacts;
}

inline void Contacts::SetCountContacts(size_t CountContacts) {
	this->CountContacts = CountContacts;
}

inline int Contacts::FindContact(char* FirstName, char*LastName, char* SurName) {
	for (int i = 0; i < CountContacts; i++) {
		if (strcmp(FirstName, contacts[i].GetFirstName()) == 0 && strcmp(LastName, contacts[i].GetLastName()) == 0 && 
			strcmp(SurName, contacts[i].GetSurName()) == 0)
			return i;
	}
	return -1;
}

inline void Contacts::AddContact(const Contact& contact) {
	Contact* NewContacts = new Contact[CountContacts + 1];
	for (int i = 0; i < CountContacts; i++)
		NewContacts[i] = contacts[i];
	delete[] contacts;
	NewContacts[CountContacts] = contact;
	contacts = NewContacts;
	CountContacts++;
}

inline void Contacts::DeleteContact(int index) {
	if (index != -1) {
		for (int i = index; i < CountContacts - 1; i++)
			contacts[i] = contacts[i + 1];
		CountContacts--;
		Contact* NewContacts = new Contact[CountContacts];
		for (int i = 0; i < CountContacts; i++)
			NewContacts[i] = contacts[i];
		delete[] contacts;
		contacts = NewContacts;
	}
}

inline void Contacts::PrintOneContact(int index) {
	if (index != -1)
		contacts[index].Show();
	else
		cout << "Contact not found!" << endl;
}

inline void Contacts::Show() {
	for (int i = 0; i < CountContacts; i++) {
		contacts[i].Show();
		cout << endl;
	}
}