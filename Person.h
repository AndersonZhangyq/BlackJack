#pragma once
#include <string>

class Person {
public:
	Person();
	Person(std::string name);
	std::string getName();
private:
	std::string name;
};
