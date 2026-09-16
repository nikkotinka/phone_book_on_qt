#pragma once
#include <map>
#include <vector>
#include "Contact.h"
class ContactManager
{
private:
	std::map <std::string, Contact> contact_map;

public:
	ContactManager() {};

	void AddContact(std::string name, Contact cont)
	{
		contact_map.insert({ name , cont });
	}

	std::map <std::string, Contact> GetMap()
	{
		return contact_map;
	}

	Contact FindContact(std::string name)
	{
		if(contact_map.find(name) != contact_map.end())
			return contact_map.at(name);
		return Contact(); // добавить более осмысленный возврат ошибки через expected
	}

	std::vector <std::pair <std::string, Contact>> FindClosestContacts(std::string name)
	{
		std::vector <std::pair <std::string, Contact>> results_after_find;
		for (auto it = contact_map.begin(); it != contact_map.end(); it++)
		{
			if (it->first.find(name) != std::string::npos) // улучшить чтобы находил более гибко подстроки
				results_after_find.push_back(*it);
		}
	}
};

