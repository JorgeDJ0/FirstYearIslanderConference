#include <iostream>
#include <string>
#include <vector>
#include "Discipline.h"
using namespace std;

void Discipline::getKeyWords() const
{
    for (int i = 0; i < keyWords.size(); i++)
        cout << keyWords[i] << " ";
}

bool Discipline::searchKeyWords(string s)
{
    for (int i = 0; i < keyWords.size(); i++)
    {
        if (s == keyWords[i] || (keyWords[i].find(s) != string::npos && s.size() > 3) || (s.find(keyWords[i]) != string::npos && keyWords[i].size() > 3))
            return true;
    }

    return false;
}

int Discipline::returnKeyWordIndex(string s)
{
    for (int i = 0; i < keyWords.size(); i++)
    {
        if (keyWords[i] == s)
            return i;
    }

    return -1;
}

void Discipline::deleteKeyWord(string s)
{
    for (int i = 0; i < keyWords.size(); i++)
    {
        if (keyWords[i] == s)
            keyWords.erase(keyWords.begin() + i);
    }
}

string Discipline::getKeyWordByIndex(int num)
{
    return keyWords[num];
}