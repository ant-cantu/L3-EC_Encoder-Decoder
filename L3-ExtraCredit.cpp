//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
//* Program name	:	L3-EC (Encoder/Decoder)                         * 
//*                                                                     * 
//* Written by		:	Anthony Cantu                                   * 
//*                                                                     * 
//* Purpose         :	This applications purpose is to encode or		*
//*						deocode text from an input file using a key		*
//*						provided by the user from the key file. The		*
//*						application will output the encoded or decoded	*
//*						text to the output file specified by the user.  * 
//*                                                                     * 
//* Inputs          :	- User enters input file						*
//*						- User enters key file							*
//*						- User enters output file						*
//*						- User selects E/e to encode or D/d to decode	*
//*                                                                     * 
//* Outputs         :	- Prompts user to enter input file to be		*
//*						  decoded or encoded.							*
//*						- Prompts user to enter key file, used to		*
//*						  decode or encode the input file.				*
//*						- Prompts user to enter output file, used		*
//*						  to store the encoded or decoded file.			*
//*						- Application outputs to file entered by user	*
//*						  the decoded or encoded text.					*
//*                                                                     * 
//* Calls           :	- getInputFile(encryption& data,				*
//*							ifstream& inFile, int& lineCount);			*
//*						- getKeyFile(encryption& data,					*
//*							ifstream& inFile);							*
//*						- getOutputFile(encryption& data,				*
//*							ofstream& outFile);							*
//*						- decodeData(ofstream& outFile,					*
//*							encryption data, int lineCount);			*
//*						- encodeData(ofstream& outFile,					*
//*							encryption data, int lineCount);			*
//*						- searchArray(const encryption data,			*
//*							char searchItem);							*
//*                                                                     * 
//* Structure       : BEGIN                                             * 
//*                        Straight line code no sub-processes          * 
//*                   STOP                                              * 
//*                        End of Program                               * 
//*                                                                     * 
//*---------------------------------------------------------------------* 
//* Collaboration   : The Goonies										*
//*                                                                     * 
//*---------------------------------------------------------------------* 
//* Change Log:                                                         * 
//*                         Revision                                    * 
//*       Date    Changed  Rel Ver Mod Purpose                          * 
//*		10/28/23      acantu 000.000.000 Initial release of program     * 
//*                                                                     * 
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

char q;

struct encryption
{
	string key;
	string line[200];
};

void getInputFile(encryption& data, ifstream& inFile, int& lineCount);
void getKeyFile(encryption& data, ifstream& inFile);
void getOutputFile(encryption& data, ofstream& outFile);
void decodeData(ofstream& outFile, encryption data, int lineCount);
void encodeData(ofstream& outFile, encryption data, int lineCount);
int searchArray(const encryption data, char searchItem);

int main()
{
	ifstream inFile;
	ofstream outFile;
	encryption data;

	char selection;
	int lineCount = 0;
	bool validSelection = false;

	cout << "Anthony Cantu\t" << "L3-ExtraCredit\t" << "L3-ExtraCredit.exe" << endl;

	getInputFile(data, inFile, lineCount);
	getKeyFile(data, inFile);
	getOutputFile(data, outFile);

	do
	{
		cout << endl;
		cout << "Enter \"E\" to Encode the output from the input, or\n"
			<< "enter \"D\" to Decode the input to the output: ";

		cin >> selection;
		switch (selection)
		{
		case 'E':
		case 'e':
			encodeData(outFile, data, lineCount);
			validSelection = true;
			break;
		case 'D':
		case 'd':
			decodeData(outFile, data, lineCount);
			validSelection = true;
			break;
		default:
			cout << "Invalid selection! Please make a valid selection!" << endl;
			validSelection = false;
		}
	} while (!validSelection);

	cout << endl;
	cout << "Press any key to Exit.";
	cin.ignore(2, '\n');
	cin.get(q);
	return 0;
}

