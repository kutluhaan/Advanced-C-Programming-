#include <iostream>
#include <vector>
#include <string>
#include "strutils.h"
#include "randgen.h"

using namespace std;

struct films {
	string movie, type;
	int date = 0;
};

void AlphabeticalOrder(vector <string> );
void displaythechoice(vector <films> archive);
void print(vector <films> archive, string genre, string org_genre);

void Assigning(vector <string>& allfilms) {
	//initializations
	int wantedindex, year;
	vector <films> archive(allfilms.size());
	string name, genre, yearstr, hold;

	//assigning
	for (int i = 0; i < allfilms.size(); i++) {
		hold = allfilms[i];
		wantedindex = hold.find(';');
		if (wantedindex != string::npos) {
			name = hold.substr(0, wantedindex);
			archive[i].movie = name;
			hold = hold.substr(wantedindex + 1);
			wantedindex = hold.find(';');
			if (wantedindex != string::npos) {
				yearstr = hold.substr(0, wantedindex);
				year = stoi(yearstr);
				archive[i].date = year;
				hold = hold.substr(wantedindex + 1);
				archive[i].type = hold;
			}
		}
		//cout << endl << archive[i].movie << endl << archive[i].date << endl << archive[i].type << endl;
	}
	displaythechoice(archive);
}
void Separate(string filminput, vector <string> & allfilms) {
	//finding films
	string film;
	int wantedindex;
	bool loop = true;
	while (loop) {
		wantedindex = filminput.find("|");
		if (wantedindex != string::npos) {
			film = filminput.substr(0, wantedindex);
			allfilms.push_back(film);
			filminput = filminput.substr(wantedindex + 1);
		}
		else if (wantedindex == string::npos) {
			allfilms.push_back(filminput);
			loop = false;
		}
	}
}

void displaythechoice(vector <films> archive) {
	string choice;
	bool loop = true;	
	while (loop) {
		cout << endl << "Enter your choice: ";
		cin >> choice;
		if (choice == "1") {
			string org_genre, genre;
			cout << "Please enter the genre of the movie you want to watch: ";
			cin >> org_genre;
			genre = LowerString(org_genre);
			if (genre == "drama") {
				print(archive, "Drama", org_genre);
			}
			else if (genre == "sci-fi") {
				print(archive, "Sci-Fi", org_genre);
			}
			else if (genre == "comedy") {
				print(archive, "Comedy", org_genre);
			}
			else if (genre == "action") {
				print(archive, "Action", org_genre);
			}
			else {
				cout << endl << "There are no " << org_genre << " movies!" << endl;
			}
		}
		else if (choice == "2") {
			string stryear;
			cout << "Please enter the year of the movie you want to watch: ";
			cin >> stryear;

			if (stryear.find("-") == string::npos) {
				struct films {
					string moviename, genre;
				};
				int intyear, films_same_year = 0;
				intyear = atoi(stryear);

				for (int i = 0; i < archive.size(); i++) {
					if (archive[i].date == intyear) {
						films_same_year++;
					}
				}
				vector <films> film(films_same_year);
				int j = 0;
				for (int i = 0; i < archive.size(); i++) {
					if (archive[i].date == intyear) {
						film[j].moviename = archive[i].movie;
						film[j].genre = archive[i].type;
						j++;
					}
				}

				if (film.size() > 0) {
					if (film.size() > 1) {
						vector <string> input(film.size());
						for (int i = 0; i < film.size(); i++) {
							input[i] = film[i].moviename + "/" + film[i].genre;
						}
						//AlphabeticalOrder(input);
						struct values {
							string name, kind;
						};
						vector <values> namesandgenre(input.size());
						//finding the names and genres and appending them to the values
						int location;
						for (int i = 0; i < input.size(); i++) {
							location = input[i].find("/");
							string text = input[i];
							namesandgenre[i].name = text.substr(0, location);
							namesandgenre[i].kind = text.substr(location + 1);
						}

						//ordering
						string firstname, firstgenre, secondname, secondgenre;
						char first, second;
						for (int i = 0; i < namesandgenre.size(); i++) {
							for (int j = 1; j < namesandgenre.size(); j++) {
								first = namesandgenre[i].name[i];
								second = namesandgenre[j].name[i];
								if (first > second) {

									firstname = namesandgenre[i].name;
									firstgenre = namesandgenre[i].kind;
									secondname = namesandgenre[j].name;
									secondgenre = namesandgenre[j].kind;

									namesandgenre[j].name = firstname;
									namesandgenre[j].kind = firstgenre;
									namesandgenre[i].name = secondname;
									namesandgenre[i].kind = secondgenre;

								}
								else if (second == first) {
									i++;
								}
							}
						}
						cout << "Movies released in " << stryear << " from A to Z:" << endl;
						for (int i = 0; i < namesandgenre.size(); i++) {
							cout << "Movie name: " << namesandgenre[i].name << " Genre: " << namesandgenre[i].kind << endl;
						}
					}
					else {
						cout << "Movies released in " << stryear << " from A to Z: " << "Movie name: " << film[0].moviename << " Genre: " << film[0].genre;
					}
				}
				else {
					cout << "There are no movies released in " << intyear << "!" << endl;
				}
			}
			else {
				int firstyear, secondyear, location = stryear.find("-");
				firstyear = atoi(stryear.substr(0, location));
				secondyear = atoi(stryear.substr(location + 1));
				string filmcell;
				struct collection {
					string moviename, genre;
					int date = 0;
				};

				//collecting the films in a vector
				int counter = 0;
				for (int i = 0; i < archive.size(); i++) {
					if (firstyear <= archive[i].date && archive[i].date <= secondyear) {
						counter++;
					}
				}

				vector <collection> interval(counter);

				//appending the elements
				int j = 0;
				for (int i = 0; i < archive.size(); i++) {
					if (firstyear <= archive[i].date && archive[i].date <= secondyear) {
						interval[j].date = archive[i].date;
						interval[j].genre = archive[i].type;
						interval[j].moviename = archive[i].movie;
						j++;
					}
				}

				if (interval.size() > 0) {
					//ordering the vector
					for (int i = 0; i < interval.size(); i++) {
						for (int j = i + 1; j < interval.size(); j++) {
							if (interval[j].date > interval[i].date) {
								string temp_genre, temp_name;
								int temp_date;
								temp_genre = interval[j].genre;
								temp_name = interval[j].moviename;
								temp_date = interval[j].date;

								interval[j].genre = interval[i].genre;
								interval[j].moviename = interval[i].moviename;
								interval[j].date = interval[i].date;

								interval[i].genre = temp_genre;
								interval[i].moviename = temp_name;
								interval[i].date = temp_date;
							}
						}
					
					}

					//finding with the same year and ordering alphabetically
					string firstname, firstgenre, secondname, secondgenre;
					char first, second;
					int i = 0, k = 0;
					for (int j = i + 1; j < interval.size(); i++, j++) {
						if (interval[j].date == interval[i].date) {
							first = interval[i].moviename[k];
							second = interval[j].moviename[k];
							bool loop = true;
							while (loop) {

							}
							if (first > second) {

								firstname = interval[i].moviename;
								firstgenre = interval[i].genre;
								secondname = interval[j].moviename;
								secondgenre = interval[j].genre;

								interval[j].moviename = firstname;
								interval[j].genre = firstgenre;
								interval[i].moviename = secondname;
								interval[i].genre = secondgenre;
							}
							else if (second == first) {
								k++;
							}
						}
					}
					
					cout << "Movies released between the years " << stryear << " from A to Z with decreasing year ordering:" << endl;
					for (int i = 0; i < interval.size(); i++) {
						cout << "Movie name: " << interval[i].moviename << " Release Year: " <<interval[i].date << " Genre: " << interval[i].genre << endl;
					}
				}
				else {
					cout << "There are no movies released between " << stryear << "!" << endl;
				}
			}
		}
		else if (choice == "3") {
			RandGen random;
			int number = random.RandInt(archive.size());
			cout << "Movie name: " << archive[number].movie << " Release Year: " << archive[number].date << " Genre: " << archive[number].type << endl;
		}
		else {
			cout << "Thank you..." << endl;
			loop = false;
		}
	}
}

