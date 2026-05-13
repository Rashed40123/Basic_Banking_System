#include <bits/stdc++.h>
#include <conio.h>
#include <cstdlib>
#include <unistd.h>
#include <windows.h>
using namespace std;
//Functions
void SetColor(int textColor, int bgColor);
void welcome_message();
void login_menu();
void main_menu();
void profile_menu();
void registration_menu();
void check_balance(long double balance);
void save_user_information(string username, string password, long double balance);
void save_user_balance(string username, long double balance);
void delete_account(string username);
void log_transaction(const string& username, const string& type, long double amount);
void delete_log_transaction(string username);
void view_transaction_history(const string& username);
void account_information(string username);
void change_password(string username, string password);
string get_username();
string get_password();
long double get_balance(string username);
int withdraw(long double &balance);
int deposit(long double &balance);
//Global Variables
string current_username;
string current_userpassword;
long double balance = 0;

int main() {
    SetColor(15, 0);
    welcome_message();
    main_menu();
    return 0;
}

void SetColor(int textColor, int bgColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}

void welcome_message() {
    cout << "\t\t\t\t --------------------------------------------------------" << endl;
    cout << "\t\t\t\t\t\t\tPseudo Bank!" << endl;
    cout << "\t\t\t\t --------------------------------------------------------" << endl;
    cout << endl;
}

void login_menu() {
    cout << "\t\t\t\t\t\t\t Log In Menu" << endl << endl;
    string username = get_username();
    current_username = username;
    cout << "Enter Password: ";
    string password = get_password();
    ifstream file("user_information.txt");
    string file_username, file_password;
    long double file_balance;
    bool user_found = false;
    while (file >> file_username >> file_password >> file_balance) {
        if (file_username == username && file_password == password) {
            balance = file_balance;
            user_found = true;
            break;
        }
    }
    if (user_found) {
        system("cls");
        cout << "Login successful!" << endl << endl;
        current_userpassword=password;
        sleep(1);
        system("cls");
    cout << "Welcome, " << current_username << "!" << endl;
        profile_menu();
    } else {
        system("cls");
        SetColor(15, 4);
        cout << "Invalid ID or Password. Please try again." << endl << endl;
        SetColor(15, 0);
    }
}

void main_menu() {
    int option;
    while (true) {
    cout << "\t\t\t\t\t\t Main Menu" << endl << endl;
        cout << "1. Log into your account." << endl;
        cout << "2. Register account." << endl;
        cout << "3. Exit." << endl << endl;
        cout << "Choose an option: ";
        cin >> option;
        system("cls");
        if (option == 1) {
            login_menu();
        } else if (option == 2) {
            registration_menu();
        } else if (option == 3) {
            cout << "Program Exited Successfully! GOOD BYE!!" << endl << endl;
            exit(0);
        } else {
            cout << "Please choose a valid option!";
            sleep(1);
            system("cls");
        }
    }
}

void profile_menu()
{
    int option;
    while (true) {
    cout << "\t\t\t\t\t\t Profile Menu" << endl << endl;
        cout << "1. Account Information." << endl;
        cout << "2. Check Balance." << endl;
        cout << "3. Withdraw Money." << endl;
        cout << "4. Deposit Money." << endl;
        cout << "5. View Transaction History." << endl;
        cout << "6. Change Your Password "<<endl;
        cout << "7. Delete Account." << endl;
        cout << "8. Log Out." << endl << endl;

        cout << "Choose an option: ";
        cin >> option;
        system("cls");
        if(option == 1)
        account_information(current_username);
        else if (option == 2)
        {
            check_balance(balance);
        }
         else if (option == 3)
        {
            withdraw(balance);
        }
        else if (option == 4)
        {
            deposit(balance);
        }
         else if (option == 5)
        {
            view_transaction_history(current_username);
        }
        else if(option == 6)
        {
            system("cls");
            string old_password;
            cout<<"Enter old Password: ";
            old_password=get_password();
            change_password(current_username,old_password);
        }
        else if (option == 7)
        {
            string old_password;
            SetColor(15, 4);
            cout << "Are you sure? (y/n):";
            SetColor(15, 0);
            char a;
            cin>>a;
            if(a=='y' || a=='Y')
            {
            cout<<"Enter Your Password: ";
            old_password=get_password();
              if (old_password==current_userpassword)
              {
                system("cls");
                delete_log_transaction(current_username);
                delete_account(current_username);
              }
              else
              {
                system("cls");
        SetColor(15, 4);
        cout << "Invalid Password. Please try again." << endl << endl;
        SetColor(15, 0);
        system("pause");
        system("cls");
        continue;
              }
            }
            else
            {
                SetColor(15, 2);
                cout << endl << "Account Deletion Cancelled!";
                SetColor(15, 0);
                sleep(2);
                system("cls");
            }
        } else if (option == 8) {
            cout << "Logging Out..";
            sleep(2);
            system("cls");
            main();
        } else {
            cout << "Please choose a valid Option!";
            sleep(1);
            system("cls");
        }
    }
}

