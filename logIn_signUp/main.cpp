#include<iostream>
#include<cstdlib>
#include<string>
#include<fstream>
#include<map>
#include<limits>
using namespace std;

#define print(x) cout<<x<<endl
#define horizontalLine "========================================================="
#define userFile "username.data"
#define passFile "password.data"

void welcome();
void signUp();
void logIn();
void mainProgram();

void getLoginInfo(map<string, string> &m);
void openCrashWindows();
void initForTheFirstTime();
void clear_istream();

bool verifyPassword(string password);
void registerAccount(string username, string password);

string currentAccount = "";

int main(){
    initForTheFirstTime();
    welcome();
    mainProgram();
    return 0;
}


void welcome(){
    tryAgain:
    system("cls");
    print(horizontalLine);
    print("Welcome to myUserName program!");
    print("Press 1 to register");
    print("Press 2 to log in");
    print("Press 0 to exit");
    cout<<"Your choice: "; int choice; cin>>choice; clear_istream(); 
    switch (choice)
    {
    case 1:
        signUp();
        goto tryAgain;
        break;
    case 2:
        logIn();
        break;
    case 0:
        exit(0);
    default:
        goto tryAgain;
    }
}

bool verifyPassword(string password){
    if (password.size() <= 8) return false;
    if (password.find(' ') == string::npos) return true;
    return false;
}

void initForTheFirstTime(){
    ofstream username(userFile,ios::app);
    ofstream password(passFile,ios::app);
    username.close();
    password.close();
}

void getLoginInfo(map<string, string> &m){
    ifstream username(userFile, ifstream::binary);
    if (username.fail()) openCrashWindows();
    ifstream password(passFile, ifstream::binary);
    if (password.fail()) openCrashWindows();

    while(!username.eof()){
        string __username, __password;
        username>>__username; password>>__password;
        m[__username] = __password;
    }
    username.close();
    password.close();
}

void registerAccount(string username, string password){
    ofstream usernameFile(userFile, ofstream::binary | ofstream::app);
    ofstream passwordFile(passFile, ofstream::binary | ofstream::app);
    if (usernameFile.fail()) openCrashWindows();
    if (passwordFile.fail()) openCrashWindows();

    usernameFile<<username;
    usernameFile<<endl;
    passwordFile<<password;
    passwordFile<<endl;
    
    usernameFile.close();
    passwordFile.close();
}

void openCrashWindows(){
    system("cls");
    print("Oops, something's wrong. Please try again later");
    system("pause");
    exit(-1);
}

void signUp(){
    map<string, string> mp;         //data structure that consists users' informations
    getLoginInfo(mp);
    string username, password, confirmPassword;

    system("cls");
    print("By creating an account, you will have lots of benefits");
    print("First, type your username, or type \"exit\" to return to welcome screen ");
    print(horizontalLine);

    //Get username
    while(true){
        cout<<"Username: ";getline(cin,username);
        if (username == "exit") return;
        if (mp.find(username) == mp.end()) break;
        print("Username has already existed");
    }

    //Get password
    print("Type your password. Password cannot include space, must have more than 8 letters.");
    print("Or type \"exit\" to return to welcome screen");
    while(true){
        cout<<"Password: ";getline(cin,password);
        if (password == "exit") return;
        if (verifyPassword(password)) break;
        print("Wrong password");
    }

    //Confirm password
    print("Confirm password");
    print("Or type \"exit\" to return to welcome screen");
    while(true){
        cout<<"Confirm password: ";getline(cin,confirmPassword);
        if (password == "exit") return;
        if (password == confirmPassword) break;
        print("Wrong password. Try again");
    }
    registerAccount(username, password);
}

void logIn(){
    map<string, string> mp;     //data
    getLoginInfo(mp);
    string username, password;

    print("Please type your username and password, or \"exit\" to return to welcome menu: ");
    print(horizontalLine);
    
    //Get username
    while(true){
        cout<<"Username: ";getline(cin,username);
        if (username == "exit"){
            welcome();
            return; 
        } 
        if (mp.find(username) != mp.end()) break;
        cout<<endl;
        print("Wrong username");
    }

    //Get password
    while(true){
        cout<<"Password: ";getline(cin,password);
        if (password == "exit") {
            welcome();
            return;
        }
        if (mp[username] == password) break;
        print("Wrong password");
    }

    currentAccount = username;
}

void clear_istream(){
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
}

void mainProgram(){
    print("Welcome back, "<<currentAccount);
    print("Sorry, our program is under maintenance, please come back later :<");
    system("pause");
}