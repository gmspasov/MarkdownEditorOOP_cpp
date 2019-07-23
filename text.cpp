#include "Text.h"
#include <iostream>
#include <cstring>
#include <string.h>
#include <fstream>
#include "Line.h"
#include <string>
#include "Word.h"


using namespace std;
/** constants */
const char* space=" ";
const char* new_line=" \n ";

Text::Text(char*path)
{
    cout<<"Creating a text object."<<endl;
    fstream txt;
    Set_path(path);
    txt.open(path,ios::in| ios::out);
    if(txt.good())
    {
        cout<<"File has been successfully opened in the constructor."<<endl;
    }
    else
    {
        cout<<"Opening File Error in the constructor."<<endl;
    }
    int startt=0;
    int endd=0;
    if(!txt)
    {
        cout <<"Couldn't open a file in the constructor."<<endl;
    }
    else
    {
        cout<<"The file has been opened for reading in the constructor."<<endl;
        txt.seekg(0,ios::end);
        endd=txt.tellg();
        txt.clear();
        txt.seekg(0,ios::beg);
        startt=txt.tellg();
        cout<<"The size of the file is "<<endd-startt<<"."<<endl;
        size=endd-startt; /**file size*/
        string readLine;
        int counter=0;

        while(getline(txt,readLine))
        {
            counter++; /**number of lines*/
            try
            {
                if(strlen(readLine.c_str())>1024)
                {
                    throw 1025;
                }
            }
            catch(int h)
            {
                cout<<"Too big line! Error. Maximum length of 1024 symbols is allowed."<<endl;
            }
        }


        lines=new Line[counter];
        Set_number_of_lines(counter);
        cout<<"the number of lines is "<< number_of_lines<<"."<< endl;
        txt.clear();
        txt.seekg(0,ios::beg);

        for(int w=0; w<number_of_lines; ++w)
        {
            if(getline(txt,readLine))
            {
                lines[w].Set_content(readLine);
                lines[w].Set_size(strlen(readLine.c_str()+1));
                lines[w].Set_words();
            }
        }
        txt.clear();
        txt.close();

        cout<<"The text object has been created." <<endl;

    }
}

Text::~Text()
{
    delete[] content;
    delete[] lines;
    delete[] path;
    cout<<"A text object has been deleted."<<endl;//dtor
}

void Text:: put_content_in_md_file()
{
    cout<<"The program writes a file in .md format."<<endl;
    fstream md;
    string new_name=Create_name_md(path);//טלועמ חא לה פאיכא
    md.open(new_name.c_str(),ios::binary |ios::out|ios::trunc);
    if(md)
    {
        cout<<"Md file has been successfully opened."<<endl;
    }
    else
    {
        cout<<"open error of the .md file."<<endl;
    }
    md.clear();
    md.seekp(0,ios::beg);
    cout<<"The writing in the .md file has begun."<<endl;

    int sum_size=0;
    for(int g=0; g<number_of_lines; ++g)
    {
        md.write(lines[g].Get_content(),lines[g].Get_size()+1);
        md.write(new_line,strlen(new_line));
        sum_size+=(lines[g].Get_size()+1);
        sum_size+=strlen(new_line);
    }
    md.seekp(0,ios::end);
    if(md.tellp()==sum_size)
    {
        cout<<"Everything has been written in the md file."<<endl;
    }
    else
    {
        cout<<"Not everything has been written in the md file."<<endl;
    }
    md.close();
}

void Text:: make_a_line_Heading(unsigned line_number)
{
    if(number_of_lines<line_number||line_number<1)
    {
        cout<<"The line cannot be made a heading. No such line. There are " <<number_of_lines<<" lines."<<endl;
    }
    else
    {
        lines[line_number-1].make_heading();
        size+=2;
        cout<<"Line number "<<line_number<<" has been made a heading."<<endl;
    }
}

