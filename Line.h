#ifndef LINE_H
#define LINE_H
#include "Word.h"
#include <iostream>
#include <cstring>
#include <string.h>
#include <fstream>
using namespace std;

class Line
{
public:
    Line();
    Line(char* content);
    ~Line();
    Line& operator=(const Line& other);

    size_t Get_size()
    {
        return size;
    }

    void Set_size(size_t val)
    {
        size = val;
    }

    unsigned Get_number_of_words()
    {
        return number_of_words;    /** the number of the words on the line*/
    }

    void Set_number_of_words(unsigned val)
    {
        number_of_words = val;
    }

    char* Get_content()
    {
        return content;
    }
    void Set_content(string);
    void Set_content_by_words(); /** regenerates content word by word */
    Word* Get_words()
    {
        return words;
    }
    void Set_word(int,string,size_t); /** on position int puts word string with size size_t */
    void make_heading();
    void make_words_italic(unsigned,unsigned);
    void make_words_bold(unsigned,unsigned);
    void make_words_combined(unsigned,unsigned);
    void Set_words_size(int);
    void make_line_null();
    void Set_words();/** divides the words of the line in a Word array */
    void Set_words(Word*,int);
    void Set_content(char*);

protected:

private:
    size_t size; /** size of content*/
    unsigned number_of_words;
    char* content;
    Word* words;
};

#endif // LINE_H
