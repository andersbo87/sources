//
//  main.cpp
//  binSearchTree
//
//  Created by Anders Bolt-Evensen on 25/02/15.
//  Copyright (c) 2015 Anders Bolt-Evensen. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <exception>
#include <sys/timeb.h>
#include <sys/time.h>
using namespace std;
const char *prog_name;
class nullptrexception: public exception
{
    virtual const char* what() const throw()
    {
        return "There seems to be a null pointer somewhere.\n";
    }
} nullptrexception;
class Node
{
    int key;
    Node *left;
    Node *right;
    Node *parent;
public:
    Node(){
        key=0x0;
        left=0x0;
        right=0x0;
        parent=0x0;
    }
    void setKey(int key)
    {
        this->key = key;
        //key = this->key; //fremprovoserer en SIGSEGV.
    }
    void setLeft(Node *left){
        this->left = left;
    }
    void setRight(Node *right){
        this->right = right;
    }
    void setParent(Node *parent){
        this->parent = parent;
    }
    int getKey()
    {
        if(key){
            return key;
        }
        else
        throw runtime_error("There is an error.");
        //return key;
    }
    Node* getLeft()
    {
        //if(left != 0x0){
        //    return left;
        //}
        return left;
    }
    Node *getRight()
    {
        return right;
    }
    Node *getParent(){
        return parent;
    }
};

