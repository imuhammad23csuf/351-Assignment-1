#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <vector>
#include <string>


using namespace std;

//Funtion to search the given section of the array for key using linear search
int linear_search(const vector<string>& array, const string& key, size_t start, size_t end)
{
    for (size_t i = start; i < end; i++) 
    {
        if (array[i].find(key) != string::npos)
        {
            return 0;
        }
    }

    return 1;
}

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
    vector<size_t> start(processNum);
    vector<size_t> end(processNum);
    vector<size_t> child(processNum);

    for (int i = 0; i < processNum; i++)
    {
        start[i] = i * section;
        if (i == processNum - 1)
        {
            end[i] = array.size();
        } else {
            end[i] = (i + 1) * section;
        }
    }

    for (int i = 0; i < processNum; i++)
    {
        pid_t pid = fork();
        if (pid < 0) {
            fprintf(stderr, "Fork Failed");
            exit(-1);
        } else if (pid == 0) {
            int stringFound = linear_search(array, key, start[i], end[i]);
            exit(stringFound);
        } 
        child[i] = pid;
    }  

    int exit_status;

    for (int i = 0; i < processNum; i++)
    {
        if (wait(&exit_status) < 1) 
        {
            perror("wait");
            exit(-1);
        }

        if (WEXITSTATUS(exit_status) == 0) 
        {
            cout << "String found ending process" << endl;
            for (int i = 0; i < processNum; i++)
            {
                kill(child[i], SIGKILL);
            }
            return 0;
        }
    }

    cout << "No string found" << endl;
    return 0;
}
