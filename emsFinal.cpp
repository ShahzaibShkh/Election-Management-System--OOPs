#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <cctype>
#include <Windows.h>
#include <unordered_map>


using namespace std;

//Candidate* arr = new Candidate[5];


void SetColorAndBackground(int ForgC, int BackC)
{
	WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
	;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
	return;
}


bool isValidString(string str) {
	for (char ch : str) {
		if (!isalpha(ch)) {
			return false;
		}
	}
	return true;
}
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

int NumberOfCandidatesToRegister = 0;
const int numcan = 10;

class Candidate {

	//properties
	string name;
	int age;
	string partyName;
	CandidateType type;
	Cities city;
	PollingStation station;
	Towns contestingTown;



public:
	int votesGained = 0;
	Candidate() {

	}
	//Constructor
	Candidate(string name, CandidateType type, int age, Cities city, PollingStation Pstat, Towns contestingTown, string partyName) {
		this->name = name;
		this->type = type;
		this->age = age;
		this->partyName = partyName;
		this->city = city;
		this->station = Pstat;
		this->contestingTown = contestingTown;

	}

	int getVotes() {
		return this->votesGained;
	}

	string getCity() {
		return enumToString(this->city);
	}
	string getTown()
	{
		return enumToString(this->contestingTown);
	}
	string  getName()
	{
		return this->name;
	}
	int getAge()
	{
		return this->age;
	}
	string getType()
	{
		return enumToString(this->type);
	}
	string getPartyName()
	{
		return this->partyName;
	}

	Towns getRawTown()
	{
		return this->contestingTown;
	}
};

Candidate candi[numcan];



class Voter {
protected:
	string name;
	int age;
	string cnic;
	string nationality;
	bool criminalRecordFound = false;

public:
	static int Votercount;
	Voter() {
		name = "";
		age = 0;
		cnic = "";
		nationality = "";

	}



	void setName() {
		std::cout << "Enter Your Name: ";
			cin >> name;
		//getline(std::cin, name);
		while (!isValidString(name)) {
			cout << "Enter name Correctly: " << endl;
		//getline(std::cin, name);
			cin >> name;

		}
		
	}

	void setAge() {
		std::cout << "Enter your Age:" << endl;
		std::cout << "Age(must be above 18) : ";
		std::cin >> age;
		if (age < 18 || age> 80) {
			cerr << "Invalid age.\n";
		}
		//std::cin.ignore();
	}

	void setCNIC() {

		std::cout << "Enter CNIC (13 digits): ";
		std::cin >> cnic;

		if (cnic.length() != 13) {
			cerr << "Invalid CNIC. Please enter a 13-digit numeric CNIC.\n";
		}
		else {
			// Check if all characters are digits
			for (char c : cnic) {
				if (!isdigit(c)) {
					cerr << "Invalid CNIC. Please enter a 13-digit numeric CNIC.\n";

					break;
				}
			}
		}

		//		//add criminal record check from file 'CRVoters', it will contain cnic with criminal records
		//	   // ifstream file("CRVoters1");
		//
		//	   // if (file.is_open()) {
		//	   //     string line;
		//	   //     while (getline(file, line)) {
		//	   //         for (int i = 0; i < line.length(); i++)
		//	   //         {
		//
		//	   //             if (cnic[i] == line[i]) {
		//	   //                 if (line[i] == ',') {
		//	   //                     if (line[i + 1] == '1') {
		//	   //                         criminalRecordFound = true;
		//	   //                         cerr << "You have criminal record." << endl;
		//	   //                     }
		//	   //                     else if (line[i + 1] == '0') {
		//	   //                         criminalRecordFound = false;
		//	   //                         std::cout << "No criminal record found." << endl;
		//
		//	   //                     }
		//	   //                 }
		//	   //             }
		//	   //         }
		//	   //         file.close();
		//	   //     }
		//	   // }
		//	   ///* else {
		//	   //     cerr << "Error opening file: CRVoters1\n";
		//	   // }*/
	}

	void setNationality() {
		std::cout << "Nationality (must be Pakistani): ";
		std::cin >> nationality;
		if (!(nationality == "Pakistani" || nationality == "pakistani")) {
			cerr << "Invalid nationality. Program terminated.\n";
		}
	}

	// Getter functions
	string getName() const {
		return name;
	}

	int getAge() const {
		return age;
	}

	string getCNIC() const {
		return cnic;
	}

	string getNationality() const {
		return nationality;
	}

	// Function to check if age and nationality are valid
	bool isValid() {
		return (age >= 18 && (nationality == "Pakistani" || nationality == "pakistani"));

	}
	static int getVotercount() {
		return Votercount;
	}

