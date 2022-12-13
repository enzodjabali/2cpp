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

using namespace std;


vector<string> divideStringIntoArray(string line, string search) {
    // parsing

    //std::string line = "test1,1,152,121,2;test2,3,81,21,3;test3,1,100,100,2";
    std::string arr[100];
    //std::string search = ";";
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


#include "taskExecutor.cpp"
#include "taskEditor.cpp"
#include "taskRecorder.cpp"

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
    std::cout << "Type a number: "; // Type a number and press enter
    std::cin >> x; // Get user input from the keyboard
    x = x-1;
    std::cout << '\n';

    return x;
}


int displayMainMenu() {
    std::cout << "Welcome to the SUPINFO AutoClicker!\n\n";

    // ask for action : execute a task / create a task / delete a task / duplicate a task / schedule a task / /!\ TASK MOVEMENT PREVIEW
    std::cout << "Available actions:\n";

    std::vector<string> availableActions = {"Execute a task", "Create a task", "Delete a task", "Rename a task", "Duplicate a task", "Schedule a task",  "Simulate a task's path as a preview", "Quit"};

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
    //std::vector<int> clicksInfosInt;
    //clicksInfosInt = convertVectorStringToVectorInt({"1111", "21", "3", "411123"});

    while(true) {
        displayMainMenu();
        std::cout << "\n";
    }

    //ReadFile();

    //recordSchema();

    return 0;
}
