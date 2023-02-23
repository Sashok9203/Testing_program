#pragma once
#include <string>
#include "TestResult.h"
#include <vector>
#include "mylib.h"
struct FI
{
	std::string name, surname;
};
struct Addres
{
	std::string country, city,street;
	int homeNumber;
};
class User
{
private:
	
	const char* user_results = "<userrests>";
	FI fi;
	Addres addres;
	std::string phoneNumber;
	std::string password;
	std::string login;
	std::vector<TestResult> tResults;
	void show_res(bool np ) const;
public:
	User():fi({ "NoName","NoSurname" }), addres({"NoCountry","City","Street",0}),phoneNumber("NoNumber"),
		password("NoPassword"),login("NoLogin") {}
	User(std::ifstream& ifs):fi({ "NoName","NoSurname" }), addres({ "NoCountry","City","Street",0 }), phoneNumber("NoNumber"),
		password("NoPassword"), login("NoLogin") { fromFStream(ifs); }
	const std::string& getPassword() const { return password; }
	const std::string& getlogin() const { return login; }
	const FI getFI() const { return fi; }
	const Addres getAddres() const { return addres; }
	const std::string& getPhone() const { return phoneNumber; }
	const int  getResultsCount() const { return tResults.size(); }
	void setPassword(const std::string& pass);
	void setLogin(const std::string& log);
	void setName(const std::string& name);
	void setSurname( const std::string& surname);
	void setStreet(const std::string& street);
	void setCity(const std::string& city);
	void setCountry(const std::string& country);
	void setHomeNumber(int num);
	void setPhone(const std::string& country);

	void addResult(const TestResult& result) { tResults.push_back(result); };
	void delResult(int ind);
	TestResult& getTestResult(int index);
	void toFStream(std::ofstream& ofs) const ;
	void fromFStream(std::ifstream& ifs);
	void showResults() const;
	void showNPResults() const;
	void show(int index = 0) const;

};

