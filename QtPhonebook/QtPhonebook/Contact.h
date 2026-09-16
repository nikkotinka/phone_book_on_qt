#pragma once
#include <string>
class Contact
{
private:
	std::string phone_number;
	std::string email;
	std::string adres;
public:
	Contact() {};
	Contact(std::string phone_number, std::string email, std::string adres) : phone_number (phone_number), email(email), adres(adres)
	{
		
	}
	std::string GetAll()
	{
		std::string res = "";
		res += phone_number;
		res += ", ";
		res += email;
		res += ", ";

		res += adres;
		return res;
	}
};