void registration_menu() {
    cout << "\t\t\t\t\t\t\tRegistration Menu" << endl << endl;
    string username = get_username();
    current_username = username;
    cout << "Enter Password: ";
    string password = get_password();
    ifstream file("user_information.txt");
    string file_username;
    while (file >> file_username) {
        if (file_username == username) {
            system("cls");
            SetColor(15, 4);
            cout << endl << endl << "Username already exists! Please choose a different Username." << endl << endl;
            SetColor(15, 0);
            return;
        }
    }
    save_user_information(username, password, 0.00);
    SetColor(15, 1);
    cout << endl << "Your account has been created successfully!" << endl;
    SetColor(15, 0);
    cout << "Please wait..";
    sleep(2);
    system("cls");
    main_menu();
}

void check_balance(long double balance) {
    SetColor(15, 2);
    cout << "Your current balance is: BDT " << fixed << setprecision(2) << balance << endl << endl;
    SetColor(15, 0);
}

void save_user_information(string username, string password, long double balance) {
    ofstream file("user_information.txt", ios::app);
    file << username << "\t" << password << "\t" << fixed << setprecision(2) << balance << endl;
}
void save_user_balance(string username, long double balance) {
    ifstream infile("user_information.txt");
    stringstream updated_data;
    string file_username, file_password;
    long double file_balance;
    while (infile >> file_username >> file_password >> file_balance) {
        if (file_username == username)
            updated_data << file_username << "\t" << file_password << "\t" << fixed << setprecision(2) << balance << endl;
        else
            updated_data << file_username << "\t" << file_password << "\t" << file_balance << endl;
    }
    infile.close();
    ofstream outfile("user_information.txt", ios::trunc);
    outfile << updated_data.str();
    outfile.close();
}
void delete_account(string username)
{
    ifstream infile("user_information.txt");
    stringstream updated_data;
    string file_username, file_password;
    long double file_balance;
    while (infile >> file_username >> file_password >> file_balance) {
        if (file_username == username) continue;
        updated_data << file_username << "\t" << file_password << "\t" << file_balance << endl;
    }
    infile.close();
    ofstream outfile("user_information.txt", ios::trunc);
    outfile << updated_data.str();
    outfile.close();
    SetColor(15, 4);
    cout << endl << "Your Account Has Been Deleted Successfully!" << endl << endl;
    SetColor(15, 0);
    system("pause");
    system("cls");
    main();
}
void log_transaction(const string& username, const string& type, long double amount)
{
    ofstream file("transaction_history.txt", ios::app);
    time_t now = chrono::system_clock::to_time_t(chrono::system_clock::now());
    tm* local_time = localtime(&now);
    ostringstream time_stream;
    time_stream << put_time(local_time, "%d-%m-%Y %H:%M:%S");
    file << username << "\t" << type << "\t" << fixed << setprecision(2) << amount << "\t" << time_stream.str() << endl;
    file.close();
}
void delete_log_transaction(string username) {
    ifstream infile("transaction_history.txt");
    stringstream updated_data;
    string file_username, file_type, file_timestamp;
    long double file_amount;
    bool transaction_found = false;
    while (infile >> file_username >> file_type >> file_amount) {
        getline(infile, file_timestamp);
        if (file_username == username) {
            transaction_found = true;
            continue;
        }
        updated_data << file_username << "\t" << file_type << "\t"  << fixed << setprecision(2) << file_amount << "\t" << file_timestamp << endl;
    }
    infile.close();
    ofstream outfile("transaction_history.txt", ios::trunc);
    outfile << updated_data.str();
    outfile.close();
    if (transaction_found) {
        system("cls");
        SetColor(15, 4);
        cout << "Your Transactions History has been removed." << endl;
        SetColor(15, 0);
    } else {
        SetColor(15, 4);
        cout << "Your Transactions History has been removed." << endl;
        SetColor(15, 40);
    }
}

