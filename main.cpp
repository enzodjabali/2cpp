#include <iostream>
#include <windows.h>
#include <conio.h>
#include <unistd.h>

#include <fstream>
#include <string>
#include <vector>

#include <sstream>


using namespace std;

int keyPressed(int key){
    return (GetAsyncKeyState(key) & 0x8000 != 0);
}
POINT point;

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

    for (int i = 0; i < resultsFromFileVector.size(); i++) {
        std::cout << resultsFromFileVector.at(i) << '\n';
    }


    return 0;
}

int displayMainMenu() {

    // display tasks

    // ask for action : execute a task / create a task / delete a task / duplicate a task / schedule a task

    return 0;
}


int main(){
    ReadFile();

    //recordSchema();

    return 0;
}
