#include "Word.h"
#include <iostream>
#include <cstring>
#include <string.h>
#include <sstream>
#include <fstream>
#include "Line.h"
#include "Text.h"
using namespace std;

Line::Line()
{
    words=NULL;
    size=0;
    number_of_words=0;
    content=NULL;
}

Line::Line(char* cont)
{
    content=new char[strlen(cont)+1];
    strcpy(content,cont);
    size=strlen(cont);
    Set_words();
}

Line::~Line()
{
    delete[] words;
}

void Line:: Set_words_size(int size)
{
    this-> number_of_words=size;
    if(words!=NULL){delete [] words;}
    words=new Word[number_of_words];
}

void Line::Set_words()
{
    int wordNumber=0;
    string current_word;
    stringstream content_stream(content);
    content_stream.clear();
    content_stream.seekg(0,ios::beg);
    while(content_stream>>current_word)
    {
        ++wordNumber;
    }
    content_stream.clear();
    content_stream.seekg(0,ios::beg);
    number_of_words=wordNumber;
    words=new Word[number_of_words];
    for(int i=0; i<number_of_words; ++i)
    {
        content_stream>>current_word;
        Set_word(i,current_word,strlen(current_word.c_str()));
    }
    content_stream.clear();
}

void Line::Set_word(int k,string c,size_t s)
{
    words[k].Set_content(c);
    this->words[k].Set_size(s);
}

void Line:: Set_content(string u)
{
    if(content!=NULL){delete [] content;}
    content=NULL;
    content=new char[strlen(u.c_str())];
    strcpy(content,u.c_str());
    this->size=strlen(u.c_str());
}

void Line:: Set_content(char* cont)
{
    if(content!=NULL){delete [] content;}
    content=NULL;
    content=new char[strlen(cont)+1];
    strcpy(content,cont);
}

void Line:: Set_content_by_words()
{
    int new_size;
    for(int h=0; h<number_of_words; ++h)
    {
        new_size+=(words[h].Get_size());
    }
    content=new char[new_size+number_of_words];
    const char* space=" ";
    for(int h=0; h<number_of_words-1; ++h)
    {
        strcat(content,words[h].Get_content());
        strcat(content,space);
    }
    strcat(content,words[number_of_words-1].Get_content());
    content[new_size+number_of_words-1]=0;
}

void Line:: make_heading()
{
    char* temp=new char[size+3];
    strcpy(temp,"# ");
    strcat(temp,content);
    size+=2;
    if(content!=NULL){delete[] content;}
    content=new char[size+2];
    strcpy(content,temp);
    delete[] temp;
}

void Line:: make_words_bold(unsigned from, unsigned to)
{
    char* f=new char[words[from].Get_size()+3];
    strcpy(f,"**");
    char* t=new char[words[to].Get_size()+3];
    strcpy(t,"**");
    words[from].Set_size(words[from].Get_size()+2);
    words[to].Set_size(words[to].Get_size()+2);
    words[from].Set_content(strcat(f,(const char*)words[from].Get_content()));
    words[to].Set_content(strcat(words[to].Get_content(),t));
    size+=4;
    Set_content_by_words();
}

void Line:: make_words_italic(unsigned from, unsigned to)
{
    char* f=new char[words[from].Get_size()+2];
    strcpy(f,"_");
    char* t=new char[words[to].Get_size()+2];
    strcpy(t,"_");
    words[from].Set_size(words[from].Get_size()+1);
    words[from].Set_content(strcat(f,(const char*)words[from].Get_content()));
    words[to].Set_size(words[to].Get_size()+1);
    words[to].Set_content(strcat(words[to].Get_content(),t));
    size+=2;
    Set_content_by_words();
}

void Line:: make_words_combined(unsigned from, unsigned to)
{
    char* f=new char[words[to].Get_size()+4];
    strcpy(f,"_**");
    char* t=new char[words[from].Get_size()+4];
    strcpy(t,"**_");
    words[from].Set_content(strcat(t,(const char*)words[from].Get_content()));
    words[from].Set_size(words[from].Get_size()+3);
    words[to].Set_content(strcat(words[to].Get_content(),f));
    words[to].Set_size(words[to].Get_size()+3);
    size+=6;
    Set_content_by_words();
}

Line& Line:: operator=(const Line& l)
{
    if(&l==this){return * this;}
    size=l.size;
    number_of_words=l.number_of_words;
    Set_content(l.content);
    Set_words();
    return *this;
}

void Line :: make_line_null()
{
    size=0;
    delete[] words;
    delete[] content;
    number_of_words=0;
}

void Line:: Set_words(Word* other, int Word_number)
{

if(words!=NULL){delete[] words;}
Set_number_of_words(Word_number);
words=new Word[Word_number];
for(int i=0;i<Word_number;++i)
{
    words[i]=other[i];
}

}
