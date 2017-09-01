/* 
 * File:   newRBTree.cpp.cpp
 * Author: andersbo
 *
 * Created on April 14, 2015, 1:35 PM
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

using namespace std;

/*
 * 
 */
enum Color { red, black };
const char *prog_name;
class Node
{
private:
    Node *left, *right, *parent;
    long int value = 0;
    Color color;
    
public:
    Node(long int nodeValue)
    {
        color = black;
        value = nodeValue;
    }
    ~Node()
    {
        
    }
    /**
     * Gir noden en ny farge.
     * @param newColor Fargen som skal angis. Fargen kan enten være rød eller svart.
     */
    void setColor(Color newColor)
    {
        color = newColor;
    }
    
    /**
     * Henter nodens verdi.
     * @return value: Nodens verdi.
     */
    long int getValue()
    {
        return value;
    }
    /**
     * Henter nodens nåværende farge.
     * @return color: Nodens nåværende farge, enten rød eller svart.
     */
    Color getColor()
    {
        if(color == red)
            return red;
        else
            return black;
    }
    
    /**
     * Henter nodens venstrebarn.
     * @return left: Nodens venstrebarn.
     */
    Node *getLeft()
    {
        return left;
    }
    /**
     * Henter høyrebarnet til noden.
     * @return right: Nodens høyrebarn.
     */
    Node *getRight()
    {
        return right;
    }
    /**
     * Henter foreldrenoden til noden.
     * @return parent: Nodens foreldrenode.
     */
    Node *getParent()
    {
        return parent;
    }
    /**
     * Angir en ny verdi for noden.
     * @param newValue Nodens nye verdi.
     */
    void setValue(int newValue)
    {
        value = newValue;
    }
    /**
     * Angir et nytt venstrebarn for gjeldende node.
     * @param newLeft Nodens nye venstrebarn.
     */
    void setLeft(Node *newLeft)
    {
        left = newLeft;
    }
    /**
     * Angir et nytt høyrebarn for gjeldende node.
     * @param newRight Nodens nye høyrebarn.
     */
    void setRight(Node *newRight)
    {
        right = newRight;
    }
    /**
     * Angir en ny foreldrenode for den nåværende noden.
     * @param newParent Nodens nye foreldrenode.
     */
    void setParent(Node *newParent)
    {
        parent = newParent;
    }
};

class RBTree
{
    
    
    // Konstruktør
public:
    Node *root;
    Node *nil;
    RBTree()
    {
        nil = new Node(-100000000);
        //nil->setValue(-100000000);
        root = nil;
    }
    
    // Destruktør
    ~RBTree()
    {
        freeNode(root);
        freeNode(nil);
    }
    
private:
    void freeNode(Node* node)
    {
        if(node != 0x0){
            freeNode(node->getLeft());
            freeNode(node->getRight());
            delete node;
        }
    }
    /**
     * Roterer en node mot venstre.
     * @param t Treet det skal roteres i.
     * @param x Noden som skal roteres mot venstre.
     */
    void leftRotate(RBTree *t, Node *x)
    {
        Node *y = x->getRight();                    // sett y
        x->setRight(y->getLeft());                  // bytter om y sitt venstre subtre med det høyre subtreet.
        if(y->getLeft() != t->nil)
            y->getLeft()->setParent(x);
        y->setParent(x->getParent());               // Lenker x sin forelder til y
        if(x->getParent() == t->nil)
            t->root = y;
        else if(x == x->getParent()->getLeft())
            x->getParent()->setLeft(y);
        else
            x->getParent()->setRight(y);
        
        y->setLeft(x);                              // setter x på y sin venstreside.
        x->setParent(y);
    }
    
    /**
     * Roterer en node mot høyre.
     * @param t Treet det skal roteres i.
     * @param x Noden som skal roteres mot høyre.
     */
    void rightRotate(RBTree *t, Node *x)
    {
        Node *y = x->getLeft();                     // Sett y
        x->setLeft(y->getRight());                  // Bytter om y sitt høyre subtre med det venstre subtreet.
        if(y->getRight()!=t->nil)
            y->getRight()->setParent(x);
        y->setParent(x->getParent());               // Lenker x sin forelder til y
        if(x->getParent() == t->nil)
            t->root = y;
        else if(x == x->getParent()->getRight())
            //x->getParent()->setRight(y);
            x->getParent()->setRight(y); // hentet fra https://www.andrew.cmu.edu/user/mm6/95-771/examples/RedBlackTreeProject/dist/javadoc/redblacktreeproject/RedBlackTree.html#leftRotate%28redblacktreeproject.RedBlackNode%29
        else
            //x->getParent()->setLeft(y);
            x->getParent()->setLeft(y); // https://www.andrew.cmu.edu/user/mm6/95-771/examples/RedBlackTreeProject/dist/javadoc/redblacktreeproject/RedBlackTree.html#leftRotate%28redblacktreeproject.RedBlackNode%29
        
        y->setRight(x);                             // setter x på y sin høyreside.
        x->setParent(y);
    }
    
