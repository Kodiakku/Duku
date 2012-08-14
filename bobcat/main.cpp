#include <iostream>
#include "HEADER/libBobcat.h"
#include "HEADER/mainHelper.h"
using namespace std;

int main(int argc, char**argv){
handleArgs(argc, argv);

if(argc>=2)
file=argv[1];
else{
cout << "Filename? :";
cin >> file;
}
ask();
}
