#include "../data_structures/Graph.h"
#include "stack"
using namespace std;

template <typename T>
vector<vector<T>> sccTarjan(Graph<T>* g) {
    vector<vector<T>> res;
    int index=1;
    stack<Vertex<T>*> s;
    for (Vertex<T>* v: g->getVertexSet()) {
        v->setVisited(false);
        v->setNum(-1);
        v->setLow(-1);
    }
    for (Vertex<T>* v: g->getVertexSet()) {
        if (v->getNum()==-1) {
            dfs(v,&s,index,&res);
        }
    }
    return res;
}

template <typename T>
void dfs(Vertex<T>* v,stack<Vertex<T>*>* s, int& index, vector<vector<T>>* res) {
    v->setNum(index);
    v->setLow(index);
    index++;
    v->setVisited(true);
    s->push(v);
    for (Edge<T>* e: v->getAdj()) {
        Vertex<T>* u = e->getDest();
        if (u->getNum()==-1) {
            dfs(u,s,index,res);
            v->setLow(min(v->getLow(),u->getLow()));
        }else if (u->isVisited()) {
            v->setLow(min(v->getLow(),u->getNum()));
        }
    }
    if (v->getNum()==v->getLow()) {
        vector<T> ve;
        Vertex<T>* ver;
        do {
            ver = s->top();
            s->pop();
            ver->setVisited(false);
            ve.push_back(ver->getInfo());
        }while (v!=ver);
        res->push_back(ve);
    }
}

