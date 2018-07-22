#include <iostream>
#include "ApiAccess.cpp"

//** APIAccess.cpp TEST MAIN Method **//

int main(void){
    ApiAccess api;
    //api.postScore("chino", 300);
    map<string, int> result = api.getScore();
    for(auto mp : result) {
        cout << mp.first << " " << mp.second << endl;
    }
    return 0;
}