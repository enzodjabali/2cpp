#include <iostream>
#include <windows.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

using namespace std;

POINT point;

vector<string> divideStringIntoArray(string line, string search) {
    // parsing

    std::string arr[100];
    int spacePos;
    int currPos = 0;
    int k = 0;
    int prevPos = 0;

    do {
        spacePos = line.find(search,currPos);

        if(spacePos >= 0)
        {
            currPos = spacePos;
            arr[k] = line.substr(prevPos, currPos - prevPos);
            currPos++;
            prevPos = currPos;
            k++;
        }
    } while(spacePos >= 0);

    arr[k] = line.substr(prevPos,line.length());
    std::vector<string> myArrays;

    for(int i = 0; i < k+1; i++)
    {
        myArrays.push_back(arr[i]);
    }

    return myArrays;
}


vector<string> getData() {
    filesystem::path pwd = filesystem::current_path();
    pwd /= "..\\data.txt";

    std::ifstream file(pwd);
    std::string str;
    std::string result;

    while (std::getline(file, str)) {
        result = str;
    }

    std::vector<string> data;
    data = divideStringIntoArray(result, "|");

    return data;
}


int updateData(string newData, bool isAppend) {
    filesystem::path pwd = filesystem::current_path();
    pwd /= "..\\data.txt";

    // create and open a text file
    std::ofstream MyFile;

    if (isAppend) {
        MyFile.open(pwd, std::ios_base::app);
    } else {
        MyFile.open(pwd);
    }

    // write to the file
    MyFile << newData;

    // close the file
    MyFile.close();

    return 0;
}


#include "taskExecutor.cpp"
#include "taskEditor.cpp"
#include "taskRecorder.cpp"


int displayAvailableTasks() {
    // display tasks
    std::vector<string> resultsFromFileVector;
    resultsFromFileVector = getData();
    std::string infoTask;
    std::vector<string> resultsInfoTask;
    std::vector<string> listOfTasksNames;

    for (int i = 0; i < resultsFromFileVector.size(); i++) {
        infoTask = resultsFromFileVector.at(i);
        resultsInfoTask = divideStringIntoArray(infoTask, ";");
        listOfTasksNames.push_back(resultsInfoTask.at(0));
        std::cout << i+1 << ": " << listOfTasksNames.at(i) << '\n';
    }

    std::cout << '\n';
    int x;
    std::cout << "Type a number: "; // type a number and press enter
    std::cin >> x; // get user input from the keyboard
    x = x-1;
    std::cout << '\n';

    return x;
}


int displayMainMenu() {
    std::cout << "Welcome to the SUPINFO AutoClicker!\n\n";
    std::cout << "Available actions:\n";
    std::vector<string> availableActions = {"Execute a task", "Create a task", "Delete a task", "Rename a task", "Duplicate a task", "Schedule a task",  "Simulate a task's path as a preview", "Quit"};

    for (int i = 0; i < availableActions.size(); i++) {
        std::cout << i+1 << ": " << availableActions.at(i) << '\n';
    }
    std::cout << '\n';

    int x;
    std::cout << "Type a number: ";
    std::cin >> x;
    std::cout << '\n';

    int chosenTask;
    string deletedTask;

    switch (x) {
        case 1:
            chosenTask = displayAvailableTasks();
            executeTask(chosenTask, false);
            std::cout << "Done.\n";
            break;
        case 2:
            taskRecord();
            std::cout << "Task saved.\n";
            std::exit(0);
        case 3:
            chosenTask = displayAvailableTasks();
            deleteTask(chosenTask);
            std::cout << "Done.\n";
            break;
        case 4:
            chosenTask = displayAvailableTasks();
            deletedTask = deleteTask(chosenTask);
            renameTask(deletedTask);
            std::cout << "Done.\n";
            break;
        case 5:
            chosenTask = displayAvailableTasks();
            duplicateTask(chosenTask);
            std::cout << "Done.\n";
            break;
        case 6:
            chosenTask = displayAvailableTasks();
            scheduleTask(chosenTask);
            std::cout << "Done.\n";
            break;
        case 7:
            chosenTask = displayAvailableTasks();
            executeTask(chosenTask, true);
            std::cout << "Done.\n";
            break;
        case 8:
            std::cout << "Bye.\n";
            std::exit(0);
    }

    return 0;
}


int main(){
    while(true) {
        displayMainMenu();
        std::cout << "\n";
    }

    return 0;
}
