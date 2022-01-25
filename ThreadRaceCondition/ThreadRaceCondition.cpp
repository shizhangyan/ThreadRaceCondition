// ThreadRaceCondition.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
using namespace std;
class Wallet
{
    int mMoney;
    mutex mMutex;
public:
    Wallet() : mMoney(0){}
    int getMoney() { return mMoney; }
    void addMoney(int money) {
 //       mutex.lock();
        lock_guard<mutex> lockGuard(mMutex);
        //IN constructor it locks the mutex
        for (int i = 0; i < money; ++i)
        {
            // If some exception occurs at this point
            // then destructor of lockGuard will be called
            // due to stack unwinding.
            mMoney++;
        }
 //       mutex.unlock();
        // Once function exits, then destructor of lockGuard Object will be called.
        // In destructor it unlocks the mutex
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
