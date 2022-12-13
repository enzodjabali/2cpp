#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <chrono>

using namespace std;

uint64_t generateTimeStampInMicroSeconds(){
    using namespace std::chrono;
    return duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
}


int keyPressed(int key){
    return (GetAsyncKeyState(key) & 0x8000 != 0);
}


int taskRecord(){
    string taskName;
    std::cout << "Type a name: ";
    std::cin >> taskName;
    std::cout << '\n';

    std::vector<int> xPos;
    std::vector<int> yPos;
    std::vector<int> clickedKey;
    std::vector<int> breaks;

    long long timeStampInitial;
    long long timeStampCalculated;
    timeStampInitial = generateTimeStampInMicroSeconds();

    cout<<"We will now record your path, press right shift to end"<<endl;

    while(1){
        if(keyPressed(VK_LBUTTON)){
            if (GetCursorPos(&point)) {
                cout << "Left click on x: " << point.x << " and y: " << point.y << "\n";

                xPos.push_back(point.x);
                yPos.push_back(point.y);
                clickedKey.push_back(1);

                timeStampCalculated = generateTimeStampInMicroSeconds() - timeStampInitial;
                timeStampInitial = generateTimeStampInMicroSeconds();

                breaks.push_back(timeStampCalculated);
            }
        } else if (keyPressed(VK_MBUTTON)){
            if (GetCursorPos(&point)) {
                cout << "Middle click on x: " << point.x << " and y: " << point.y << "\n";

                xPos.push_back(point.x);
                yPos.push_back(point.y);
                clickedKey.push_back(2);

                timeStampCalculated = generateTimeStampInMicroSeconds() - timeStampInitial;
                timeStampInitial = generateTimeStampInMicroSeconds();

                breaks.push_back(timeStampCalculated);
            }
        } else if (keyPressed(VK_RBUTTON)){
            if (GetCursorPos(&point)) {
                cout << "Right click on x: " << point.x << " and y: " << point.y << "\n";

                xPos.push_back(point.x);
                yPos.push_back(point.y);
                clickedKey.push_back(3);

                timeStampCalculated = generateTimeStampInMicroSeconds() - timeStampInitial;
                timeStampInitial = generateTimeStampInMicroSeconds();

                breaks.push_back(timeStampCalculated);
            }
        } else if (keyPressed(VK_RSHIFT)){
            string taskSchema;

            for(int v = 0; v < clickedKey.size(); v++){
                string x = to_string(xPos[v]);
                string y = to_string(yPos[v]);
                string click = to_string(clickedKey[v]);
                string time = to_string(breaks[v]);
                string details = click + "," + x + "," + y + "," + time + ";";

                taskSchema.append(details);
            }

            taskSchema = taskSchema.substr(0, taskSchema.size()-1);

            updateData("|", true);
            updateData(taskName + ";", true);
            updateData(taskSchema, true);

            break;
        }
    }

    return 1;
}
