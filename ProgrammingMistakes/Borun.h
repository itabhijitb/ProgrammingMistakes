#pragma once
#include <cstdio>
#include <cstring>
#include <iostream>
namespace Test4 {

struct GetExt {
    const char *mFilename;
    char ext[4];
    GetExt(const char *pFilename):mFilename(pFilename) {
        const char *pch = strrchr(pFilename,'.');
        strcpy(ext,pch + 1);
        //strncpy(ext, pch + 1, sizeof(ext) / sizeof(ext[0]));
    };
    char * operator () (){
        return ext;
    }
};
struct GetExtFixed {
    const char *mFilename;
    char ext[4];
    GetExtFixed(const char *pFilename):mFilename(pFilename) {
        const char *pch = strrchr(pFilename,'.');
        //strcpy(ext,pch + 1);
        strncpy(ext, pch + 1, sizeof(ext) / sizeof(ext[0]) - 1);
        ext[sizeof(ext) - 1] = 0;
    };
    char * operator () (){
        return ext;
    }
};
int test(bool bFixed) {
    std::cout<<((bFixed)?GetExtFixed("Document.mobi")():GetExt("Document.mobi")())<<std::endl;
    return 0;
}
}