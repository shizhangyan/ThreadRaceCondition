// ThreadRaceCondition.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <thread>
using namespace std;
class Wallet
{
    int mMoney;
public:
    Wallet() : mMoney(0){}
    int getMoney() { return mMoney; }
    void addMoney(int money) {
        for (int i = 0; i < money; ++i)
        {
            mMoney++;
        }
    }
};
int testMultithreadWallet()
{
    Wallet walletObject;
    vector<thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.push_back(thread(&Wallet::addMoney, &walletObject, 1000));
    }
    for (int i = 0; i < threads.size(); i++) {
        threads.at(i).join();
    }
    return walletObject.getMoney();
}
int main()
{
    int val = 0;
    for (int k = 0; k < 1000; k++) {
        if ((val = testMultithreadWallet()) != 5000) {
            cout << "Error at count = " << k << " Money in Wallet = " << val << endl;
        }
        //else {
        //    cout << "Money in Wallet = " << val << endl;
        //}
    }

    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
