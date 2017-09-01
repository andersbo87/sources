#include <iostream>
#include <cstdlib>
#include <vector>
#define INF INT_MAX

// Oppgave 1
const char *prog_name;
using namespace std; // usikker på om dette er tillatt, da vi ikke får lov til å bruke tredjeparters biblioteker...
template <class T>
class Node {
private:
    T indeks, data, forrige, prioritet;
public:
    Node *lenke;
    bool operator()(const Node &a, const Node &b){
        return a.data > b.data;
    }
    // Funksjoner som heter verdier
    T hentData()
    {
        return data;
    }
    T hentForrige()
    {
        return forrige;
    }
    T hentIndeks()
    {
        return indeks;
    }
    T hentPrioritet()
    {
        return prioritet;
    }
    // Funksjoner som setter verdier
    void settData(int nyData)
    {
        data = nyData;
    }
    void settForrige(int nyForrige)
    {
        forrige = nyForrige;
    }
    void settIndeks(int nyIndeks)
    {
        indeks = nyIndeks;
    }
    void settPrioritet(int nyPrioritet)
    {
        prioritet = nyPrioritet;
    }
};

class Vector {
public:
    //Constructors
    Vector(std::initializer_list<int>); //constructor with {x, y, z} init (ie Vector v({1, 2, 3}); )
    Vector(int); //declare size, and initialize all elements to 0
    Vector();   //empty constructor
    Vector(const Vector& a); //COPY CONSTRUCTOR - rule of 3
    ~Vector(); //DESTRUCTOR - rule of 3

    //Overloaded operators
    int& operator[](int) const; //function type: int& because returns a[i] (or &a[i])
    const Vector& operator++();
    const Vector& operator--();
    const bool operator==(Vector&) const;
    Vector& operator=(const Vector&); //COPY ASSIGNMENT - rule of 3
    Vector& operator+=(const Vector&); //a Vector, += a vector (since its IN the vector class)
    const Vector operator+(const Vector&); //adds values of two equal sized vectors
    const Vector& operator+(int);       //deals with adding a single int (essentially .pushBack(int))

    //Input functions
    const Vector& pushBack(int); //add single element to end
    void addToEnd(std::initializer_list<int>); //add list to end
    Vector softRest() const;
    const Vector& hardRest();

    //Output functions
    int size() const;
    void arr_print() const;


private:
    int sz;
    int* elem;
};


template <class T1, class T2, class T3>
class priorityQueue
{
private:
    Node<int> *front;
public:
    priorityQueue(){
        front = 0x0; // 0x0 tilsvarer null i Java. I C++ kan 0x0 på mange systemer skrives 0x0.
    }
    bool tom()
    {
        if(!front)
            return true;
        else return false;
    }
    Node<int> *top()
    {
        return front;
    }
    void settInn(int data, int prioritet)
    {
        Node<int> *temp, *q;
        temp = new Node<int>();
        temp->settData(data);
        temp->settPrioritet(prioritet);
        if(!front || prioritet < front->hentPrioritet())
        {
            temp->lenke = front;
            front = temp;
        }
        else
        {
            q = front;
            while(q->lenke && q->lenke->hentPrioritet() <= prioritet)
            {
                q = q->lenke;
            }
            temp->lenke = q ->lenke;
            q->lenke = temp;
        }
    }
    void slett()
    {
        Node<int> *temp;
        if(!front)
        {
            fprintf(stderr, "Queue underflow...\n");
        }
        else
        {
            temp = front;
            fprintf(stdout, "Slettet data %d\n", temp->hentData());
            front=front->lenke;
            free(temp);
        }
    }
    
    void vis()
    {
        Node<int> *peker = front;
        if(!front){
            fprintf(stderr, "Køen er tom.\n");
        }
        else
        {
            fprintf(stdout, "Prioritet\tData\n");
            while(peker)
            {
                fprintf(stdout, "%d\t%d", peker->hentPrioritet(), peker->hentData());
                peker = peker->lenke;
            }
        }
    }
};

void initialize(vector<Node<int> > &vn, int s){
    vn[s].settData(0);
}

void relax(vector<Node<int> > &vn, vector<vector<int> >  &vov, priorityQueue< Node<int>, vector<Node<int> >, Node<int> > &pq, int u, int v)
{
    if(vn[v].hentData() > vn[u].hentData() + vov[u][v]){
        vn[v].settData(vn[u].hentData() + vov[u][v]);
        vn[v].settForrige(u);
        pq.settInn(vn[v].hentData(), 1);
    }
}

void dijkstra(vector< vector<int> > &vov, vector<Node<int> > &vn, priorityQueue< Node<int>, vector<Node<int> >, Node<int> > &pq, int s)
{
    int i, j, k;
    initialize(vn, s);
    pq.settInn(vn[s].hentData(),2);
    while(!pq.tom()){
        i = pq.top()->hentIndeks();
        pq.slett();
        for(j=0; j < vn.size(); j++){
            if(vov[i][j])
                relax(vn, vov, pq,i,j);
        }
    }
}
// Slutt på oppgave 1

// Oppgave 2
int main(int argc, char** argv) {
    prog_name = "dijkstra";
    if(argc != 2){
        fprintf(stderr, "usage: %s fil1\n", prog_name);
        return 1;
    }
    int nodes, edges, a,b,i,j,k,s,u,v,w;
    Node<int> node;
    vector<Node<int> > ve; 
    vector<int> vi;
    priorityQueue<Node<int>, vector<Node<int> >, Node<int> > pq;
    vector< vector<int> > vov;
    
    cin >> nodes >> edges;
    fprintf(stdout, "Slutt 1\n");
    for(j = 0; j < nodes; j++){
        node.settIndeks(j);
        node.settData(INF);
        node.settForrige(-1);
        ve.push_back(node);
    }
    fprintf(stdout, "Slutt 2\n");
    for(i=0; i<nodes; i++){
        vi.clear();
        for(j=0; j < nodes; j++){
            vi.push_back(0);
        }
    }
    for(i=0; i<edges; i++){
        cin >> u >> v >> w;
        vov[u-1][v-1] = w;
    }
    cin >> s;
    s--;
    dijkstra(vov,ve,pq,s);
    for( i = 0; i < nodes; i++ ) {
        node = ve[i];
        vi.clear();
        vi.push_back(i);
        while( node.hentForrige() != -1 ) {
            vi.push_back(node.hentForrige());
            node = ve[node.hentForrige()];
        }
 
        cout << "Shortest path is : ";
        for( j = vi.size()-1; j > 0; j-- ) {
            cout << vi[j]+1 << " -> ";
        }
 
        cout << vi[0]+1 << " and distance is " << ve[i].hentData() << "\n";
    }
    return 0;
}

