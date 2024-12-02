#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

// Gloabal variables
const int gsize = 20;
const int maxPrice = INT_MAX;
const int minPrice = INT_MIN;
const int maxBuyers = 20;
string buyerUsernames[maxBuyers];
string buyerPasswords[maxBuyers];
float buyerBalances[maxBuyers];
int currentBuyerCount = 0;

// MenuDisplay
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
// menuOption
void menuOption()
{
    cout << "1.Login as seller" << setw(25) << "2.Login as buyer" << setw(25) << "3.Create buyer account" << setw(20) << "0.Exit" << endl;
    cout << "choose an option:";
}
// sellerOption
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
// buyerOption
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
// check seller name and password
bool verify(string &user, string &pwd)
{
    cout << "Username:";
    cin >> user;
    cout << "Password:";
    cin >> pwd;
    if (user == "a" && pwd == "z")
    {
        return true;
    }
    else
    {
        cout << "YOU ARE NOT THE ONE!" << endl;
        return false;
    }
}
// creating account
void createBuyerAccount(string buyerUsernames[], string buyerPasswords[], float buyerBalances[], int &currentBuyerCount)
{
    if (currentBuyerCount < maxBuyers)
    {
        string username, password;
        float balance;
        cout << "Enter your desired username:";
        cin >> username;
        cout << "Enter your password:";
        cin >> password;
        cout << "Enter your initial balance:";
        cin >> balance;
        cin.ignore(256, '\n');
        cin.clear();
        buyerUsernames[currentBuyerCount] = username;
        buyerPasswords[currentBuyerCount] = password;
        buyerBalances[currentBuyerCount] = balance;
        currentBuyerCount++;
        cout << "Account created successfully!" << endl;
    }
    else
    {
        cout << "ACCOUNTS FULL" << endl;
    }
}
// remove account
void removeBuyerAccount(string buyerUsernames[], string buyerPasswords[], float buyerBalances[], int &currentBuyerCount)
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
        cout << setw(5) << i + 1 << "." << setw(25) << buyerUsernames[i] << setw(25) << buyerBalances[i] << "$" << endl;
    }
    cout << "******************************************************" << endl;
    int choice;
    cout << "Enter the number of the buyer account you want to remove:";
    cin >> choice;
    while (!cin || choice < 1 || choice > currentBuyerCount)
    {
        cout << "Wrong input.Enter again:";
        cin.clear();
        cin.ignore(255, '\n');
        cin >> choice;
    }
    for (int i = choice - 1; i < currentBuyerCount - 1; i++)
    {
        buyerUsernames[i] = buyerUsernames[i + 1];
        buyerPasswords[i] = buyerPasswords[i + 1];
        buyerBalances[i] = buyerBalances[i + 1];
    }
    currentBuyerCount--;
    cout << "Buyer account removed successfully!" << endl;
}
// add game
void addGame(string games[], float gamePrices[], int &gameLimit, const int minPrice, const int maxPrice)
{
    if (gameLimit < gsize)
    {
        cout << "Enter the game you want to add:";
        cin.ignore();
        getline(cin, games[gameLimit]);
        cout << "Enter the price of the game:";
        cin >> gamePrices[gameLimit];
        while (!cin || gamePrices[gameLimit] < minPrice || gamePrices[gameLimit] > maxPrice)
        {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Enter the price again:";
            cin >> gamePrices[gameLimit];
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
// list game
void listGames(string games[], float gamePrices[], int gameLimit)
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
            cout << setw(5) << i + 1 << "." << setw(25) << games[i] << setw(25) << gamePrices[i] << "$" << endl;
        }
        cout << "******************************************************" << endl;
    }
}
// remove game
void removeGame(string games[], float gamePrices[], int &gameLimit)
{
    if (gameLimit == 0)
    {
        cout << "No games to remove" << endl;
    }
    else
    {
        listGames(games, gamePrices, gameLimit);
        cout << "Enter the gmae your want to remove:";
        int choice;
        cin >> choice;
        while (!cin || choice < 1 || choice > gameLimit)
        {
            cout << endl
                 << "Invalid choice" << endl;
            cin.clear();
            cin.ignore(255, '\n');
            cout << "Enter again:";
            cin >> choice;
        }
        for (int i = choice - 1; i < gameLimit - 1; i++)
        {
            games[i] = games[i + 1];
            gamePrices[i] = gamePrices[i + 1];
        }
        cout << "Game removed successfully!" << endl;
        gameLimit--;
    }
}
// add component
void addComponent(string component[], float componentPrices[], int &componentLimit, const int gsize, const int minPrice, const int maxPrice)
{
    if (componentLimit < gsize)
    {
        cout << "Enter the component you want to add:";
        cin.ignore();
        getline(cin, component[componentLimit]);
        cout << "Enter the price of the component:";
        cin >> componentPrices[componentLimit];
        while (!cin || componentPrices[componentLimit] < minPrice || componentPrices[componentLimit] > maxPrice)
        {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Enter the price again:";
            cin >> componentPrices[componentLimit];
        }
        componentLimit++;
        cout << "Component added successfully" << endl;
    }
    else
    {
        cout << "Game list is full" << endl;
    }
    cin.ignore(256, '\n');
}
// listcomponent
void listcomponent(string component[], float componentPrices[], int componentLimit)
{
    if (componentLimit == 0)
    {
        cout << "No component available" << endl;
    }
    else
    {
        cout << "Available component:" << endl;
        cout << setw(5) << "Sr" << "." << setw(25) << "NAME" << setw(25) << "PRICE" << endl;
        cout << "******************************************************" << endl;
        for (int i = 0; i < componentLimit; i++)
        {
            cout << setw(5) << i + 1 << "." << setw(25) << component[i] << setw(25) << componentPrices[i] << "$" << endl;
        }
        cout << "******************************************************" << endl;
    }
}
// remove component
void removeComponent(string component[], float componentPrices[], int &componentLimit)
{
    if (componentLimit == 0)
    {
        cout << "No component to remove" << endl;
    }
    else
    {
        listcomponent(component, componentPrices, componentLimit);
        cout << "Enter the component your want to remove:";
        int choice;
        cin >> choice;
        while (!cin || choice < 1 || choice > componentLimit)
        {
            cout << endl
                 << "Invalid choice" << endl;
            cin.clear();
            cin.ignore(255, '\n');
            cout << "Enter again:";
            cin >> choice;
        }
        for (int i = choice - 1; i < componentLimit - 1; i++)
        {
            component[i] = component[i + 1];
            componentPrices[i] = componentPrices[i + 1];
        }
        cout << "Component removed successfully!" << endl;
        componentLimit--;
    }
}
// search game
void searchgame(string games[], float gamePrices[], int &gameLimit, bool &found)
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
            if (games[i] == search)
            {
                cout << setw(5) << i + 1 << "." << setw(25) << games[i] << setw(25) << gamePrices[i] << "$" << endl;
                found = true;
            }
        }
    }
    if (!found)
    {
        cout << "No Match" << endl;
    }
}
// filter the games
void filterGames(string games[], float gamePrices[], int gameLimit)
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
            if (gamePrices[i] >= minRange && gamePrices[i] <= maxRange)
            {
                cout << setw(5) << i + 1 << "." << setw(25) << games[i] << setw(25) << gamePrices[i] << "$" << endl;
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
// buy game
void buyGame(string games[], float gamePrices[], int &gameLimit, int buyerIndex, float buyerBalances[])
{
    listGames(games, gamePrices, gameLimit);
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
    if (buyerBalances[buyerIndex] >= gamePrices[gameChoice - 1])
    {
        buyerBalances[buyerIndex] -= gamePrices[gameChoice - 1];
        cout << "Game purchased successfully!" << endl;
        cout << "Your new balance: $" << buyerBalances[buyerIndex] << endl;
    }
    else
    {
        cout << "Insufficient balance" << endl;
    }
}
// buy component
void buyComponent(string component[], float componentPrices[], int &componentLimit, int buyerIndex, float buyerBalances[])
{
    listcomponent(component, componentPrices, componentLimit);
    if (componentLimit == 0)
    {
        cout << "No component available to buy" << endl;
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

    if (buyerBalances[buyerIndex] >= componentPrices[componentChoice - 1])
    {
        buyerBalances[buyerIndex] -= componentPrices[componentChoice - 1];
        cout << "Component purchased successfully!" << endl;
        cout << "Your new balance: $" << buyerBalances[buyerIndex] << endl;
    }
    else
    {
        cout << "Insufficient Balance" << endl;
    }
}
// verify
bool verifyBuyer(string &user, string &pwd, string buyerUsernames[], string buyerPasswords[], int currentBuyerCount, int &buyerIndex)
{
    cout << "Username:";
    cin >> user;
    cout << "Password:";
    cin >> pwd;
    for (int i = 0; i < currentBuyerCount; i++)
    {
        if (buyerUsernames[i] == user && buyerPasswords[i] == pwd)
        {
            buyerIndex = i;
            cout << "Login successful!" << endl;
            cout << "Your current balance: $" << buyerBalances[i] << endl;
            return true;
        }
    }
    cout << "Invalid username or password!" << endl;
    return false;
}

void saveData(string games[], float gamePrices[], int gameLimit, string component[], float componentPrices[], int componentLimit)
{
    ofstream gameFile("games.txt");
    ofstream componentFile("component.txt");

    if (gameFile.is_open() && componentFile.is_open())
    {
        for (int i = 0; i < gameLimit; i++)
        {
            gameFile << games[i] << endl;
            gameFile << gamePrices[i] << endl;
        }

        for (int i = 0; i < componentLimit; i++)
        {
            componentFile << component[i] << endl;
            componentFile << componentPrices[i] << endl;
        }

        gameFile.close();
        componentFile.close();
    }
    else
    {
        cout << "Unable to open files" << endl;
    }
}
void loadData(string games[], float gamePrices[], int &gameLimit, string component[], float componentPrices[], int &componentLimit)
{
    ifstream gameFile("games.txt"), componentFile("component.txt");
    if (gameFile.is_open())
    {
        while (gameFile >> ws && getline(gameFile, games[gameLimit]) && gameFile >> gamePrices[gameLimit])
        {
            gameLimit++;
        }
        gameFile.close();
    }

    if (componentFile.is_open())
    {
        while (componentFile >> ws && getline(componentFile, component[componentLimit]) && componentFile >> componentPrices[componentLimit])
        {
            componentLimit++;
        }
        componentFile.close();
    }
}

void saveData(string games[], float gamePrices[], int gameLimit, string component[], float componentPrices[], int componentLimit, string buyerUsernames[], string buyerPasswords[], float buyerBalances[], int currentBuyerCount)
{
    ofstream gameFile("games.txt"), componentFile("component.txt"), buyerFile("buyers.txt");

    if (gameFile.is_open())
    {
        for (int i = 0; i < gameLimit; i++)
        {
            gameFile << games[i] << endl
                     << gamePrices[i] << endl;
        }
        gameFile.close();
    }

    if (componentFile.is_open())
    {
        for (int i = 0; i < componentLimit; i++)
        {
            componentFile << component[i] << endl
                          << componentPrices[i] << endl;
        }
        componentFile.close();
    }

    if (buyerFile.is_open())
    {
        for (int i = 0; i < currentBuyerCount; i++)
        {
            buyerFile << buyerUsernames[i] << endl
                      << buyerPasswords[i] << endl
                      << buyerBalances[i] << endl;
        }
        buyerFile.close();
    }
}

// main
int main()
{

    string games[gsize], component[gsize];
    float gamePrices[gsize], componentPrices[gsize];
    int gameLimit = 0, componentLimit = 0;
    int input = -1, seller = -1, buyer = -1, buy, option, buyerIndex;
    string user, pwd, choice;
    bool found = false, isSeller = false, isBuyer = false;

    // Load data at the start
    loadData(games, gamePrices, gameLimit, component, componentPrices, componentLimit);

    do
    {
        menu();
        menuOption();
        cin >> input;
        while (!cin || input < 0 || input > 3)
        {
            cout << endl
                 << "Invalid choice" << endl;

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
                    cout << "choose an option:";
                    cin >> seller;
                    while (!cin || seller < 0 || seller > 7)
                    {
                        cout << endl
                             << "Invalid choice" << endl;
                        cin.clear();
                        cin.ignore(255, '\n');
                        sellerDisplay();
                        cin >> seller;
                    }

                    switch (seller)
                    {
                    case 1:
                        addGame(games, gamePrices, gameLimit, minPrice, maxPrice);
                        break;

                    case 2:
                        addComponent(component, componentPrices, componentLimit, gsize, minPrice, maxPrice);
                        break;

                    case 3:
                        removeComponent(component, componentPrices, componentLimit);
                        break;

                    case 4:
                        removeGame(games, gamePrices, gameLimit);
                        break;

                    case 5:
                        listGames(games, gamePrices, gameLimit);
                        break;

                    case 6:
                        listcomponent(component, componentPrices, componentLimit);
                        break;

                    case 7:
                        removeBuyerAccount(buyerUsernames, buyerPasswords, buyerBalances, currentBuyerCount);
                        break;

                    case 0:

                    default:
                        cout << "Invalid Choice" << endl;
                    }
                } while (seller != 0);
            }
        }
        else if (input == 2)
        {
            isBuyer = verifyBuyer(user, pwd, buyerUsernames, buyerPasswords, currentBuyerCount, buyerIndex);
            if (isBuyer)
            {
                do
                {
                    buyerDisplay();
                    cout << "Choose an option:";
                    cin >> buyer;
                    while (!cin || buyer < 0 || buyer > 6)
                    {
                        cout << endl
                             << "Invalid choice" << endl;
                        cin.clear();
                        cin.ignore(255, '\n');
                        buyerDisplay();
                        cin >> buyer;
                    }
                    switch (buyer)
                    {
                    case 1:
                        listGames(games, gamePrices, gameLimit);
                        break;

                    case 2:
                        listcomponent(component, componentPrices, componentLimit);
                        break;

                    case 3:
                        searchgame(games, gamePrices, gameLimit, found);
                        break;

                    case 4:
                        filterGames(games, gamePrices, gameLimit);
                        break;

                    case 5:
                        buyGame(games, gamePrices, gameLimit, buyerIndex, buyerBalances);
                        break;

                    case 6:
                        buyComponent(component, componentPrices, componentLimit, buyerIndex, buyerBalances);
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
            saveData(games, gamePrices, gameLimit, component, componentPrices, componentLimit, buyerUsernames, buyerPasswords, buyerBalances, currentBuyerCount);

            cout << "THANKS FOR USING THE SYSTEM :)" << endl;
        }
        else if (input == 3)
        {
            createBuyerAccount(buyerUsernames, buyerPasswords, buyerBalances, currentBuyerCount);
        }

    } while (input != 0);

    return 0;
}
