#include <iostream>
#include <windows.h>
#include <conio.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

#include "config.cpp"

using namespace std;

POINT point;

vector<int> convertVectorStringToVectorInt(vector<string> strings) {
    std::vector<int> ints;
    std::transform(strings.begin(), strings.end(), std::back_inserter(ints), [&](std::string s) {
        return stoi(s);
    });

    return ints;
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

int makeClick(int key, int x2, int y2, bool isPreview) {
    if (isPreview) {
        if (GetCursorPos(&point)) {
            int x1 = point.x;
            int y1 = point.y;

            int xDiff;
            int yDiff;

            if (x2 < x1) {
                xDiff = x1 - x2;

                while(xDiff > 0) {
                    SetCursorPos(x2 + xDiff, y1);
                    xDiff--;
                    usleep(1000);
                }
            } else {
                xDiff = x2 - x1;

                while(xDiff > 0) {
                    SetCursorPos(x2 - xDiff, y1);
                    xDiff--;
                    usleep(1000);
                }
            }

            if (y2 < y1) {
                yDiff = y1 - y2;

                while(yDiff > 0) {
                    SetCursorPos(x2, y2 + yDiff);
                    yDiff--;
                    usleep(1000);
                }
            } else {
                yDiff = y2 - y1;

                while(yDiff > 0) {
                    SetCursorPos(x2, y2 - yDiff);
                    yDiff--;
                    usleep(1000);
                }
            }
        }
    }

    SetCursorPos(x2, y2);

    // here we are making the click on the screen

    switch (key) {
        case 1:
            if (!isPreview) {
                mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, x2, y2, 0, 0);
                cout << "Right click on x: " << x2 << " and y: " << y2 << "\n";
            } else {
                cout << "[PREVIEW] Right click on x: " << x2 << " and y: " << y2 << "\n";
            }
            break;
        case 2:
            if (!isPreview) {
                mouse_event(MOUSEEVENTF_MIDDLEDOWN | MOUSEEVENTF_MIDDLEUP, x2, y2, 0, 0);
                cout << "Middle click on x: " << x2 << " and y: " << y2 << "\n";
            } else {
                cout << "[PREVIEW] Middle click on x: " << x2 << " and y: " << y2 << "\n";
            }
            break;
        case 3:
            if (!isPreview) {
                mouse_event(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP, x2, y2, 0, 0);
                cout << "Left click on x: " << x2 << " and y: " << y2 << "\n";
            } else {
                cout << "[PREVIEW] Left click on x: " << x2 << " and y: " << y2 << "\n";
            }
            break;
    }

    return 0;
}


int executeTask(int chosenTask, bool isPreview) {
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

    //cout << infoTask;
    //std::cout << '\n';
    std::cout << resultsInfoTask.at(0) << " is being executed...\n";

    std::vector<string> clicksInfos;
    std::vector<int> clicksInfosInt;

    for (int i = 0; i < resultsInfoTask.size(); i++) {
        // here we get all elements from a task
        // the first one will be the name of the task [0]
        // the others will be the clicks' infos

        //std::cout << resultsInfoTask.at(i) << '\n';

        if (i != 0) {
            clicksInfos = divideStringIntoArray(resultsInfoTask.at(i), ",");
            clicksInfosInt = convertVectorStringToVectorInt(clicksInfos);

            // we have to make the click right now
            if (isPreview) {
                // we're just making a preview of the click here
                makeClick(clicksInfosInt.at(0), clicksInfosInt.at(1), clicksInfosInt.at(2), true);
            } else {
                makeClick(clicksInfosInt.at(0), clicksInfosInt.at(1), clicksInfosInt.at(2), false);
            }

            // the waiting time value stored in the data file in microseconds
            usleep(clicksInfosInt.at(3));
        }
    }

    return 0;
}