#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <exception>
#include <stdexcept>
#include <sys/time.h>
#include <string>
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
    int verdi;
    Node *venstre;
    Node *hoyre;
    Node *forelder;
public:
    Node(){
        // 0x0 tilsvarer NULL eller null (sistnevnte i Java).
        verdi=0x0;
        venstre=0x0;
        hoyre=0x0;
        forelder=0x0;
    }
    void settVerdi(int verdi)
    {
        this->verdi = verdi;
        //verdi = this->verdi; //fremprovoserer en SIGSEGV.
    }
    void settVenstre(Node *venstre){
        this->venstre = venstre;
    }
    void settHoyre(Node *hoyre){
        this->hoyre = hoyre;
    }
    void settForelder(Node *forelder){
        this->forelder = forelder;
    }
    int hentVerdi()
    {
        if(verdi){
            return verdi;
        }
        else
        throw std::runtime_error("Verdi er av en eller annen merkelig grunn null.");
    }
    Node* hentVenstre()
    {
       return venstre;
    }
    Node *hentHoyre()
    {
        return hoyre;
    }
    Node *hentForelder(){
        return forelder;
    }
};

class bst
{
    Node* rot;
public:
    bst()
    {
        rot = 0x0;
    }
    ~bst(){
        befriNode(rot);
    }
    Node *hentRot()
    {
        if(rot)
            return rot;
        else
        return 0x0;
    }
    Node *settRot(int verdi){
        rot->settVerdi(verdi);
        return rot;
    }
    void leggTilNode(int verdi)
    {
        //if(rot == NULL){
        if(!rot){
            Node *n = new Node();
            n->settVerdi(verdi);
            rot = n;
        }
        else{
            leggTilNode(verdi, rot);
        }
    }
    Node *finnNode(int verdi, Node* node)
    {
        if(!node)
        {
            throw std::runtime_error("Noden finnes ikke.\n");
        }
        else if(node->hentVerdi() == verdi){
            return node;
        }
        else if(verdi <= node->hentVerdi()){
            return finnNode(verdi,node->hentVenstre());
        }
        else if(verdi > node->hentVerdi()){
            return finnNode(verdi,node->hentHoyre());
        }
        else
            return 0x0;
    }
    void inorderTraversering(Node* node)
    {
      fprintf(stdout, "(");
      if(node->hentVenstre())
      {
	inorderTraversering(node->hentVenstre());
	fprintf(stdout, " ");
      }
      fprintf(stdout, "%d", node->hentVerdi());
      if(node->hentHoyre()){
	fprintf(stdout, " ");
	inorderTraversering(node->hentHoyre());
      }
      fprintf(stdout, ")");
    }
    void slettNode(int verdi)
    {
        Node *gjeldendeVerdi = finnNode(verdi, rot); // tilsvarer z i pseudokoden
        // Hvis z ikke har noen barn:
        if(!gjeldendeVerdi->hentVenstre() && !gjeldendeVerdi->hentHoyre()){
            if(gjeldendeVerdi->hentVerdi() > gjeldendeVerdi->hentForelder()->hentVerdi()){
                gjeldendeVerdi->hentForelder()->settHoyre(0x0);
            }
            else{
                gjeldendeVerdi->hentForelder()->settVenstre(0x0);
            }
            delete gjeldendeVerdi;
        }
        // Hvis z kun har ett barn, så fjerner vi denne og erstatter den med barnet.
        else if(!gjeldendeVerdi->hentVenstre() && gjeldendeVerdi->hentHoyre()){
            if(gjeldendeVerdi->hentVerdi() > gjeldendeVerdi->hentForelder()->hentVerdi()){
                gjeldendeVerdi->hentForelder()->settHoyre(gjeldendeVerdi->hentHoyre());
            }
            else{
                gjeldendeVerdi->hentForelder()->settVenstre(gjeldendeVerdi->hentHoyre());
            }
            delete gjeldendeVerdi;
        }
        else if(gjeldendeVerdi->hentVenstre() && !gjeldendeVerdi->hentHoyre()){
            if(gjeldendeVerdi->hentVerdi() > gjeldendeVerdi->hentForelder()->hentVerdi()){
                gjeldendeVerdi->hentForelder()->settHoyre(gjeldendeVerdi->hentVenstre());
            }
            else{
                gjeldendeVerdi->hentForelder()->settVenstre(gjeldendeVerdi->hentVenstre());
            }
            delete gjeldendeVerdi;
        }
        /*
         Hvis z har 2 barn, finner vi forgjengeren (eller etterfølgeren),
         fjerner forgjengeren/etterfølgeren og erstatter noden som skal fjernes
         med forgjengeren eller etterfølgeren.
         */
        else if(gjeldendeVerdi->hentVenstre() && gjeldendeVerdi->hentHoyre()){
            Node *sub = forgjenger(gjeldendeVerdi, gjeldendeVerdi->hentVerdi());
            if(!sub){
                sub = etterfolger(gjeldendeVerdi, gjeldendeVerdi->hentVerdi());
            }
            if(sub->hentForelder()->hentVerdi() <= sub->hentVerdi()){
                sub->hentForelder()->settHoyre(sub->hentHoyre());
            }
            else{
                sub->hentForelder()->settVenstre(sub->hentVenstre());
            }
            gjeldendeVerdi->settVerdi(sub->hentVerdi());
            delete sub;
        }
    }
    Node* treMinimum(Node* node)
    {
        if(!node)
        {
            throw std::runtime_error("Noden som ble sendt som parameter til treMinimun er null.\n");
        }
        if(node){
            while(node->hentVenstre()){
                node = node->hentVenstre();
            }
        }
        return node;
    }
    Node* treMaksimum(Node* node)
    {
        if(!node)
        {
            throw std::runtime_error("Noden som ble sendt som parameter til treMinimun er null.\n");
        }
        else
        {
            while(node->hentHoyre())
            {
                node = node->hentHoyre();
            }
        }
        return node;
    }
    Node* etterfolger(Node* anode, int verdi)
    {
        Node* gjeldendeVerdi = finnNode(verdi, anode);
        if(gjeldendeVerdi){
            if(gjeldendeVerdi->hentHoyre())
                return gjeldendeVerdi->hentHoyre();
            else{
                throw ("gjeldendeVerdi->hentHoyre() er null.");
            }
        }
        else{
            throw ("Noden finnes ikke.\n");
        }
    }
    Node* forgjenger(Node* forelder, int verdi)
    {
        Node *gjeldendeVerdi = finnNode(verdi, forelder);
        if(gjeldendeVerdi){
            if(gjeldendeVerdi->hentVenstre())
                return treMaksimum(gjeldendeVerdi->hentVenstre());
            else{
                throw ("gjeldendeVerdi->hentVenstre() er null.");
            }
        }
        else{
           throw ("Noden finnes ikke.\n");
        }
    }
private:
    void befriNode(Node* bladNode)
    {
        if(bladNode != 0x0){
            befriNode(bladNode->hentVenstre());
            befriNode(bladNode->hentHoyre());
            delete bladNode;
        }
    }
    //privat driverfunksjon for leggTilNode.
    void leggTilNode(int verdi, Node* bladNode)
    {
        if(verdi <= bladNode->hentVerdi()){
            if(bladNode->hentVenstre() != 0x0){
                leggTilNode(verdi, bladNode->hentVenstre());
            }
            else{
                Node *n = new Node();
                n->settVerdi(verdi);
                n->settForelder(bladNode);
                bladNode->settVenstre(n);
            }
        }
        else{
            if(bladNode->hentHoyre() != 0x0){
                leggTilNode(verdi, bladNode->hentHoyre());
            }
            else{
                Node *n = new Node();
                n->settVerdi(verdi);
                n->settForelder(bladNode);
                bladNode->settHoyre(n);
            }
        }
    }
}; // end of class bst

