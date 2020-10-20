#pragma once
#include <string>
#include <iostream>
using namespace std;

class Book
{
private:
	string title;
	double price;

public:
	Book(string title, double price) : title(title), price(price) {
		cout << "Constructor..." << endl;
	};

	//copy constructor
	Book(const Book& other) {
		cout << "Copy Constructor..." << endl;
		this->price = other.getPrice();
		this->title = other.getTitle();
	}

	~Book() {
		cout << "Destructor..." << endl;
	};

	//getters/setters
	string getTitle() const { return this->title; }
	double getPrice() const { return this->price; }

	//assignment
	void operator=(const Book& other) {
		this->price = other.getPrice();
		this->title = other.getTitle();
	}

	friend ostream& operator<<(ostream& os, const Book& book) {
		os << book.title << " - " << book.price << endl;
		return os;
	}
};


