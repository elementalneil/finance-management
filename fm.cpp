#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include <time.h>
#include <windows.h> //For the output formatting commands

using namespace std;

class finances{
	int savingsBalance, walletBalance;
	void updateBalance(){		//Updates values of savingsBalance and walletBalance from the file
		fstream fileSavings;
		fileSavings.open("files/savings.txt", ios::in);
		fileSavings >> savingsBalance;
		fileSavings.close();
		fstream fileWallet;
		fileWallet.open("files/wallet.txt", ios::in);
		fileWallet >> walletBalance;
		fileWallet.close();
	}
	void updateFiles(){			//Updates files savings and wallet with current values from the program
		ofstream fileSavings;
		fileSavings.open("files/savings.txt", ios::trunc);
		fileSavings << savingsBalance;
		fileSavings.close();
		ofstream fileWallet;
		fileWallet.open("files/wallet.txt", ios::trunc);
		fileWallet << walletBalance;
		fileWallet.close();
	}
	void logToTemp(){
		string str1;
		fstream file1;
		fstream file2;
		file1.open("files/logs.txt", ios::in);
		file2.open("files/temp.txt", ios::out);
		while(!file1.eof()){
			getline(file1,str1);
			file2 << str1 << endl;
		}
		file1.close();
		file2.close();
	}
	void tempToLog(){
		string str1;
		fstream file1;
		fstream file2;
		file1.open("files/temp.txt", ios::in);
		file2.open("files/logs.txt", ios::app);
		while(!file1.eof()){
			getline(file1,str1);
			file2 << str1 << endl;
		}
		file1.close();
		file2.close();
	}
	void updateLog(int serial, int amount){
		if(amount==0){
			return;
		}
		string reason;
		logToTemp();
		ofstream log;
		log.open("files/logs.txt", ios::out);
		time_t currentTime;
		time(&currentTime);
		log << ctime(&currentTime);
		switch(serial){
			case 1: log << "Rs. " << amount << " added to wallet." << endl; break;
			case 2: log << "Rs. " << amount << " spent from wallet." << endl; break;
			case 3: log << "Rs. " << amount << " added to wallet from savings." << endl; break;
			case 4: log << "Rs. " << amount << " added to savings from wallet." << endl; break;
			case 5: log << "Rs. " << amount << " added to savings." << endl; break;
			case 6: log << "Rs. " << amount << " spent from savings." << endl; break;
		}
		cout << "\nPlease enter some details about the transaction:\n";
		cin.ignore();
		getline(cin, reason);
		log << reason << endl;
		updateBalance();
		log << "Balance after transaction: Rs " << walletBalance << " in wallet and Rs " << savingsBalance << " in savings" << endl << endl;
		log.close();
		tempToLog();
	}
public:
	void addToWallet(){			//Adds money to the wallet
		int amount;
		char choice;
		updateBalance();
		label2:
		cout << "\nPlease enter the amount you want to add: ";
		cin >> amount;
		cout << "\nPress Y to confirm amount, press N to enter again: ";
		choice=getch();
		if(choice=='y'||choice=='Y'){
			walletBalance=walletBalance+amount;
		}
		else{
			goto label2;
		}
		updateFiles();
		updateLog(1, amount);
		cout << "Amounts Updated...";
	}
	void spendFromWallet(){		//Subtracts money from the wallet
		int amount;
		char choice;
		updateBalance();
		cout << "\nPlease enter the amount you spent: ";
		cin >> amount;
		walletBalance=walletBalance-amount;
		updateFiles();
		updateLog(2, amount);
		cout << "Amounts Updated...";
	}
	void moveToWallet(){		//Moves money to the wallet from savings
		int amount;
		char choice;
		updateBalance();
		cout << "\nPlease enter the amount you want to add: ";
		cin >> amount;
		walletBalance=walletBalance+amount;
		savingsBalance=savingsBalance-amount;
		updateFiles();
		updateLog(3, amount);
		cout << "Amounts Updated...";
	}
	void moveToSavings(){		//Moves money to savings from the wallet
		int amount;
		char choice;
		updateBalance();
		cout << "\nPlease enter the amount you want to add: ";
		cin >> amount;
		walletBalance=walletBalance-amount;
		savingsBalance=savingsBalance+amount;
		updateFiles();
		updateLog(4, amount);
		cout << "Amounts Updated...";
	}
	void addToSavings(){		//Adds money to the savings
		int amount;
		char choice;
		updateBalance();
		label3:
		cout << "\nPlease enter the amount you want to add: ";
		cin >> amount;
		cout << "\nPress Y to confirm amount, press N to enter again: ";
		choice=getch();
		if(choice=='y'||choice=='Y'){
			savingsBalance=savingsBalance+amount;
		}
		else{
			goto label3;
		}
		updateFiles();
		updateLog(5, amount);
		cout << "Amounts Updated...";
	}
	void spendFromSavings(){	//Subtracts money from savings
		int amount;
		char choice;
		updateBalance();
		label4:
		cout << "\nPlease enter the amount you want to spend: ";
		cin >> amount;
		cout << "\nPress Y to confirm amount, press N to enter again: ";
		choice=getch();
		if(choice=='y'||choice=='Y'){
			savingsBalance=savingsBalance-amount;
		}
		else{
			goto label4;
		}
		updateFiles();
		updateLog(6, amount);
		cout << "Amounts Updated...";
	}
	void viewBalance(){
		updateBalance();
		cout << "Your wallet balance is: Rs " << walletBalance << endl;
		cout << "Your savings balance is: Rs " << savingsBalance;
	}
	void clearFiles(){
		system("cls");
		string password;
		cout << "Please enter the password to clear files: ";
		cin >> password;
		if(password=="fI9L3#goA8"){
			fstream file1;
			file1.open("files/logs.txt", ios::out|ios::trunc);
			file1.close();
			file1.open("files/savings.txt", ios::out|ios::trunc);
			file1.close();
			file1.open("files/temp.txt", ios::out|ios::trunc);
			file1.close();
			file1.open("files/wallet.txt", ios::out|ios::trunc);
			file1.close();
			cout << "Files cleared!!!";
		}
		else{
			cout << "Wrong Password!!! Press any key to exit...";
			getch();
			exit(0);
		}
	}
};
int main(){
	system("color 70");
	CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;
    cfi.dwFontSize.Y = 19;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    std::wcscpy(cfi.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	//The above lines set the formatting of the output, and have no bearing on the logic of the actual program.
	
	finances f1;
	char option, choice, choice2;
	label1:
	cout << "Finance Management\n\n\n";
	cout << "Options: ";
	cout << "\n\t1. Add Money Directly to Wallet";
	cout << "\n\t2. Spend Money from Wallet";
	cout << "\n\t3. Move Money from Savings to Wallet ";
	cout << "\n\t4. Move Money from Wallet to Savings";
	cout << "\n\t5. Add Money to Savings";
	cout << "\n\t6. Spend Money Directly from Savings";
	cout << "\n\t7. View Current Balance";
	cout << "\n\t8. Exit Program";
	
	cout << "\n\nPlease enter an option: ";
	option=getch();
	
	system("cls");
	switch(option){
		
		case '1': f1.addToWallet(); break;
		case '2': while(1){
					f1.spendFromWallet();
					cout << "\nDo you want to enter more?(Y/N): ";
					choice = getch();
					if(choice=='y'||choice=='Y'){
						continue;
					}
					else{
						break;
					}
				}	
				break;
		case '3': f1.moveToWallet(); break;
		case '4': f1.moveToSavings(); break;
		case '5': f1.addToSavings(); break;
		case '6': f1.spendFromSavings(); break;
		case '7': f1.viewBalance(); break;
		case '8': exit(0);
		case '`': f1.clearFiles(); break;
		default:cout << "Wrong Input! Please try again."; 
				cout << "\n\nPress any key to continue...";
				getch();
				system("cls");
				goto label1;
	}
	cout << "\n\nPress any key to exit program or press M to return to main menu... ";
	choice2=getch();
	if(choice2=='M'||choice2=='m'){
		system("cls");
		goto label1;
	}
	return 0;
}