void Text:: make_Italic(unsigned line_number,unsigned from,unsigned to)
{
    if(from>to)
    {
        swap(from,to);
    }
    if(number_of_lines<line_number||line_number<1)
    {
        cout<<"The text will not be modified because there is no such line. There are " <<number_of_lines<<" lines."<<endl;
    }
    else
    {

        if(lines[line_number-1].Get_number_of_words()<to)
        {
            cout<<"There are not so many words on line "<<line_number<<" . Nothing will be modified. "<<endl;
        }
        else
        {
            lines[line_number-1].make_words_italic(from-1,to-1);
            size+=4;
            cout<<"Words from "<<from<<" to "<<to<<" on line number "<<line_number<<" has been made italic."<<endl;
        }
    }
}


void Text:: make_Bold(unsigned line_number,unsigned from, unsigned to)
{
    if(from>to)
    {
        swap(from,to);
    }
    if(number_of_lines<line_number||line_number<1)
    {
        cout<<"The text will not be modified because there is no such line. There are " <<number_of_lines<<" lines."<<endl;
    }
    else
    {
        if(lines[line_number-1].Get_number_of_words()<to)
        {
            cout<<"There are not so many words on line "<<line_number<<" . Nothing will be modified. "<<endl;
        }
        else
        {
            lines[line_number-1].make_words_bold(from-1,to-1);
            size+=4;
            cout<<"Words from "<<from<<" to "<<to<<" on line number "<<line_number<<" has been made bold."<<endl;
        }
    }
}


void Text ::make_Combined(unsigned line_number,unsigned from,unsigned to)
{
    if(from>to)
    {
        swap(from,to);
    }
    if(number_of_lines<line_number||line_number<1)
    {
        cout<<"The text will not be modified because there is no such line. There are " <<number_of_lines<<" lines."<<endl;
    }
    else
    {
        if(lines[line_number-1].Get_number_of_words()<to)
        {
            cout<<"There are not so many words on line "<<line_number<<" . Nothing will be modified. "<<endl;
        }
        else
        {
            lines[line_number-1].make_words_combined(from-1,to-1);
            size+=4;
            cout<<"Words from "<<from<<" to "<<to<<" on line number "<<line_number<<" has been made italic and bold."<<endl;
        }
    }
}

void Text:: add_line (char* line)
{
    GrowLines(1);
    lines[number_of_lines-1].Set_content(line);
    lines[number_of_lines-1].Set_size(strlen(line)-1);
    lines[number_of_lines-1].Set_words();


    size+=(strlen(line)-1);
    cout<<"A line has been added."<<endl;
}

void Text:: remove_line (unsigned line_number)
{
    if(line_number>0&&line_number<=number_of_lines)
    {
        lines[line_number-1].make_line_null();
        for(int b=line_number-1; b<=number_of_lines-2; ++b)
        {
            lines[b]=lines[b+1];/**every line goes one position forward*/
        }
        GrowLines(-1);/**removes the last line*/
        cout<<"Line number "<<line_number<<" has been removed."<<endl;
    }

    else
    {
        cout<<"There is no such line. There are: "<<number_of_lines<<" lines."<<endl;
    }
}

void Text:: exit()
{
    put_content_in_md_file();
}

void Text::GrowLines(int how_much)
{
    if(how_much<0&&how_much< (number_of_lines*(-1)))/** a check if more lines than there are in the text are being removed*/
    {
        cout<<"Not allowed to remove so much lines.";
    }
    else
    {
        Line* new_lines = new Line[number_of_lines+how_much];

        int smaller;
        if(number_of_lines<number_of_lines+how_much)
        {
            smaller=number_of_lines;
        }
        else
        {
            smaller=number_of_lines+how_much;
        }


        for(int i=0; i<smaller; ++i)
        {
            new_lines[i]=lines[i];
        }

        if(lines!=NULL)
        {
            delete[] lines;
        }

        number_of_lines+=how_much;
        lines=new Line[number_of_lines];

        for(int j=0; j<smaller; ++j)
        {
            lines[j]=new_lines[j];
        }
        delete[] new_lines;
    }
}

void Text:: Get_line(int k)
{
    if(k<number_of_lines)
    {
        cout<<lines[k].Get_content()<<endl;
    }
    else
    {
        cout<<"There are not so much lines."<<endl;
    }
}

string Text::Create_name_md(char* path)
{
    string v(path);
    string jj;
    jj = v.substr(0,v.find_last_of ('.',strlen((const char*)path)))+".md";/** takes the name of the file before .txt and adds .md*/
    return jj;
}




