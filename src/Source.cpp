// Final Project
// Program to encrypt or decrypt messages using the Vigenere Method
// Tyler Cox, 9 Dec 2022, CIS-7

#include <iostream>
#include <string>
#include <vector>
using namespace std;

string VigenereMethod(string, string, bool);	// The Vigenere Method to en/decrypt messages
// 1st param: plain/ciphertext, 2nd: key, 3rd: true = encrypt, false = decrypt
string WriteKey();	// function to write a valid key

int main() {
	// declaring var
	string message;					// message to en/decrypt
	string key;						// key to use to en/decrypt
	unsigned short choice;			// used for selecting choices
	bool analyzeMode;				// encrypting = true, decrypting = false
	bool keyMode;					// use same key = false, ask for new key = true;
	bool noExitC = true;			// exit condition
	vector<string> messageBox;	// stores each en/decrypted message
	int slot = 0;					// where the program is at in the vector

	// information for user
	cout << "This program will encrypt or decrypt any message inputted with the given key using the Vigenere Method.\n"
		"You will be allowed to continuously input messages to be analyzed, and can select whether or not you\n"
		"would like to repeatedly use the same key or not. Additionally, you may change whether to encrypt or\n"
		"decrypt at the end of analyzing & changing each message.\n\n";

	// input for whether user will be encrypting or decrypting
	cout << "Will you be:\n\t1. encrypting, or \n\t2. decrypting?\n\n";
	while (true) {
		cin >> choice;
		if (choice == 1) {
			analyzeMode = true;
			break;
		}
		if (choice == 2) {
			analyzeMode = false;
			break;
		}
		cout << "Please enter 1 or 2.\n\n";
		cin.clear(); cin.ignore();	// if a non-number was inputted
	}

	// input for whether user will use same key every time or not
	cout << "\nWill you be:\n\t1. using the same key for each message, or\n\t2. using a new key for each message?\n\n";
	while (true) {
		cin >> choice;
		if (choice == 1) {
			keyMode = false;
			break;
		}
		if (choice == 2) {
			keyMode = true;
			break;
		}
		cout << "Please enter 1 or 2.\n\n";
		cin.clear(); cin.ignore();	// if a non-number was inputted
	}

	// begin main process
	cin.ignore();		// clear \n from buffer
	do {
		// if user always wants a new key or if a key has not been entered yet
		if (keyMode || key.empty()) {
			cout << "\nEnter the key for the message:\n\n";
			key = WriteKey();
		}
		// message input
		cout << "\nEnter the message to be ";
		analyzeMode ? cout << "encrypted.\n\n" : cout << "decrypted.\n\n";	// change based on analyze mode
		getline(cin, message);

		// encrypt/decrypt the message
		messageBox.push_back(VigenereMethod(message, key, analyzeMode));
		analyzeMode ? cout << "\nEncrypted " : cout << "\nDecrypted "; cout << "message: " << messageBox.at(slot);
		slot++;

		// debug
		// cout << endl << message << endl << key << endl;

		// loop to display & run further commands
		while (true) {
			int cpc = 5;	// used for choices after 4 since, at this point, there is a command that may not exist for the user's current settings

			// print commands
			cout << "\n\nEnter the number of what you would like to do next:\n" <<
				"\t" << "1. Print all encrypted/decrypted messages created in this session\n" <<
				"\t" << "2. Continue "; analyzeMode ? cout << "encrypting" : cout << "decrypting"; cout << " messages\n" <<
				"\t" << "3. Switch to "; analyzeMode ? cout << "decryption\n" : cout << "encryption\n"; cout <<
				"\t" << "4. "; keyMode ? cout << "Don't change key for every message anymore\n" : cout << "Change key for every message\n";
			if (!keyMode) {
				cout << "\t" << cpc++ << ". Change key\n";
			} cout <<
				"\t" << cpc << ". Close program\n\n";

			cin >> choice;		// input choice

			// case 6 is exit, so change it to that if exit was printed as number 5
			if (keyMode)
				if (choice == 5)
					choice = 6;
				else if (choice == 6)
					choice = 0;			// choice 6 would be nothing in this case

			// analyze choice
			switch (choice) {
				// print everything
				case 1:
					cout << "\nHere are all of the currently encrypted/decrypted messages processed:\n";
					for (int i = 1; i <= messageBox.size(); i++)
						cout << '\t' << i << ". " << messageBox.at(i - 1) << endl;
					cout << endl << "Press any key to continue.";
					system("pause>0");	// pause program
					continue;			// reprint commands
				// en/decrypt some more
				case 2:
					cin.ignore();
					break;
				// switch analyze mode
				case 3:
					analyzeMode = !analyzeMode;
					continue;
				// switch key mode
				case 4:
					keyMode = !keyMode;
					continue;
				// change key
				case 5:
					cout << "\nEnter what you would like to change the key to:\n\n";
					cin.ignore();
					key = WriteKey();
					cout << "\nThe new key has been saved. Press any key to continue.";
					system("pause>0");
					continue;
				// quit
				case 6:
					noExitC = false;
					break;
				// invalid choice
				default:
					cout << "\nPlease enter a number between 1 and " << cpc << ".";
					cin.clear(); cin.ignore();	// if a non-number was inputted
					continue;
			}
			break;
		}
	} while (noExitC);

	// end
	return NULL;
}

string WriteKey() {
	bool invalid = true;
	string key;
	while (invalid) {
		invalid = false;
		// cin.ignore();
		getline(cin, key);
		if (key.length() != 0)
			for (int i = 0; i < key.length(); i++) {
				if (!isalpha(key[i])) {
					cout << "\nEnter a key that only contains alphabetic characters.\n\n";
					invalid = true;
					i = key.length();
					key.clear();
				}
			}
		else {
			cout << "\nThe key must have at least one letter in it.\n\n";
			invalid = true;
		}
	}
	return key;
}

string VigenereMethod(string input, string key, bool mode) {
	// declaring var
	//vector<char> array(input.length());// old way to find translated word
	string trans = input;				// translated word (final product)
	int j = -1;							// for keeping track of where we are in key
	int n;								// holds characters for converted input
	int k;								// holds character for converted key
	bool cpTL;							// if current letter is capital or not

	// processing
	for (int i = 0; i < input.length(); i++) {

		// process key counter
		j++;				// increment key counter
		if (j >= key.length())
			j = 0;			// loop key to beginning if j has gone over key's length

		// check for case & convert characters
		if (input[i] >= 65 && input[i] <= 90) {
			cpTL = true;		// letter is uppercase
			n = input[i] - 65;	// convert to easier to read number
		}
		else if (input[i] >= 97 && input[i] <= 122) {
			cpTL = false;		// letter is lowercase
			n = input[i] - 97;	// convert to easier to read number
		}
		else				// this else statement is why j = -1 at the beginning
			continue;		// skip to next letter; current character is a symbol/number
		k = (toupper(key[j]) - 65);	// don't need to save the key's case

		// calculate new letter (converted)
		if (mode) {	// encrypt
			// array.push_back((n + k) % 26);	// old way
			n = (n + k) % 26;
		}
		else		// decrypt
			n = (n - k + 26) % 26;

		// convert new letter back to normal value
		cpTL ? trans[i] = n + 65 : trans[i] = n + 97;
	}

	return trans;
}
