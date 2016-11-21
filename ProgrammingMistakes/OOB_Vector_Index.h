#pragma once
#include <map>
#include <vector>
#include <iostream>
#include <functional>
namespace Test2 {
    template<typename _Ty, typename BinOP>
    class Reduce {
    public:
        _Ty Run(std::vector<_Ty>  expr) {
            auto it = expr.begin();
            auto result =*it;
            for(it++; it != expr.end();it++) {
                result = BinOP()(result, *it);
            }
            return result;
        }
        _Ty RunFixed(std::vector<_Ty>  expr) {
            if (expr.size() < 1) return 0;
            auto it = expr.begin();
            auto result =*it;
            for(it++; it != expr.end();it++) {
                result = BinOP()(result, *it);
            }
            return result;
        }
        _Ty (Reduce::*pRun)(std::vector<_Ty>  expr);
    };
    int test(bool bFixed) {   
        Reduce<double, std::plus<double>> objReduce;
        objReduce.pRun = bFixed?&Reduce<double, std::plus<double>>::RunFixed:&Reduce<double, std::plus<double>>::Run;
        double arr[] = {1.0,2.0,3.0,4.0};
        std::vector<double>  expr(arr , arr + sizeof(arr)/ sizeof(arr[0]));    
        std::cout<<(objReduce.*(objReduce.pRun))(expr)<<std::endl;
        expr.erase(expr.begin(), expr.end());
        std::cout<<(objReduce.*(objReduce.pRun))(expr)<<std::endl;
        return 0;
    }
   
};
