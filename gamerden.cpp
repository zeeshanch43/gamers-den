#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

// Constants
const int gsize = 20;
const int maxPrice = INT_MAX; 
const int minPrice = INT_MIN;
const int maxBuyers = 20;

// Structs
struct Buyer
{
    string username;
    string password;
    float balance;
};

struct Game
{
    string name;
    float price;
};

struct Component
{
    string name;
    float price;
};

// Global variables
Buyer buyers[maxBuyers];
Game games[gsize];
Component components[gsize];
int currentBuyerCount = 0;
int gameLimit = 0;
int componentLimit = 0;

// Function declarations
void menu();
void menuOption();
void sellerDisplay();
void buyerDisplay();
bool verify(string &user, string &pwd);
void createBuyerAccount();
void removeBuyerAccount();
void addGame();
void listGames();
void removeGame();
void addComponent();
void listComponents();
void removeComponent();
void searchGame(bool &found);
void filterGames();
void buyGame(int buyerIndex);
void buyComponent(int buyerIndex);
bool verifyBuyer(string &user, string &pwd, int &buyerIndex);
void saveData();
void loadData();

// Function definitions
void menu()
{
    cout << "=======================================================================================" << endl;
    cout << "      #####     #    #     # ####### ######   #####     ######  ####### #     #  " << endl;
    cout << "     #     #   # #   ##   ## #       #     # #     #    #     # #       ##    # " << endl;
    cout << "     #        #   #  # # # # #       #     # #          #     # #       # #   # " << endl;
    cout << "     #  #### #     # #  #  # #####   ######   #####     #     # #####   #  #  # " << endl;
    cout << "     #     # ####### #     # #       #   #         #    #     # #       #   # # " << endl;
    cout << "     #     # #     # #     # #       #    #  #     #    #     # #       #    ## " << endl;
    cout << "      #####  #     # #     # ####### #     #  #####     ######  ####### #     # " << endl;
    cout << "=======================================================================================" << endl;
}

void menuOption()
{
    cout << "1.Login as seller" << setw(25) << "2.Login as buyer" << setw(25) << "3.Create buyer account" << setw(20) << "0.Exit" << endl;
    cout << "choose an option:";
}

void sellerDisplay()
{
    menu();
    cout << "1.Add Game" << endl;
    cout << "2.Add a PC Component" << endl;
    cout << "3.Remove a PC component" << endl;
    cout << "4.Remove a Game" << endl;
    cout << "5.List of Games" << endl;
    cout << "6.List of PC component" << endl;
    cout << "7.Remove Buyer Account" << endl;
    cout << "0.Logout" << endl;
}

void buyerDisplay()
{
    menu();
    cout << "1.List of Games" << endl;
    cout << "2.List of PC component" << endl;
    cout << "3.Search game by name" << endl;
    cout << "4.Filter Games" << endl;
    cout << "5.Buy Games" << endl;
    cout << "6.Buy component" << endl;
    cout << "0.Logout" << endl;
}

bool verify(string &user, string &pwd)
{
    cout << "Username:";
    cin >> user;
    cout << "Password:";
    cin >> pwd;
    return (user == "a" && pwd == "z");
}

void createBuyerAccount()
{
    if (currentBuyerCount < maxBuyers)
    {
        cout << "Enter your desired username:";
        cin >> buyers[currentBuyerCount].username;
        cout << "Enter your password:";
        cin >> buyers[currentBuyerCount].password;
        cout << "Enter your initial balance:";
        cin >> buyers[currentBuyerCount].balance;
        currentBuyerCount++;
        cout << "Account created successfully!" << endl;
    }
    else
    {
        cout << "ACCOUNTS FULL" << endl;
    }
}

void removeBuyerAccount()
{
    if (currentBuyerCount == 0)
    {
        cout << "No buyer accounts to remove." << endl;
        return;
    }
    cout << "Buyer Accounts:" << endl;
    cout << setw(5) << "Sr" << "." << setw(25) << "USERNAME" << setw(25) << "BALANCE" << endl;
    cout << "******************************************************" << endl;
    for (int i = 0; i < currentBuyerCount; i++)
    {
        cout << setw(5) << i + 1 << "." << setw(25) << buyers[i].username << setw(25) << buyers[i].balance << "$" << endl;
    }
    cout << "******************************************************" << endl;
    int choice;
    cout << "Enter the number of the buyer account you want to remove:";
    cin >> choice;
    while (!cin || choice < 1 || choice > currentBuyerCount)
    {
        cout << "Wrong input. Enter again:";
        cin.clear();
        cin.ignore(255, '\n');
        cin >> choice;
    }
    for (int i = choice - 1; i < currentBuyerCount - 1; i++)
    {
        buyers[i] = buyers[i + 1];
    }
    currentBuyerCount--;
    cout << "Buyer account removed successfully!" << endl;
}

