#pragma once
#include <map>
#include <vector>
#include <qstring.h>

#include "Contact.h"
class ContactManager
{
private:
	std::map <QString, Contact> contact_map;

public:
	std::map <QString, Contact> finded_map;

	ContactManager() {};

	void AddContact(QString name, Contact cont)
	{
		contact_map.insert({ name , cont });
	}

	Contact* FindContact(QString name)
	{
		auto it = contact_map.find(name);
		if (it == contact_map.end())
			return new Contact();

		return &it->second;
	}

	std::map <QString, Contact>& GetMap()
	{
		return contact_map;
	}

	std::map <QString, Contact>& FindContactsAtAllFields(QString name)
	{
		finded_map.clear();
		for (auto it = contact_map.begin(); it != contact_map.end(); it++)
		{
			if (it->first.contains(name))
				finded_map.emplace(*it);
			if (it->second.GetAll().contains(name))
				finded_map.emplace(*it);
		}

		return finded_map;
	}

	bool DeleteContact(QString& name)
	{
		return contact_map.erase(name);
	}
};

