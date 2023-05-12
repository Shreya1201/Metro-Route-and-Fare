#include <bits/stdc++.h>
#include <iostream>
#include <iomanip>
#include <time.h>
#include <conio.h>
#include <cstring>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
using namespace std;

class Node
{
public:
    string name;
    int idx;
    vector<Node *> Neighbours;

    Node(string stationName, int index)
    {
        name = stationName;
        idx = index;
    }
};

const int numberOfStations = 40;
Node *stations[numberOfStations];
vector<string> stationsName = {"SHAHEED STHAL", "HINDON", "ARTHALA", "MOHAN NAGAR", "SHYAM PARK", "MAJOR MOHIT SHARMA", "RAJ BAGH",
                               "SHAHEED NAGAR", "DILSHAD GARDEN", "JHILMIL", "MANSAROVAR PARK", "SHAHDARA", "WELCOME", "SEELAMPUR",
                               "VAISHALI", "KAUSHAMBI", "ANAND VIHAR", "KARKARDUMA", "PREET VIHAR", "NIRMAN VIHAR", "LAXMI NAGAR",
                               "YAMUNA BANK", "INDRAPRASTHA", "AKSHARDHAM", "MAYUR VIHAR-I", "MAYUR VIHAR EXTENSION", "NEW ASHOK NAGAR",
                               "SHIV VIHAR", "JOHRI ENCLAVE", "GOKULPURI", "MAUJPUR", "JAFFRABAD", "EAST AZAD NAGAR", "KRISHNA NAGAR",
                               "KARKARDUMA COURT", "IP EXTENSION", "MANDAWALI", "EAST VINOD NAGAR", "TRILOKPURI", "MAYUR VIHAR POCKET I"};

vector<vector<int>> connections = {{1}, {0, 2}, {1, 3}, {2, 4}, {3, 5}, {4, 6}, {5, 7}, {6, 8}, {7, 9}, {8, 10}, {9, 11}, {10, 12}, {11, 13, 31, 32}, {12}, {15}, {14, 16}, {15, 17, 35}, {16, 18, 34}, {17, 19}, {18, 20}, {19, 21}, {20, 22, 23}, {21}, {21, 24}, {23, 25, 39}, {24, 26}, {25}, {28}, {27, 29}, {28, 30}, {29, 31}, {30, 12}, {12, 33}, {32, 34}, {17, 33}, {16, 36}, {35, 37}, {36, 38}, {37, 39}, {38, 24}};

void buildMap()
{
    for (int i = 0; i < numberOfStations; i++)
    {
        stations[i] = new Node(stationsName[i], i);
    }

    for (int currStation = 0; currStation < numberOfStations; currStation++)
    {
        for (int ngbrs = 0; ngbrs < connections[currStation].size(); ngbrs++)
        {
            stations[currStation]->Neighbours.push_back(stations[connections[currStation][ngbrs]]);
        }
    }
}

void printMap()
{
    for (int i = 0; i < numberOfStations; i++)
    {
        std::cout << stations[i]->name << '\n';
    }
}

void findStationIndex(Node *curr, vector<bool> &visited, int &idx, string station)
{
    if (curr->name == station)
    {
        idx = curr->idx;
    }
    visited[curr->idx] = true;
    int siz = curr->Neighbours.size();
    for (int i = 0; i < siz; i++)
    {
        if (visited[curr->Neighbours[i]->idx] == false)
        {
            findStationIndex(curr->Neighbours[i], visited, idx, station);
        }
    }
}

void findpath(Node *curr, vector<bool> &visited, vector<string> &path, vector<string> &shortestPath, string dest, int &currlen)
{
    path.push_back(curr->name);
    if (curr->name == dest)
    {
        if (currlen > path.size())
        {
            currlen = path.size();
            shortestPath = path;
        }
        path.pop_back();
        return;
    }
    visited[curr->idx] = true;
    int siz = curr->Neighbours.size();
    for (int i = 0; i < siz; i++)
    {
        Node *temp = curr->Neighbours[i];
        if (visited[temp->idx] == false)
        {
            findpath(temp, visited, path, shortestPath, dest, currlen);
        }
    }
    path.pop_back();
    visited[curr->idx] = false;
    return;
}

