#include "emsHead.h"
#include<Windows.h>

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