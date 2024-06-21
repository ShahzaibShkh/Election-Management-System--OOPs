#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <cctype>
#include <Windows.h>
#include <unordered_map>
#include "emsHead.h"

using namespace std;

// Candidate class definition
Candidate::Candidate() {}

Candidate::Candidate(string name, CandidateType type, int age, Cities city, PollingStation Pstat, Towns contestingTown, string partyName) {
    this->name = name;
    this->type = type;
    this->age = age;
    this->partyName = partyName;
    this->city = city;
    this->station = Pstat;
    this->contestingTown = contestingTown;
}

int Candidate::getVotes() {
    return this->votesGained;
}

string Candidate::getCity() {
    return enumToString(this->city);
}

string Candidate::getTown() {
    return enumToString(this->contestingTown);
}

string Candidate::getName() {
    return this->name;
}

int Candidate::getAge() {
    return this->age;
}

string Candidate::getType() {
    return enumToString(this->type);
}

string Candidate::getPartyName() {
    return this->partyName;
}

Towns Candidate::getRawTown() {
    return this->contestingTown;
}

// Voter class definition
int Voter::Votercount = 0;

Voter::Voter() {
    name = "";
    age = 0;
    cnic = "";
    nationality = "";
}

void Voter::setName() {
    cout << "Enter Your Name: ";
    cin >> name;
    while (!isValidString(name)) {
        cout << "Enter name Correctly: " << endl;
        cin >> name;
    }
}

void Voter::setAge() {
    cout << "Enter your Age:" << endl;
    cout << "Age(must be above 18) : ";
    cin >> age;
    if (age < 18 || age > 80) {
        cerr << "Invalid age.\n";
    }
}

void Voter::setCNIC() {
    cout << "Enter CNIC (13 digits): ";
    cin >> cnic;
    if (cnic.length() != 13) {
        cerr << "Invalid CNIC. Please enter a 13-digit numeric CNIC.\n";
    }
    else {
        for (char c : cnic) {
            if (!isdigit(c)) {
                cerr << "Invalid CNIC. Please enter a 13-digit numeric CNIC.\n";
                break;
            }
        }
    }
}

void Voter::setNationality() {
    cout << "Nationality (must be Pakistani): ";
    cin >> nationality;
    if (!(nationality == "Pakistani" || nationality == "pakistani")) {
        cerr << "Invalid nationality. Program terminated.\n";
    }
}

string Voter::getName() const {
    return name;
}

int Voter::getAge() const {
    return age;
}

string Voter::getCNIC() const {
    return cnic;
}

string Voter::getNationality() const {
    return nationality;
}

bool Voter::isValid() {
    return (age >= 18 && (nationality == "Pakistani" || nationality == "pakistani"));
}

int Voter::getVotercount() {
    return Votercount;
}

void Voter::incrementVotercount() {
    ++Votercount;
}

// City class definition
City::City() {}

City::City(const string& name) : cityName(name) {}

void City::display() const {
    cout << "City: " << cityName << endl;
}

// Area class definition
Area::Area(const string& name) : areaName(name), pollingStations(nullptr), candidateNames(nullptr), numPollingStations(0) {}

Area::~Area() {
    delete[] pollingStations;
    delete[] candidateNames;
}

void Area::saveToFile() const {
    ofstream file("pollingstations.txt", ios::app);
    if (file.is_open()) {
        for (int i = 0; i < numPollingStations; ++i) {
            file << cityName << "," << areaName << "," << pollingStations[i] << "\n";
        }
        file.close();
    }
    else {
        cerr << "Unable to open the file for saving.\n";
    }
}

void Area::addPollingStation(const City& city) {
    string id;
    cout << "Enter Polling Station ID: ";
    cin >> id;

    string* newPollingStations = new string[numPollingStations + 1];
    string* newCandidateNames = new string[numPollingStations + 1];

    for (int i = 0; i < numPollingStations; ++i) {
        newPollingStations[i] = pollingStations[i];
        newCandidateNames[i] = candidateNames[i];
    }

    newPollingStations[numPollingStations] = id;
    cout << "Enter Candidate Names (comma-separated): ";
    cin.ignore();
    getline(cin, newCandidateNames[numPollingStations]);

    delete[] pollingStations;
    delete[] candidateNames;
    pollingStations = newPollingStations;
    candidateNames = newCandidateNames;
    ++numPollingStations;
    saveToFile();
}

void Area::removePollingStation() {
    string id;
    cout << "Enter Polling Station ID to remove: ";
    cin >> id;

    int index = -1;
    for (int i = 0; i < numPollingStations; ++i) {
        if (pollingStations[i] == id) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        string* newPollingStations = new string[numPollingStations - 1];
        string* newCandidateNames = new string[numPollingStations - 1];

        for (int i = 0, j = 0; i < numPollingStations; ++i) {
            if (i != index) {
                newPollingStations[j] = pollingStations[i];
                newCandidateNames[j] = candidateNames[i];
                ++j;
            }
        }

        delete[] pollingStations;
        delete[] candidateNames;
        pollingStations = newPollingStations;
        candidateNames = newCandidateNames;
        --numPollingStations;
        saveToFile();
    }
    else {
        cerr << "Polling Station not found.\n";
    }
}

