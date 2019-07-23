#include <iostream>
#include <cstring>
#include <string.h>
#include <fstream>
#include "Word.h"
using namespace std;

Word::Word(char*contento,size_t sizeo):content(contento),size(sizeo) {}

Word::~Word()
{
    if(content!=NULL){
    delete[] content;
    }
}

void Word::Set_content(char* val)
{
    string vaw=val;
    if(content!=NULL){delete [] content;}
    content=new char[vaw.length()+1];
    strcpy(content,(const char*)val);
}

void Word:: Set_content(string val)
{
    if(content!=NULL)
    {
        delete[] content;
    }
    content= new char[strlen(val.c_str())+1];
    strcpy(content,val.c_str());
}

Word& Word::operator=(const Word& other)
{
if(&other==this){return * this;}
if(content==NULL){delete[] content;}
content=new char[strlen(other.Get_content())+1];
strcpy(content,other.Get_content());
size=other.size;
}
