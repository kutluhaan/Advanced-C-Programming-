#include "movie.h"
#include <iostream>

Movie::Movie() {
	name = "";
	year = 0;
	genre = "";
}

Movie::Movie(string n, int y, string g) {
	name = n;
	year = y;
	genre = g; 
}

void Movie::setName(string n) {
	name = n;
}

string Movie::getName() const {
	return name;
}

void Movie::setGenre(string g) {
	genre = g;
}

string Movie::getGenre() const {
	return genre;
}

void Movie::setYear(int y) {
	year = y;
}

int Movie::getYear() const {
	return year;
}

void Movie::print() const {
	cout << name << " " << year << " " << genre;
}