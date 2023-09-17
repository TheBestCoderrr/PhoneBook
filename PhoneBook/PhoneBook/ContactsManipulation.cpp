//#include <iostream>
//#include "Class.h"
//void SaveContactsInFile(FILE* ContactsFile, Group contacts) {
//	Contact* copycontacts = contacts.GetContacts();
//	PIB copyPIB;
//	for (int i = 0; i < contacts.GetCountContacts(); i++) {
//		copyPIB = copycontacts[i].GetPIB();
//		fprintf(ContactsFile, "PIB: %s %s %s\nHomePhone: %ize_t\tWorkPhone: %i\tMobilePhone: %i\tAdditional info: %s", copyPIB.FirstName, copyPIB.LastName, 
//			copyPIB.SurName, copycontacts[i].GetHomePhone(), copycontacts[i].GetWorkPhone(), copycontacts[i].GetMobilePhone(), copycontacts[i].GetContactInfo());
//	}
//}