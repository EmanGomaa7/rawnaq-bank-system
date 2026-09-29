#include "Client.h"
#include"Validation.h"


	double Client:: enterBal(double& balance) {
		bool isValid = false;
		while (!isValid) {

			if (!Validation::validBal(balance)) {
				cout << "Please try again \n";
				cout << "Enter your Balance : ";
				cin >> balance;
			}
			else isValid = true;

		}
		return balance;
	}
	//Setter
	void Client::setBalance(double balance) {
		double bal = enterBal(balance);
		this->balance = bal;
	}
	//Getter
	double Client::getBalance() {
		return balance;
	}

	//Methods
	void Client::deposit(double amount) {
		balance += amount;
		cout << "Deposit completed successfully.\n";
		cout << "==============================\n";

	}
	void Client::withdraw(double amount) {
		if (!Validation::validAmount(amount, balance)) {
			cout << "Withdraw completed unsuccessfully.\n";
			cout << "==============================\n";

			return;
		}
		balance -= amount;
		cout << "Withdraw completed successfully.\n";
		cout << "==============================\n";

	}
	void Client::transferTo(double amount, Client& recipient) {
		if (!Validation::validAmount(amount, balance)) {
			cout << "Transfer completed Unsuccessfully.\n";
			cout << "==============================\n";

			return;
		}
		recipient.balance += amount;
		balance -= amount;
		cout << "Transfer completed successfully.\n";
		cout << "==============================\n";

	}
	void Client::checkBalance() {
		cout << "\n\n";
		cout << "==============================\n";
		cout << "BALANCE : " << balance << "\n";

	}
	void Client::DisplayInfo() {
		Person::DisplayInfo();
		cout << "Balance   : " << balance << " EGP\n";
		cout << "==============================\n";

	}


