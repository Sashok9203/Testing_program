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
	std::string show_res(bool np ) const;
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

	int  getResultsCount() const { return (int)tResults.size(); }
	int  getPNPResultsCount( bool pass) const;
	int  getAverageRating() const;
	double  getAveragePercent() const;
	int  getGetTotalQuesCount() const;
	int  getGetTotalRACount() const;

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

	std::string getResStr() const;
	std::string getNPResStr() const;
	std::string  getUserStr(int index = 0) const;
	std::string  getShortStatStr(int index = 0) const;
	std::string  getSUserInfo(int index = 0) const;
	std::string  getStatStr() const;
};

