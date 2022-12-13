#include <iostream>
#include <windows.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <filesystem>

std::string getCurrentDate() {
    auto end = std::chrono::system_clock::now();

    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::string date = std::ctime(&end_time);

    return date;
}

std::vector<int> convertVectorStringToVectorInt(std::vector<std::string> strings) {
    std::vector<int> ints;
    std::transform(strings.begin(), strings.end(), std::back_inserter(ints), [&](std::string s) {
        return stoi(s);
    });

    return ints;
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
                std::cout << "Right click on x: " << x2 << " and y: " << y2 << "\n";
            } else {
                std::cout << "[PREVIEW] Right click on x: " << x2 << " and y: " << y2 << "\n";
            }
            break;
        case 2:
            if (!isPreview) {
                mouse_event(MOUSEEVENTF_MIDDLEDOWN | MOUSEEVENTF_MIDDLEUP, x2, y2, 0, 0);
                std::cout << "Middle click on x: " << x2 << " and y: " << y2 << "\n";
            } else {
                std::cout << "[PREVIEW] Middle click on x: " << x2 << " and y: " << y2 << "\n";
            }
            break;
        case 3:
            if (!isPreview) {
                mouse_event(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP, x2, y2, 0, 0);
                std::cout << "Left click on x: " << x2 << " and y: " << y2 << "\n";
            } else {
                std::cout << "[PREVIEW] Left click on x: " << x2 << " and y: " << y2 << "\n";
            }
            break;
    }

    return 0;
}

int writeHistory(std::string taskName, std::string date, long executionTime) {
    executionTime = executionTime / 1000000;
    std::string newTaskHistory = "Task: " + taskName + "\nDate: " + date + "Execution time: " + std::to_string(executionTime) + "s\n";

    std::filesystem::path path = std::filesystem::current_path();
    path /= "..\\history.txt";

    std::ofstream historyFile;
    historyFile.open(path, std::ios_base::app);
    historyFile << newTaskHistory;
    historyFile.close();

    return 0;
}

int showHistory() {
    std::filesystem::path path = std::filesystem::current_path();
    path /= "..\\history.txt";

    std::ifstream file(path);
    std::string str;

    int lineCounter = 0;

    while (std::getline(file, str)) {
        std::cout << str << "\n";
        lineCounter++;

        if (lineCounter % 3 == 0) {
            std::cout << "------------------------------\n";
        }
    }

    return 0;
}

int executeTask(int chosenTask, bool isPreview) {
    // getting the date of the execution of the task
    std::string date;
    date = getCurrentDate();

    // the below code will execute the given task's number

    std::vector<std::string> resultsFromFileVector;
    resultsFromFileVector = getData();
    std::string infoTask;
    std::vector<std::string> resultsInfoTask;

    infoTask = resultsFromFileVector.at(chosenTask);
    resultsInfoTask = divideStringIntoArray(infoTask, ";");

    std::cout << resultsInfoTask.at(0) << " is being executed...\n";
    std::vector<std::string> clicksInfos;
    std::vector<int> clicksInfosInt;
    long executionTime = 0;

    for (int i = 0; i < resultsInfoTask.size(); i++) {
        // here we get all elements from a task
        // the first one will be the name of the task [0]
        // the others will be the clicks' infos

        if (i != 0) {
            clicksInfos = divideStringIntoArray(resultsInfoTask.at(i), ",");
            clicksInfosInt = convertVectorStringToVectorInt(clicksInfos);

            executionTime += clicksInfosInt.at(3);

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

    // we need add the task to the history here
    writeHistory(resultsInfoTask.at(0), date, executionTime);

    return 0;
}

int scheduleTask(int chosenTask) {
    // we need to ask the user for how many seconds to wait before starting the chosen task

    int waitingTimeInSeconds;
    std::cout << "How many seconds will the program wait before launching the task: ";
    std::cin >> waitingTimeInSeconds;
    std::cout << '\n';
    std::cout << "The program will wait " << waitingTimeInSeconds << "s before executing the task.\n";

    int waitingTimeInMicroSeconds = waitingTimeInSeconds * 1000000;
    usleep(waitingTimeInMicroSeconds);
    executeTask(chosenTask, false);

    return 0;
}
