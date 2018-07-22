#include <iostream>
#include "ApiAccess.cpp"

//** APIAccess.cpp TEST MAIN Method **//

int main(void){
    ApiAccess api;
    //api.postScore("chino", 300);
    string result = api.getScore();
    cout << "score: " << result << endl;
    return 0;
}