#ifndef TEXT_H
#define TEXT_H
#include "Word.h"
#include <iostream>
#include <cstring>
#include <string.h>
#include <fstream>
#include "Line.h"

using namespace std;
class Text
{
public:
    Text(char*path);
    ~Text();

    size_t Get_size() const
    {
        return size;
    }

    void Set_size(size_t val)
    {
        size = val;
    }

    unsigned Get_number_of_lines() const
    {
        return number_of_lines;
    }

    void Set_number_of_lines(unsigned val)
    {
        number_of_lines = val;
    }

    char* Get_content() const
    {
        return content;
    }

    void Set_content(char* val)
    {
        if(content!=NULL){delete[] content;}
        content=new char[strlen(val)+1];
        strcpy(content,val);
    }

    char* Get_path() const
    {
        return path;
    }

    void Set_path(char* val)
    {
        if(path!=NULL){delete[] path;}
        path=new char[strlen(val)+1];
        strcpy(path,val);
    }

    void Get_line(int);
    void put_content_in_md_file();
    void make_a_line_Heading(unsigned);
    void make_Italic(unsigned,unsigned,unsigned);
    void make_Bold(unsigned,unsigned,unsigned);
    void make_Combined(unsigned,unsigned,unsigned);
    void add_line (char*);
    void remove_line (unsigned);
    void exit();
    void GrowLines(int);/**resizes the array*/
    string Create_name_md(char*);/** generates the name of the .md file*/

protected:

private:
    size_t size;
    unsigned number_of_lines;
    char* content;
    char* path;
    Line* lines;
};

#endif // TEXT_H
