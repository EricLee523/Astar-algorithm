//#include "stdafx.h"

#include "astar.h"
using namespace std;
int main(int argc, char* argv[])
{
    Astar astar;
    Node *startPos = new Node(1,1);
    Node *endPos = new Node(6,10);
    astar.search(startPos,endPos);
    return 0;
}
