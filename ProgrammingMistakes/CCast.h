#include <iostream>
namespace Test5 {
    struct IBase {
        virtual void Display() = 0;
    };
    class Foo: public IBase {
        int n;
    public:
        Foo():n(1){};
        virtual void Display() {
            std::cout <<"Within Foo with n = "<<n<<std::endl;
        }
    };
    class Bar: public IBase {
        int n;
    public:
        Bar():n(2){};
        virtual void Display() {
            std::cout <<"Within Bar with n = "<<n<<std::endl;
        }
    };
    int test(bool bFixed) {
        Foo *pFoo = new Foo();
        IBase *pBase = pFoo;
        Bar *pBar;
        if (bFixed) 
            pBar = dynamic_cast<Bar *>(pBase);
        else
            pBar = (Bar *)pBase;
        if (pBar)
            pBar->Display();
        else
            std::cout << "Invalid Cast"<<std::endl;
        return 0;
    }
}
