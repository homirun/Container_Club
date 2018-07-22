#include <iostream>
#include "ApiAccess.cpp"
#include <vector>

//** APIAccess.cpp TEST MAIN Method **//

int main(void){
    ApiAccess api;
    //api.postScore("chino", 300);
    vector<pair<string, int>> result = api.getScore();
    for(auto vc : result) {
        cout << vc.first << " " << vc.second << endl;
    }
    return 0;
}