void getInputFile(encryption& data, ifstream& inFile, int& lineCount)
{
	string fileSelection;

	cout << "Enter the name of the input file or enter \"~\" to use" << endl
		<< "\"Lab3ExtraCreditPT.txt\": ";

	cin >> fileSelection;
	if (fileSelection == "~")
		fileSelection = "Lab3ExtraCreditPT.txt";
	
	inFile.open(fileSelection);

	if (!inFile.is_open())
	{
		cout << "ERROR: Unable to open file location. Application is terminated." << endl;
		cout << "Prease any key to Exit.";
		cin.ignore(2, '\n');
		cin.get(q);
		exit(1);
	}

	while (getline(inFile, data.line[lineCount]))
		lineCount++;

	inFile.close();

	cout << endl;
}

void getKeyFile(encryption& data, ifstream& inFile)
{
	string fileSelection;

	cout << "Enter the name of the Key file or enter \"~\" to use" << endl
		<< "\"Lab3ExtraCreditKEY.txt\": ";

	cin >> fileSelection;
	if (fileSelection == "~")
		fileSelection = "Lab3ExtraCreditKEY.txt";

	inFile.open(fileSelection);

	if (!inFile.is_open())
	{
		cout << "ERROR: Unable to open file location. Application is terminated." << endl;
		cout << "Prease any key to Exit.";
		cin.ignore(2, '\n');
		cin.get(q);
		exit(1);
	}

	getline(inFile, data.key);

	inFile.close();

	cout << endl;
}

void getOutputFile(encryption& data, ofstream& outFile)
{
	string fileSelection;

	cout << "Enter the name of the output file or enter \"~\" to use" << endl
		<< "\"Lab3ExtraCreditCT.txt\": ";

	cin >> fileSelection;
	if (fileSelection == "~")
		fileSelection = "Lab3ExtraCreditCT.txt";

	outFile.open(fileSelection);

	if (!outFile.is_open())
	{
		cout << "ERROR: Unable to open file location. Application is terminated." << endl;
		cout << "Prease any key to Exit.";
		cin.ignore(2, '\n');
		cin.get(q);
		exit(1);
	}
}

void decodeData(ofstream& outFile, encryption data, int lineCount)
{
	char letter;
	int charCount = 0;

	cout << "Decrypting file." << endl;

	for (int i = 0; i < lineCount; i++)
	{
		for (int x = 0; x < data.line[i].length(); x++)
		{
			letter = data.line[i][x];
			if (isalpha(letter))
			{
				if (searchArray(data, letter) > 25)
					data.line[i][x] = static_cast<char>((searchArray(data, letter) - 26) + 97);
				else if (searchArray(data, letter) <= 25)
					data.line[i][x] = static_cast<char>(searchArray(data, letter) + 65);
			}
		}
		charCount += static_cast<int>(data.line[i].length());
	}	

	cout << "Successfully read and translated " << charCount << " characters.";

	for (int i = 0; i < lineCount; i++)
		outFile << data.line[i] << endl;

	outFile.close();
}

void encodeData(ofstream& outFile, encryption data, int lineCount)
{
	char letter;
	int charCount = 0;

	cout << "Encrypting file." << endl;

	for (int i = 0; i < lineCount; i++)
	{
		for (int x = 0; x < data.line[i].length(); x++)
		{
			letter = data.line[i][x];
			if (isalpha(letter))
			{
				if(isupper(letter))
					data.line[i][x] = data.key[(static_cast<int>(letter) - 65)];
				else
					data.line[i][x] = data.key[(static_cast<int>(letter) + 26) - 97];
			}
		}
		charCount += static_cast<int>(data.line[i].length());
	}

	cout << "Successfully read and translated " << charCount << " characters.";

	for (int i = 0; i < lineCount; i++)
		outFile << data.line[i] << endl;

	outFile.close();
}

int searchArray(const encryption data, char searchItem)
{
	int location = 0;
	bool found = false;

	while (location < data.key.length() && !found)
		if (data.key[location] == searchItem)
			found = true;
		else
			location++;

	if (found)
		return location;
	else
		return -1;
}