class binSearchTree
{
    Node* root;
public:
    binSearchTree()
    {
        root = 0x0;
    }
    ~binSearchTree(){
        freeNode(root);
    }
    Node *getRoot()
    {
        if(root != 0x0)
            return root;
        else
        return 0x0;
    }
    Node *setRoot(int val){
        root->setKey(val);
        return root;
    }
    void addNode(int key)
    {
        if(root == NULL){
            cout << "Legg til rotnode … " << key << endl;
            Node *n = new Node();
            n->setKey(key);
            root = n;
        }
        else{
            cout << "Legg til en annen node … " << key << endl;
            addNode(key, root);
        }
    }
    /*void treeInsert(binSearchTree *T, Node* z)
    {
        Node *y = 0x0;
        Node *x = T->root;
        while(x != 0x0){
            y = x;
            if(z->getKey() < x->getKey()){
                x = x->getLeft();
            }
            else
                x = x->getRight();
        }
        z->setParent(y);
    }*/
    Node *findNode(int key, Node* node)
    {
        if(!node)
        {
            string str = "A node with the key ";
            str += std::to_string(key);
            str += " does not exist.\n";
            throw runtime_error(str);
        }
        else if(node->getKey() == key){
            return node;
        }
        else if(key <= node->getKey()){
            return findNode(key,node->getLeft());
        }
        else if(key > node->getKey()){
            return findNode(key,node->getRight());
        }
        else
            return 0x0;
    }
    void preorderTraversal(Node* node)
    {
        if(node){
            fprintf(stdout, "%d ", node->getKey());
            preorderTraversal(node->getLeft());
            preorderTraversal(node->getRight());
        }
    }
    void inorderTraversal(Node* node)
    {
      fprintf(stdout, "(");
      if(node->getLeft())
      {
	inorderTraversal(node->getLeft());
	fprintf(stdout, " ");
      }
      fprintf(stdout, "(%d)", node->getKey());
      if(node->getRight()){
	fprintf(stdout, " ");
	inorderTraversal(node->getRight());
      }
      fprintf(stdout, ")");
    }
    void postorderTraversal(Node *node)
    {
        if(node){
            postorderTraversal(node->getLeft());
            postorderTraversal(node->getRight());
            fprintf(stdout, "%d ", node->getKey());
        }
    }
  /*void walk(Node* node){
        if(node){
            cout << node->getKey() << " ";
            walk(node->getLeft());
            walk(node->getRight());
        }
	}*/
    void deleteNode(int key)
    {
        fprintf(stdout, "Fjerner noden med nøkkel %d (hvis den finnes, da)…\n", key);
        Node *thisKey = findNode(key, root); // tilsvarer z i pseudokoden
        // Hvis z ikke har noen barn:
        if(!thisKey->getLeft() && !thisKey->getRight()){
            if(thisKey->getKey() > thisKey->getParent()->getKey()){
                thisKey->getParent()->setRight(0x0);
            }
            else{
                thisKey->getParent()->setLeft(0x0);
            }
            delete thisKey;
        }
        // Hvis z kun har ett barn, så fjerner vi denne og erstatter den med barnet.
        if(thisKey->getLeft() == 0x0 && thisKey->getRight() != 0x0){
            if(thisKey->getKey() > thisKey->getParent()->getKey()){
                thisKey->getParent()->setRight(thisKey->getRight());
            }
            else{
                thisKey->getParent()->setLeft(thisKey->getRight());
            }
            delete thisKey;
        }
        if(thisKey->getLeft() && !thisKey->getRight()){
            if(thisKey->getKey() > thisKey->getParent()->getKey()){
                thisKey->getParent()->setRight(thisKey->getLeft());
            }
            else{
                thisKey->getParent()->setLeft(thisKey->getLeft());
            }
            delete thisKey;
        }
        /*
         Hvis z har 2 barn, finner vi forgjengeren (eller etterfølgeren),
         fjerner forgjengeren/etterfølgeren og erstatter noden som skal fjernes
         med forgjengeren eller etterfølgeren.
         */
        if(thisKey->getLeft() && thisKey->getRight()){
            Node *sub = predecessor(thisKey, thisKey->getKey());
            if(!sub){
                sub = successor(thisKey, thisKey->getKey());
            }
            if(sub->getParent()->getKey() <= sub->getKey()){
                sub->getParent()->setRight(sub->getRight());
            }
            else{
                sub->getParent()->setLeft(sub->getLeft());
            }
            thisKey->setKey(sub->getKey());
            delete sub;
        }
    }
    Node* treeMinimum(Node* node)
    {
        if(!node)
        {
            throw std::runtime_error("The node that was sent as a parameter to treeMinimum is null.\n");
        }
        if(node){
            while(node->getLeft()){
                node = node->getLeft();
            }
        }
        return node;
    }
    Node* treeMaximum(Node* node)
    {
        if(node == 0x0)
        {
            throw std::runtime_error("The node that was sent as a parameter to treeMax is null.\n");
        }
        else
        {
            while(node->getRight() != 0x0){
                node = node->getRight();
            }
        }
        return node;
    }
    Node* successor(Node* anode, int key)
    {
        Node* thisKey = findNode(key, anode);
        if(thisKey){
            if(thisKey->getRight())
                return thisKey->getRight();
            else{
                throw runtime_error("thisKey->getRight() er null.");
            }
        }
        else{
            string str = "A node with the key ";
            str += std::to_string(key);
            str += " does not exist.\n";
            throw runtime_error(str);
        }
    }
    Node* predecessor(Node* parent, int key)
    {
        Node *thisKey = findNode(key, parent);
        if(thisKey){
            if(thisKey->getLeft())
                return treeMaximum(thisKey->getLeft());
            else{
                throw runtime_error("thisKey->getLeft() er null.");
            }
        }
        else{
            string str = "A node with the key ";
            str += std::to_string(key);
            str += " does not exist.\n";
            throw runtime_error(str);
        }
        /*if(parent->getLeft() != 0x0){
         return treeMinimum(parent->getLeft());
         }
         node *y = parent->getParent();
         while(y != 0x0 && parent == y->getLeft()){
         parent = y;
         y = y->getParent();
         }
         return y;*/
    }
private:
    void freeNode(Node* leaf)
    {
        if(leaf != 0x0){
            freeNode(leaf->getLeft());
            freeNode(leaf->getRight());
            delete leaf;
        }
    }
    //privat driverfunksjon for addNode.
    void addNode(int key, Node* leaf)
    {
        if(key <= leaf->getKey()){
            if(leaf->getLeft() != 0x0){
                addNode(key, leaf->getLeft());
            }
            else{
                Node *n = new Node();
                n->setKey(key);
                n->setParent(leaf);
                leaf->setLeft(n);
            }
        }
        else{
            if(leaf->getRight() != 0x0){
                addNode(key, leaf->getRight());
            }
            else{
                Node *n = new Node();
                n->setKey(key);
                n->setParent(leaf);
                leaf->setRight(n);
            }
        }
    }
}; // end of class binSearchTree