void view_transaction_history(const string& username)
{
    ifstream file("transaction_history.txt");
    string file_username, type, timestamp;
    long double amount;
    cout << "\tTransaction History "<< endl;
    cout << "----------------------------------------------------------" << endl;
    cout << left << setw(15) << "Activity" << setw(15) << "Amount" << setw(20) << "Date and Time" << endl;
    cout << "----------------------------------------------------------" << endl;
    bool history_found = false;
    while (file >> file_username >> type >> amount >> ws) {
        getline(file, timestamp);
        if (file_username == username) {
            cout << left << setw(15) << type << setw(15) << fixed << setprecision(2) << amount << setw(20) << timestamp << endl;
            history_found = true;
        }
    }
    if (!history_found)
    {
    SetColor(15, 4);
     cout << "No transaction history found for this account." << endl;
    SetColor(15, 0);
    }
    cout << "----------------------------------------------------------" << endl;
    cout<<endl;
    system("pause");
    system("cls");
    profile_menu();
}
void account_information(string username)
{
    ifstream file("user_information.txt");
    string file_username,file_password;
    long double file_balance;
    bool history_found = false;
    while (file >> file_username >> file_password >> file_balance ) {
        if (file_username == username) {
            cout <<left<< "Account Name: "<< file_username << "\nAccount Balance: "<< fixed << setprecision(2)<< file_balance<<"BDT" <<endl;
        }
    }
    cout<<endl;
    system("pause");
    system("cls");
}
void change_password(string username, string old_password)
{
    string current_password, new_password, confirm_password;
    bool is_password_changed = false;
    ifstream infile("user_information.txt");
    stringstream updated_data;
    string file_username, file_password;
    long double file_balance;
    while (infile >> file_username >> file_password >> file_balance) {
        if (file_username == username) {
            if (file_password == old_password)
            {
                is_password_changed = true;
                while (true) {
                    cout << "Enter new password: ";
                    new_password = get_password();
                    cout << "Confirm new password: ";
                    confirm_password = get_password();

                    if (new_password != confirm_password)
                    {
                        SetColor(15, 4);
                        cout << "Passwords do not match. Please try again.\n";
                        SetColor(15, 0);
                        continue;
                    }
                    file_password = new_password;
                    current_userpassword = new_password;
                    SetColor(15, 1);
                    cout << "Your password has been changed successfully!\n";
                    SetColor(15, 0);
                    break;
                }
            } else {
                SetColor(15, 4);
                cout << "Old password is incorrect. Password change failed.\n";
                SetColor(15, 0);
            }
        }
        updated_data << file_username << "\t" << file_password << "\t"
                     << fixed << setprecision(2) << file_balance << endl;
    }
    infile.close();
    ofstream outfile("user_information.txt", ios::trunc);
    outfile << updated_data.str();
    outfile.close();
    system("pause");
    system("cls");
}
string get_username()
{
    string name;
    cout << "Enter Username: ";
    cin >> name;
    return name;
}
string get_password()
{
    string pass;
    char ch;
    while ((ch = getch()) != 13)
    {
        if (ch == 8)
        {
            if (pass.length() > 0)
            {
                pass.pop_back();
                cout << "\b \b";
            }
        }
        else
        {
            pass.push_back(ch);
            cout << '*';
        }
    }
    cout << endl;
    return pass;
}
int withdraw(long double &balance) {
    long double amount;
    cout << "Enter amount to Withdraw: BDT ";
    cin >> amount;
    if (amount <= balance) {
        balance -= amount;
        save_user_balance(current_username, balance);
        log_transaction(current_username, "Withdrew", amount);
        SetColor(15, 1);
        cout << "You have successfully withdrawn BDT " << amount << endl << endl;
        SetColor(15, 0);
    }
    else
    {
        SetColor(15, 4);
        cout << "Insufficient Balance!" << endl << endl;
        SetColor(15, 0);
    }
    return 0;
}
int deposit(long double &balance)
{
    long double amount;
    cout << "Enter amount to Deposit: BDT ";
    cin >> amount;
    system("cls");
    balance += amount;
    save_user_balance(current_username, balance);
    log_transaction(current_username, "Deposited", amount);
    SetColor(15, 2);
    cout << "You have successfully Deposited BDT " << amount << endl << endl;
    SetColor(15, 0);
    return 0;
}
//credit us + stackoverflow,youtube,chatgpt,internet
