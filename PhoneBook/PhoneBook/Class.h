#pragma once
#include <iostream>
#include "Consts.h"
using namespace std;
class PIB {
public:
	char* FirstName;
	char* LastName;
	char* SurName;

	PIB() = default;
	PIB(const PIB& otherpib) noexcept;
	PIB(PIB&& otherpib) noexcept;
	~PIB();

	PIB& operator=(const PIB& otherpib) noexcept;
};

inline PIB::PIB(const PIB& otherpib) noexcept {
	FirstName = otherpib.FirstName;
	LastName = otherpib.LastName;
	SurName = otherpib.SurName;
}

inline PIB::PIB(PIB&& otherpib) noexcept{
	FirstName = otherpib.FirstName;
	otherpib.FirstName = nullptr;
	LastName = otherpib.LastName;
	otherpib.LastName = nullptr;
	SurName = otherpib.SurName;
	otherpib.SurName = nullptr;
}

inline PIB::~PIB() {
	delete[] FirstName, LastName, SurName;
}

inline PIB& PIB::operator=(const PIB& otherpib) noexcept {
	if (this != &otherpib) {
		delete[] FirstName, LastName, SurName;
		FirstName = _strdup(otherpib.FirstName);
		LastName = _strdup(otherpib.LastName);
		SurName = _strdup(otherpib.SurName);
	}
	return *this;
}



class Contact {
private:
	PIB pib;
	size_t HomePhone;
	size_t WorkPhone;
	size_t MobilePhone;
	char* ContactInfo;
public:
	void SetPIB(PIB PIB);
	PIB GetPIB() { return pib; }

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

inline void Contact::SetPIB(PIB pib) {
	this->pib = pib;
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
	pib.FirstName = NULL;
	pib.LastName = NULL;
	pib.SurName = NULL;
	HomePhone = NULL;
	WorkPhone = NULL;
	MobilePhone = NULL;
	ContactInfo = NULL;
}

inline Contact::~Contact() {
	delete[] pib.FirstName, pib.LastName, pib.SurName;
	delete[] ContactInfo;
}

inline Contact::Contact(const Contact& other) noexcept {
	pib.FirstName = _strdup(other.pib.FirstName);
	pib.LastName = _strdup(other.pib.LastName);
	pib.SurName = _strdup(other.pib.SurName);
	HomePhone = other.HomePhone;
	WorkPhone = other.WorkPhone;
	MobilePhone = other.MobilePhone;
	ContactInfo = _strdup(other.ContactInfo);
}

inline Contact& Contact::operator=(const Contact& other) noexcept {
	if (this != &other) {
		delete[] pib.FirstName, pib.LastName, pib.SurName;
		pib.FirstName = _strdup(other.pib.FirstName);
		pib.LastName = _strdup(other.pib.LastName);
		pib.SurName = _strdup(other.pib.SurName);
		HomePhone = other.HomePhone;
		WorkPhone = other.WorkPhone;
		MobilePhone = other.MobilePhone;
		delete[] ContactInfo;
		ContactInfo = _strdup(other.ContactInfo);
	}
	return *this;
}

inline void Contact::EnteringContact() {
	pib.FirstName = new char[PIBSIZE];
	pib.LastName = new char[PIBSIZE];
	pib.SurName = new char[PIBSIZE];
	cin.ignore();
	cout << "Enter first name: ";
	cin.getline(pib.FirstName, PIBSIZE);
	cout << "Enter last name: ";
	cin.getline(pib.LastName, PIBSIZE);
	cout << "Enter surname: ";
	cin.getline(pib.SurName, PIBSIZE);
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
	cout << "PIB: " << pib.FirstName << ' ' << pib.LastName << ' ' << pib.SurName << endl;
	cout << "HomePhone: " << HomePhone << "\tWorkPhone: " << WorkPhone << "\tMobilePhone: " << MobilePhone << endl;
	cout << "Additional info: " << ContactInfo << endl;
}

class Contacts {
private:
	Contact* contacts = NULL;
	size_t CountContacts = 0;
public:
	void SetContacts(Contact* contacts);
	Contact* GetContacts() { return  contacts;  }
	void SetCountContacts(size_t CountContacts);
	size_t GetCountContacts() { return  CountContacts;  }

	int FindContact(const PIB pib);
	void AddContact(const Contact& contact);
	void DeleteContact(int index);
	void PrintOneContact(int index);
	void Show();
};
	
inline void Contacts::SetContacts(Contact* contacts) {
	this->contacts = contacts;
}

inline void Contacts::SetCountContacts(size_t CountContacts) {
	this->CountContacts = CountContacts;
}

inline int Contacts::FindContact(const PIB otherpib) {
	PIB pib;
	for (int i = 0; i < CountContacts; i++) {
		pib = contacts[i].GetPIB();
		if (strcmp(pib.FirstName, otherpib.FirstName) == 0 && strcmp(pib.LastName, otherpib.LastName) == 0 && strcmp(pib.SurName, otherpib.SurName) == 0)
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