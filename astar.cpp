//#include "stdafx.h"
#include "astar.h"

int map[101][101] =
{
//    {0,0,0,1,0,1,0,0,0},
//    {0,0,0,1,0,1,0,0,0},
//    {0,0,0,0,0,1,0,0,0},
//    {0,0,0,1,0,1,0,1,0},
//    {0,0,0,1,0,1,0,1,0},
//    {0,0,0,1,0,0,0,1,0},
//    {0,0,0,1,0,0,0,1,0}

        {1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,1,1,0,1,0,0,0,0,1},
		{1,0,0,1,1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,0,0,1,1,1},
		{1,1,1,0,0,0,0,0,1,1,0,1},
		{1,1,0,1,0,0,0,0,0,0,0,1},
		{1,0,1,0,0,0,0,1,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1}
};
Astar::Astar()
{

}
Astar::~Astar()
{

}

void Astar::search( Node* startPos,Node* endPos )
{
    if (startPos->x < 0 || startPos->x > row || startPos->y < 0 || startPos->y >col ||
        endPos->x < 0 || endPos->x > row || endPos->y < 0 || endPos->y > col)
        return ;
    Node* current;
    this->startPos = startPos;
    this->endPos = endPos;
    openList.push_back(startPos);
    //��Ҫ����飬�ѿ�ʼ�Ľڵ����openlist��ʼ�����Աߵ�8���ڵ㣬
    //������곬����Χ����closelist��return
    //����Ѿ�����openlist�ͶԱȵ�ǰ�ڵ㵽���������Ǹ��ڵ��Gֵ�͵�ǰ�ڵ㵽ԭ�����ڵ��Gֵ
    //���ԭ����Gֵ�Ƚϴ� ���ù� �������¸�ֵGֵ ���ڵ� ��f ������½ڵ� ���뵽openlist ֱ��opellistΪ�ջ��ҵ��յ�
    while(openList.size() > 0)
    {
        current = openList[0];//������󣨴�С���󣩵Ŀ����б�ĵ�һ���ڵ㸳ֵ����ǰ�ڵ�
        if (current->x == endPos->x && current->y == endPos->y)//�жϵ�ǰ�ڵ��Ƿ�ָ��Ŀ��ڵ�
        {
            cout<<"find the path"<<endl;
            printMap();//��ӡ��ͼ����
            printPath(current);//��ӡ·�������õݹ���õķ�ʽ���ҵ�Ŀ��ڵ�����õݹ�ӵ�һ��·���ڵ㿪ʼ˳���������·����
            openList.clear();//��տ����б�
            closeList.clear();//��չر��б�
            break;
        }
        NextStep(current);
        closeList.push_back(current);//����ǰ�ڵ�ӵ��ر��б�
        openList.erase(openList.begin());//����һ�����뵽�ر��б��еĽڵ�ӿ����б���ɾ��
        sort(openList.begin(),openList.end(),compare);//��С��������
    }
}

void Astar::checkPoit( int x,int y,Node* father,int g)
{
    if (x < 0 || x > row || y < 0 || y > col)//��x��yԽ�緵��
        return;
    if (this->unWalk(x,y))//����·��ͨʱ����
        return;
    if (isContains(&closeList,x,y) != -1)//�жϸõ��Ƿ��ڹر��б��У�����ڹر��б����򷵻�
        return;
    int index;
    if ((index = isContains(&openList,x,y)) != -1)//�жϸõ��Ƿ��ڿ����б��У�����ڿ����б����򽫸õ����б��е���Ÿ�ֵ��index
    {
        Node *point = openList[index];
        if (point->g > father->g + g)
        {
            point->father = father;
            point->g = father->g + g;
            point->f = point->g + point->h;
        }
    }
    else
    {
        Node * point = new Node(x,y,father);//���õ㲻���ڿ�ʼ�б���ʱ��Ϊ�õ��¿���һ���ڵ�
        countGHF(point,endPos,g);//����ýڵ��g��f��hֵ
        openList.push_back(point);//���õ���뿪ʼ�б�
    }
}

void Astar::NextStep( Node* current )
{
    checkPoit(current->x - 1,current->y,current,WeightW);//��
    checkPoit(current->x + 1,current->y,current,WeightW);//��
    checkPoit(current->x,current->y + 1,current,WeightW);//��
    checkPoit(current->x,current->y - 1,current,WeightW);//��
    checkPoit(current->x - 1,current->y + 1,current,WeightWH);//����
    checkPoit(current->x - 1,current->y - 1,current,WeightWH);//����
    checkPoit(current->x + 1,current->y - 1,current,WeightWH);//����
    checkPoit(current->x + 1,current->y + 1,current,WeightWH);//����
}

int Astar::isContains(vector<Node*>* Nodelist, int x,int y )
{
    for (int i = 0;i < Nodelist->size();i++)
    {
        if (Nodelist->at(i)->x  == x && Nodelist->at(i)->y == y)
        {
            return i;
        }
    }
    return -1;
}

void Astar::countGHF( Node* sNode,Node* eNode,int g)
{
    int h = (abs(sNode->x - eNode->x) + abs(sNode->y - eNode->y)) * WeightW;
    int currentg = sNode->father->g + g;//��ǰ�ڵ�ĸ��ڵ��gֵ+g(WeightW = 10��WeightWH = 14)
    int f = currentg + h;//����fֵ
    sNode->f = f;
    sNode->h = h;
    sNode->g = currentg;
}

bool Astar::compare( Node* n1,Node* n2 )
{
    //printf("%d,%d",n1->f,n2->f);
    return n1->f < n2->f;
}

bool Astar::unWalk( int x,int y)
{
    if (map[x][y] == 1)
    return true;
    return false;
}

void Astar::printPath( Node* current )
{
    if (current->father != NULL)
        printPath(current->father);
    printf("(%d,%d)",current->x,current->y);
}

void Astar::printMap()
{
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            printf("%d ",map[i][j]);
        }
        printf("\n");
    }
}
