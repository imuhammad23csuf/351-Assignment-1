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

    //loading contents of file into array
    vector<string> array;
    string text;
    while (getline(file, text)) 
    {
        array.push_back(text);
    }
    file.close();

    size_t section = array.size() / processNum;
    vector<pid_t> pids(processNum);

    

    

    int exit_status;
    bool stringFound = false;

    for (int i = 0; i < processNum; ++i)
    {
        if (wait(&exit_status) < 1) 
        {
            perrer("wait");
            exit(-1);
        }

        if (WEXITSTATUS(exit_status) == 0) 
        {
            stringFound = true;
        }
    }

    if (stringFound)
    {
        cout << "String found" << endl;
    } else {
        cout << "No string found" << endl;
    }







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