void Area::display() const {
    cout << "Area: " << areaName << endl;
    cout << "Polling Stations:\n";
    for (int i = 0; i < numPollingStations; ++i) {
        cout << "  " << i + 1 << ". " << pollingStations[i] << " - Candidates: " << candidateNames[i] << endl;
    }
}

// EMS class definition
EMS::EMS() {
    voters = nullptr;
    cities = nullptr;
    numCities = 0;
}

EMS::~EMS() {
    delete[] voters;
    delete[] cities;
}

void EMS::displayMenu() const {
    cout << "Election Management System Menu:\n";
    cout << "1. Add City\n";
    cout << "2. Display Cities\n";
    cout << "3. Add Area to City\n";
    cout << "4. Display Areas in City\n";
    cout << "5. Add Polling Station to Area\n";
    cout << "6. Remove Polling Station from Area\n";
    cout << "7. Add Candidate\n";
    cout << "8. Display Candidates\n";
    cout << "9. Cast Vote\n";
    cout << "0. Exit\n";
}

void EMS::run() {
    int choice;
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // consume the newline character

        switch (choice) {
        case 1:
            addCity();
            break;
        case 2:
            displayCities();
            break;
        case 3:
            addArea();
            break;
        case 4:
            displayAreas();
            break;
        case 5:
            addPollingStation();
            break;
        case 6:
            removePollingStation();
            break;
        case 7:
            addCandidate();
            break;
        case 8:
            displayCandidates();
            break;
        case 9:
            castVote();
            break;
        case 0:
            cout << "Exiting the program.\n";
            break;
        default:
            cerr << "Invalid choice. Please enter a valid option.\n";
        }
    } while (choice != 0);
}

void EMS::addCity() {
    string name;
    cout << "Enter City Name: ";
    cin >> name;

    City newCity(name);

    City* newCities = new City[numCities + 1];
    for (int i = 0; i < numCities; ++i) {
        newCities[i] = cities[i];
    }

    newCities[numCities] = newCity;

    delete[] cities;
    cities = newCities;
    ++numCities;
}

void EMS::displayCities() const {
    cout << "Cities:\n";
    for (int i = 0; i < numCities; ++i) {
        cities[i].display();
    }
}

void EMS::addArea() {
    string cityName;
    cout << "Enter City Name: ";
    cin >> cityName;

    int cityIndex = findCity(cityName);

    if (cityIndex != -1) {
        string areaName;
        cout << "Enter Area Name: ";
        cin >> areaName;

        Area newArea(areaName);

        City* newCities = new City[numCities];
        for (int i = 0; i < numCities; ++i) {
            newCities[i] = cities[i];
        }

        newCities[cityIndex].addArea(newArea);

        delete[] cities;
        cities = newCities;
    }
    else {
        cerr << "City not found.\n";
    }
}

void EMS::displayAreas() const {
    string cityName;
    cout << "Enter City Name: ";
    cin >> cityName;

    int cityIndex = findCity(cityName);

    if (cityIndex != -1) {
        cities[cityIndex].displayAreas();
    }
    else {
        cerr << "City not found.\n";
    }
}

void EMS::addPollingStation() {
    string cityName;
    cout << "Enter City Name: ";
    cin >> cityName;

    int cityIndex = findCity(cityName);

    if (cityIndex != -1) {
        cities[cityIndex].addPollingStation(cities[cityIndex]);
    }
    else {
        cerr << "City not found.\n";
    }
}

void EMS::removePollingStation() {
    string cityName;
    cout << "Enter City Name: ";
    cin >> cityName;

    int cityIndex = findCity(cityName);

    if (cityIndex != -1) {
        cities[cityIndex].removePollingStation();
    }
    else {
        cerr << "City not found.\n";
    }
}

void EMS::addCandidate() {
    string cityName;
    cout << "Enter City Name: ";
    cin >> cityName;

    int cityIndex = findCity(cityName);

    if (cityIndex != -1) {
        cities[cityIndex].addCandidate();
    }
    else {
        cerr << "City not found.\n";
    }
}

void EMS::displayCandidates() const {
    string cityName;
    cout << "Enter City Name: ";
    cin >> cityName;

    int cityIndex = findCity(cityName);

    if (cityIndex != -1) {
        cities[cityIndex].displayCandidates();
    }
    else {
        cerr << "City not found.\n";
    }
}

void EMS::castVote() {
    string cityName;
    cout << "Enter City Name: ";
    cin >> cityName;

    int cityIndex = findCity(cityName);

    if (cityIndex != -1) {
        cities[cityIndex].castVote();
    }
    else {
        cerr << "City not found.\n";
    }
}

int EMS::findCity(const string& name) const {
    for (int i = 0; i < numCities; ++i) {
        if (cities[i].getName() == name) {
            return i;
        }
    }
    return -1;
}