class bstIO
{
private:
    string *minStreng;
public:
    bstIO()
    {
        minStreng = 0x0; //initialiserer minStreng...
    }
    ~bstIO()
    {
        
    }
public:
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
    fprintf(stderr, "Det har oppstått en såkalt segmentation violation. Avslutter…\n");
    signal(sig_num, SIG_DFL);
    kill(getpid(), sig_num);
}

void catch_sigbus(int sig_num)
{
    signal(SIGBUS, catch_sigbus);
    fprintf(stderr, "Det har oppstått en såkalt bussfeil (bus error). Avslutter…\n");
    signal(sig_num, SIG_DFL);
    kill(getpid(), sig_num);
}
int thisNode, allNodes;
string status;
void printInfo(int currentNode, int allNodes)
{
	if(status.compare("innsetting") == 0){
		fprintf(stdout, "Setter inn node %d av %d.\n", currentNode, allNodes);
	}
	else if(status.compare("sletting") == 0)
	fprintf(stdout, "Sletter node %d av %d.\n", currentNode, allNodes);
}
void catch_siginfo(int sig_num)
{
    #ifdef SIGINFO
    signal(SIGINT, catch_siginfo);
    fprintf(stdout, "Oppretter, setter inn i, traverserer og sletter fra et binært søketre.\n");
    #endif
}


