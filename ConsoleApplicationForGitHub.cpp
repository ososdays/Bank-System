#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;
enum enMainMenuOption { eShowClientList = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClient = 4, eFindClient = 5, eExit = 6 };
struct stClient
{
	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string PhoneNumber = "";
	long double AccountBalanced = 0;
	bool MarkForDelete = false;
};
string ClientsFileName = "Clients.txt";
void ShowMainMenu();
short ReadMainMenuChoice()
{
	short Choice = 0;
	cout << "Please enter what do you want to do ? ";
	cin >> Choice;
	return Choice;
}
void GoBackToMainMenu()
{
	cout << "\n\nPress any key to go back to main menu ... ";
	system("pause > 0");
	ShowMainMenu();
}
vector <string> SplitString(string S1, string delimiter)
{
	vector<string>vString;

	short pos = 0;
	string sWord;

	while ((pos = S1.find(delimiter)) != std::string::npos)
	{
		sWord = S1.substr(0, pos);
		if (sWord != "")
		{
			vString.push_back(sWord);
		}
		S1.erase(0, pos + delimiter.length());
	}
	if (S1 != "")
	{
		vString.push_back(S1);
	}
	return vString;
}
stClient ConvertLineDataToRecord(string S1, string Separator)
{
	stClient Client;
	vector<string>vStrings = SplitString(S1, Separator);

	Client.AccountNumber = vStrings.at(0);
	Client.PinCode = vStrings.at(1);
	Client.Name = vStrings[2];
	Client.PhoneNumber = vStrings[3];
	Client.AccountBalanced = stod(vStrings[4]);
	return Client;
}
vector<stClient> LoadClientsDataFromFile(string FileName)
{
	fstream MyFile;
	vector<stClient>vClients;

	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		string stLine = "";
		stClient Client;
		while (getline(MyFile, stLine))
		{
			if (stLine != "")
			{
				Client = ConvertLineDataToRecord(stLine, "#//#");
				vClients.push_back(Client);
			}
		}
		MyFile.close();
	}
	return vClients;
}
void PrintClient(stClient Client)
{
	cout << "\nThe following are client details : \n\n";

	cout << "Enter Account Number ? ";
	cout << Client.AccountNumber << "\n";

	cout << "Enter PinCode ? ";
	cout << Client.PinCode << endl;

	cout << "Enter Name ? ";
	cout << Client.Name << endl;

	cout << "Enter Phone ? ";
	cout << Client.PhoneNumber << endl;

	cout << "Enter Account Balance ? ";
	cout << Client.AccountBalanced << endl;
}
void PrintClientRecordLine(stClient Client)
{
	cout << " | " << left << setw(15) << Client.AccountNumber;
	cout << "| " << left << setw(10) << Client.PinCode;
	cout << "| " << left << setw(40) << Client.Name;
	cout << "| " << left << setw(12) << Client.PhoneNumber;
	cout << "| " << left << setw(12) << Client.AccountBalanced;
	cout << "\n";
}
void ShowAllClientsScreen()
{
	vector<stClient>vClients = LoadClientsDataFromFile(ClientsFileName);
	cout << "\n\t\t\tClient List (" << vClients.size() << ") Clients(s).\n";
	cout << "________________________________________________________________________________________________________________\n";
	cout << " | " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n________________________________________________________________________________________________________________\n\n";

	if (vClients.size() == 0)
	{
		cout << "\t\t\tNo Clients Available In the System \n";
	}
	else
	{
		for (stClient& Client : vClients)
		{
			PrintClientRecordLine(Client);
		}
		cout << "________________________________________________________________________________________________________________\n\n";
	}
}
bool ClientExistByAccountNumber(string AccountNumber, string FileName)
{
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		string stLine;
		stClient Client;
		while (getline(MyFile, stLine))
		{
			Client = ConvertLineDataToRecord(stLine, "#//#");
			if (Client.AccountNumber == AccountNumber)
			{
				MyFile.close();
				return true;
			}
		}
		MyFile.close();
	}
	return false;
}
stClient ReadNewClient()
{
	stClient Client;

	cout << "Enter Account Number ? ";
	getline(cin >> ws, Client.AccountNumber);
	while (ClientExistByAccountNumber(Client.AccountNumber, ClientsFileName))
	{
		cout << "Client with Account Number (" << Client.AccountNumber << ") Already Exist , Enter another Account Number? ";
		getline(cin >> ws, Client.AccountNumber);
	}

	cout << "\nEnter PinCode ? ";
	getline(cin, Client.PinCode);

	cout << "Enter Name ? ";
	getline(cin, Client.Name);

	cout << "Enter Phone ? ";
	getline(cin, Client.PhoneNumber);

	cout << "Enter Account Balance ? ";
	cin >> Client.AccountBalanced;
	return Client;
}
void AddDataLineToFile(string FileName, string stDataLine)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);
	if (MyFile.is_open())
	{
		MyFile << stDataLine << endl;
		MyFile.close();
	}
}
string RecordToLine(stClient RecordData, string Separator = "#//#")
{
	string stClientRecord = "";

	stClientRecord += RecordData.AccountNumber + Separator;
	stClientRecord += RecordData.PinCode + Separator;
	stClientRecord += RecordData.Name + Separator;
	stClientRecord += RecordData.PhoneNumber + Separator;
	stClientRecord += to_string(RecordData.AccountBalanced);
	return stClientRecord;
}
void AddNewClient()
{
	stClient Client;
	Client = ReadNewClient();
	AddDataLineToFile(ClientsFileName, RecordToLine(Client));
}
void AddNewClients()
{
	char AddMore = 'Y';
	do
	{
		cout << "Adding New Client : \n\n";

		AddNewClient();


		cout << "\nClient Added Successfully , Do you want to add more client [Y/N] ? ";
		cin >> AddMore;
	} while (AddMore == 'y' || AddMore == 'Y');
}
void ShowAddNewClientScreen()
{
	cout << "\n------------------------------------- \n";
	cout << "      Add New Client Screen \n";
	cout << "-------------------------------------\n\n";
	AddNewClients();
}
string ReadClientAccountNumber()
{
	string AccountNumber = "";
	cout << "Please enter Account Number ? ";
	cin >> AccountNumber;
	return AccountNumber;
}
bool FindClientByAccountNumber(string AccountNumber, stClient& Client, vector<stClient>& vClients)
{
	for (stClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}
bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<stClient>& vClients)
{

	for (stClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}
void SaveClientDataToFile(string FileName, vector<stClient>& vClients)
{
	fstream MyFile;
	string DataLine = "";
	MyFile.open(FileName, ios::out);
	if (MyFile.is_open())
	{
		for (stClient& C : vClients)
		{
			if (C.MarkForDelete != true)
			{
				DataLine = RecordToLine(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
}
bool DeleteClientFromFile(string AccountNumber, vector<stClient>& vClients)
{
	stClient Client;
	char AreYouSure = 'Y';
	if (FindClientByAccountNumber(AccountNumber, Client, vClients))
	{
		PrintClient(Client);

		cout << "\nAre you sure you want to delete this client [Y/N] ? ";
		cin >> AreYouSure;
		if (AreYouSure == 'y' || AreYouSure == 'Y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveClientDataToFile(ClientsFileName, vClients);

			vClients = LoadClientsDataFromFile(ClientsFileName);

			cout << "\nClient Deleted Successfully .\n";
			return true;
		}
	}
	else
	{
		cout << "\nClient with account number (" << AccountNumber << ") Not Found ! \n\n";
		return false;
	}
}
void ShowDeleteClientScreen()
{
	cout << "\n------------------------------------- \n";
	cout << "      Delete Client Screen \n";
	cout << "-------------------------------------\n\n";

	vector<stClient>vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	DeleteClientFromFile(AccountNumber, vClients);
}
stClient ChangeClientRecord(string AccountNumber)
{
	stClient Client;

	Client.AccountNumber = AccountNumber;

	cout << "\nEnter PinCode ? ";
	getline(cin >> ws, Client.PinCode);

	cout << "Enter Name ? ";
	getline(cin, Client.Name);

	cout << "Enter Phone ? ";
	getline(cin, Client.PhoneNumber);

	cout << "Enter Account Balance ? ";
	cin >> Client.AccountBalanced;
	return Client;


}
bool UpdateClientByAccountNumber(string AccountNumber, vector<stClient>& vClients)
{
	stClient Client;
	char AreYouSure = 'N';

	if (FindClientByAccountNumber(AccountNumber, Client, vClients))
	{
		PrintClient(Client);

		cout << "Are you sure you want to update this client [Y/N] ? ";
		cin >> AreYouSure;
		if (AreYouSure == 'Y' || AreYouSure == 'y')
		{
			for (stClient& C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}
			SaveClientDataToFile(ClientsFileName, vClients);

			cout << "Client Updated Successfully . \n";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
		return false;
	}
}
void ShowUpdateClientScreen()
{
	cout << "\n------------------------------------- \n";
	cout << "      Update Client Screen \n";
	cout << "-------------------------------------\n\n";

	vector<stClient>vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	UpdateClientByAccountNumber(AccountNumber, vClients);

}
void ShowFindClientScreen()
{
	cout << "\n-------------------------------------\n ";
	cout << "       Find Client Screen \n";
	cout << "-------------------------------------\n\n";

	stClient Client;
	vector<stClient>vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	if (FindClientByAccountNumber(AccountNumber, Client, vClients))
	{
		PrintClient(Client);
	}
	else
		cout << "\nClient with Account Number (" << AccountNumber << ") Not Found ! \n";
}
void ShowEndScreen()
{
	cout << "------------------------------\n";
	cout << "       Program Ends  :-) \n";
	cout << "------------------------------\n";

}
void ConfirmMainMenuOption(enMainMenuOption MainMenuOption)
{
	switch (MainMenuOption)
	{
	case enMainMenuOption::eShowClientList:
		system("cls");
		ShowAllClientsScreen();
		GoBackToMainMenu();
		break;
	case enMainMenuOption::eAddNewClient:
		system("cls");
		ShowAddNewClientScreen();
		GoBackToMainMenu();
		break;
	case enMainMenuOption::eDeleteClient:
		system("cls");
		ShowDeleteClientScreen();
		GoBackToMainMenu();
		break;
	case enMainMenuOption::eUpdateClient:
		system("cls");
		ShowUpdateClientScreen();
		GoBackToMainMenu();
		break;
	case enMainMenuOption::eFindClient:
		system("cls");
		ShowFindClientScreen();
		GoBackToMainMenu();
		break;
	case enMainMenuOption::eExit:
		system("cls");
		ShowEndScreen();
		break;
	}
}
void ShowMainMenu()
{
	system("cls");
	cout << "=================================================\n";
	cout << "               Main Menu Screen                  \n";
	cout << "=================================================\n";
	cout << "        [1] Show Client List. \n";
	cout << "        [2] Add New Client. \n";
	cout << "        [3] Delete Client.\n";
	cout << "        [4] Update Client Info. \n";
	cout << "        [5] Find Client. \n";
	cout << "        [6] Exit. \n";
	cout << "=================================================\n";

	ConfirmMainMenuOption(enMainMenuOption(ReadMainMenuChoice()));
}
int main()
{
	ShowMainMenu();





	system("pause > 0");
	return 0;
}