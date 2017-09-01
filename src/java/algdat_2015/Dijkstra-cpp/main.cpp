/* 
 * File:   main.cpp
 * Author: andersbo
 *
 * Created on May 18, 2015, 1:57 PM
 */

#include <cstdlib>
#include <iosfwd>
#include <iterator>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "main.h"
using namespace std;

/*
 * 
 */
PrioritetsKo::PrioritetsKo(int storrelse) {
    a = new GrafNode[m*storrelse];
    n = 0;
}

PrioritetsKo::~PrioritetsKo() {
    delete a;
}
GrafNode PrioritetsKo::minimum(){
    return a[0];
}
void PrioritetsKo::heapify(int i)
{
    int venstre = 2*i+1;
    int hoyre = 2*i+2;
    int minst;
    if(venstre < n && a[venstre].hentAvstand() < a[i].hentAvstand())
        minst = venstre;
    else
        minst = i;
    if(hoyre < n && a[hoyre].hentAvstand() < a[minst].hentAvstand())
        minst = hoyre;
    if(minst != i){
        GrafNode *temp = a[minst];
        a[minst] = a[i];
        a[minst]->settPos(minst);
        a[i] = temp;
        a[i]->settPos(i);
        heapify(minst);
    }
}
GrafNode *PrioritetsKo::extractMin(){
    --n;
    GrafNode *min = a[0];
    a[0] = a[n];
    a[0]->settPos(0);
    heapify(0);
    return min;
}
void PrioritetsKo::mink(GrafNode* x, double d){
    if(d > a[x->hentPos()].hentAvstand())
        return;
    a[x->hentPos()]->settAvstand(d);
    int forelder = (x->hentPos()-1)/2;
    while(x->hentPos() > 0 && a[forelder].hentAvstand() > a[x->hentPos()].hentAvstand()){
        GrafNode *temp = a[forelder];
        a[forelder] = a[x->hentPos()];
        a[x->hentPos()] = temp;
        a[x->hentPos()]->settPos(forelder);
        forelder = (x->hentPos() - 1) / 2;
    }
}
void PrioritetsKo::settInn(GrafNode* node)
{
    node->settPos(n);
    a[n] = node;
    mink(node, node->hentAvstand());
    n++;
}
bool PrioritetsKo::erTom()
{
    return n == 0;
}

LinkList::LinkList() {
}
void NaboNode::settNeste(NaboNode* nyNeste){
    neste = nyNeste;
}
void NaboNode::settForrige(NaboNode* nyForrige){
    forrige = nyForrige;
}
NaboNode *NaboNode::hentForrige()
{
    return forrige;
}
NaboNode *NaboNode::hentNeste()
{
    return neste;
}
NaboNode::NaboNode(Edge* newEdge)
{
    edge = newEdge;
}
LinkList::LinkList(const LinkList& orig) {
}

LinkList::~LinkList() {
}

void LinkList::insert(Edge* edge)
{
    NaboNode *x = new NaboNode(edge);
    x->settNeste(hode);
    if(hode){
        hode->settForrige(x);
    }
    hode = x;
    x->settForrige(0x0);
}

/*LinkList::iterator()
{
    return new std::iterator<Edge>(){
        NaboNode *gjeldende;
        public bool hasNext()
        {
            if(gjeldende)
                return gjeldende->hentNeste() != 0x0;
            else
                return hode != 0x0;
        }
    };
}*/
GrafNode::GrafNode(int nyID) {
    id = nyID;
    adj = new LinkList();
    settAvstand(10000000);
    settForelder(0x0);
}

GrafNode::~GrafNode() {
}
void GrafNode::settAvstand(double nyAvstand)
{
    avstand = nyAvstand;
}
void GrafNode::settForelder(GrafNode* nyForelder)
{
    forelder = nyForelder;
}
void GrafNode::settID(int nyID){
    id = nyID;
}
void GrafNode::settPos(int nyPos)
{
    pos = nyPos;
}
double GrafNode::hentAvstand()
{
    return avstand;
}
GrafNode *GrafNode::hentForelder()
{
    return forelder;
}
int GrafNode::hentPos()
{
    return pos;
}
int GrafNode::hentID()
{
    return id;
}
void GrafNode::leggTilNabo(GrafNode *v, double w)
{
    adj->insert(new Edge(this, v, w));
}

std::string GrafNode::printPath()
{
    if(!hentForelder())
        // konverter int til streng
        std::to_string(id);
    else
        return hentForelder()->printPath() + " " + std::to_string(hentAvstand());
}

std::string GrafNode::tilStreng()
{
    if(!hentForelder())
        return "NA";
    else
        return printPath() + " " + std::to_string(hentAvstand());
}

Edge::Edge(GrafNode *newU, GrafNode *newV, double newW) 
{
    u = newU;
    v = newV;
    w = newW;
}

Edge::~Edge() {
    // lar destruktøren bare stå tom.
}
class Dijkstra
{
private:
    int max;
public:
    GrafNode *liste;
    PrioritetsKo *q;
    PrioritetsKo *opprettKo(){
        
        PrioritetsKo *ret = new PrioritetsKo(max);
        for(GrafNode *v : liste){
            ret->settInn(v);
        }
    }
};
int main(int argc, char** argv) 
{
    if(argc != 3)
    {
        fprintf(stdout, "Usage: dijkstra file1 arg1.\n");
    }
    string line;
    ifstream infile;
    infile.open(argv[1]);
    string str = getline(infile, line);
    max = atoi(str);
    while(getline(infile,line))
    {
        // legg til i listen.
    }
    
    return 0;
}

