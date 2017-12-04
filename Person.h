#pragma once
#include <string>

class Person {
public:
	Person();
	Person(std::string name);
	std::string getName() const;
private:
	std::string name;
};
