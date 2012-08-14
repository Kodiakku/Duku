/*
*Verison 2 - Revival
*mainHelper.h
*
*Mainhelper helps main, thus the name. Utilities for parsing command
*line options are the application startup go here. Anything relating
*to the configuration file also go here as that relates to the startup
*of the application.
*/
#include <fstream>
#include <iostream>
using namespace std;
int version=1;//Version of the program
int gnus=1;//How many command line options there are
int options=4;//The number of options in the configuration file

const string defPath = "No configuration file loaded";//The default path that conf uses
string info[2]={"Norton Jenkins and Kodiakku", "dominantshoe@gmail.com"};//The author's contact information
vector<string> optTrigs(4);//Lines of the configuration file followed by "true" or "false". For instance, allow crunch true

//!Used to trick std::vector
struct wrapper{
bool is;
wrapper(){};
};
vector<wrapper> settings(options);//An array used by the conf file
string conf=defPath;//The path to the configuration file

/**
*Set the number of command line options.
*@param number - The number of command line options
*/
void setGnus(int number){
gnus=number;
}
/**
*Sets the version of the program.
*@param number - The version
*/
void setVersion(int number){
version=number;
}

/**
*How many possible tokens are in the configuration file?
*@param number - The number to set
*/
void setOptions(int number){
options=number;
}

/**
*Set the author info for the program.
*@param name - The authors name
*@param email - The author's email
*/
void setInfo(string name, string email){
info[0]=name;
info[1]=email;
}

/**
*Required step if you have a configuration file. Set
*the lines that trigger settings being set.
*/
void setOptTrigs(vector<string> trigs){
optTrigs=trigs;
}
//BEGIN CONFIGURATION FILE UTILITIES
struct config
{
    bool want_learn;//Can the bot learn?
    bool allow_crunch;//Can a user execute crunch commands?
    bool allow_exl;//Can the bot quietly learn?

    string path;//Path to the configuration file

    config()
    {
        path=conf;
    }

//!Does the line contain "false"?
    bool isFalse(string line)
    {
        return (line.find("false")!=-1)?true:false;
    }

    /**
    *Sets the structure's internal options based on a file.
    *To specify the file set config.path
    */
    void setOptions()
    {
        ifstream reader(path.c_str());//Configuration file stream
        string line;//Used for individual line from reader's stream

        for(int index=0; getline(reader, line); index++)//Iterate through lines
        {

            for(int sindex=0; sindex<options; sindex++)//Iterate through arguments and match it with line
                if(line.find(optTrigs[sindex])!=-1)
                {
                    if(isFalse(line))
                      settings[sindex].is=false;
                    else settings[sindex].is=true;
                }
        }
        reader.close();
    }
    void loadConfig(bool arr[])
    {
        for(int index=0; index<options; index++){
        arr[index]= settings[index].is;
        }
    }
};
config pConfig;
void setConfFile(string arg)
{
    pConfig.path=arg;
    pConfig.setOptions();

}
struct cLineOption
{
    string longname;//The long -- name of the command.
    string shortname;//The short letter symbol of a command.
    bool quitAfter;//Whether or not to quit after execution
    bool parseForward;//Whether or not to take an argument from the next token.

    void (*gcmd)(string);//The command to execute
//!Creates a command line option with a longname, a shortname, quit after, parse forward, and f(str)
    cLineOption(string ln, string sn, bool qA, bool pF, void (*gnuFun)(string))
    {
        longname=ln;
        shortname=sn;
        quitAfter=qA;
        parseForward=pF;
        gcmd=gnuFun;
    }

    cLineOption(){}
    /**
    *If the shortname or the longname are found
    *@param arg - The string to search in
    *@return true if found, false otherwise
    */
    bool ifMatches(string arg)
    {
        if(arg.find(shortname)!=-1||arg.find(longname)!=-1)
            return true;
        return false;
    }

    void exec(string arg)
    {
        gcmd(arg);
    }
};
//                       long       short quit  take    function
cLineOption clVersion("--version",  "-v", true, false, &versionGet);
cLineOption clHelp(   "--help",     "-h", true, false, &helpGet);

vector<cLineOption> allCLOptions(0);

/**
*Adds a command line option to the vector of cLineOptions.
*@param option - The cLineOption to add.
*/
void addcLineOption(cLineOption option){
allCLOptions.push_back(option);
gnus++;
}

/**
*Handles the command line arguments of main.
*@param argc - Number of args
*@param argv - The arguments
*@return handled - If an argument was found
*/
bool handleArgs(int argc, char**argv)
{
    bool found; //If the command is found, regardless of array options

    for(int index=1; index<argc; index++)//Iterate through args
    {
        /*
        *LOOP OUTLINE
        *Iterate through arguments
        *Iterate through commands, comparing them to argument
        *Execute command if it is found, go to next argument otherwise
        *Exit if that is specified
        *Return false if nothing was done
        */
        for(int gnuCommands=0; gnuCommands<gnus; gnuCommands++)//Iterate through commands on one arg
        {
            found=false;


            if(allCLOptions[gnuCommands].ifMatches(string(argv[index])))
            {
                found=true;
            }
            else continue;

            if(found&&!allCLOptions[gnuCommands].parseForward){
                allCLOptions[gnuCommands].exec(string(argv[index]));//Executes the command that matches the name
            }

            if(found&&allCLOptions[gnuCommands].parseForward)
            {
                if(argc>index);
                allCLOptions[gnuCommands].exec(string(argv[index+1]));//Parsed forward to next option
            }

            if(found&&allCLOptions[gnuCommands].quitAfter)
            {
                exit(0);
            }
            else return true;//The command was found, executed, but did not want to quit

        }//END command search
    }//END arg list
    return false;
}//END function

