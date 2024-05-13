#include <iostream>

#include <vector>
#include <exception>

using namespace std;

class OpenFileException : public exception
{
    virtual const char* what() const throw()
    {
        return "I was not able to open file";
    }
} openFileException;

class ProcessFileException : public exception
{
    virtual const char* what() const throw()
    {
        return "My file is not open";
    }
} processFileException;


bool openFile()
{
    //throw openFileException;

    return true; // 1
    //return false; // 0
    //throw false;
}

bool processFile()
{
    //return true; // 1
    //return false; // 0
    throw processFileException;
}

int doSomething()
{
    try
    {
        if(!openFile())
        {
            throw "Error opening file";
        }
        std::cout << "Beginn ProcessFile" << std::endl;
        processFile();
    }
    catch (exception &ex){
        std::cout << "throw ex.what()" << std::endl;
        throw ex.what();
    }
    catch (const bool value){
        std::cout << "throw -1" << std::endl;
        throw -1;
    }
    catch (const char* msg){
        std::cout << "throw msg" << std::endl;
        throw msg;
    }


    // I am happy, all works
    return 0;
}

int main()
{
    try
    {
        doSomething();
    }
    catch (const int code)
    {
        cerr << "doSomething() did not work. Code: " << code << endl;
        return -1;
    }
    catch (const char* msg)
    {
        cerr << "doSomething(): did not work because: " << msg << endl;
        return -2;
    }
    catch (...)
    {
        cerr << "Unhandled exception" << endl;
        return -3;
    }

    cout << "doSomething() runs, yay! " << endl;

    return 0;
}
