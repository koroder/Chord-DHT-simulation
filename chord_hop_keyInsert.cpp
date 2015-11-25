#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
using namespace std;

#define BASE 2
#define ID_BIT 30
#define ID_SPACE (int)pow(BASE,ID_BIT)
/* GRID is circumference of earth in meters: 40000000 */
#define GRID 10000
#define LIVE 1
#define DEAD 0
#define PRINT_STAT 0
#define NODES (int)pow(10,4)
#define KEYS_ADD (int)pow(10,4)

int DEBUG=0;
int HOP=0;
int DISTANCE=0;


class Node
{
public:
    int id;
    Node* successor;
    Node* predecessor;

    /* Finger Table Start */
    int FT_start[ID_BIT];
    int FT_end[ID_BIT];
    Node* FT_node[ID_BIT];
    /* Finger Table End */

    /* Co-ordinates start  */
    int x;
    int y;
    /* Co-ordinates end */

    /* state can take values LIVE or DEAD */
    int state;


    void setValue (int id, int state, int x, int y);
    Node* findSuccessor(int id);
    Node* findPredecessor(int id);
    Node* closestPrecedingFinger(int id);
    void join(Node* n_old);
    void join_first(Node* self);
    void initFingerTable(Node* n_old);
    void updateOthers();
    void updateFingerTable(Node* s, int i);
    bool isInInterval(int val, int left, int right, int left_inc, int right_inc);
    double distance(Node* n1, Node* n2);
};

void Node::setValue (int id, int state, int x, int y)
{
    this->id = id;
    this->state = state;
    this->x = x;
    this->y = y;
}

double Node::distance(Node* n1, Node* n2)
{
    return sqrt(pow(n1->x - n2->x,2)+pow(n1->y - n2->y,2));
}

bool Node::isInInterval(int val, int left, int right, int left_inc, int right_inc)
{
    if(left_inc && val == left)
        return true;

    if(right_inc && val == right)
        return true;

    if(right > left)
    {
        if (val > left && val < right )
            return true;

        return false;
    }

    if(right < left)
    {
        if (val >= right && val <= left)
            return false;

        return true;
    }

    return true; // left = right | covers the entire circular space
}

Node* Node::closestPrecedingFinger(int id)
{
    for (int i = ID_BIT-1; i >= 0; --i)
    {
        /* code */
        if(isInInterval(FT_node[i]->id,this->id,id,0,0))
            return FT_node[i];
    }
    return this;
}

Node* Node::findPredecessor(int id)
{
    Node* n_new = this;
    Node* n_prev = this;
    while(!isInInterval(id,n_new->id,n_new->successor->id,0,1))
    {
        n_new = n_new->closestPrecedingFinger(id);
        if (HOP)
        {
            DISTANCE++;
        }
        n_prev = n_new;
    }

    return n_new;
}

Node* Node::findSuccessor(int id)
{
    Node* n = findPredecessor(id);
    Node* succ = n->successor;
    if(HOP)
    {
        DISTANCE++;
    }
    return succ;
}

void Node::initFingerTable(Node* n_old)
{
    for (int i = 0; i < ID_BIT; ++i)
    {
        /* code */
        FT_start[i] = (id + (int)pow(2,i))%ID_SPACE;
        FT_end[i] = (id + (int)pow(2,i+1)-1)%ID_SPACE;
    }

    FT_node[0] = n_old->findSuccessor(FT_start[0]);
    successor = FT_node[0]; 
    predecessor = successor->predecessor;
    successor->predecessor = this;
    for (int i = 0; i < ID_BIT-1; ++i)
    {
        /* code */
        if (isInInterval(FT_start[i+1],id,FT_node[i]->id,1,0))
            FT_node[i+1] = FT_node[i];
        else
            FT_node[i+1] = n_old->findSuccessor(FT_start[i+1]);
    }
    return;
}

void Node::updateFingerTable(Node* s, int i)
{
    if(isInInterval(s->id,id,FT_node[i]->id,1,0) && 
                                      s != this)
    {
        FT_node[i] = s;
        if (i == 0)
        {
            successor = s;
            successor->predecessor = this;
        }
        Node* p = predecessor;
        if (HOP)
        {
            DISTANCE++;
        }
        p->updateFingerTable(s,i);
    }
    return;
}

void Node::updateOthers(void)
{
    Node* p = NULL;
    for (int i = 0; i < ID_BIT; ++i)
    {
        /* code */
        p = findPredecessor(((id - (int)pow(2,i))%ID_SPACE + ID_SPACE)%ID_SPACE);
        p->updateFingerTable(this,i);
    }
    return;
}

void Node::join(Node* n_old)
{
    cout << "Node: " << id << " ADDED VIA " << "Node: " << n_old->id << endl;
    initFingerTable(n_old);
    updateOthers();
    return;
}

void Node::join_first(Node* self)
{
    cout << "Node: " << id << " JOINED FIRST TIME\n";
    for (int i = 0; i < ID_BIT; ++i)
    {
        /* code */
        FT_start[i] = (id + (int)pow(2,i))%ID_SPACE;
        FT_end[i] = (id + (int)pow(2,i+1)-1)%ID_SPACE;
        FT_node[i] = self;
    }
    predecessor = self;
    successor = FT_node[0];
    return;
}

int main (void)
{
    Node n[NODES];
    int contact = 0; // to be equated to actual value in for loop

    ofstream nodeJoin_t;
    nodeJoin_t.open("keyInsert_h.txt");

    for (int i = 0; i < NODES; ++i)
    {
        /* code */
        n[i].setValue(rand()%ID_SPACE, LIVE, rand()%GRID, rand()%GRID);
        if(i == 0)
        {
            n[i].join_first(&n[i]);
            contact = i;
        }
        else
        {
            n[i].join(&n[contact]);
            contact = rand()%(i+1);
        }
    }
    HOP = 1;
    cout << "----INSERTING TOTAL OF " << KEYS_ADD << " KEYS---------\n";
    double avg_dis = 0;
    int max = 14;
    double dis[max];
    for (int i = 0; i < max; ++i)
    {
        /* code */
        dis[i] = 0;
    }

    for (int i = 0; i < KEYS_ADD; i++)
    {
        /* code */
        DISTANCE = 0;
        contact = rand()%(NODES);
        n[contact].findSuccessor(rand()%ID_SPACE);
        
        nodeJoin_t << DISTANCE << endl;
        avg_dis = avg_dis + DISTANCE;
        dis[DISTANCE-1]++;
    }
    nodeJoin_t.close();

    avg_dis = avg_dis/KEYS_ADD;

    cout << "AVERAGE #HOP FOR SEARCHING OF KEYS: " << avg_dis << " UNITS\n";

    for (int i = 0; i < max; ++i)
    {
        /* code */
        dis[i] = dis[i]/KEYS_ADD;
        cout << dis[i] << endl;
    }

    cout << "-----------------------------------------------\n";
    if (PRINT_STAT)
    {
        cout << "NODE#  NODE-ID   SUCCESSOR  PREDECESSOR\n";
        for (int i = 0; i < NODES; ++i)
            cout << "Node" << i << ": " << n[i].id << " " << n[i].successor->id << " " << n[i].predecessor->id << " " << endl;
    }

    return 0;
}
