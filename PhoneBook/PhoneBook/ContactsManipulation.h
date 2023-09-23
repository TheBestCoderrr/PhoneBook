#pragma once
#include "Class.h"
void EnteringPIB(char* FirstName, char* LastName, char* SurName);
void GetContactsFromFile(FILE* ContactsFile, Contacts contacts);
void SaveContactsInFile(FILE* ContactsFile, Contacts contacts);