#include <iostream>
#include <windows.h>
#include <conio.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <filesystem>

#include "taskExecutor.cpp"


using namespace std;

int keyPressed(int key){
    return (GetAsyncKeyState(key) & 0x8000 != 0);
}



int recordSchema() {

    //SetCursorPos(100, 400);
    //mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);}

    while(1){
        if(keyPressed(VK_LBUTTON)){
            printf("%s\n","Click gauche");

            if (GetCursorPos(&point)) {
                cout << point.x << "," << point.y << "\n";
            }
        } else if (keyPressed(VK_RBUTTON)){
            printf("%s\n","Click droit");

            if (GetCursorPos(&point)) {
                cout << point.x << "," << point.y << "\n";
            }
        } else if (keyPressed(VK_LSHIFT)){
            printf("%s\n","SHIFT");
            break;
        }
    }

    return 1;
}




int ReadFile() {
    // Create and open a text file
    ofstream MyFile("C:/Users/$4UR000-S8CC9UP2KJ2T/CLionProjects/2cpp/data.txt");

    // Write to the file
    //std::string myText = "test1,1,152,121,2;test2,3,81,21,3;test3,1,152,121,2";
    std::string myText = "test1;1,152,121,2;3,81,21,3|test2;1,152,121,2;3,81,21,3;1,152,121,2|test3;1,152,121,2;3,81,21,3;1,152,121,2;3,81,21,3";

    MyFile << myText;

    // Close the file
    MyFile.close();

    std::ifstream file("C:/Users/$4UR000-S8CC9UP2KJ2T/CLionProjects/2cpp/data.txt");
    std::string str;

    std::string result;

    while (std::getline(file, str))
    {
        // Process str
        result = str;
    }

    //cout << result;

    std::vector<string> resultsFromFileVector;
    resultsFromFileVector = divideStringIntoArray(result, "|");

    std::string infoTask;

    std::vector<string> resultsInfoTask;

    std::vector<string> listOfTasksNames;

    for (int i = 0; i < resultsFromFileVector.size(); i++) {

        // here we have each task (we're printing it out below)
        std::cout << resultsFromFileVector.at(i) << '\n';
        infoTask = resultsFromFileVector.at(i);

        // now we want to split each data from the current task
        resultsInfoTask = divideStringIntoArray(infoTask, ";");

        for (int i = 0; i < resultsInfoTask.size(); i++) {
            std::cout << resultsInfoTask.at(i) << '\n';

        }

        listOfTasksNames.push_back(resultsInfoTask.at(0));

        for (int i = 0; i < listOfTasksNames.size(); i++) {
            std::cout << listOfTasksNames.at(i) << '\n';
        }

    }

    return 0;
}

int displayAvailableTasks() {
    // display tasks
    std::cout << "Available tasks:\n";

    std::ifstream file(DATA_FILE_PATH);
    std::string str;
    std::string result;

    while (std::getline(file, str)) {
        result = str;
    }

    std::vector<string> resultsFromFileVector;
    resultsFromFileVector = divideStringIntoArray(result, "|");
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
    std::cout << "Type a number: "; // Type a number and press enter
    std::cin >> x; // Get user input from the keyboard
    x = x-1;
    std::cout << '\n';

    return x;
}

int updateData(string newData, bool isAppend) {
    filesystem::path pwd = filesystem::current_path();
    pwd /= "..\\data.txt";

    // Create and open a text file
    std::ofstream MyFile;

    if (isAppend) {
        MyFile.open(pwd, std::ios_base::app);
    } else {
        MyFile.open(pwd);
    }

    // Write to the file
    MyFile << newData;

    // Close the file
    MyFile.close();

    return 0;
}


string deleteTask(int chosenTask) {
    // here we need to delete a task

    filesystem::path pwd = filesystem::current_path();
    pwd /= "..\\data.txt";

    std::ifstream file(pwd);
    std::string str;
    std::string result;

    while (std::getline(file, str)) {
        result = str;
    }

    std::vector<string> resultsFromFileVector;
    resultsFromFileVector = divideStringIntoArray(result, "|");
    std::string infoTask;
    std::vector<string> resultsInfoTask;

    infoTask = resultsFromFileVector.at(chosenTask);

    std::string newData;

    for (int i = 0; i < resultsFromFileVector.size(); i++) {
        if (i != chosenTask) {
            newData += resultsFromFileVector.at(i);
            newData += "|";
        }
    }

    newData = newData.substr(0, newData.size()-1);

    // we're updating the data file
    updateData(newData, false);

    return infoTask;
}

int renameTask(string deletedTask) {
    string newName;
    std::cout << "New name: ";
    std::cin >> newName;
    std::cout << '\n';

    std::vector<string> resultsInfoTask;

    resultsInfoTask = divideStringIntoArray(deletedTask, ";");
    resultsInfoTask.at(0) = newName;

    std::string newTask;

    for (int i = 0; i < resultsInfoTask.size(); i++) {
       newTask += resultsInfoTask.at(i);
       newTask += ";";
    }

    newTask = newTask.substr(0, newTask.size()-1);

    updateData("|", true);
    updateData(newTask, true);

    return 0;
}


int displayMainMenu() {
    std::cout << "Welcome to the SUPINFO AutoClicker!\n\n";

    // ask for action : execute a task / create a task / delete a task / duplicate a task / schedule a task / /!\ TASK MOVEMENT PREVIEW
    std::cout << "Available actions:\n";

    std::vector<string> availableActions = {"Execute a task", "Create a task", "Delete a task", "Rename a task", "Duplicate a task", "Schedule a task",  "Simulate a task's path as a preview"};

    for (int i = 0; i < availableActions.size(); i++) {
        std::cout << i+1 << ": " << availableActions.at(i) << '\n';
    }
    std::cout << '\n';

    int x;
    std::cout << "Type a number: "; // Type a number and press enter
    std::cin >> x; // Get user input from the keyboard
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
            cout << "2";
            break;
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
            cout << "5";
            break;
        case 6:
            cout << "6";
            break;
        case 7:
            chosenTask = displayAvailableTasks();
            executeTask(chosenTask, true);
            std::cout << "Done.\n";
            break;
    }

    return 0;
}


int main(){
    //std::vector<int> clicksInfosInt;
    //clicksInfosInt = convertVectorStringToVectorInt({"1111", "21", "3", "411123"});

    displayMainMenu();

    //ReadFile();

    //recordSchema();

    return 0;
}