void addGame()
{
    if (gameLimit < gsize)
    {
        cout << "Enter the game you want to add:";
        cin.ignore();
        getline(cin, games[gameLimit].name);
        cout << "Enter the price of the game:";
        cin >> games[gameLimit].price;
        while (!cin || games[gameLimit].price < minPrice || games[gameLimit].price > maxPrice)
        {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Enter the price again:";
            cin >> games[gameLimit].price;
        }
        gameLimit++;
        cout << "Game added successfully" << endl;
    }
    else
    {
        cout << "Game list is full" << endl;
    }
    cin.ignore(256, '\n');
}

void listGames()
{
    if (gameLimit == 0)
    {
        cout << "No games available" << endl;
    }
    else
    {
        cout << "Available games:" << endl;
        cout << setw(5) << "Sr" << "." << setw(25) << "NAME" << setw(25) << "PRICE" << endl;
        cout << "******************************************************" << endl;
        for (int i = 0; i < gameLimit; i++)
        {
            cout << setw(5) << i + 1 << "." << setw(25) << games[i].name << setw(25) << games[i].price << "$" << endl;
        }
        cout << "******************************************************" << endl;
    }
}

void removeGame()
{
    if (gameLimit == 0)
    {
        cout << "No games to remove" << endl;
    }
    else
    {
        listGames();
        cout << "Enter the game you want to remove:";
        int choice;
        cin >> choice;
        while (!cin || choice < 1 || choice > gameLimit)
        {
            cout << "Invalid choice" << endl;
            cin.clear();
            cin.ignore(255, '\n');
            cout << "Enter again:";
            cin >> choice;
        }
        for (int i = choice - 1; i < gameLimit - 1; i++)
        {
            games[i] = games[i + 1];
        }
        gameLimit--;
        cout << "Game removed successfully!" << endl;
    }
}

void addComponent()
{
    if (componentLimit < gsize)
    {
        cout << "Enter the component you want to add:";
        cin.ignore();
        getline(cin, components[componentLimit].name);
        cout << "Enter the price of the component:";
        cin >> components[componentLimit].price;
        while (!cin || components[componentLimit].price < minPrice || components[componentLimit].price > maxPrice)
        {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Enter the price again:";
            cin >> components[componentLimit].price;
        }
        componentLimit++;
        cout << "Component added successfully" << endl;
    }
    else
    {
        cout << "Component list is full" << endl;
    }
    cin.ignore(256, '\n');
}

void listComponents()
{
    if (componentLimit == 0)
    {
        cout << "No components available" << endl;
    }
    else
    {
        cout << "Available components:" << endl;
        cout << setw(5) << "Sr" << "." << setw(25) << "NAME" << setw(25) << "PRICE" << endl;
        cout << "******************************************************" << endl;
        for (int i = 0; i < componentLimit; i++)
        {
            cout << setw(5) << i + 1 << "." << setw(25) << components[i].name << setw(25) << components[i].price << "$" << endl;
        }
        cout << "******************************************************" << endl;
    }
}

void removeComponent()
{
    if (componentLimit == 0)
    {
        cout << "No components to remove" << endl;
    }
    else
    {
        listComponents();
        cout << "Enter the component you want to remove:";
        int choice;
        cin >> choice;
        while (!cin || choice < 1 || choice > componentLimit)
        {
            cout << "Invalid choice" << endl;
            cin.clear();
            cin.ignore(255, '\n');
            cout << "Enter again:";
            cin >> choice;
        }
        for (int i = choice - 1; i < componentLimit - 1; i++)
        {
            components[i] = components[i + 1];
        }
        componentLimit--;
        cout << "Component removed successfully!" << endl;
    }
}

