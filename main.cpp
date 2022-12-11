#include <iostream>
#include <windows.h>
#include <conio.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

const string DATA_FILE_PATH = "C:/Users/$4UR000-S8CC9UP2KJ2T/CLionProjects/2cpp/data.txt";
POINT point;

int keyPressed(int key){
    return (GetAsyncKeyState(key) & 0x8000 != 0);
}

vector<int> convertVectorStringToVectorInt(vector<string> strings) {
    std::vector<int> ints;
    std::transform(strings.begin(), strings.end(), std::back_inserter(ints), [&](std::string s) {
        return stoi(s);
    });

    return ints;
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
        //cout << arr[i] << endl;
        myArrays.push_back(arr[i]);
    }

    return myArrays;

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

int makeClick(int key, int x, int y) {
    // here we are making the click on the screen

    SetCursorPos(x, y);
    mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, x, y, 0, 0);

    return 0;
}

int executeTask(int chosenTask) {
    // the below code will execute the given task's number

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

    infoTask = resultsFromFileVector.at(chosenTask);
    resultsInfoTask = divideStringIntoArray(infoTask, ";");

    cout << infoTask;

    std::cout << '\n';

    std::vector<string> clicksInfos;
    std::vector<int> clicksInfosInt;

    for (int i = 0; i < resultsInfoTask.size(); i++) {
        // here we get all elements from a task
        // the first one will be the name of the task [0]
        // the others will be the clicks' infos
        std::cout << resultsInfoTask.at(i) << '\n';

        if (i != 0) {
            clicksInfos = divideStringIntoArray(resultsInfoTask.at(i), ",");
            clicksInfosInt = convertVectorStringToVectorInt(clicksInfos);

            // we have to make the click right now
            makeClick(clicksInfosInt.at(0), clicksInfosInt.at(1), clicksInfosInt.at(2));

            // the sleep value should be replaced by the real waiting time value stored in the data file
            usleep(1000000);
        }
    }

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

    switch (x) {
        case 1:
            chosenTask = displayAvailableTasks();
            executeTask(chosenTask);
            break;
        case 2:
            cout << "2";
            break;
        case 3:
            cout << "3";
            break;
        case 4:
            cout << "4";
            break;
        case 5:
            cout << "5";
            break;
        case 6:
            cout << "6";
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