class binSearchTreeIO
{
private:
    string *minStreng;
public:
    binSearchTreeIO()
    {
        minStreng = 0x0; //initialiserer minStreng...
    }
    ~binSearchTreeIO()
    {
        
    }
public:
    string *readArray(const char *filename)
    {
        /*Les fra fil*/
        ifstream in(filename);
        if(!in)
        {
            fprintf(stderr, "%s: Kan ikke lese filen %s (error code %d).\n", prog_name, filename, EINVAL);
            exit(1); // avslutter programmet istedenfor å returnere en tom tabell.
        }
        string str2 = " ";
        stringstream buffer;
        buffer << in.rdbuf();
        string test = buffer.str();
        
        size_t pos1 = 0;
        size_t pos2;
        size_t str_pos1 = 0;// str_pos2;
        int count = 0;
        while((str_pos1 = test.find(str2, str_pos1)) < test.length())
        {
            str_pos1 += str2.length();
            count++;
        }
        static string *str; str = new string[count];
        //fprintf(stdout, "Lengden på tabellen: %d\n", count);
        if(count == 0)
        {
            fprintf(stderr, "%s: Lengden på tabellen er for liten. Lengden på tabellen må være >= 0.\n", prog_name);
            exit(1); // avlsutter programmet istedenfor å returnere en tom tabell.
        }
        for(int x = 0; x < count; x++){
            pos2 = test.find(" ", pos1);
            str[x] = test.substr(pos1, (pos2-pos1));
            //if(x != 0){
            //    long l = strtol(str[x].c_str(), NULL, 10);
            //}
            pos1 = pos2+1;
        }
        minStreng = str;
        return minStreng;
    }
};

/*
 Funksjoner som "fanger" ulike UNIX-signaler. 
 Merk at SIGINFO ikke støttes av Linux, da SIGINFO 
 kun fungerer på BSD-baserte
 systemer som f. eks. OS X, FreeBSD, OpenBSD og NetBSD.
 */

void catch_sigsegv(int sig_num)
{
    signal(SIGSEGV, catch_sigsegv);
    //fprintf(stderr, "It seems like there has been a segmentation violation. Exiting…\n");
    //throw nullptrexception;
    signal(sig_num, SIG_DFL);
    //kill(getpid(), sig_num);
}

void catch_siginfo(int sig_num)
{
    #ifdef SIGINFO
    signal(SIGINT, catch_siginfo);
    fprintf(stdout, "Creating, inserting into, traversing and deleting from a BST.\n");
    #endif
}


