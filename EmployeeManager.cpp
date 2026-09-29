#include "EmployeeManager.h"
#include "FilesHelper.h"
#include "FileManager.h"
#include "ClientManger.h"

void EmployeeManager::printEmployeeMenu() {
	cout << "===============EMPLOYEE MENU=================\n\n";
	cout << "1.Display my info.\n";
	cout << "2.Add new client.\n";
	cout << "3.Search for client.\n";
	cout << "4.List all clients.\n";
	cout << "5.Edit client info.\n";
	cout << "6.Update password.\n";
	cout << "7.Logout.\n\n";
}

void EmployeeManager::updatePassword(Employee* employee) {
	ClientManger::updatePassword(employee);
	FileManager fm;
	fm.updateEmployee();
}

void EmployeeManager::newClient(Employee* employee) {
	cout << "===============Add new client===============\n";

	Client c;
	string name, password;
	double balance;

	cout << "Enter client name :";
	cin >> ws;
	getline(cin, name);
	c.setName(name);

	cout << "Enter client password :";
	getline(cin, password);
	c.setPassword(password);

	cout << "Enter client balance :";
	cin >> balance;
	c.setBalance(balance);

	c.setId(FilesHelper::getLast("lastIdClient.txt") + 1);
	employee->addClient(c);
}

void EmployeeManager::listAllClients(Employee* employee) {
	employee->listClient();
}

void EmployeeManager::searchForClient(Employee* employee) {
	cout << "===================Search===================\n";

	int id;
	cout << "Enter client id :";
	cin >> id;
	Client* c = employee->searchClient(id);
	if (c == nullptr) {
		cout << "No client found with this ID.\n";
		return;
	}
	c->DisplayInfo();
}

void EmployeeManager::editClientInfo(Employee* employee) {
	cout << "==============Edit client info===============\n";

	int id;
	string name, password;
	double balance;

	cout << "Enter client id :";
	cin >> id;
	Client* c = employee->searchClient(id);
	if (c == nullptr) {
		cout << "No client found with this ID.\n";
		return;
	}

	cout << "Enter new name     :";
	cin >> ws;
	getline(cin, name);
	cout << "Enter new password :";
	getline(cin, password);
	cout << "Enter new balance  :";
	cin >> balance;

	employee->editClient(id, name, password, balance);
}

Employee* EmployeeManager::login(int id, string password) {
	for (int i = 0; i < FilesHelper::Employees.size(); i++) {
		if (FilesHelper::Employees[i].getId() == id &&
			FilesHelper::Employees[i].getPassword() == password) {
			cout << "Login Successfully.\n";
			cout << "Welcome ," << FilesHelper::Employees[i].getName() << "\n";
			return &FilesHelper::Employees[i];
		}
	}
	return nullptr;
}

bool EmployeeManager::employeeOptions(Employee* employee) {
	printEmployeeMenu();
	cout << "Enter your choice:";
	int choice; cin >> choice;
	switch (choice) {
	case 1: employee->DisplayInfo(); break;
	case 2: newClient(employee); break;
	case 3: searchForClient(employee); break;
	case 4: listAllClients(employee); break;
	case 5: editClientInfo(employee); break;
	case 6: updatePassword(employee); break;
	case 7: return false;
	default:
		cout << "Invalid choice.\n";
		return false;
	}
	return true;
}
