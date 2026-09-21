#pragma once
#include <string>
#include <qstring.h>

class Contact
{
private:
	QString phone_number;
	QString email;
	QString adres;
public:
	Contact() {};
	Contact(QString phone_number, QString email, QString adres) : phone_number (phone_number), email(email), adres(adres)
	{
		
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
};

