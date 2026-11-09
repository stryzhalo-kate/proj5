#include "work.h"
#include <iostream>
#include <syncstream>
#include <thread>
#include <future>
#include <chrono>

using namespace std;

void slow(const string &name)
{
    this_thread::sleep_for(7s);
    osyncstream(cout) << name << endl;
}

void quick(const string &name)
{
    this_thread::sleep_for(1s);
    osyncstream(cout) << name << endl;
}
void work()
{
    auto start = chrono::high_resolution_clock::now();
    auto c2_d2 = async(launch::async, []()
                       {
                           quick("C2");
                           quick("D2");
                       });
    slow("A");
    slow("B");
    quick("C1");
    c2_d2.get();
    quick("D1");
    quick("F");

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "Work took " << elapsed.count() << " seconds." << endl;
    cout << "Work is done!" << endl;
}
