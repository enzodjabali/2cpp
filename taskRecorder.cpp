#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int keyPressed(int key){
    return (GetAsyncKeyState(key) & 0x8000 != 0);
}

int taskRecord(){
    string taskName;
    std::cout << "Type a name: ";
    std::cin >> taskName;
    std::cout << '\n';

    std::vector<int> xpos;
    std::vector<int> ypos;
    std::vector<int> rorl;
    std::vector<int> tim;

    cout<<"We will now record your path, press right shift to end"<<endl;

    while(1){
        if(keyPressed(VK_LBUTTON)){
            printf("%s\n","Click gauche");

            if (GetCursorPos(&point)) {
                cout << point.x << "," << point.y << "\n";
                xpos.push_back(point.x);
                ypos.push_back(point.y);
                rorl.push_back(2);
            }
        } else if (keyPressed(VK_RBUTTON)){
            printf("%s\n","Click droit");

            if (GetCursorPos(&point)) {
                cout << point.x << "," << point.y << "\n";
                xpos.push_back(point.x);
                ypos.push_back(point.y);
                rorl.push_back(1);
            }

        } else if (keyPressed(VK_MBUTTON)){
            printf("%s\n","Click molette");

            if (GetCursorPos(&point)) {
                cout << point.x << "," << point.y << "\n";
                xpos.push_back(point.x);
                ypos.push_back(point.y);
                rorl.push_back(3);
            }

        } else if (keyPressed(VK_RSHIFT)){
            cout <<"Vector 'xpos' : ";
            int h;

            while(h < xpos.size()) {
                cout<<xpos[h]<<" ";
                h++;
            }

            cout<<endl;

            cout <<"Vector 'ypos' : ";

            int i;
            while(i < ypos.size()) {
                cout<<ypos[i]<<" ";
                i++;
            }

            cout<<endl;
            cout <<"Vector 'rorl' : ";

            for(int x = 0; x < rorl.size() ; x++){
                cout<<rorl[x]<<" ";

            }

            cout << endl;
            cout << endl;
            printf("%s\n","SHIFT");
            string final;

            for(int v = 0; v < rorl.size(); v++){
                string ex = to_string(xpos[v]);
                string why = to_string(ypos[v]);
                string arel = to_string(rorl[v]);
                string deets = arel + "," + ex + "," + why + ",1000000;";

                final.append(deets);
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
