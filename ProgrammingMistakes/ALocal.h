#include <cstring>
#include <iostream>
namespace Test6 {
    char *GetExt(const char *pFilename) {
        char ext[4];
        const char *pch = strrchr(pFilename,'.');
        strncpy(ext, pch + 1, sizeof(ext) / sizeof(ext[0]));
        return ext;
    };
    struct GetExtFixed {
        const char *mFilename;
        char ext[4];
        GetExtFixed(const char *pFilename):mFilename(pFilename) {
            const char *pch = strrchr(pFilename,'.');
            strncpy(ext, pch + 1, sizeof(ext) / sizeof(ext[0]) - 1);
            ext[sizeof(ext) - 1] = 0;
        };
        char * operator () (){
            return ext;
        }
    };
    int test(bool bFixed) {
        if (bFixed)
            std::cout<<"Extension of filename.mobi is "<<GetExtFixed("filename.mobi")()<<std::endl;
        else
            std::cout<<"Extension of filename.mobi is "<<GetExt("filename.mobi")<<std::endl;
        return 0;
    }
}