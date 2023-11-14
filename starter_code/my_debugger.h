#pragma once
#include <cstddef>
#include <fstream>
#include <exception>
#include <iostream>
#include <string>
using namespace std;

#define DEBUG_MODE
#ifdef DEBUG_MODE
    class Logger
    {
    public:
        template<typename... Args>
        static void log(const Args&... args)
        {
            ofstream logfile { msDebugFileName, ios_base::app };
            if (logfile.fail()) {
            cerr << "Unable to open debug file!" << endl;
            return;
            }
        // Use a C++17 unary right fold, see Chapter 26.
        ((logfile << args),...);
        logfile << endl;
        }

    private:
    static const string msDebugFileName;
    };
    const string Logger::msDebugFileName="debugfile.out";

    #define log(...) Logger::log(__func__, "(): ", __VA_ARGS__)
#else
    #define log(...)
#endif