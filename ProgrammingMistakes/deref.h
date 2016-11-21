#ifndef __DEREF__
#define __DEREF__
#include <map>
namespace Test1 {
    struct Node {
        int data;
        Node(int n):data(n) {}
    };
    class UpdatableMap {
        std::map<int, Node *> holes;
    public:    
        void Add(int n, int val) {
            auto it = holes.find(n); 
            if (it != holes.end()) {
                delete it->second;
                it->second = new Node(val);
            } else {
                holes[n] = new Node(n);
            }
        }
        void Remove(int n) {
            delete  holes[n];
        }
        void RemoveFixed(int n) {
            if (holes[n]) {
                delete  holes[n];
                holes[n] = NULL;
            }
        }
        ~UpdatableMap()  {
            for(auto it = holes.begin(); it!= holes.end(); it++)
                delete it->second;
            holes.erase(holes.begin(),holes.end());
        }
    };
    int test(bool bFixed) {
        UpdatableMap umap;
        umap.Add(1, 10);
        umap.Add(2, 20);
        umap.Add(3, 30);
        if (bFixed)
            umap.RemoveFixed(1);
        else
            umap.Remove(1);
        return 0;
    };
};
#endif