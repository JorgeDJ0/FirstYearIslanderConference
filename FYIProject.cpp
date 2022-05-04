#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>
#include "Discipline.h"
using namespace std;

void loadDisciplines(vector<Discipline>&);
void saveDisciplines(vector<Discipline>);
void addDiscipline(vector<Discipline>&);
void editDiscipline(vector<Discipline>&);
void deleteDiscipline(vector<Discipline>&);
void seeDiscipline(vector<Discipline>);
void displayDisciplines(vector<Discipline>);
void analyzeText(vector<Discipline>);
void analyzeFew(vector<Discipline>, vector<string>);
void clearScreen();

int main() 
{
    char option;
    int runs = 0;
    vector<Discipline> vec;

    loadDisciplines(vec);
    
    while (option != '7')
    {    
      if (runs > 0)
          cout << "Not a valid option, try again" << endl << endl;
      
        cout << "Do you want to add a discpline(1), edit a discipline(2), delete a discipline(3), look at the contents of a discpline(4), look at all disciplines(5), analyze a text(6), or quit(7)?: ";
        cin >> option;

        switch (option)
        {
            case '1': addDiscipline(vec);
                break;

            case '2': editDiscipline(vec);
                break;

            case '3': deleteDiscipline(vec);
                break;

            case '4': seeDiscipline(vec);
                break;

            case '5': displayDisciplines(vec);
                break;

            case '6': analyzeText(vec);
                break;

            case '7': return 0;
          
            default :
                break;
        }
      clearScreen();
      runs++;
    }

    saveDisciplines(vec);

    return 0;
}

void clearScreen()
{
  cout << "\33[H\33[2J";
}

void loadDisciplines(vector<Discipline> &vect)
{
    Discipline dTemp;
    ifstream inFileD, inFileK, inFileN;
    string temp;
    int count = 0, discCount, keyCount = 0, iTemp;
    vector<int> num;

    inFileD.open("discipline.txt");
    inFileK.open("keywords.txt");
    inFileN.open("numbers.txt");

    while (inFileD >> temp)
    {
        vect.push_back(dTemp);

        vect[count].setDiscipline(temp);

        count++;
    }

    discCount = count;

    count = 0;

    while (inFileN >> iTemp)
        num.push_back(iTemp);

    count = 0;

    while (inFileK >> temp)
    {
        vect[count].addKeyWord(temp);

        if (++keyCount == num[count])
        {
            keyCount = 0;
            count++;
        }
    }

    inFileD.close();
    inFileN.close();
    inFileK.close();
}

void saveDisciplines(vector<Discipline> vect)
{
    ofstream outFileD, outFileK, outFileN;
    
    outFileD.open("discipline.txt");
    outFileK.open("keywords.txt");
    outFileN.open("numbers.txt");

    for (int i = 0; i < vect.size(); i++)
    {
        outFileD << vect[i].getDiscipline() << " ";

        outFileN << vect[i].getKeyWordsSize() << " ";

        for (int j = 0; j < vect[i].getKeyWordsSize(); j++)
            outFileK << vect[i].getKeyWordByIndex(j) << " ";
    }

    outFileD.close();
    outFileN.close();
    outFileK.close();
}

void addDiscipline(vector<Discipline> &vect)
{
    string temp;
    char opt;
    ifstream inFile;
    Discipline dTemp;
    
    cout << "What is the name of the new discipline?: ";
    cin >> temp;

    dTemp.setDiscipline(temp);

    for (int i = 0; i < vect.size(); i++)
    {
        if (dTemp.getDiscipline() == vect[i].getDiscipline())
        {
            cout << "Discipline already exists\n";
            return;
        }
    }

    cout << "Do you want to enter in key words manually(1) or with a text file(2)?: ";
    cin >> opt;

    switch (opt)
    {
        case '1': cout << "Enter key words with no spaces and enter 00000 to end\n";
            cin >> temp;
            while (temp != "00000")
            {
                for (int i = 0; i < temp.length(); i++)
                {
                    if (!isalnum(temp[i]) && temp[i] != '-')
                        temp.erase(i);
            
                    temp[i] = tolower(temp[i]);
                }
                
                dTemp.addKeyWord(temp);

                cin >> temp;
            }
            vect.push_back(dTemp);
            break;

        case '2': cout << "What is the name of the text file you would like to input with the .txt at the end?: ";
            getline(cin, temp);
            inFile.open(temp);
            while (inFile >> temp)
            {
                for (int i = 0; i < temp.length(); i++)
                {
                    if (!isalnum(temp[i]) && temp[i] != '-')
                        temp.erase(i);
            
                    temp[i] = tolower(temp[i]);
                }
                
                dTemp.addKeyWord(temp);
            }
            vect.push_back(dTemp);
            inFile.close();
            break;

        default: cout << "Not a valid option\n";
            break;
    }
}

void editDiscipline(vector<Discipline> &vect)
{
    string temp;
    char opt;
    int target = -1;

    cout << "What discpline would you like to edit?: ";
    cin >> temp;

    for (int i = 0; i < vect.size(); i++)
    {
        if (temp == vect[i].getDiscipline())
            target = i;
    }

    if (target > -1)
    {
        cout << "Do you want to edit the discipline name(1) or the keywords(2)?: ";
        cin >> opt;
    }
    else
    {
        cout << "Discipline not found\n";
        return;
    }

    switch (opt)
    {
        case '1': cout << "What do you want the new name of the discipline to be?: ";
            cin >> temp;
            vect[target].setDiscipline(temp);
            return;
            break;
        
        case '2': opt = '0'; 
            cout << "Do you want to add(1) or delete a key word(2)?: ";
            cin >> opt;
            break;

        default: cout << "Not a valid option\n";
            break;
    }

    switch (opt)
    {
        case '1': cout << "Add key words without spaces, enter 00000 to end\n";
            cin >> temp;
            while (temp != "00000")
            {
                for (int i = 0; i < temp.length(); i++)
                {
                    if (!isalnum(temp[i]) && temp[i] != '-')
                        temp.erase(i);
            
                    temp[i] = tolower(temp[i]);
                }
                vect[target].addKeyWord(temp);
                cin >> temp;
            }
            break;

        case '2': opt = '0'; cout << "What key word do you want to delete? Enter 00000 to stop: ";
            cin >> temp;
            while (temp != "00000")
            {
                if (vect[target].searchKeyWords(temp))
                    vect[target].deleteKeyWord(temp);
                else
                    cout << "Keyword not found\n";
                
                cout << "What key word do you want to delete? Enter 00000 to stop: ";
                cin >> temp;
            }
            break;
    }
}

