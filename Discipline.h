#ifndef DISCIPLINE_H
#define DISCIPLINE_H
#include <string>
#include <vector>
using namespace std;

class Discipline
{
    private:
        string disc;
        vector<string> keyWords;
    
    public:
        Discipline()
        {   disc = " ";   }
        Discipline(string s)
        {   disc = s; }
        void setDiscipline(string s)
        {   disc = s; }
        void addKeyWord(string s)
        {   keyWords.push_back(s);  }
        string getDiscipline() const
        {   return disc;   }
        void getKeyWords() const;
        int getKeyWordsSize() const
        {   return keyWords.size(); }
        string getKeyWordByIndex(int);
        bool searchKeyWords(string);
        int returnKeyWordIndex(string);
        void deleteKeyWord(string);
};

#endif