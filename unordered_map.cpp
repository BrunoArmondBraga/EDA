#include <iostream>
#include <map>

using namespace std;

int main() {
    map<int, int> mymap;

    mymap[2] = 3;
    mymap[-1] = 7;
    mymap[1] = 20;
    mymap[40] = 12;
    mymap[0] = 10;
    mymap[200] = 6;

    for (const auto& pair : mymap) {
        cout << "Key = " << pair.first << " Value = " << pair.second << endl;
    }

    return 0;
}
