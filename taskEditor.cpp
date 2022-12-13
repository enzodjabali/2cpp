#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::string deleteTask(int chosenTask) {
    // here we need to delete a task

    std::vector<std::string> resultsFromFileVector;
    resultsFromFileVector = getData();
    std::string infoTask;
    std::vector<std::string> resultsInfoTask;

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

int renameTask(std::string deletedTask) {
    std::string newName;
    std::cout << "New name: ";
    std::cin >> newName;
    std::cout << '\n';

    std::vector<std::string> resultsInfoTask;

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

int duplicateTask(int chosenTask) {
    // we're duplicating a task here

    std::vector<std::string> resultsFromFileVector;
    resultsFromFileVector = getData();

    updateData("|", true);
    updateData(resultsFromFileVector.at(chosenTask), true);

    return 0;
}
