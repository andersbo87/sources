/* 
 * File:   main.h
 * Author: andersbo
 *
 * Created on May 18, 2015, 3:35 PM
 */

#ifndef MAIN_H
#define	MAIN_H
class Edge;
class LinkList;
class GrafNode;
class GrafNode {
public:
    GrafNode();
    void settID(int);
    void settForelder(GrafNode*);
    void settPos(int nyPos);
    void settAvstand(double nyAvstand);
    double hentAvstand();
    GrafNode *hentForelder();
    int hentPos();
    int hentID();
    GrafNode(int nyID);
    void leggTilNabo(GrafNode*, double);
    std::string printPath();
    std::string tilStreng();
    virtual ~GrafNode();
private:
    int id;
    double avstand;
    GrafNode *forelder;
    int pos;
    LinkList *adj;
};
class Edge {
public:
    Edge(GrafNode *, GrafNode *, double);
    virtual ~Edge();
private:
    GrafNode *u, *v;
    double w;
};
class NaboNode{
private:
    NaboNode *neste, *forrige;
    Edge *edge;
public:
    void settNeste(NaboNode *);
    void settForrige(NaboNode *);
    NaboNode *hentForrige();
    NaboNode *hentNeste();
    NaboNode(Edge *);
    ~NaboNode();
};
class LinkList {
public:
    LinkList();
    LinkList(const LinkList& orig);
    void insert(Edge *edge);
    std::iterator<std::input_iterator_tag, Edge> iterator();
    virtual ~LinkList();
    
private:
    NaboNode *hode;
};
class PrioritetsKo {
private:
    GrafNode *a; // opprinnelig GrafNode *a;
    int n;
public:
    int const m = 2;
    PrioritetsKo(int);
    virtual ~PrioritetsKo();
    GrafNode minimum();
    void heapify(int i);
    GrafNode extractMin();
    void mink(GrafNode * , double );
    void settInn(GrafNode *);
    bool erTom();
    

};

#endif	/* MAIN_H */

