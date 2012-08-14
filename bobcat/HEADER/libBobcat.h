/*
 *This program is free software distributed with no warrant, expressed or implied
 *besides the hopes that the program is found useful. The program is licensed under
 *the GNU General Public License, revision 2. If you did not receive a copy of the
 *GNU GPL 2 with this program, please contact the Free Software Foundation.
 *
 *Bobcat version 1
 *Authors: Dymatic, Kodiakku
 */
#ifndef BOBCAT_H
#define BOBCAT_H

#include <iostream>//<<, >>
#include <cstdlib>//system()
#include <fstream>//ifstream

#include "nsl.h"//linec()
using namespace std;//cout, string

string file;//The package definition file/**

/**
*Read the file, get input, and execute commands accordingly.
*/
void ask()
{

    string inp;//Input
    string buff;//A line of the defintion file
    ifstream reader(file.c_str());//The actual definition file

    for(int index=0; index<linec(file); index++)
    {
        getline(reader, buff);

        cout << buff.substr(0, buff.find("_")-1);
        cin  >> inp;
        cout << endl;

        buff=buff.substr(buff.find("_")+1, buff.length());//gnome#install gnome|kde#installKDE

        for(int index=0; ; index++)
        {
            if(buff.substr(0, buff.find("#")).find(inp)!=-1) //Between 0 and #, find input
            {
                if(buff.find("%")!=-1) //If it has more than one
                {
                    system(buff.substr(buff.find("#")+1, buff.find("%")).c_str());//Then execute the command between # and |
                    exit(0);
                }
                else
                {
                    (system(buff.substr(buff.find("#")+1, buff.length()).c_str()));    //If there is not more than one, execute between # and length
                }
                break;//Get the next line for the script
            }
            else if(buff.find("%")!=-1)
            {
                buff=buff.substr(buff.find("%")+1, buff.length());//If the input is not found buff becomes equal to the next possible set
            }
            else break;
        }
    }
}
#endif BOBCAT_H
