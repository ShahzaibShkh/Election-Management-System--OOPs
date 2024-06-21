#ifndef EMSHEAD_H
#define EMSHEAD_H

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <cctype>
#include <Windows.h>
#include <unordered_map>

using namespace std;

enum class PollingStation { IT001, JT001, MT002, FT002, };
enum class Cities { Lahore, Faisalabad };
enum class Towns { FaisalTown, ModelTown, JinnahTown, IqbalTown };
enum class CandidateType { MPA, MNA };

unordered_map<Cities, string> cityToString{
    {Cities::Lahore, "Lahore"},
    {Cities::Faisalabad, "Faisalabad"}
};

unordered_map<Towns, string> townToString{
    {Towns::FaisalTown, "Faisal Town"},
    {Towns::ModelTown, "Model Town"},
    {Towns::JinnahTown, "Jinnah Town"},
    {Towns::IqbalTown, "Iqbal Town"}
};

unordered_map<CandidateType, string> typeToString{
    {CandidateType::MPA, "MPA"},
    {CandidateType::MNA, "MNA"}
};
unordered_map<PollingStation, string> stationToString{
    {PollingStation::IT001, "IT001"},
    {PollingStation::JT001, "JT001"},
    {PollingStation::MT002, "MT002"},
    {PollingStation::FT002, "FT002"}
};

template<typename T>
string enumToString(T value) {
    unordered_map<T, string> mapping;

    if constexpr (is_same<T, Cities>::value) {
        mapping = cityToString;
    }
    else if constexpr (is_same<T, Towns>::value) {
        mapping = townToString;
    }
    else if constexpr (is_same<T, CandidateType>::value) {
        mapping = typeToString;
    }
    else if constexpr (is_same<T, PollingStation>::value) {
        mapping = stationToString;
    }
    else {
        // Handle other enum types if needed
    }

    return mapping[value];
}

class Candidate {
    string name;
    int age;
    string partyName;
    CandidateType type;
    Cities city;
    PollingStation station;
    Towns contestingTown;

public:
    int votesGained = 0;
    Candidate();
    Candidate(string name, CandidateType type, int age, Cities city, PollingStation Pstat, Towns contestingTown, string partyName);

    int getVotes();
    string getCity();
    string getTown();
    string getName();
    int getAge();
    string getType();
    string getPartyName();
    Towns getRawTown();
};

class Voter {
protected:
    string name;
    int age;
    string cnic;
    string nationality;
    bool criminalRecordFound = false;

public:
    static int Votercount;
    Voter();

    void setName();
    void setAge();
    void setCNIC();
    void setNationality();

    string getName() const;
    int getAge() const;
    string getCNIC() const;
    string getNationality() const;

    bool isValid();
    static int getVotercount();
    static void incrementVotercount();
};

class City : public Voter {
protected:
    string cityName;

public:
    City();
    City(const string& name);

    void display() const;
};

class Area : public City {
protected:
    string areaName;
    string* pollingStations;
    string* candidateNames;
    int numPollingStations;

public:
    Area(const string& name);
    ~Area();

    void saveToFile() const;
    void addPollingStation(const City& city);
    void removePollingStation();
    void display() const;
};

void SetColorAndBackground(int ForgC, int BackC);
bool isValidString(string str);

Candidate CandidateRegistration();
void CandidateReport(Candidate contestant);

void VoterInfo(Voter* persons, int numVoters);
int InputValidation();
int OptionValidation(int limit);

void WriteToFile(string filename, string DataToWrite);
string ReadTheFile(string filename);

void PollingAgent();
void AdminPanel();
void AdminOPt();
void giveVote();
void StartupMessage();
void CandidateRegisteration();
void VoterFunc();

#endif // EMSHEAD_H
