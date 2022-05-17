#include <iostream>
#include <cstring>

using namespace std;

int main () {
    char str[10]; //how many characters i want in my string
    cout << "hypothetical string from server" << endl;
    cin.getline(str, 10); //getline function to read string from input

    char * pointr; //declare a ptr pointer
    pointr = strtok(str,"."); // use srtok() to seperate string by "."
    cout << "\n string which has been split: " << endl;

    char split[4];
    int i = 0;

    while (pointr != NULL)
    {
        cout << pointr << endl; //print string token
        split[i] = *pointr;
        //cout << split[i] <<endl; //extra print causing double
        i++;
        pointr = strtok (NULL, ".");
    }

    for (int j = 0; j<i; j++) {
        cout << split[j] << endl;
    
    }
    return 0;
}