    void RBTransplant(RBTree *t, Node *u, Node *v)
    {
        if(u->getParent() == t->nil)
            t->root = v;
        else if(u == u->getParent()->getLeft())
            u->getParent()->setLeft(v);
        else
            u->getParent()->setRight(v);
        v->setParent(u->getParent());
    }
    
    /**
     * Funksjon som retter opp balansen og andre ting etter innsetting av noder.
     * @param t Treet det skal rettes opp i
     * @param z Noden med selve utgangspunktet for operasjonen.
     */
    void RBInsertFixup(RBTree *t, Node *z)
    {
        Node *x, *y;
        while(z->getParent()->getColor() == red)
        {
            if(z->getParent() == z->getParent()->getParent()->getLeft())
            {
                y = z->getParent()->getParent()->getRight();
                if(y->getColor() == red)
                {
                    z->getParent()->setColor(black);
                    y->setColor(black);
                    z->getParent()->getParent()->setColor(red);
                    z = z->getParent()->getParent();
                }
                else 
                {
                    if(z == z->getParent()->getRight())
                    {
                        z = z->getParent();
                        leftRotate(t,z);
                    }
                    z->getParent()->setColor(black);
                    z->getParent()->getParent()->setColor(red);
                    rightRotate(t,z->getParent()->getParent());
                }
            }
            else
            {
                y = z->getParent()->getParent()->getLeft();
                if(y->getColor() == red)
                {
                    z->getParent()->setColor(black);
                    y->setColor(black);
                    z->getParent()->getParent()->setColor(red);
                    z = z->getParent()->getParent();
                }
                else
                { 
                    if(z == z->getParent()->getLeft())
                    {
                        z = z->getParent();
                        rightRotate(t,z);
                    }
                    z->getParent()->setColor(black);
                    z->getParent()->getParent()->setColor(red); //z->getParent()->getParent() blir før eller siden null.
                    leftRotate(t,z->getParent()->getParent());
                }
            }// slutt på hvis
        } // slutt på while-løkke
        t->root->setColor(black);
    }
    
    /**
     * Funksjon som retter opp balansen og andre ting etter sletting i treet.
     * @param t Treet som skal rettes
     * @param x Utgangspunktet for operasjonen
     */
    void RBDeleteFixup(RBTree *t, Node *x)
    {
        Node *w;
        while(x != t->root && x->getColor() == black)
        {
            if(x == x->getParent()->getLeft())
            {
                w = x->getParent()->getRight();
                if(w->getColor() == red)
                {
                    w->setColor(black);
                    x->getParent()->setColor(red);
                    leftRotate(t,x->getParent());
                    w = x->getParent()->getRight();
                }
                if(w->getLeft()->getColor() == black && w->getRight()->getColor() == black)
                {
                    w->setColor(red);
                    x = x->getParent();
                }
                else
                { 
                    if(w->getRight()->getColor() == black)
                    {
                        w->getLeft()->setColor(black);
                        w->setColor(red);
                        rightRotate(t,w);
                        w = x->getParent()->getRight();
                    }
                    w->setColor(x->getParent()->getColor());
                    x->getParent()->setColor(black);
                    w->getRight()->setColor(black);
                    leftRotate(t,x->getParent());
                    x = t->root;
                }
            }
            else // bytt om "right" of "left" sammenlignet med if-setningen ovenfor.
            {
                w = x->getParent()->getLeft();
                if(w->getColor() == red)
                {
                    w->setColor(black);
                    x->getParent()->setColor(red);
                    rightRotate(t,x->getParent());
                    w = x->getParent()->getLeft();
                }
                if(w->getRight()->getColor() == black && w->getLeft()->getColor() == black)
                {
                    w->setColor(red);
                    x = x->getParent();
                }
                else
                { 
                    if(w->getLeft()->getColor() == black)
                    {
                        w->getRight()->setColor(black);
                        w->setColor(red);
                        leftRotate(t,w);
                        w = x->getParent()->getLeft();
                    }
                    w->setColor(x->getParent()->getColor());
                    x->getParent()->setColor(black);
                    w->getLeft()->setColor(black);
                    rightRotate(t,x->getParent());
                    x = t->root;
                }
            }
        } // slutt på while
        x->setColor(black);
    }
    Node *treeMinimum(Node* node)
    {
        while(node->getLeft() != nil)
        {
            node = node->getLeft();
        }
        return node;
    }
    
    
    /**
     * Traverserer treet inOrder (venstrebarn --> rot --> høyrebarn)
     * @param node Utgangspunktet (roten) for traverseringen
     */
    void inOrderTraversalDriver(Node *node)
    {
        if(node->getColor() == red)
            fprintf(stdout, "\033[31m(\033[0m");
        else
            fprintf(stdout, "(");
        if(node->getLeft() && node->getLeft() != nil)
        {
            inOrderTraversalDriver(node->getLeft());
            fprintf(stdout, " ");
        }
        if(node->getColor() == red)
            fprintf(stdout, "\033[31m%ld\033[0m", node->getValue());
        else
            fprintf(stdout, "%ld", node->getValue());
        if(node->getRight() && node->getRight() != nil)
        {
            fprintf(stdout, " ");
            inOrderTraversalDriver(node->getRight());
        }
        if(node->getColor() == red)
            fprintf(stdout, "\033[31m)\033[0m");
        else
            fprintf(stdout, ")");
    }
    
public:
    // de basiske funksjonene for å sette inn, søke etter og fjerne fra treet.
    
