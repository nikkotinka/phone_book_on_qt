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
	ContactManager() {};

	void AddContact(QString name, Contact cont)
	{
		contact_map.insert({ name , cont });
	}

	std::map <QString, Contact>& GetMap()
	{
		return contact_map;
	}

	std::map <QString, Contact> FindContactsAtAllFields(QString name)
	{
		std::map <QString, Contact> results_after_find;
		for (auto it = contact_map.begin(); it != contact_map.end(); it++)
		{
			if (it->first.contains(name))
				results_after_find.emplace(*it);
			if (it->second.GetAll().contains(name))
				results_after_find.emplace(*it);
		}

		return results_after_find;
	}

	bool DeleteContact(QString& name)
	{
		return contact_map.erase(name);
	}
};

