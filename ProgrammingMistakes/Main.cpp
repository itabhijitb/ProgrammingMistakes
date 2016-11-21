#include "deref.h"
#include "OOB_Vector_Index.h"
#include "Exp.h"
#include "Borun.h"
#include "CCast.h"
#include "ALocal.h"
#include <iostream>
#include <Windows.h>
using namespace std;
#include <map>
#include <vector>
#define SCREEN_WIDTH  80
std::string& CenterAlign(std::string& st) {
    int size = st.size();
    if (size > SCREEN_WIDTH) return st;
    st = std::string((SCREEN_WIDTH - size) /2 , ' ') + st;
    return st;
}
int menu() {

    std::cout<<std::endl;
    std::cout<<CenterAlign(string("________________________________________________"))<<std::endl;
    std::cout<<CenterAlign(string("|               Choose your Test               |"))<<std::endl;
    std::cout<<CenterAlign(string("|______________________________________________|"))<<std::endl;
    std::cout<<CenterAlign(string("| Faulty Version                               |"))<<std::endl;
    std::cout<<CenterAlign(string("| (1) Double Delete                            |"))<<std::endl;
    std::cout<<CenterAlign(string("| (2) STL Bound Checking                       |"))<<std::endl;
    std::cout<<CenterAlign(string("| (3) Ignoring Exception/ Return               |"))<<std::endl;
    std::cout<<CenterAlign(string("| (4) Buffer Overrun                           |"))<<std::endl;
    std::cout<<CenterAlign(string("| (5) Using C-Cast instead of template Cast    |"))<<std::endl;
    std::cout<<CenterAlign(string("| (6) Return Add/Ref to NULL                   |"))<<std::endl;
    std::cout<<CenterAlign(string("| Fixed Version                                |"))<<std::endl;
    std::cout<<CenterAlign(string("| (7) Double Delete                            |"))<<std::endl;
    std::cout<<CenterAlign(string("| (8) STL Bound Checking                       |"))<<std::endl;
    std::cout<<CenterAlign(string("| (9) Ignoring Exception/ Return               |"))<<std::endl;
    std::cout<<CenterAlign(string("| (a) Buffer Overrun                           |"))<<std::endl;
    std::cout<<CenterAlign(string("| (b) Safe Casting using Template Cast         |"))<<std::endl;
    std::cout<<CenterAlign(string("| (c) Return Add/Ref to NULL                   |"))<<std::endl;
    std::cout<<CenterAlign(string("| (q) Quit                                     |"))<<std::endl;
    std::cout<<CenterAlign(string("|                                              |"))<<std::endl;
    std::cout<<CenterAlign(string("|______________________________________________|"))<<std::endl;
    std::cout<<CenterAlign(string("Select An Option ?"));
    auto option = std::cin.get();
    std::cin.ignore();
    return option;
}
DWORD ExceptionFilter(DWORD excode) {
    switch(excode) {
    case EXCEPTION_ACCESS_VIOLATION:
    case STATUS_STACK_BUFFER_OVERRUN:
        return EXCEPTION_EXECUTE_HANDLER;
        break;
    default:
        return EXCEPTION_CONTINUE_SEARCH;
        break;
    }
}
int main() {
    for(char option = menu(); option != 'q';option = menu()) {
        __try {
            switch(option) {
            case '1':
                Test1::test(false);
                break;
            case '2':
                Test2::test(false);
                break;
            case '3':
                Test3::test(false);
                break;
            case '4':
                Test4::test(false);
                break;
            case '5':
                Test5::test(false);
                break;
            case '6':
                Test6::test(false);
                break;
            case '7':
                Test1::test(true);
                break;
            case '8':
                Test2::test(true);
                break;
            case '9':
                Test3::test(true);
                break;
            case 'a':
                Test4::test(true);
                break;
            case 'b':
                Test5::test(true);
                break;
            case 'c':
                Test6::test(true);
                break;
            }
        } __except(ExceptionFilter(GetExceptionCode()))
        {
            std::cout<<"Your Program has crashed"<<std::endl;
        }
    }
    return 0;
}