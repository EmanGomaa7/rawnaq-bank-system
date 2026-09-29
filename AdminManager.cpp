#include "AdminManager.h"
#include "EmployeeManager.h"
#include "FilesHelper.h"
#include "FileManager.h"
#include "ClientManger.h"

void AdminManager::printAdminMenu() {
	cout << "================ADMIN MENU===================\n\n";
	cout << "1.Display my info.\n";
	cout << "2.Add new client.\n";
	cout << "3.Search for client.\n";
	cout << "4.List all clients.\n";
	cout << "5.Edit client info.\n";
	cout << "6.Remove all clients data.\n";
	cout << "7.Add new employee.\n";
	cout << "8.Search for employee.\n";
	cout << "9.List all employees.\n";
	cout << "10.Edit employee info.\n";
	cout << "11.Remove all employees data.\n";
	cout << "12.Remove all Admins data.\n";
	cout << "13.Update password.\n";
	cout << "14.Logout.\n\n";
}

void AdminManager::updatePassword(Admin* admin) {
	ClientManger::updatePassword(admin);
	FileManager fm;
	fm.updateAdmin();
}

void AdminManager::newEmployee(Admin* admin) {
	cout << "==============Add new employee==============\n";

	Employee e;
	string name, password;
	double salary;

	cout << "Enter employee name :";
	cin >> ws;
	getline(cin, name);
	e.setName(name);

	cout << "Enter employee password :";
	getline(cin, password);
	e.setPassword(password);

	cout << "Enter employee salary :";
	cin >> salary;
	e.setSalary(salary);

	e.setId(FilesHelper::getLast("lastIdEmployee.txt") + 1);
	admin->addEmployee(e);
}

void AdminManager::searchForEmployee(Admin* admin) {
	cout << "====================Search==================\n";

	int id;
	cout << "Enter employee id :";
	cin >> id;
	Employee* e = admin->searchEmployee(id);
	if (e == nullptr) {
		cout << "No employee found with this ID.\n";
		return;
	}
	e->DisplayInfo();
}

void AdminManager::listAllEmployees(Admin* admin) {
	admin->listEmployee();
}

void AdminManager::editEmployeeInfo(Admin* admin) {
	cout << "==============Edit employee info============\n";

	int id;
	string name, password;
	double salary;

	cout << "Enter employee id :";
	cin >> id;
	Employee* e = admin->searchEmployee(id);
	if (e == nullptr) {

		cout << "No employee found with this ID.\n";
		return;
	}

	cout << "Enter new name :";
	cin >> ws;
	getline(cin, name);
	cout << "Enter new password :";
	getline(cin, password);
	cout << "Enter new salary :";
	cin >> salary;

	admin->editEmployee(id, name, password, salary);
}

Admin* AdminManager::login(int id, string password) {
	for (int i = 0; i < FilesHelper::Admins.size(); i++) {
		if (FilesHelper::Admins[i].getId() == id &&
			FilesHelper::Admins[i].getPassword() == password) {
			cout << "Login Successfully.\n";
			cout << "Welcome ," << FilesHelper::Admins[i].getName() << "\n";
			return &FilesHelper::Admins[i];
		}
	}
	return nullptr;
}

bool AdminManager::AdminOptions(Admin* admin) {
	printAdminMenu();
	cout << "Enter your choice:";
	int choice; cin >> choice;
	switch (choice) {
	case 1:  admin->DisplayInfo(); break;
	case 2:  EmployeeManager::newClient(admin); break;
	case 3:  EmployeeManager::searchForClient(admin); break;
	case 4:  EmployeeManager::listAllClients(admin); break;
	case 5:  EmployeeManager::editClientInfo(admin); break;
	case 6:  {
		cout << "==========Remove all Clients data===========\n";
		cout << "WARNING: This action will permanently delete all clients data.\n";
		cout << "Are you sure you want to continue? (y/n): ";
		char ans; cin >> ans;
		if (ans == 'Y' || ans == 'y') {
			FileManager fm; fm.removeAllClients();
			cout << "All clients data has been removed successfully.\n";
		}
		else {
			cout << "Operation cancelled.\n";
		}
	} break;
	case 7:  newEmployee(admin); break;
	case 8:  searchForEmployee(admin); break;
	case 9:  listAllEmployees(admin); break;
	case 10:  editEmployeeInfo(admin); break;
	case 11: { 
		cout << "=========Remove all Employees data=========\n";
		cout << "WARNING: This action will permanently delete all employees data.\n";
		cout << "Are you sure you want to continue? (y/n): ";
		char ans; cin >> ans;
		if (ans == 'Y' || ans == 'y') {
			FileManager fm; fm.removeAllEmployees(); 
			cout << "All employees data has been removed successfully.\n";
		}
		else {
			cout << "Operation cancelled.\n";
		}
		} break;
	case 12: {
		cout << "=========Remove all Admins data=========\n";
		cout << "WARNING: This action will permanently delete all admins data.\n";
		cout << "Are you sure you want to continue? (y/n): ";
		char ans; cin >> ans;
		if (ans == 'Y' || ans == 'y') {
			FileManager fm; fm.removeAllAdmins();
			cout << "All admins data has been removed successfully.\n";
		}
		else {
			cout << "Operation cancelled.\n";
		}
	}  break;
	case 13: updatePassword(admin); break;
	case 14: return false;
	default:
		cout << "Invalid choice.\n";
		return false;
	}
	return true;
}
