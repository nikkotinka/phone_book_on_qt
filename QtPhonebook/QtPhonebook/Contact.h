#pragma once
#include <string>
#include <qstring.h>

class Contact
{
private:
	QString phone_number;
	QString email;
	QString adres;
	bool favorite;
public:
	Contact() {};
	Contact(QString phone_number, QString email, QString adres) : phone_number (phone_number), email(email), adres(adres)
	{
		favorite = false;
	}
	QString GetAll()
	{
		QString res = "";
		res += phone_number;
		res += ", ";
		res += email;
		res += ", ";

		res += adres;
		return res;
	}

	QString GetPhone()
	{
		return phone_number;
	}
	QString GetEmail()
	{
		return email;
	}
	QString GetAdress()
	{
		return adres;
	}

	void SetAllInfo(QString phone_number, QString email, QString adres)
	{
		this->email = email;
		this->adres = adres;
		this->phone_number = phone_number;
	}

	void SetFavorite(bool fav)
	{
		favorite = fav;
	}

	bool GetFavorite()
	{
		return favorite;
	}
};