	// Increment Votercount
	static void incrementVotercount() {
		++Votercount;
	}


};



class City : public Voter {
protected:
	string cityName;

public:
	City() {

	}
	City(const string& name) : cityName(name) {}

	void display() const {
		std::cout << "City: " << cityName << endl;
	}
};

class Area :public City {
protected:
	string areaName;
	string* pollingStations;
	string* candidateNames;
	int numPollingStations;

public:
	Area(const string& name) : areaName(name), pollingStations(nullptr), candidateNames(nullptr), numPollingStations(0) {}
	/* void addPollingStation(const City& city);
	 void removePollingStation(const City& city);*/
	~Area() {
		delete[] pollingStations;
		delete[] candidateNames;
	}
	void saveToFile() const {
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

	void addPollingStation(const City& city) {
		string id;
		std::cout << "Enter Polling Station ID: ";
		std::cin >> id;


		string* newPollingStations = new string[numPollingStations + 1];
		string* newCandidateNames = new string[numPollingStations + 1];


		for (int i = 0; i < numPollingStations; ++i) {
			newPollingStations[i] = pollingStations[i];
			newCandidateNames[i] = candidateNames[i];
		}

		// Add the new polling station and candidate names
		newPollingStations[numPollingStations] = id;
		std::cout << "Enter Candidate Names (comma-separated): ";
		std::cin.ignore();
		getline(std::cin, newCandidateNames[numPollingStations]);


		delete[] pollingStations;
		delete[] candidateNames;
		pollingStations = newPollingStations;
		candidateNames = newCandidateNames;
		++numPollingStations;
		saveToFile();
	}

	void removePollingStation() {
		string id;
		std::cout << "Enter Polling Station ID to remove: ";
		std::cin >> id;

		// Check if the polling station exists
		int index = -1;
		for (int i = 0; i < numPollingStations; ++i) {
			if (pollingStations[i] == id) {
				index = i;
				break;
			}
		}

		if (index != -1) {
			// Create new arrays with one less space
			string* newPollingStations = new string[numPollingStations - 1];
			string* newCandidateNames = new string[numPollingStations - 1];

			// Copy existing polling stations and candidate names to the new arrays (excluding the removed one)
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
	}

	void display() const {
		std::cout << "Area: " << areaName << endl;
		std::cout << "Polling Stations:" << endl;
		for (int i = 0; i < numPollingStations; ++i) {
			std::cout << "ID: " << pollingStations[i] << ", Candidates: " << candidateNames[i] << endl;
		}
	}
};

int Voter::Votercount = 0;

void VoterInfo(Voter* persons, int numVoters) {
	std::cin.ignore();
	for (int i = 0; i < numVoters; ++i) {
		std::cout << "Enter details for person " << i + 1 << ":\n";

		persons[i].setName();
		persons[i].setAge();
		persons[i].setCNIC();
		persons[i].setNationality();
	}
}

int InputValidation()
{
	int choice = 0;
	while (true) {
		// Check if the input is an integer
		while (!(std::cin >> choice)) {
			std::cout << "Invalid input. Please enter a number: ";
			std::cin.clear();  // Clear the error flag
			//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard invalid input
		}
		break;
	}
	return choice;
}

int OptionValidation(int limit)
{
	int choice = 0;
	choice = InputValidation();
	while (choice > limit || choice < 0)
	{
		cout << "Enter the Correct Option: ";
		choice = InputValidation();
	}
	return choice;
}

Candidate CandidateRegistration() {

	//MPA MNA
	int choice = 0;
	cout << "-!- Candidate Registration -!-\n";
	cout << "1. MPA\n";
	cout << "2. MNA\n";
	choice = OptionValidation(2);


	//Assigning Candidate Type
	CandidateType type = choice == 1 ? CandidateType::MPA : CandidateType::MNA;

	cout << "-!- Select City for the Candidate -!-\n";
	cout << "Avaliable Cities :\n";
	cout << 1 << ". " << "Lahore" << endl;
	cout << 2 << ". " << "Faisalabad" << endl;
	choice = OptionValidation(2);


	//Candidate City
	Cities CandidateCity = choice == 1 ? Cities::Lahore : Cities::Faisalabad;

	std::cout << std::endl;

	cout << "-!- Select Town for the Candidate -!-\n";

	CandidateCity == Cities::Lahore ?
		cout << "1. " << "Faisal Town" << "\n" << "2. " << "Model Town\n"
		:
		cout << "1. " << "Jinnah Town" << "\n" << "2. " << "Iqbal Town\n"
		;
	choice = OptionValidation(2);

	//Candidate Town
	Towns candidateTown = CandidateCity == Cities::Lahore ? choice == 1 ? Towns::FaisalTown : Towns::ModelTown : choice == 1 ? Towns::JinnahTown : Towns::IqbalTown;


	//Cnadidate Name
	string candidateName;
	std::cout << "Enter the name of candidate: ";
	std::cin >> candidateName;

	while (!isValidString(candidateName))
	{
		cout << "Enter the name of candidate correctly: ";
		std::cin >> candidateName;
	}
	///assigning Age
	cout << "Enter the Age of the Candidate(above 25): ";
	int candidateAge = InputValidation();
	while (candidateAge < 25)
	{
		cout << "Age should be at least 25 \n";
		cout << "Enter the Age Correctly: ";
		candidateAge = InputValidation();
	}

	//for Party!
	string candidateParty;
	cout << "Enter the name of candidate party: ";
	std::cin >> candidateParty;

	//Party validation
	while (!isValidString(candidateParty))
	{
		cout << "Enter the name of candidate party correctly: ";
		std::cin >> candidateParty;
	}
	//assigning a Polling Stataion
	PollingStation PStation;

	switch (candidateTown)
	{
	case Towns::FaisalTown:
		PStation = PollingStation::FT002;
		break;
	case Towns::ModelTown:
		PStation = PollingStation::MT002;
		break;
	case Towns::JinnahTown:
		PStation = PollingStation::JT001;
		break;
	case Towns::IqbalTown:
		PStation = PollingStation::IT001;
		break;
	default:
		break;
	}

	return Candidate(candidateName, type, candidateAge, CandidateCity, PStation, candidateTown, candidateParty);
}






void CandidateReport(Candidate contestant)
{
	cout << "-- Election Candidate Report -- \n";
	cout << "Name: " << contestant.getName() << endl;
	cout << "Age: " << contestant.getAge() << endl;
	cout << "City: " << contestant.getCity() << endl;
	cout << "Town: " << contestant.getTown() << endl;
	cout << "Type: " << contestant.getType() << endl;
	cout << "Party: " << contestant.getPartyName() << endl;
	
	cout << "Votes: " << contestant.getVotes() << endl;
}



void StartupMessage()
{
	SetColorAndBackground(14, 0);

	cout << "Enter Access Mode: " << endl;
	SetColorAndBackground(14, 0);
	SetColorAndBackground(8, 0);
	cout << "1. Voter." << endl;
	cout << "2. Polling Agent." << endl;
	cout << "3. Candidate Registeration." << endl;
	cout << "4. Admin." << endl;
	cout << "0. To Exit." << endl;
	SetColorAndBackground(8, 0);
}



void WriteToFile(string filename, string DataToWrite)
{
	ofstream WriteFile;
	WriteFile.open(filename, std::ios::out | std::ios::app);
	if (WriteFile.fail())
	{
		cout << "Error Opening the File";
	}
	else {
		WriteFile << DataToWrite;
		WriteFile.close();
	}

}

//Candidate Registeration;
void CandidateRegisteration()
{

	cout << "Enter the Number of candidates to register : ";
	NumberOfCandidatesToRegister = InputValidation();


	 
	for (int i = 0; i < NumberOfCandidatesToRegister; i++)
	{
		Candidate ElectoralCandidates = CandidateRegistration();
		candi[i] = ElectoralCandidates;
		string CandidateDetails =
			"Name: " + ElectoralCandidates.getName() + "\n" +
			"Age: " + std::to_string(ElectoralCandidates.getAge()) + "\n" +
			"City: " + ElectoralCandidates.getCity() + "\n" +
			"Town: " + ElectoralCandidates.getTown() + "\n" +
			"Type: " + ElectoralCandidates.getType() + "\n" +
			"Votes: " + std::to_string(ElectoralCandidates.getVotes()) +
			"\n\n";

		WriteToFile("candidates.txt", CandidateDetails);
	}
}

string ReadTheFile(string filename) {
	string FileText;
	try
	{
		ifstream MyReadFile(filename);
		while (getline(MyReadFile, FileText))
		{
			cout << FileText;
		}
		MyReadFile.close();

	}
	catch (exception e)
	{
		cout << "Error Reading the File";
	}
	return FileText;
}


void PollingAgent() {
	int chp = 0;
	City Lahore("Lahore");
	City Faisalabad("Faisalabad");

	Area MT("Model Town");
	Area FT("Faisal Town");
	Area IT("Iqbal Town");
	Area JT("Jinnah Town");
	cout << endl;
	std::cout << " 1. Add Polling Station\n";
	std::cout << " 2. Remove Polling Station\n";
	std::cout << " 3. Display Polling stations \n";
	cout << " 0. Back." << endl;

	std::cin >> chp;

	if (chp == 1) {
		std::cout << "\nEnter the City to add a Polling Station:\n";
		std::cout << "1. Lahore\n";
		std::cout << "2. Faisalabad\n";
		int cityChoice, areaChoice;
		std::cin >> cityChoice;

		if (cityChoice == 1) {
			std::cout << "   Enter area." << endl;
			std::cout << "   1.Model Town" << endl;
			std::cout << "   2.Faisal Town" << endl;
			std::cin >> areaChoice;
			if (areaChoice == 1) {
				MT.addPollingStation(Lahore);
				MT.saveToFile();
			}
			else if (areaChoice == 2) {
				FT.addPollingStation(Lahore);
				FT.saveToFile();
			}
		}
		else if (cityChoice == 2) {
			std::cout << "   Enter area." << endl;
			std::cout << "   1.Iqbal Town" << endl;
			std::cout << "   2.Jinnah Town" << endl;
			std::cin >> areaChoice;
			if (areaChoice == 1) {
				IT.addPollingStation(Lahore);
				IT.saveToFile();
			}
			else if (areaChoice == 2) {
				JT.addPollingStation(Lahore);
				JT.saveToFile();
			}
		}
		else {
			std::cout << "Invalid City choice.\n";
		}
	}

	else if (chp == 2) {
		std::cout << "\nEnter the City to remove a Polling Station:\n";
		std::cout << "1. Lahore\n";
		std::cout << "2. Faisalabad\n";
		int cityChoice, areaChoice;
		std::cin >> cityChoice;
		if (cityChoice == 1) {
			std::cout << "   Enter area." << endl;
			std::cout << "   1.Model Town" << endl;
			std::cout << "   2.Faisal Town" << endl;
			std::cin >> areaChoice;
			if (areaChoice == 1) {
				MT.removePollingStation();
				MT.saveToFile();
			}
			else if (areaChoice == 2) {
				FT.removePollingStation();
				FT.saveToFile();
			}
		}
		else if (cityChoice == 2) {
			std::cout << "   Enter area." << endl;
			std::cout << "   1.Iqbal Town" << endl;
			std::cout << "   2.Jinnah Town" << endl;
			std::cin >> areaChoice;
			if (areaChoice == 1) {
				IT.removePollingStation();
				IT.saveToFile();
			}
			else if (areaChoice == 2) {
				JT.removePollingStation();
				JT.saveToFile();
			}
		}
		else {
			std::cout << "Invalid City choice.\n";
		}
	}
	else if (chp == 3) {

		MT.display();
		FT.display();

		// Read and display data from the file "pollingstations.txt"
		ifstream inputFile("pollingstations.txt");
		if (inputFile.is_open()) {
			string line;
			std::cout << "\nPolling Stations from File:\n";
			while (getline(inputFile, line)) {
				std::cout << line << endl;
			}
			inputFile.close();
		}
		else {
			cerr << "Unable to open the file 'pollingstations.txt' for reading.\n";
		}

	}
}

void AdminPanel() {

	for (int i = 0; i < NumberOfCandidatesToRegister; i++)
	{
		CandidateReport(candi[i]);
		cout << "\n";
	}

	int maxVotes = 10;
	string name;
	for (int i = 0; i < NumberOfCandidatesToRegister; i++)
	{

		if (candi[i].getVotes() < maxVotes)
		{
			name = candi[i].getName();
			maxVotes = candi[i].getVotes();
		}
	}

	//cout << name;
	cout << "\nMaximum Votes: " << maxVotes;
	cout << "\n";

}

void AdminOPt(){
	int optA;

	cout << "1. Candidate Report." << endl;
	cout << "0. Back." << endl;
	cin >> optA;
	if (optA == 1) {

		AdminPanel();
	}
}

void giveVote() {

	cout << "Enter the Town for Voting: " << endl;

	std::cout << "City: Lahore\n";
	std::cout << "1.Model Town\n";
	std::cout << "2.Faisal Town\n\n";
	std::cout << "City: Faisalabad\n";
	std::cout << "3.Iqbal Town\n";
	std::cout << "4.Jinnah Town\n";
	int option = OptionValidation(4);

	Towns _town = option == 1 ? Towns::ModelTown : option == 2 ? Towns::FaisalTown : option == 3 ? Towns::IqbalTown : Towns::JinnahTown;

	for (int i = 0; i < NumberOfCandidatesToRegister; i++)
	{
		if (candi[i].getRawTown() == _town)
		{
			cout << "-- Election Candidate Info -- \n";
			cout << "Name: " << candi[i].getName() << endl;
			cout << "Town: " << candi[i].getTown() << endl;
			cout << "Type: " << candi[i].getType() << endl;
			cout << "Enter 1 to Vote: \n";
			cout << "Enter 0 For Next Candidate: ";



		}
		option = OptionValidation(2);

		if (option == 1) {
			candi[i].votesGained++;
			cout << "Vote Counted for " << candi[i].getName() << "," << candi[i].getType() << "\n\n";
			//break;
		}
		else {
			/*break;*/
		}
	}
}

	int voter1At = 0;
void VoterFunc()
{
	bool validVoter = false;

	int chv = 0;
	std::cout << "\n";
	SetColorAndBackground(12, 0);

	cout << "--Note: Register voter first before giving vote." << endl << endl;
	SetColorAndBackground(12, 0);
	SetColorAndBackground(8, 0);

	std::cout << "1. Register Voter. " << endl;
	std::cout << "2. Voter Count." << endl;
	std::cout << "3. Vote.\n";
	cout << "0. Back." << endl;

	SetColorAndBackground(8, 0);
	SetColorAndBackground(7, 0);


	std::cin >> chv;
	if (chv == 1) {
		int numVoters = 0;
		std::cout << "Enter the number of persons to register to vote: " << endl;
		std::cin >> numVoters;
		voter1At++;
		Voter* persons = new Voter[numVoters];



		VoterInfo(persons, numVoters);

		ofstream outputFile("voterdata1.txt", ios::app);
		if (outputFile.is_open()) {
			for (int i = 0; i < numVoters; ++i) {
				if (persons[i].isValid()) {
					outputFile << persons[i].getName() << "," << persons[i].getAge() << "," << persons[i].getCNIC() << "," << persons[i].getNationality() << "\n";
					
					Voter::incrementVotercount();
					validVoter = true;
					ofstream countFile("votercount.txt", ios::app);
					if (countFile.is_open()) {
						countFile << Voter::getVotercount() << "\n";
						countFile.close();
						
					}
					else {
						cerr << "Unable to open the file 'votercount.txt' for saving.\n";
					}
				}
			}

			outputFile.close();
			//std::cout << "Voter/s Registered successfully.\n";

		}
		else {
			cerr << "Unable to open the file.\n";
		}

		/*if (validVoter == true) {
			cout << "Voter Eligible to vote:" << endl;
			cout<<endl;
			
		}
		else {
			cout << "Voter Invalid!" << endl;
		}*/

		delete[] persons;
		
	}

	else if (chv == 2) {
		std::cout << "Total Voters:\n ";
		std::cout << Voter::Votercount << endl;
	}
	else if (chv == 3) {

		if (voter1At == 0) {
			cout << endl;
			cout << "Register Voters first!" << endl;
		}
		else if (voter1At > 0) {

		giveVote();
		}		
	}

}

int main() {


	SetColorAndBackground(11, 0);
	cout << endl;
	std::cout << "================/////// Election Management System \\\\\\\\===================" << endl << endl;
	SetColorAndBackground(11, 0);
	SetColorAndBackground(12, 0);
	cout << "Note:" << endl;
	cout << "Register Candidates for Election before giving Vote, you can do this by going to option 3. " << endl << endl;
	SetColorAndBackground(12, 0);
	SetColorAndBackground(13, 0);


	int option = 0;
	while (true)
	{
		StartupMessage();
		option = OptionValidation(4);
		switch (option)
		{
		case 1:
			SetColorAndBackground(5, 0);

			VoterFunc();
			SetColorAndBackground(5, 0);

			break;
		case 2:
			SetColorAndBackground(7, 0);

			PollingAgent();
			SetColorAndBackground(7, 0);

			break;
		case 3:
			SetColorAndBackground(7, 0);

			CandidateRegisteration();
			SetColorAndBackground(7, 0);


			break;
		case 4:
			SetColorAndBackground(11, 0);

			AdminOPt();
			SetColorAndBackground(11, 0);

			break;

		case 0:
			SetColorAndBackground(4, 0);

			cout << "Program Terminated!" << endl;
			SetColorAndBackground(4, 0);

			exit(0);
		default:
			option = OptionValidation(4);
			break;
		}
	}
	return 0;
}