    /**
     * Metode som sletter en node fra treet
     * @param t Treet det skal slettes fra
     * @param z Noden som skal slettes
     */
    void RBDelete(RBTree* t, Node* z)
    {
        Node *y = z;
        Node *x;
        Color yOriginalColor = y->getColor();
        if(z->getLeft() == t->nil)
        {
            x = z->getRight();
            RBTransplant(t,z,z->getRight());
        }
        else if(z->getRight() == t->nil)
        {
            x = z->getLeft();
            RBTransplant(t,z,z->getLeft());
        }
        else
        {
            y = treeMinimum(z->getRight());
            yOriginalColor = y->getColor();
            x = y->getRight();
            if(y->getParent() == z)
            {
                x->setParent(y);
            }
            else
            {
                RBTransplant(t, y,y->getRight());
                y->setRight(z->getRight());
                y->getRight()->setParent(y);
            }
            RBTransplant(t,z,y);
            y->setLeft(z->getLeft());
            y->getLeft()->setParent(y);
            y->setColor(z->getColor());
        }
        if(yOriginalColor == black)
        {
            RBDeleteFixup(t,x);
        }
    }
    /**
     * Setter en ny node inn i treet.
     * @param t Treet det skal settes inn i
     * @param z Noden som skal settes inn
     */
    void RBInsert(RBTree *t, Node *z)
    {
        /*if(!root)
        {
            Node *n = new Node(z->getValue());
            //n->setValue(z->getValue());
            root = n;
        }*/
        Node *y = t->nil;
        Node *x = t->root;
        while(x != t->nil)
        {
            y = x;
            if(z->getValue() < x->getValue())
                x = x->getLeft();
            else
                x = x->getRight();
        }
        z->setParent(y);
        if(y == t->nil)
            t->root = z;
        else if(z->getValue() < y->getValue())
            y->setLeft(z);
        else
            y->setRight(z);
        z->setLeft(t->nil);
        z->setRight(t->nil);
        z->setColor(red);
        RBInsertFixup(t,z);
    }
    
    /**
     * Søker etter en node med gitt verdi
     * @param x Noden som er utgangspunktet for søket (vanligvis rotnoden)
     * @param verdi Verdien det skal søkes etter
     * @return Noden med matchende verdi og null ellers.
     */
    Node *searchNode(Node *x, int verdi)
    {
        /*if(x == nil || verdi == x->getValue())
            return x;*/
        if(!x){
            return x;
        }
        else if(verdi == x->getValue())
            return x;
        else if(verdi < x->getValue())
           return searchNode(x->getLeft(), verdi);
        else if(verdi >= x->getValue()) 
            return searchNode(x->getRight(), verdi);
        else
            return 0x0;
    }
    
    void inOrderTraversal()
    {
        inOrderTraversalDriver(root);
        fprintf(stdout, "\n");
    }
};


