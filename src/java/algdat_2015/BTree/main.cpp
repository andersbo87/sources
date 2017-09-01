/* 
 * File:   main.cpp
 * Author: andersbo
 *
 * Created on May 22, 2015, 3:17 PM
 */

#include <cstdlib>

using namespace std;
class Node
{
private:
    Node *parent; 
    bool leaf;
    int n, key;
public:
    Node()
    {
    
    }
    ~Node()
    {
           
    }
    void setKey(int newKey){
        key = newKey;
    }
    void setParent(Node *newParent){
        parent = newParent;
    }
    void setLeaf(Node *newLeaf)
    {
        leaf = newLeaf;
    }
    void setN(Node *newN){
        next = newNext;
    }
    Node *getParent()
    {
        return parent;
    }
    bool isLeaf()
    {
        if(leaf == true)
            return true;
        else
            return false;
    }
    int getN(){
        return next;
    }
    int getKey()
    {
        return key;
    }
};
class BTree
{
public:
    int treeSearch(Node *x, int k)
    {
        int i = 0;
        while(i<=x->getN() && k > x->getKey()){
            i = i + 1;
        }
        if(i <= x->getN() k == x->getKey())
            return(x,i);
        
    }    
};
/*
 * 
 */
int main(int argc, char** argv) {

    return 0;
}

