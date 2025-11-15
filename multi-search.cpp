#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) 
{
    //loading all arguments into variables
    string fileName = argv[1];
    string key = argv[2];
    int processNum = atoi(argv[3]);

    //reading the file
    ifstream file(fileName);
    if (!file.is.open())
    {
        cerr << "Error opening file" << endl;
        return 1;
    }

    //loading contents of file into array
    vector<string> array;
    string text;
    while (getline(file, text)) 
    {
        array.push_back(text);
    }
    file.close();

    





}

//Funtion to search the given section of the array for key using linear search
int linear_search(const vector<string>& array, const string& key, size_t start, size_t end)
{
    for (size_t i = start; i <) 
    {
        if (array[i].find(key) != string::npos)
        {
            return 0;
        }
    }

    return 1;
}