#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class BankAccount {
private:
    string name;
    int accountNum;
    double balance;

public:
    BankAccount(string n, int ac, double bal) {
        name = n;
        accountNum = ac;
        balance = bal;
    }

    string getName() const {
        return name;
    }

    int getAccountNum() const {
        return accountNum;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        balance += amount;
    }

    bool withdraw(double amount) {
        if (amount > balance) return false;
        balance -= amount;
        return true;
    }

    void display() const {
        cout << setw(15) << accountNum
             << setw(20) << name
             << setw(12) << fixed << setprecision(2) << balance << endl;
    }
};

class BankManagement {
private:
    vector<BankAccount> accounts;

public:
    void addAccount(string name, int accountNum, double balance) {
        accounts.push_back(BankAccount(name, accountNum, balance));
    }

    void showAllAccounts() const {
        if (accounts.empty()) {
            cout << "\t\tNo accounts found.\n";
            return;
        }

        cout << "\n" << setw(15) << "Account No"
             << setw(20) << "Name"
             << setw(12) << "Balance\n";
        cout << "---------------------------------------------------------------\n";

        for (const auto& acc : accounts)
            acc.display();
    }

    BankAccount* searchAccount(int accountNum) {
        for (auto& acc : accounts) {
            if (acc.getAccountNum() == accountNum)
                return &acc;
        }
        return nullptr;
    }
};

int main() {
    BankManagement bank;
    int choice;
    char op;

    do {
        cout << "\n\t\t::Bank Management System::\n";
        cout << "\t\t\tMain Menu\n";
        cout << "\t\t1. Create New Account\n";
        cout << "\t\t2. Show All Accounts\n";
        cout << "\t\t3. Search Account\n";
        cout << "\t\t4. Deposit Money\n";
        cout << "\t\t5. Withdraw Money\n";
        cout << "\t\t6. Exit\n";
        cout << "\t\tEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name;
                int accountNum;
                double balance;

                cout << "\t\tEnter name: ";
                cin >> ws;
                getline(cin, name);

                cout << "\t\tEnter account number: ";
                cin >> accountNum;

                cout << "\t\tEnter initial balance: ";
                cin >> balance;

                bank.addAccount(name, accountNum, balance);
                cout << "\t\tAccount created successfully!\n";
                break;
            }

            case 2:
                bank.showAllAccounts();
                break;

            case 3: {
                int accNum;
                cout << "\t\tEnter account number to search: ";
                cin >> accNum;

                BankAccount* acc = bank.searchAccount(accNum);
                if (acc) {
                    cout << "\t\tAccount found:\n";
                    acc->display();
                } else {
                    cout << "\t\tAccount not found.\n";
                }
                break;
            }

            case 4: {
                int accNum;
                double amount;
                cout << "\t\tEnter account number: ";
                cin >> accNum;

                BankAccount* acc = bank.searchAccount(accNum);
                if (acc) {
                    cout << "\t\tEnter amount to deposit: ";
                    cin >> amount;
                    acc->deposit(amount);
                    cout << "\t\tAmount deposited successfully.\n";
                } else {
                    cout << "\t\tAccount not found.\n";
                }
                break;
            }

            case 5: {
                int accNum;
                double amount;
                cout << "\t\tEnter account number: ";
                cin >> accNum;

                BankAccount* acc = bank.searchAccount(accNum);
                if (acc) {
                    cout << "\t\tEnter amount to withdraw: ";
                    cin >> amount;
                    if (acc->withdraw(amount)) {
                        cout << "\t\tWithdrawal successful.\n";
                    } else {
                        cout << "\t\tInsufficient balance.\n";
                    }
                } else {
                    cout << "\t\tAccount not found.\n";
                }
                break;
            }

            case 6:
                cout << "\t\tThanks for using the Bank Management System!\n";
                break;

            default:
                cout << "\t\tInvalid choice. Try again.\n";
        }

        cout << "\n\t\tDo you want to continue [y/n]? ";
        cin >> op;

    } while (op == 'y' || op == 'Y');

    return 0;
}
