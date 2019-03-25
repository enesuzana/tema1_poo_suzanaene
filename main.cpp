#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");

class Nod{
    Nod *prev;
    Nod *next;
    float val;
public:
    Nod(Nod*prev, Nod*next, float val);
    Nod();

    float getVal(){ return val;}
    void setVal(float value){ val = value;}
    void setNext(Nod *nextt){ next = nextt;};
    void setPrev(Nod *prevv){ prev = prevv;};
    Nod* getNext(){ return next;}
    Nod* getPrev(){ return prev;}

    friend class List;
};


Nod::Nod(Nod *prevNod, Nod *nextNod, float value){
    prev = prevNod;
    next = nextNod;
    val = value;
}

Nod::Nod(){
    prev = NULL;
    next = NULL;
    val = 0;
}

class List{
    Nod *head;
    Nod *nod;
    Nod *tail;
    int n;
public:
    List();

    void inserare(float val, int poz);
    void afis();
    void del(float val);

    Nod * getHead(){return head;}
    Nod * getTail(){return tail;}

    float getValue(){return nod->getVal();}

    Nod* getNextNod(){ return nod->getNext();}
    void setNextNod(Nod *next){ nod->setNext(next);}

    void setPrevNod(Nod *prev){ nod->setPrev(prev); }
    Nod* getPrevNod(){ return nod->getPrev();}

    void setCounter(int nn){ n = nn;}
    int getCounter(){ return n;}

    List concat(List l1, List l2);

    friend istream& operator>>(istream& cin, List &lista);
    friend ostream& operator<<(ostream& out, List &lista);
    friend List operator+(List l1, List l2);
};


List::List(){
    n = 0;
    head = new Nod();
    tail = new Nod();
}

void List::inserare(float valoare, int poz){
    Nod *p = head;
    // lista nula
    if(p->val == 0){
        head->val = valoare;
        tail = head;
    }
    else{
    if( poz == 0){ //ins pe prima poz
        Nod *inserat = new Nod(NULL, head, valoare);
        head->prev = inserat;
        head = inserat;
    }
    else if( poz == n ){ // pe ultima poz
        //while( p->next != NULL){
              //  p = p->next;}
        Nod *inserat = new Nod(tail, NULL, valoare);
        tail->next = inserat;
        tail = inserat;
    }
    else{// in interior
        for( int i = 0; i < poz; i++){
            p = p->next;
        }
        Nod *inserat = new Nod(p->prev, p, valoare);
        p->prev->next = inserat;
        p->prev = inserat;
    }
    }
    n++;
}

istream& operator>>(istream& in, List &lista){
    float nr;
    cout << "enter val: ";
    in >> nr;
    lista.inserare(nr, lista.getCounter());
    return in;
}

ostream& operator<<(ostream& out, List &lista){
    out << endl;
    lista.nod = lista.getHead();
    for(int i = 0 ; i < lista.getCounter() ; i++){
        out << lista.getValue() << " ";
        lista.nod = lista.getNextNod();
    }
    out << endl;

    out << "In sens invers: " << endl;
    lista.nod = lista.getTail();
    for(int i = lista.getCounter()-1; i >= 0; i--){
        out << lista.getValue() << " ";
        lista.nod = lista.getPrevNod();
    }

    out<<"nr elem" << lista.getCounter();
    out << endl;
    return out;
}

void List::del(float val){
     Nod *p = head;
     // daca e primul
     if( p->val == val){
        p->next->prev = NULL;
        head = p->next;
        delete p;
     }
     else{//altfel caut pana gasesc valoarea
        int contor = 0;
        while( p->val != val ){
            p = p->next;
            contor++;
        }
        if(contor != n-1){
            (p->next)->prev = p->prev;
            (p->prev)->next = p->next;
            delete p;
        }
        else{
            p->prev->next = NULL;
            tail = p->prev;
            delete p;
        }
     }
     n--;
}

void List::afis(){
    Nod *p = head;
    for(int i = 0 ; i < n ; i++){
        cout << p->val << " ";
        p = p->next;
    }
    cout << endl;
}

List operator+(List l1, List l2){
    List l3;
    l3.head = l1.getHead();
    l1.nod = l1.getTail();
    l2.nod = l2.getHead();
    l1.setNextNod(l2.nod);
    l2.setPrevNod(l1.nod);
    l3.tail = l2.getTail();
    l3.n = l1.getCounter() + l2.getCounter();
    return l3;
}


int main(){
    int n;
    float x, val;
    cout << "Cate liste? ";
    cin >> n;
    List lista[n];

    //citirea listelor
    for(int i = 0 ; i < n; i++){
        cout << "Cate elemente pentru lista " << i <<" ?" << endl;
        cin >> x;
        for( int k = 0; k < x ; k++ ){
            //cout <<"enter val: ";
            //cin >> val;
            //lista[i].inserare(val, k);
            cin >> lista[i];
        }

    }
    //afisarea listelor
    for(int i = 0 ; i < n; i++){
        lista[i].afis();
    }
    //exemplu de concatenare
    cout << "-----------------------------------";
    cout << endl << "Dupa concatenare:";
    List l= lista[0]+lista[1];
    cout << l;
    cout << "-----------------------------------";
    //exemplu de stergere
    cout << "lista originala: " << endl;
    l.afis();
    lista[0].del(3);
    cout << "Dupa stergere:" << endl;
    lista[0].afis();
    cout << "-----------------------------------";
    lista[1].afis();
    lista[1].inserare(3,1);
    cout << " Dupa inserarea lui 3 pe poz 1: " << endl;
    lista[1].afis();
    return 0;
}