int main(int argc, char **argv){
    signal(SIGSEGV, catch_sigsegv);
#ifdef SIGINFO
    signal(SIGINFO, catch_siginfo);
#endif
    prog_name = "binSearchTree";
    if(argc < 2 || argc > 3)
    {
        fprintf(stderr, "bruk:\t%s file1\n\t%s file1 file2\n", prog_name,prog_name);
        return 1;
    }
    try
    {
        struct timeval totStart, totEnd, insStart, insEnd, searchStart, searchEnd, delStart, delEnd;
        long mtime_ins, mtime_search, mtime_del, totTime;
        gettimeofday(&totStart, NULL);
        binSearchTree* tree = new binSearchTree(); // Add nodes
        binSearchTreeIO *bio = new binSearchTreeIO();
        //int startTime = getMilliCount();
        string *str;
        str = bio->readArray(argv[1]);
        int instot = stoi(str[0]), i;
        
        //int insertionStartTime = getMilliCount();
        gettimeofday(&insStart, NULL);
        for(i = 1; i <= instot; i++)
        {
            tree->addNode(stoi(str[i]));
        }
        gettimeofday(&insEnd, NULL);
        //int elapsedInsertionTime = getMilliSpan(insertionStartTime);
        // Traverse the tree
        fprintf(stdout, "Traverserer inorder…\n");
        tree->inorderTraversal(tree->getRoot());
        fprintf(stdout, "\nTraverserer preorder…\n");
        tree->preorderTraversal(tree->getRoot());
        fprintf(stdout, "\n");
        // Find nodes
        //int searchStartTime = getMilliCount();
        gettimeofday(&searchStart, NULL);
        if ( tree->findNode(5, tree->getRoot()) )
        {
            //cout << "Node 500 found" << endl;
            fprintf(stdout, "Node 5 ble funnet\n");
        }
        else
            cout << "Node 5 not found" << endl;
        gettimeofday(&searchEnd, NULL);
        //int elapsedSearchTime = getMilliSpan(searchStartTime);
        //fprintf(stdout, "Søk etter node 5 tok %d millisekunder.\n", elapsedSearchTime);
        if ( tree->findNode(6, tree->getRoot()) )
            cout << "Node 6 found" << endl;
        else
            cout << "Node 6 not found" << endl;
        // Min & Max
        cout << "Min=" << tree->treeMinimum(tree->getRoot())->getKey() << endl;
        cout << "Max=" << tree->treeMaximum(tree->getRoot())->getKey() << endl;
        // Successor and Predecessor
        //cout << "Successor to 300=" << tree->successor(tree->getRoot(),4)->getKey() << endl;
        //cout << "Predecessor to 300=" << tree->predecessor(tree->getRoot(),3000)->getKey() << endl;
        if(argc == 3)
        {
            // Delete a node
            int i, del_tot;
            string *del_str;
            del_str = bio->readArray(argv[2]);
            del_tot = stoi(del_str[0]);
            //int deleteStartTime = getMilliCount();
            gettimeofday(&delStart, NULL);
            for(i=1; i<=del_tot;i++)
            {
                tree->deleteNode(stoi(del_str[i]));
            }
            gettimeofday(&delEnd, NULL);
            mtime_ins = searchEnd.tv_usec - searchStart.tv_usec;
            mtime_search = searchEnd.tv_usec - searchStart.tv_usec;
            mtime_del = delEnd.tv_usec - delStart.tv_usec;
            //int elapsedDeleteTime=getMilliSpan(deleteStartTime);
            // Traverse the tree
            fprintf(stdout, "Traversering etter sletting: ");
            tree->inorderTraversal(tree->getRoot()); cout << endl;
            delete tree;
            //int stopTime = getMilliSpan(startTime);
            gettimeofday(&totEnd, NULL);
            totTime = totEnd.tv_sec - totStart.tv_sec;
            fprintf(stdout,
                    "Programmet brukte %ld sekunder på hele kjøringen.\n"
                    "Programmet brukte %ld mikrosekunder på å sette inn %d noder\n"
                    "Programmet brukte %ld mikrosekunder på å søke etter node 5\n"
                    "Programmet brukte %ld mikrosekunder på å slette %d noder\n", totTime, mtime_ins, instot, mtime_search, mtime_del, del_tot);
            return 0;
        }
        delete tree;
        //int stopTime = getMilliSpan(startTime);
        mtime_ins = insEnd.tv_usec - insStart.tv_usec;
        mtime_search = searchEnd.tv_usec - searchStart.tv_usec;
        gettimeofday(&totEnd, NULL);
        totTime = totEnd.tv_sec - totStart.tv_sec;
        fprintf(stdout,
                "Programmet brukte %ld sekunder på hele runddansen.\n"
                "Programmet brukte %ld mikrosekunder på å sette inn %d noder\n"
                "Programmet brukte %ld mikrosekunder på å søke etter node 5\n", totTime, mtime_ins, instot, mtime_search);
        return 0;
    } catch (std::exception &e) {
        fprintf(stderr, "Something is wrong: %s", e.what());
        return 1;
    }

    
}
