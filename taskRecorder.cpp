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
            printf("%s\n","Click gauche");

            if (GetCursorPos(&point)) {
                cout << point.x << "," << point.y << "\n";
                xPos.push_back(point.x);
                yPos.push_back(point.y);
                clickedKey.push_back(2);

                timeStampCalculated = generateTimeStampInMicroSeconds() - timeStampInitial;
                std::cout << timeStampCalculated << "\n";
                timeStampInitial = generateTimeStampInMicroSeconds();

                breaks.push_back(timeStampCalculated);
            }
        } else if (keyPressed(VK_RBUTTON)){
            printf("%s\n","Click droit");

            if (GetCursorPos(&point)) {
                cout << point.x << "," << point.y << "\n";
                xPos.push_back(point.x);
                yPos.push_back(point.y);
                clickedKey.push_back(1);

                timeStampCalculated = generateTimeStampInMicroSeconds() - timeStampInitial;
                std::cout << timeStampCalculated << "\n";
                timeStampInitial = generateTimeStampInMicroSeconds();

                breaks.push_back(timeStampCalculated);
            }

        } else if (keyPressed(VK_MBUTTON)){
            printf("%s\n","Click molette");

            if (GetCursorPos(&point)) {
                cout << point.x << "," << point.y << "\n";
                xPos.push_back(point.x);
                yPos.push_back(point.y);
                clickedKey.push_back(3);

                timeStampCalculated = generateTimeStampInMicroSeconds() - timeStampInitial;
                std::cout << timeStampCalculated << "\n";
                timeStampInitial = generateTimeStampInMicroSeconds();

                breaks.push_back(timeStampCalculated);
            }

        } else if (keyPressed(VK_RSHIFT)){
            string final;

            for(int v = 0; v < clickedKey.size(); v++){
                string x = to_string(xPos[v]);
                string y = to_string(yPos[v]);
                string click = to_string(clickedKey[v]);
                string time = to_string(breaks[v]);
                string details = click + "," + x + "," + y + "," + time + ";";

                final.append(details);
            }

            final = final.substr(0, final.size()-1);

            updateData("|", true);
            updateData(taskName + ";", true);
            updateData(final, true);

            break;
        }
    }

    return 1;
}