int main(int argc, char **argv){
    signal(SIGSEGV, catch_sigsegv);
    signal(SIGBUS, catch_sigbus);
#ifdef SIGINFO
    signal(SIGINFO, catch_siginfo);
#endif
    prog_name = "bst";
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
        bst* tree = new bst(); // Add nodes
        bstIO *bio = new bstIO();
        string *str;
        str = bio->readArray(argv[1]);
        int instot;
        instot = atoi(str[0].c_str());
        int i; 
        gettimeofday(&insStart, NULL);
        for(i = 1; i <= instot; i++)
        {
            tree->leggTilNode(atoi(str[i].c_str()));
        }
        gettimeofday(&insEnd, NULL);
        fprintf(stdout, "Traverserer inorder…\n");
        tree->inorderTraversering(tree->hentRot());
        fprintf(stdout, "\n");
        // Find nodes
        gettimeofday(&searchStart, NULL);
        if ( tree->finnNode(5, tree->hentRot()) )
        {
            fprintf(stdout, "Node 5 ble funnet\n");
        }
        else
            fprintf(stdout, "Node 5 ble ikke funnet.\n");
        gettimeofday(&searchEnd, NULL);
        if ( tree->finnNode(6, tree->hentRot()) )
            fprintf(stdout, "Node 6 ble funnet.\n");
        else
            fprintf(stdout, "Node 6 ikke funnet.\n");
        if(argc == 3)
        {
            // Delete a node
            int i, del_tot;
            string *del_str;
            del_str = bio->readArray(argv[2]);
            del_tot = atoi(del_str[0].c_str());
            fprintf(stdout, "Sletter noder...\n");
            //int deleteStartTime = getMilliCount();
            gettimeofday(&delStart, NULL);
            for(i=1; i<=del_tot;i++)
            {
	      tree->slettNode(atoi(del_str[i].c_str()));
            }
            gettimeofday(&delEnd, NULL);
            mtime_ins = searchEnd.tv_sec - searchStart.tv_sec;
            mtime_search = searchEnd.tv_sec - searchStart.tv_sec;
            mtime_del = delEnd.tv_sec - delStart.tv_sec;
            //int elapsedDeleteTime=getMilliSpan(deleteStartTime);
            // Traverse the tree
            fprintf(stdout, "Traversering etter sletting:\n");
            tree->inorderTraversering(tree->hentRot()); cout << endl;
            delete tree;
            //int stopTime = getMilliSpan(startTime);
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
                fprintf(stdout, "Programmet brukte %ld mikrosekunder på å slette %d noder.\n",mtime_del_usec, del_tot);
            }
            else
                fprintf(stdout, "Programmet brukte %ld sekunder på å slette %d noder.\n", mtime_del, del_tot);
            return 0;
        }
        delete tree;
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
    } catch (std::exception &e) {
        fprintf(stderr, "%s: Noe gikk galt: %s", prog_name, e.what());
        return 1;
    }

    
}