class arrayIO
{
    string *myString;
public:
    arrayIO()
    {
        myString = 0x0;
    }
    /**
     * Funksjon som leser tekst fra fil og som kopierer denne teksten i en streng.
     * @param filename Filnavnet det skal leses fra
     * @return En streng med innholdet i filen
     */
    string *readArray(const char *filename)
    {
        /*Les fra fil*/
        ifstream in(filename);
        if(!in)
        {
            fprintf(stderr, "%s: Kan ikke lese filen %s.\n", prog_name, filename);
            exit(1); // avslutter programmet istedenfor å returnere en tom tabell.
        }
        string str2 = " ";
        stringstream buffer;
        buffer << in.rdbuf();
        string test = buffer.str();
        int last = test.size() -1;
        if(last >= 0 && test[last] != ' ') // dersom innholdet i filen ikke ender med mellomrom
        {
            /*
             * Legger til et mellomrom på slutten av strengen.
             * Dette fordi funksjonen genererer en nullpointer dersom strengen ikke ender
             * med et mellomrom. 
             */
            string spc = " ";
            test.append(spc);
        }
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
        myString = str;
        return myString;
    } 
};

#ifdef SIGINFO
	string status;
	int currNode, allNodes;
	void printInfo(int startNode, int totNodes)
	{
		// Sjekke om status = innsetting eller status = sletting
		if(status.compare("innsetting") == 0){
			fprintf(stdout, "Setter inn node %d av %d\n", startNode, totNodes);
		}
		else if(status.compare("sletting") ==0){
			fprintf(stdout, "Sletter node %d av %d\n", startNode, totNodes);
		}
	}
    /**
     * En funksjon som fanger opp siganalet SIGINFO (et signal som BSD-baserte systemer genererer ved å trykke
     * ctrl-t på tastaturet)
     * @param sig_num har verdi 29.
     */
    void catch_siginfo(int sig_num)
    {
        signal(SIGINFO, catch_siginfo);
        //fprintf(stdout, "Oppretter, setter inn i, traverserer og sletter fra et binært søketre.\n");
        printInfo(currNode, allNodes);
    }
#endif
void catch_sigsegv(int sig_num)
{
    signal(SIGSEGV, catch_sigsegv);
    fprintf(stderr, "Det har oppstått en såkalt segmentation violation. Avslutter…\n");
    signal(sig_num, SIG_DFL);
    kill(getpid(), sig_num);
}

/*void catch_sigabrt(int sig_num)
{
    signal(SIGABRT, catch_sigabrt);
    fprintf(stderr, "Et sigtrap-signal ble fanget opp. Avslutter…\n");
    signal(sig_num, SIG_DFL);
    kill(getpid(), sig_num);
}*/