void searchGame(bool &found)
{
    if (gameLimit == 0)
    {
        cout << "No games available" << endl;
    }
    else
    {
        string search;
        cout << "Enter the game you want to search:";
        cin.ignore();
        getline(cin, search);
        for (int i = 0; i < gameLimit; i++)
        {
            if (games[i].name == search)
            {
                cout << setw(5) << i + 1 << "." << setw(25) << games[i].name << setw(25) << games[i].price << "$" << endl;
                found = true;
            }
        }
    }
    if (!found)
    {
        cout << "No Match" << endl;
    }
}

void filterGames()
{
    if (gameLimit == 0)
    {
        cout << "No games available" << endl;
    }
    else
    {
        float minRange, maxRange;
        cout << "Enter minimum price:";
        cin >> minRange;
        cout << "Enter maximum price:";
        cin >> maxRange;
        while (!cin || minRange < 0 || maxRange < 0 || minRange > maxRange)
        {
            cin.clear();
            cin.ignore(255, '\n');
            cout << "Invalid" << endl;
            cout << "Enter minimum price:";
            cin >> minRange;
            cout << "Enter maximum price:";
            cin >> maxRange;
        }
        bool found = false;
        cout << setw(5) << "Sr" << "." << setw(25) << "NAME" << setw(25) << "PRICE" << endl;
        cout << "******************************************************" << endl;
        for (int i = 0; i < gameLimit; i++)
        {
            if (games[i].price >= minRange && games[i].price <= maxRange)
            {
                cout << setw(5) << i + 1 << "." << setw(25) << games[i].name << setw(25) << games[i].price << "$" << endl;
                found = true;
            }
        }
        if (!found)
        {
            cout << "No games found in this range" << endl;
        }
        cout << "******************************************************" << endl;
    }
}

void buyGame(int buyerIndex)
{
    listGames();
    if (gameLimit == 0)
    {
        cout << "No games available to buy" << endl;
        return;
    }
    cout << "Enter the number of the game you want to buy:";
    int gameChoice;
    cin >> gameChoice;

    while (!cin || gameChoice < 1 || gameChoice > gameLimit)
    {
        cout << "Invalid game choice" << endl;
        cin.clear();
        cin.ignore(255, '\n');
        cout << "Enter again:";
        cin >> gameChoice;
    }
    if (buyers[buyerIndex].balance >= games[gameChoice - 1].price)
    {
        buyers[buyerIndex].balance -= games[gameChoice - 1].price;
        cout << "Game purchased successfully!" << endl;
        cout << "Your new balance: $" << buyers[buyerIndex].balance << endl;
    }
    else
    {
        cout << "Insufficient balance" << endl;
    }
}

void buyComponent(int buyerIndex)
{
    listComponents();
    if (componentLimit == 0)
    {
        cout << "No components available to buy" << endl;
        return;
    }

    cout << "Enter the number of the component you want to buy:";
    int componentChoice;
    cin >> componentChoice;
    while (!cin || componentChoice < 1 || componentChoice > componentLimit)
    {
        cout << "Invalid component choice" << endl;
        cin.clear();
        cin.ignore(255, '\n');
        cout << "Enter again:";
        cin >> componentChoice;
    }

    if (buyers[buyerIndex].balance >= components[componentChoice - 1].price)
    {
        buyers[buyerIndex].balance -= components[componentChoice - 1].price;
        cout << "Component purchased successfully!" << endl;
        cout << "Your new balance: $" << buyers[buyerIndex].balance << endl;
    }
    else
    {
        cout << "Insufficient balance" << endl;
    }
}

bool verifyBuyer(string &user, string &pwd, int &buyerIndex)
{
    cout << "Username:";
    cin >> user;
    cout << "Password:";
    cin >> pwd;
    for (int i = 0; i < currentBuyerCount; i++)
    {
        if (buyers[i].username == user && buyers[i].password == pwd)
        {
            buyerIndex = i;
            cout << "Login successful!" << endl;
            cout << "Your current balance: $" << buyers[i].balance << endl;
            return true;
        }
    }
    cout << "Invalid username or password!" << endl;
    return false;
}

