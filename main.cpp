/**      This program takes as a command-line argument an absolute file path of a text file that is on the disc.
** The program reads the text of the file and gives opportunity to get the text modified- certain words/lines
** to become bold, italic or bold and italic simultaneously. Chosen line can be made to visualize as a headline.
** All changes will appear in .md format. After is done the program writes the new text with the modifications in
** a .md file with the same name as the old .txt file. In main() are made examples using the file Speho.txt which is
** in the program directory. In order to be used on different machines the path to Speho.txt must be changed so it
** is actually the real address of the file on the current computer. There are online markdown editors that give opportunity
**to view the modified text. https://dillinger.io is such.
**Created in 2018 by Georgi Spasov, last modification on 23.07.2019 by Georgi Spasov. The text of Speho.txt is also
**written by Georgi Spasov.
*/

#include <iostream>
#include "Text.h"
#include <cstring>
#include <string.h>
#include <fstream>
#include "Line.h"
#include <string>
#include "Word.h"

using namespace std;

int main(int argc, char*argv[])
{
    if(argc!=2)
    {
        cout<<"Arguments of main must be 2!";
    }
    else{
        cout<<"Main has received an argument."<<endl;

        Text test(argv[1]); /**a text object is created using the file path to Speho.txt*/
        test.make_a_line_Heading(1); /**line 1 becomes a headlight*/
        test.make_Bold(6,2,4);/**words 2 to 4 on line 6 become bold*/
        test.make_Bold(5,2,4);/**words 2 to 4 on line 5 will not become bold because there aren't so much words on the line*/
        test.make_Combined(9,3,5);/**words 3 to 5 on line 9 become italic and bold*/
        test.make_Italic(14,1,3);/**words 1 to 3 on line 14 become italic*/
        test.remove_line(3);/**removes line 3*/
        test.add_line("Additional line :) ");/**adds additional line at the end of the file*/
        test.exit();/** end of manipulations. Exits from the program*/
    }
    return 0;
}
