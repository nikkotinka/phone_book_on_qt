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

	std::map <QString, Contact> GetMap()
	{
		return contact_map;
	}

	Contact FindContact(const QString& name)
	{
		if(contact_map.find(name) != contact_map.end())
			return contact_map.at(name);
		return Contact(); // добавить более осмысленный возврат ошибки через expected
	}

	std::map <QString, Contact> FindClosestContacts(QString name)
	{
		std::map <QString, Contact> results_after_find;
		for (auto it = contact_map.begin(); it != contact_map.end(); it++)
		{
			if (it->first.contains(name)) // улучшить чтобы находил более гибко подстроки
				results_after_find.emplace(*it);
		}
		return results_after_find;
	}

	bool DeleteContact(QString& name)
	{
		return contact_map.erase(name);
	}
};

