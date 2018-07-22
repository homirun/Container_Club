#include <iostream>
#include <curl/curl.h>
#include <string>
#include <map>
#include "json11/json11.hpp"


using namespace std;
using namespace json11;

class ApiAccess{
private:
    string BASE_URL = "http://52.243.60.129:5000/api/score";
public:
    string result;

    int postScore(string usrname, int score){
        CURL *curl;
        CURLcode res;
        curl = curl_easy_init();

        if(curl == NULL){
            cout << "initError" << endl;
            return 1;
        }

        string postUrl = BASE_URL + "?usrname=" + usrname + "&score=" + to_string(score);
        curl_easy_setopt(curl, CURLOPT_URL, postUrl.c_str());

        // ここでexcute
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        return 0;
    }

    map<string, int> getScore(){
        string chunk;
        CURL *curl;
        CURLcode res;
        curl = curl_easy_init();

        string getUrl = BASE_URL + "/list";

        curl_easy_setopt(curl, CURLOPT_URL, getUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, ApiAccess::curlWriterWrapper);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);
        // ここでリクエストを投げる
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        return parseJson(chunk);;
    }

    /**
        コールバックメソッド
        C++の仕様でstaticメソッドでないとコールバックメソッドにできないのでstaticメソッドをwrapperにしている
    **/
    static void curlWriterWrapper(void *contents, size_t size, size_t nmemb, void *userp,void *self) {
        static_cast<ApiAccess*>(self) -> curlWriter(contents, size, nmemb, userp);
    }

    size_t curlWriter(void *contents, size_t size, size_t nmemb, void *userp){
        ((string*)userp) -> append((char*)contents, size * nmemb);
        return size * nmemb;
    }

    // JsonParse
    map<string, int> parseJson(string jsonObj){
        string err;
        map<string, int> mp;
        Json json = Json::parse(jsonObj, err);
        for(auto &obj : json.array_items()){
            mp[obj["usrname"].string_value()] = obj["score"].int_value();
        }
        return mp;
    }


};