void print(vector <films> archive, string genre, string org_genre) {
	string tempstr, tempstr_2;
	int size = 0, temp, temp_2;
	struct holder {
		string name;
		int year = 0;
	};
	//finding the number of genre
	for (int i = 0; i < archive.size(); i++) {
		if (archive[i].type == genre) {
			size++;
		}
	}
	//appending the movies in the genre
	vector <holder> hold(size);
	int j = 0;
	for (int i = 0; i < archive.size(); i++) {
		if (archive[i].type == genre) {
			hold[j].name = archive[i].movie;
			hold[j].year = archive[i].date;
			j++;
		}
	}
	//ordering the years 
	for (int i = 0; i < hold.size(); i++) {
		for (int j = i + 1; j < hold.size(); j++) {
			int a = hold[j].year, b = hold[i].year;
			if (a > b) {
				//changing the years
				temp = hold[i].year;
				temp_2 = hold[j].year;
				hold[i].year = temp_2;
				hold[j].year = temp;

				//changing the names
				tempstr = hold[i].name;
				tempstr_2 = hold[j].name;
				hold[i].name = tempstr_2;
				hold[j].name = tempstr;
			}
		}
	}

	//finding the same years and ordering alphabetically
	char first, second;
	string firstname, secondname;
	int i = 0, k = 0;
	for (int j = i + 1; j < hold.size(); i++, j++) {
		if (hold[j].year == hold[i].year) {
			bool loop = true;
			int control = 0;
			while (loop){
				first = hold[i].name[k];
				second = hold[j].name[k];
				if (first > second) {
					firstname = hold[i].name;
					secondname = hold[j].name;

					hold[j].name = firstname;
					hold[i].name = secondname;
					loop = false;
				}
				else if (second == first) {
					k++;
					control++;
				}
				else if (first < second) {
						loop = false;
				}
			}
		}
	}
	
	//printing the result
	cout << endl << org_genre << " movies from newest to oldest:" << endl;
	for (int i = 0; i < hold.size(); i++) {
		cout << "Movie name: " << hold[i].name << " Release Year: " << hold[i].year << endl;
	}
}
int main() {
	string filminput, choice;
	vector <string> allfilms;
	cout << "Welcome to the movie recommender program!" << endl << endl;
	cout << "Please enter the movie, year and genre list:" << endl;
	cin >> filminput;
	cout << endl << "Please select your action:" << endl << 
		"1. Select the genre of the movie that you want to watch" << endl << 
		"2. Select the year of the movie that you want to watch" << endl << 
		"3. Choose a random movie" << endl << 
		"4. Exit program" << endl;
	Separate(filminput, allfilms);
	Assigning(allfilms);
	return 0;
}