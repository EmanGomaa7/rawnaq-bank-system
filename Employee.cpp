#include"Employee.h"
#include"Validation.h"
#include"FileManager.h"
#include "FilesHelper.h"
#include"Person.h"

    double Employee::enterSalary(double& salary) {
        bool isValid = false;
        while (!isValid) {
            if (!Validation::validSalary(salary)) {
                cout << "Please try again.\n";
                cout << "Enter your salary : ";
                cin >> salary;
            }
            else isValid = true;
        }
        return salary;
    }

    void Employee::setSalary(double salary) {
        this->salary = enterSalary(salary);
    }
    double Employee::getSalary() {
        return salary;
    }

    void Employee::DisplayInfo()  {
        Person::DisplayInfo();
        cout << "Salary    : " << salary << " EGP\n";
        cout << "==============================\n";
    }

    void Employee::addClient(Client& client) {
        FileManager fm;
        fm.addClient(client);
        cout << "Client added successfully.\n";
    }

    Client* Employee::searchClient(int id) {
        if (id > 0 && id <= FilesHelper::Clients.size()) {
            return &FilesHelper::Clients[id - 1];
        }
        return nullptr;

    }
    void Employee::listClient() { 
        cout << "=========Clients Info=========\n";
        for (int i = 0; i < FilesHelper::Clients.size();i++) {
             FilesHelper::Clients[i].DisplayInfo();
        }

    }
    void Employee::editClient(int id, string name, string password, double balance) {

        FileManager fm;
        FilesHelper::Clients[id - 1].setId(id);
        cin.ignore();
        FilesHelper::Clients[id - 1].setName(name);
        FilesHelper::Clients[id - 1].setPassword(password);
        FilesHelper::Clients[id - 1].setBalance(balance);
        cout << "Client edited successfully.\n";
        fm.updateClient();
    }