void saveData()
{
    ofstream gameFile("games.txt"), componentFile("components.txt"), buyerFile("buyers.txt");

    if (gameFile.is_open())
    {
        for (int i = 0; i < gameLimit; i++)
        {
            gameFile << games[i].name << endl
                     << games[i].price << endl;
        }
        gameFile.close();
    }

    if (componentFile.is_open())
    {
        for (int i = 0; i < componentLimit; i++)
        {
            componentFile << components[i].name << endl
                          << components[i].price << endl;
        }
        componentFile.close();
    }

    if (buyerFile.is_open())
    {
        for (int i = 0; i < currentBuyerCount; i++)
        {
            buyerFile << buyers[i].username << endl
                      << buyers[i].password << endl
                      << buyers[i].balance << endl;
        }
        buyerFile.close();
    }
}

void loadData()
{
    ifstream gameFile("games.txt"), componentFile("components.txt"), buyerFile("buyers.txt");
    if (gameFile.is_open())
    {
        while (getline(gameFile, games[gameLimit].name) && gameFile >> games[gameLimit].price)
        {
            gameLimit++;
            gameFile.ignore();
        }
        gameFile.close();
    }

    if (componentFile.is_open())
    {
        while (getline(componentFile, components[componentLimit].name) && componentFile >> components[componentLimit].price)
        {
            componentLimit++;
            componentFile.ignore();
        }
        componentFile.close();
    }

    if (buyerFile.is_open())
    {
        while (currentBuyerCount < maxBuyers && getline(buyerFile, buyers[currentBuyerCount].username) &&
               getline(buyerFile, buyers[currentBuyerCount].password) && buyerFile >> buyers[currentBuyerCount].balance)
        {
            currentBuyerCount++;
            buyerFile.ignore();
        }
        buyerFile.close();
    }
}

// main
int main()
{
    int input = -1, seller = -1, buyer = -1, buyerIndex;
    string user, pwd;
    bool found = false;

    // Load data at the start
    loadData();

    do
    {
        menu();
        menuOption();
        cin >> input;
        while (!cin || input < 0 || input > 3)
        {
            cout << "Invalid choice" << endl;
            cin.clear();
            cin.ignore(255, '\n');
            menu();
            menuOption();
            cin >> input;
        }
        if (input == 1)
        {
            if (verify(user, pwd))
            {
                do
                {
                    sellerDisplay();
                    cout << "Choose an option:";
                    cin >> seller;
                    while (!cin || seller < 0 || seller > 7)
                    {
                        cout << "Invalid choice" << endl;
                        cin.clear();
                        cin.ignore(255, '\n');
                        sellerDisplay();
                        cin >> seller;
                    }

                    switch (seller)
                    {
                    case 1:
                        addGame();
                        break;
                    case 2:
                        addComponent();
                        break;
                    case 3:
                        removeComponent();
                        break;
                    case 4:
                        removeGame();
                        break;
                    case 5:
                        listGames();
                        break;
                    case 6:
                        listComponents();
                        break;
                    case 7:
                        removeBuyerAccount();
                        break;
                    case 0:
                        break;
                    default:
                        cout << "Invalid Choice" << endl;
                    }
                } while (seller != 0);
            }
        }
        else if (input == 2)
        {
            if (verifyBuyer(user, pwd, buyerIndex))
            {
                do
                {
                    buyerDisplay();
                    cout << "Choose an option:";
                    cin >> buyer;
                    while (!cin || buyer < 0 || buyer > 6)
                    {
                        cout << "Invalid choice" << endl;
                        cin.clear();
                        cin.ignore(255, '\n');
                        buyerDisplay();
                        cin >> buyer;
                    }
                    switch (buyer)
                    {
                    case 1:
                        listGames();
                        break;
                    case 2:
                        listComponents();
                        break;
                    case 3:
                        searchGame(found);
                        break;
                    case 4:
                        filterGames();
                        break;
                    case 5:
                        buyGame(buyerIndex);
                        break;
                    case 6:
                        buyComponent(buyerIndex);
                        break;
                    case 0:
                        cout << "Logged out" << endl;
                        break;
                    default:
                        cout << "Invalid choice" << endl;
                    }
                } while (buyer != 0);
            }
        }
        else if (input == 0)
        {
            saveData();
            cout << "THANKS FOR USING THE SYSTEM :)" << endl;
        }
        else if (input == 3)
        {
            createBuyerAccount();
        }
    } while (input != 0);

    return 0;
}