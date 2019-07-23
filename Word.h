#ifndef WORD_H
#define WORD_H
#include <iostream>
#include <cstring>
#include <string.h>
#include <fstream>
using namespace std;

class Word
{
public:
    Word()
    {
        size=0;
        content=NULL;
    }

    Word(char*content,size_t size);
    ~Word();
    Word& operator=(const Word&);

    size_t Get_size() const
    {
        return size;
    }

    void Set_size(size_t val)
    {
        size = val;
    }

    char* Get_content() const
    {
        return content;
    }

    void Set_content(char*);

    void Set_content(string); /** the same but works with string*/

protected:

private:
    size_t size;
    char* content;
};

#endif // WORD_H