void catch_sigbus(int sig_num)
{
    signal(SIGBUS, catch_sigbus);
    fprintf(stderr, "Det har oppstått en såkalt bussfeil (bus error). Avslutter…\n");
    signal(sig_num, SIG_DFL);
    kill(getpid(), sig_num);
}
int main(int argc, char** argv) {
    prog_name = "RBTree";
    arrayIO *aio = new arrayIO();
    RBTree *tree = new RBTree();
    Node *node;
    //signal(SIGABRT, catch_sigabrt);

    //try
    //{
        struct timeval totStart, totEnd, insStart, insEnd, searchStart, searchEnd, delStart, delEnd;
        long mtime_ins, mtime_search, mtime_del, totTime;
        gettimeofday(&totStart, NULL);
        string *str;
        str = aio->readArray(argv[1]);
        int instot = atoi(str[0].c_str());
        int i;
        gettimeofday(&insStart, NULL);
        for(i = 1; i <= instot; i++)
        {
			status = "innsetting";
			allNodes = instot;
			currNode = i;
			#ifdef SIGINFO
			signal(SIGINFO, catch_siginfo);
			#endif
            node = new Node(atoi(str[i].c_str()));
            tree->RBInsert(tree,node);
            //tree->RBInsert(tree,new Node(atoi(str[i].c_str())));
            //tree->RBInsert(tree, tree->root->)
        }
        fprintf(stdout, "Done\n");
        gettimeofday(&insEnd, NULL);
        fprintf(stdout, "Rotnoden er %ld\n", tree->root->getValue());
        fprintf(stdout, "Traverserer inOrder:\n");
        tree->inOrderTraversal();
        gettimeofday(&searchStart, NULL);
        if(tree->searchNode(tree->root, 6))
        {
            fprintf(stdout, "Node med verdi 6 ble funnet.\n");
        }
        else
        {
            fprintf(stderr, "Node med verdi 6 ble ikke funnet.\n");
        }
        gettimeofday(&searchEnd, NULL);
        if(tree->searchNode(tree->root, 10000))
        {
            fprintf(stdout, "Node med verdi 10000 ble funnet.\n");
        }
        else
        {
            fprintf(stderr, "Node med verdi 10000 ble ikke funnet.\n");
        }
        if(argc == 3)
        {
            string *del_str;
            del_str = aio->readArray(argv[2]);
            int deltot = 0, i = 0;
            deltot = atoi(del_str[0].c_str());
            gettimeofday(&delStart, NULL);
            
            
            for(i=1; i<= deltot; i++)
            {
				status = "sletting";
				currNode = i;
				allNodes = deltot;
				#ifdef SIGINFO
				signal(SIGINFO, catch_siginfo);
				#endif
                node = tree->searchNode(tree->root, atoi(del_str[i].c_str()));
                //tree->RBDelete(tree, tree->root);
                //node = new Node(atoi(del_str[i].c_str()));
                tree->RBDelete(tree,node);
            }
            
            
            gettimeofday(&delEnd, NULL);
            mtime_ins = searchEnd.tv_sec - searchStart.tv_sec;
            mtime_search = searchEnd.tv_sec - searchStart.tv_sec;
            mtime_del = delEnd.tv_sec - delStart.tv_sec;
            fprintf(stdout, "Traversering inOrder etter sletting av noder…\n");
            tree->inOrderTraversal();
            gettimeofday(&totEnd, NULL);
            totTime = totEnd.tv_sec - totStart.tv_sec;
            if(totTime == 0){
                long totTime_usec = totEnd.tv_usec - totStart.tv_usec;
                fprintf(stdout, "Programmet brukte %ld mikrosekunder på hele runddansen.\n", totTime_usec);
            }
            else
                fprintf(stdout, "Programmet brukte %ld sekunder på hele runddansen.\n", totTime);
            if(mtime_ins == 0){
                long mtime_ins_usec = mtime_ins = searchEnd.tv_usec - searchStart.tv_usec;
                fprintf(stdout, "Programmet brukte %ld mikrosekunder på å sette inn %d noder.\n", mtime_ins_usec, instot);
            }
            else
                fprintf(stdout, "Programmet brukte %ld sekunder på å sette inn %d noder.\n", mtime_ins, instot);
            if(mtime_search == 0){
                long mtime_search_usec = searchEnd.tv_usec - searchStart.tv_usec;
                fprintf(stdout, "Programmet brukte %ld mikrosekunder på å søke etter node 5.\n", mtime_search_usec);
            }
            else
                fprintf(stdout, "Programmet brukte %ld sekunder på å søke etter node 5.\n", mtime_search);
            if(mtime_del == 0){
                long mtime_del_usec = delEnd.tv_usec - delStart.tv_usec;
                fprintf(stdout, "Programmet brukte %ld mikrosekunder på å slette %d noder.\n",mtime_del_usec, deltot);
            }
            else
                fprintf(stdout, "Programmet brukte %ld sekunder på å slette %d noder.\n", mtime_del, deltot);
            return 0;
        }
        mtime_ins = insEnd.tv_sec - insStart.tv_sec;
        mtime_search = searchEnd.tv_sec - searchStart.tv_sec;
        gettimeofday(&totEnd, NULL);
        totTime = totEnd.tv_sec - totStart.tv_sec;
        if(totTime == 0){
            long totTime_usec = totEnd.tv_usec - totStart.tv_usec;
            fprintf(stdout, "Programmet brukte %ld mikrosekunder på hele runddansen.\n", totTime_usec);
        }
        else
            fprintf(stdout, "Programmet brukte %ld sekunder på hele runddansen.\n", totTime);
        if(mtime_ins == 0){
            long mtime_ins_usec = mtime_ins = searchEnd.tv_usec - searchStart.tv_usec;
            fprintf(stdout, "Programmet brukte %ld mikrosekunder på å sette inn %d noder.\n", mtime_ins_usec, instot);
        }
        else
            fprintf(stdout, "Programmet brukte %ld sekunder på å sette inn %d noder.\n", mtime_ins, instot);
        if(mtime_search == 0){
            long mtime_search_usec = searchEnd.tv_usec - searchStart.tv_usec;
            fprintf(stdout, "Programmet brukte %ld mikrosekunder på å søke etter node 5.\n", mtime_search_usec);
        }
        else
            fprintf(stdout, "Programmet brukte %ld sekunder på å søke etter node 5.\n", mtime_search);
    return 0;
    /*}
    catch(exception &e)
    {
        fprintf(stderr, "%s: Noe er galt: %s\n", prog_name, e.what());
    }*/
}