void printpath(vector<string> &path)
{
    int pathSize = path.size();
    int j = 0;
    int distance = -1;
    int fare = -20;
    std::cout << endl;
    for (int i = 0; i < pathSize; i++)
    {
        fare += 20;
        distance += 1;
        if (j % 5 == 0)
        {
            cout << '\n';
        }
        cout << path[i] << " ";
        if (i != pathSize - 1)
        {
            cout << "==> ";
        }
        j++;
    }
    cout << endl;
    cout << endl
         << "Your Total Fare : " << fare;
    cout << endl;
    cout << endl
         << "Your Total Distance : " << distance << "km";
    cout << endl;
    cout << endl;
    cout << endl;
}

void query(string source, string dest)
{
    int sourceidx = -1, destidx = -1;
    vector<bool> visitedsrc(numberOfStations, false);
    vector<bool> visiteddest(numberOfStations, false);
    findStationIndex(stations[0], visitedsrc, sourceidx, source);
    findStationIndex(stations[0], visiteddest, destidx, dest);
    if (sourceidx == -1 || destidx == -1)
    {
        cout << endl;
        cout << endl;
        cout << "Incorrect Source Station or Destination Station";
        cout << endl;
        cout << endl;
        return;
    }
    Node *sourceStation = stations[sourceidx];
    vector<bool> visitedpath(numberOfStations, false);
    vector<string> path;
    vector<string> shortestPath;
    int currlen = 500;
    findpath(sourceStation, visitedpath, path, shortestPath, dest, currlen);
    cout << "\n\nYour path is as follows: ";
    printpath(shortestPath);
}

void HomeScreen()
{
    int i, j, k = 0;
    for (i = 3; i >= 0; i--)
    {
        cout << "\t\t\t\t\t\t";
        for (j = 3; j > k; j--)
        {
            cout << " ";
        }
        cout << "*";
        for (j = 1; j < (k * 2); j++)
            cout << " ";
        if (i < 3)
            cout << "*";
        cout << "\n";
        k++;
    }
    cout << "\n\t\t\t\t\t     W E L C O M E\n";
    cout << "\t\t\t\t\t\t  T O\n";
    cout << "\t\t\t\t\t M E T R O   G U I D E\n\n";
    for (i = 3; i >= 0; i--)
    {
        cout << "\t\t\t\t\t\t";
        for (j = 3; j > i; j--)
        {
            cout << " ";
        }
        cout << "*";
        for (j = 1; j < (i * 2); j++)
            cout << " ";
        if (i >= 1)
            cout << "*";
        cout << "\n";
    }
    cout << "\n\n";
    time_t now; // Show date and time function
    time(&now);
    cout << " \n\t\t\t\t\t" << ("%s\n", ctime(&now));
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
}

int main()
{
    system("color 9");
    buildMap();
    HomeScreen();

    int choice, ch;
    char char_choice;
    char flag;
    cout << endl;
    cout << endl;
    cout << "\n\t\t\t\t\t START PROGRAM? [Y/N]\n";
    cout << endl;
    cin >> flag;
    if (flag == 'n' || flag == 'N')
    {
        return 0;
    }
    do
    {
        system("cls");
        cout << "#################### MENU ####################" << endl;
        cout << "1. Show Station List." << endl;
        cout << "2. Find your way." << endl;
        cout << "3. Contact Us." << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            system("cls");
            cout << "\t"
                 << "S.No."
                 << "\t"
                 << "Station Name";
            cout << endl;
            for (int i = 0; i < 40; i++)
            {
                cout << "\t" << i << "\t" << stationsName[i];
                cout << endl;
            }
            break;
        case 2:
            system("cls");
            {
                getchar();
                cout << "\nEnter the starting station name: ";
                string start, ends;
                getline(cin, start);
                cout << "\nEnter where you want to get off: ";
                getline(cin, ends);
                transform(start.begin(), start.end(), start.begin(), ::toupper);
                transform(ends.begin(), ends.end(), ends.begin(), ::toupper);
                query(start, ends);
            }
            break;
        case 3:
            system("cls");
            {
                string compla;
                cout << "\n You can contact us regarding any issues on our following handles";
                cout << endl;
                cout << "\n Write us on raayush1101@gmail.com";
                cout << endl;
                cout << "\n THANK YOU!";
                cout << endl;
                cout << "\n For being patient with us";
                cout << endl;
            }
            break;
        default:
            cout << "Wrong input!";
            break;
        }

        cout << "\nWould you rather continue?[Y/N]: ";
        cin >> char_choice;

    } while (char_choice == 'y' || char_choice == 'Y');
    return 0;
}