void deleteDiscipline(vector<Discipline> &vect)
{
    string temp;
    bool flag = false;
    int num;

    cout << "What discipline do you want to delete?: ";
    cin >> temp;

    for (int i = 0; i < vect.size(); i++)
    {
        if (temp == vect[i].getDiscipline())
        {
            flag = true;
            num = i;
        }
    }

    if (flag)
    {
        vect.erase(vect.begin() + num);
        return;
    }

    cout << "Discipline not found\n";
}

void seeDiscipline(vector<Discipline> vect)
{
    string temp;
    int target = -1;
    
    cout << "What discpline do you want to display?: ";
    cin >> temp;

    for (int i = 0; i < vect.size(); i++)
    {
        if (vect[i].getDiscipline() == temp)
            target = i;
    }

    if (target > -1)
    {
        cout << vect[target].getDiscipline() << endl;
        vect[target].getKeyWords();
        cout << endl;
    }
    else
        cout << "Discipline not found\n";
}

void displayDisciplines(vector<Discipline> vect)
{
    for (int i = 0; i < vect.size(); i++)
        cout << vect[i].getDiscipline() << endl;
}

void analyzeText(vector<Discipline> vect)
{
    char c;
    bool flag = false;
    int num, large = 0;
    vector<int> target, points;
    ifstream inFile;
    string temp;
    vector<string> text;

    cout << "What is the name of the text you want to analyze with the .txt?: ";
    cin >> temp;

    inFile.open(temp);

    if (!inFile.is_open())
    {
        cout << "File not found\n";
        return;
    }

    while (inFile >> temp)
    {
        for (int i = 0; i < temp.length(); i++)
        {
            if (!isalnum(temp[i]) && temp[i] != '-')
                temp.erase(i);
            
            temp[i] = tolower(temp[i]);
        }
        text.push_back(temp);
    }

    inFile.close();

    cout << "Do you want to use all of the disciplines or only a few?(a for all/f for a few): ";
    cin >> c;

    while (tolower(c) != 'a' && tolower(c) != 'f')
    {
        cout << "Not a valid input, try again\nDo you want to use all of the disciplines or only a few?(a/f): ";
        cin >> c;
    }

    if (tolower(c) == 'f')
    {
        analyzeFew(vect, text);
        return;
    }

    for (int i = 0; i < vect.size(); i++)
    {
        points.push_back(0);
        for (int j = 0; j < text.size(); j++)
        {
            if (vect[i].searchKeyWords(text[j]))
                points[i]++;
        }
    }

    target.push_back(0);
    
    for (int i = 1; i < vect.size(); i++)
    {
        
        if (points[i] > points[target[0]])
        {
            target.clear();
            target.push_back(i);
        }
        else if (points[i] == points[target[0]])
            target.push_back(i);
    }

    cout << "The discipline(s) that contain(s) the most jargin to this text happen to be: ";

    for (int i = 0; i < target.size(); i++)
    {
        cout << vect[target[i]].getDiscipline() << " ";
    }

    cout << endl;
}

void analyzeFew(vector<Discipline> vect, vector<string> text)
{
    vector<Discipline> select;
    vector<int> target, points;
    Discipline temp;
    string sTemp;
    bool flag = false;
    int num;

    cout << "What disciplines do you want to analyze the text with? Enter 00000 to end\n";
    cin >> sTemp;

    while (sTemp != "00000")
    {
        for (int i = 0; i < vect.size(); i++)
        {
            if (sTemp == vect[i].getDiscipline())
            {
                flag = true;
                num = i;
            }
        }

        if (flag)
        {
            temp.setDiscipline(sTemp);

            for (int i = 0; i < vect[num].getKeyWordsSize(); i++)
            {
                temp.addKeyWord(vect[num].getKeyWordByIndex(i));
            }

            select.push_back(temp);

            temp.setDiscipline(" ");

            for (int i = 0; i < vect[num].getKeyWordsSize(); i++)
            {
                temp.deleteKeyWord(vect[num].getKeyWordByIndex(i));
            }
        }
        else
            cout << "Discipline not found, try again\n";

        flag = false;

        cin >> sTemp;
    }

    for (int i = 0; i < select.size(); i++)
    {
        points.push_back(0);
        for (int j = 0; j < text.size(); j++)
        {
            if (select[i].searchKeyWords(text[j]))
                points[i]++;
        }
    }

    target.push_back(0);
    
    for (int i = 1; i < select.size(); i++)
    {
        
        if (points[i] > points[target[0]])
        {
            target.clear();
            target.push_back(i);
        }
        else if (points[i] == points[target[0]])
            target.push_back(i);
    }

    cout << "The discipline(s) that contain(s) the most jargin to this text happen to be: ";

    for (int i = 0; i < target.size(); i++)
    {
        cout << select[target[i]].getDiscipline() << " ";
    }

    cout << endl;
}