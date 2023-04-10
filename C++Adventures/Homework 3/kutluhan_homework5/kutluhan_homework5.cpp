#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "movie.h"
#include "strutils.h"

using namespace std;

void MainParseFilm(vector <string> films, vector <Movie> & filmsdb) {
	string line, name, genre;
	int first_blank = 0, sec_blank = 0, year;
	int j = 0, i = 0;
	bool loop = true;
	while (loop) {
		line = films[j];
		if (first_blank == 0) {
			first_blank = line.find(" ");
			sec_blank = line.find(" ", first_blank + 1);
		}
		else if (first_blank > sec_blank) {
			sec_blank = line.find(" ", first_blank + 1);
		}
		else if (sec_blank > first_blank){
			first_blank = line.find(" ", sec_blank + 1);
		}

		if (first_blank > sec_blank) {
			string interval = line.substr(sec_blank + 1, abs(first_blank - sec_blank) - 1);
			if (atoi(line.substr(sec_blank + 1, abs(first_blank - sec_blank) - 1))) {
				year = atoi(line.substr(sec_blank + 1, abs(first_blank - sec_blank) - 1));
				name = line.substr(0, sec_blank);
				genre = line.substr(first_blank + 1);
				filmsdb[j].setName(name);
				filmsdb[j].setGenre(genre);
				filmsdb[j].setYear(year);
				j++;
				first_blank = 0;
				sec_blank = 0;
			}
		}
		else if (sec_blank > first_blank) {
			string interval = line.substr(first_blank + 1, abs(first_blank - sec_blank) - 1);
			if (atoi(line.substr(first_blank + 1, abs(first_blank - sec_blank) - 1))){
				year = atoi(line.substr(first_blank + 1, abs(first_blank - sec_blank) - 1));
				name = line.substr(0, first_blank);
				genre = line.substr(sec_blank + 1);
				filmsdb[j].setName(name);
				filmsdb[j].setGenre(genre);
				filmsdb[j].setYear(year);
				j++;
				first_blank = 0;
				sec_blank = 0;
			}
		}
		
		if (j == films.size()) {
			loop = false;
		}
	}
}

void choice1func(vector <Movie> filmsdb, string orgenre) {
	//initializing
	vector <int> locations;

	//formatting the genre input
	string newgenre;
	newgenre = LowerString(orgenre);
	newgenre[0] = newgenre[0] - 32;
	if (newgenre.find("-") != string::npos) {
		int loc = newgenre.find("-");
		newgenre[loc + 1] = newgenre[loc + 1] - 32;
	}

	//finding the genre locations in Movie vector
	for (int i = 0; i < filmsdb.size(); i++) {
		if (filmsdb[i].getGenre() == newgenre) {
			locations.push_back(i);
		}
	}

	if (locations.size() > 0) {
		cout << endl << orgenre << " movies from newest to oldest:" << endl;
		for (int i = 0; i < locations.size(); i++) {
			cout << "Movie name: " << filmsdb[locations[i]].getName() << " Release Year: " << filmsdb[locations[i]].getYear() << endl;
		}
	}
	else {
		cout << endl << "There are no " << orgenre << " movies!" << endl;
	}
}

void choice2func(vector <Movie> filmsdb, string year) {
	vector <int> locations;
	if (year.find("-") != string::npos) {
		int firstyear, secondyear;
		firstyear = atoi(year.substr(0, year.find("-")));
		secondyear = atoi(year.substr(year.find("-") + 1));
		for (int i = 0; i < filmsdb.size(); i++) {
			if (filmsdb[i].getYear() >= firstyear && filmsdb[i].getYear() <= secondyear) {
				locations.push_back(i);
			}
		}
		if (locations.size() > 0) {
			cout << "Movies released between the years " << year << " from A to Z with decreasing year ordering:" << endl;
			for (int i = 0; i < locations.size(); i++) {
				cout << "Movie name: " << filmsdb[locations[i]].getName() << " Release Year: " << filmsdb[locations[i]].getYear() << " Genre: " << filmsdb[locations[i]].getGenre() << endl;
			}
		}
		else {
			cout << "There are no movies released between " << year << "!" << endl;
		}
	}

	else {
		int intyear = atoi(year);
		for (int i = 0; i < filmsdb.size(); i++) {
			if (filmsdb[i].getYear() == intyear) {
				locations.push_back(i);
			}
		}

		if (locations.size() > 0) {
			cout << "Movies released in " << year << " from A to Z:" << endl;
			for (int i = 0; i < locations.size(); i++) {
				cout << "Movie name: " << filmsdb[locations[i]].getName() << " Genre: " << filmsdb[locations[i]].getGenre() << endl;
			}
		}
		else {
			cout << "There are no movies released in " << year << "!" << endl;
		}
	}
}

