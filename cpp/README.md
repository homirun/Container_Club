# APIとのやり取り

testMain.cpp -> テストコード

ApiAccess.cpp -> メインコード

BUILD:

    g++ -lcurl ApiAccess.cpp testMain.cpp json11/json11.cpp -fno-rtti -fno-exceptions -O -std=c++11