void AlphabeticalOrder(vector <Movie> & filmsdb) {
	string name1, name2, genre1, genre2, tempname, tempgenre;
	int year1, year2, tempyear;
	for (int i = 0; i < filmsdb.size(); i++) {
		for (int j = i + 1; j < filmsdb.size(); j++) {
			name1 = filmsdb[i].getName();
			name2 = filmsdb[j].getName();

			genre1 = filmsdb[i].getGenre();
			genre2 = filmsdb[j].getGenre();

			year1 = filmsdb[i].getYear();
			year2 = filmsdb[j].getYear();
			if (year1 < year2) {
				tempname = name1;
				tempgenre = genre1;
				tempyear = year1;

				filmsdb[i].setName(name2);
				filmsdb[i].setGenre(genre2);
				filmsdb[i].setYear(year2);

				filmsdb[j].setName(tempname);
				filmsdb[j].setGenre(tempgenre);
				filmsdb[j].setYear(tempyear);
			}
		}
	}

	//ordering same years alphabetically
	for (int i = 0; i < filmsdb.size(); i++) {
		for (int j = i + 1; j < filmsdb.size(); j++) {
			name1 = filmsdb[i].getName();
			name2 = filmsdb[j].getName();

			genre1 = filmsdb[i].getGenre();
			genre2 = filmsdb[j].getGenre();

			year1 = filmsdb[i].getYear();
			year2 = filmsdb[j].getYear();
			if (year1 == year2) {
				bool loop = true;
				while (loop) {
					if (name1 > name2) {
						tempname = name1;
						tempgenre = genre1;

						filmsdb[i].setName(name2);
						filmsdb[i].setGenre(genre2);

						filmsdb[j].setName(tempname);
						filmsdb[j].setGenre(tempgenre);
						loop = false;
					}
					else if (name1 < name2) {
						loop = false;
					}
				}
			}
		}
	}
}

void displaychoice(vector <Movie> filmsdb) {
	string decision;
	bool absoluteloop = true;
	while (absoluteloop) {
		cout << endl << "Enter your choice: ";
		cin >> decision;
		if (decision == "1") {
			string orgenre;
			cout << "Please enter the genre of the movie you want to watch: " ;
			cin >> orgenre;
			choice1func(filmsdb, orgenre);
		}
		else if (decision == "2") {
			string year;
			cout << "Please enter the year of the movie you want to watch: ";
			cin >> year;
			choice2func(filmsdb, year);
		}
		
		else if (decision == "3") {
			cout << "Thank you..." << endl;
			absoluteloop = false;
		}
		else {
			cout << "Invalid action!" << endl;
		}
	}
}

int main() {
	ifstream input;
	string filename, s;
	vector <string> films;
	cout << "Welcome to the movie recommender program!" << endl << endl;
	bool open = true;
	cout << "Please enter the movie list filename: ";
	cin >> filename;
	while (open) {
		input.open(filename.c_str());
		if (input.fail()) {
			cout << "Please check filename! Enter a correct movie list filename: ";
			cin >> filename;
		}
		else {
			while (getline(input, s)) {
				if (s[s.length() - 1] == '\r') {
					s = s.substr(0, s.length() - 1);
				}
				films.push_back(s);
				if (input.eof()) {
					input.close();
					open = false;
				}
			}
		}
	}
	vector <Movie> filmsdb(films.size());
	cout <<
		"Please select your action:" << endl <<
		"1. Select the genre of the movie that you want to watch" << endl <<
		"2. Select the year of the movie that you want to watch" << endl <<
		"3. Exit program" << endl;
	MainParseFilm(films, filmsdb);
	AlphabeticalOrder(filmsdb);
	displaychoice(filmsdb);
	return 0;
}