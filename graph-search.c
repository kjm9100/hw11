#include <stdio.h>
#include <stdlib.h>
#define Max_size 10

// ��������Ʈ�� Edge ��� 
typedef struct Edge
{
    int Num_vertex;
    struct Edge* Edge_Vertex;
}Edge;

// ��������Ʈ�� ��� ���
typedef struct header{
    int Cnt_vertex;
    struct Edge* header_V[Max_size];
}header;

// Depth First Search�� ���� visited �迭
short visited[Max_size] = {0,};

// Breadth First Search�� ���� ť �迭
int queue[Max_size+1] = {0};
int front = 0, rear = 0;

// ť ���� �Լ�
void enqueue(int num); // ť�� ���� �����ϴ� �Լ�
int dequeue(); // ť���� ���� �����ϴ� �Լ�


// �Լ� ����
void Initialize(header* head); // �׷��� �ʱ�ȭ�ϴ� �Լ�
void freeGraph(header* head); // ��������Ʈ�� �Ҵ�� �޸𸮸� ��� ���� 
void InsertVertex(header* head); // Vertex �����ϴ� �Լ�
void InsertEdge(header* head); // Edge �����ϴ� �Լ�(���� �׷����� ����)
Edge* Search(Edge *Vertex_S, int Point_E); // Edge ���� ��ġ Ž���ϴ� �Լ�
void PrintGraph(header* head); // �׷��� ����ϴ� �Լ�
void DepthFS(header* head,int num_v); // DFS(���̿켱Ž��)�ϴ� �Լ�(���Ḯ��Ʈ�� �ƴ�  
void BreadthFS(header *head, int num_v); // BFS(�ʺ�켱Ž��)�ϴ� �Լ�
void Init_visited(); // visited �迭 �ʱ�ȭ�ϴ� �Լ�
int DuplicateCheck(Edge* toCheck, int num); // Edge ���� ��, �ߺ��Ǵ� ������ �ִ��� Ȯ���ϴ� �Լ�

int main()
{

    printf("[----- [������] [2021041068] -----]\n");

    header header = {.Cnt_vertex=0 };
    char command;
    int flag =0, m;

    do{
        // �޴� ���
        printf("\n\n");
        printf("----------------------------------------------------------------\n");
        printf("                         Graph Searches                         \n");
        printf("----------------------------------------------------------------\n");
        printf("      Initialize Graph   = z                                    \n");
        printf("      Insert Vertex      = v          Insert Edge         = e   \n");
        printf("      Depth First Search = d          Breadth First Search = b   \n");
        printf("      Print Graph        = p          Quit                = q   \n");
        printf("----------------------------------------------------------------\n");

        // ����Ű �Է�
        printf("Command : ");
        scanf(" %c", &command); // �տ� ������ ���� �������� ���� ó���� ����� ��.

        // ����Ű�� ���� ���� ����
        switch(command){
        case 'z': case 'Z': // z, Z ����Ű �Է� ��, Graph �ʱ�ȭ
            Initialize(&header);
            break;
        case 'v': case 'V': // v, V ����Ű �Է� ��, Vertex ����
            InsertVertex(&header);
            break;
        case 'e': case 'E': // e, E ����Ű �Է� ��, Edge ����
            InsertEdge(&header);
            break;
        case 'd': case 'D': // d, D ����Ű �Է� ��, ���̿켱Ž�� �� �������� �����̳� �κб׷��� ���� �ľ�
            Init_visited(); // visited Mark�迭 �ʱ�ȭ
            for(m =0, flag = 0; m < header.Cnt_vertex; m++){ // �������� ������ �κб׷��� ���� �ľ� 
                if(!visited[m])
                {
                    DepthFS(&header, m); // ���̿켱Ž��
                    printf("\n"); // �������� �κб׷��� �ľ��� ���� ���
                    flag++;
                }
            }
            if(flag > 1){printf("�̾����� ���� �κб׷������� �����ϴ� �׷����Դϴ�.\n\n");} // �������� ���� �Ǵ� �κб׷��� ���� ��, �޽��� ���
            break;
        case 'b': case 'B': // b, B ����Ű �Է� ��, �ʺ�켱Ž�� �� �������� �����̳� �κб׷��� ���� �ľ�
            Init_visited(); // visited Mark�迭 �ʱ�ȭ
            for(m = 0, flag = 0; m < header.Cnt_vertex; m++){ // �������� ������ �κб׷��� ���� �ľ�
                if(!visited[m]){
                    BreadthFS(&header, m); // �ʺ�켱Ž��
                    printf("\n"); // �������� �κб׷��� �ľ��� ���� ���
                    flag++;
                }
            }
            if(flag > 1){printf("�̾����� ���� �κб׷������� �����ϴ� �׷����Դϴ�.\n\n");} // �������� ���� �Ǵ� �κб׷��� ���� ��, �޽��� ���
            break;
        case 'p': case 'P': // p, P ����Ű �Է� ��, Graph ���
            PrintGraph(&header);
            break;
        case 'q': case 'Q': // q, Q ����Ű �Է� ��, Graph�� �Ҵ�� �޸� ���� �� ���α׷� ����
            freeGraph(&header);
            break;
        default: // �� �̿��� ����Ű �Է� ��, �ȳ� �޽��� ���
            printf("\n\n            Concentration!!    \n\n");
            break;
        }

    }while(command != 'q' && command != 'Q'); // ����Ű q, Q �Է� ��, ���α׷� ����

    return 0;
}

void Initialize(header* head){ // �ʱ�ȭ �Լ�
    if(head->Cnt_vertex!=0) // Vertex�� �����ϴٸ�, Edge ��� ���� �� �ʱ�ȭ
    {
        freeGraph(head);
    }

    head->Cnt_vertex = 0; // �����ϴ� Vertex ���� �ʱ�ȭ
    for(int i = 0; i < Max_size; i++){ // Vertex ��ȣ �ʱ�ȭ
        head->header_V[i] = NULL;
        visited[i] = 0; // visited mark �ʱ�ȭ
    }

}

void freeGraph(header* head) // Edge��忡 �Ҵ�� �޸� ��� ���� �� �ʱ�ȭ
{
    if(head->Cnt_vertex==0) // Vertex �������� ���� ���, Edge�� �����Ƿ� ����(��ó�� �˻�)
    {
        return ;
    }
    Edge* temp = NULL;
    Edge* temp_B = NULL;
    for(int i = 0; i < head->Cnt_vertex; i++) // �����ϴ� Vertex�� ���� Edge ��� ����
    {
        temp = head->header_V[i];
        temp_B = temp;
        while(temp) // Vertex���� �޸� �Ҵ�� Edge��� ��� ����
        {
            temp = temp->Edge_Vertex;
            free(temp_B);
            temp_B = temp;
        }
        head->header_V[i] = NULL; // header���� �ʱ�ȭ
    }
    return ;
}

void InsertVertex(header* head){ // Vertex �����ϴ� �Լ�
    if(head->Cnt_vertex>=Max_size){ // �ִ� Vertex ������ 10�� �Ѿ���� �ϸ� �޽��� ��� �� ����(��ó�� �˻�)
        printf("Vertex�� �ִ� ���� ���� ������ 10���Դϴ�.\n\n");
        return;
    }
    
    // Vertex�� �� ���� �ʾ��� ���, Vertex ����
    head->Cnt_vertex += 1;
}

void InsertEdge(header* head){
    int Point_S, Point_E; // ���� ��ȣ, ���� ��ȣ
    printf("������ ������ (����, ����) �������� �Է����ּ��� : ");
    scanf("%d %d", &Point_S, &Point_E);
    if(Point_S >= head->Cnt_vertex) // ���Ե��� ���� Vertex�� �������� �� Edge�� �����Ϸ��� ���, �ȳ��޽��� ��� �� ����(��ó�� �˻�)
    {
        printf("No Vertex for number %d\n\n", Point_S);
        return ;
    }else if(Point_E >= head->Cnt_vertex) // ���Ե��� ���� Vertex�� �������� �� Edge�� �����Ϸ��� ���, �ȳ��޽��� ��� �� ����(��ó�� �˻�)
    {
        printf("No Vertex for number %d\n\n" ,Point_E);
        return ;
    }

    
    if(DuplicateCheck(head->header_V[Point_S],Point_E)==1) // �����Ϸ��� Edge�� �����ϸ�, ���� �޽��� ��� �� ���� (��ó�� �˻�)
    {
        printf("The Edge to %d already exists.\n\n", Point_E);
        return;
    }

    // ��������Ʈ�� ������ Edge��� ���� �� �ʱ�ȭ
    Edge* EdgetoInsert_E = (Edge*)malloc(sizeof(Edge));
    EdgetoInsert_E->Num_vertex = Point_E;
    EdgetoInsert_E->Edge_Vertex = NULL;
    // ������ ���� �ʰų� �ش� �������κ��� �����ϴ� Edge �߿� ���� ��ȣ�� ���� ���� ���, �� �տ� ����
    if(head->header_V[Point_S] == NULL || head->header_V[Point_S]->Num_vertex > Point_E) 
    {
        EdgetoInsert_E->Edge_Vertex = head->header_V[Point_S];
        head->header_V[Point_S] = EdgetoInsert_E;
    }else{ // �߰� �Ǵ� �������� ���Ե� ���
        Edge * SearchtoInsert = Search(head->header_V[Point_S], Point_E);
        EdgetoInsert_E->Edge_Vertex = SearchtoInsert->Edge_Vertex;
        SearchtoInsert->Edge_Vertex = EdgetoInsert_E;
    }
}

Edge* Search(Edge *Vertex_S, int Point_E) // Edge�� ������ ��ġ�� Ž���ϴ� �Լ�
{
   Edge* temp = Vertex_S->Edge_Vertex;
   Edge* temp_B = Vertex_S;
   while(temp) // Edge�� ������������ �����ϱ� ���� ��ġ Ž��
   {
        if(temp->Num_vertex > Point_E) // �����ϴ� ������ �߿��� ������ ���� ��ȣ���� ū ���� �տ� �����ϱ� ���� ��ġ Ž�� 
        {
            return temp_B;
        }
        temp_B = temp;
        temp = temp->Edge_Vertex;
   }
    return temp_B; // ������ ���� ��ȣ�� �����ϴ� �����麸�� ū ���̹Ƿ� ������ ��ġ�� �������� ��ȯ
}
void PrintGraph(header *head){ // ������ ���Ŀ� ���� Graph ���
    if(head->Cnt_vertex ==0)
    {
        printf("Nothing to Print..\n\n");
        return ;
    }

    printf("----------------------\n");
    printf(" E(G) = (a, b)\n");
    printf("----------------------\n");
    printf(" a :      b       \n");
    printf("----------------------\n");
    Edge* temp = NULL;
    for(int i = 0; i < head->Cnt_vertex; i++){ // Vertex���� �ڱ��ڽ��� �������� �ϴ� Edge ���
        printf(" %d : ", i); // ���� ��ȣ ���
        temp = head->header_V[i];
        if(!temp) // Edge�� ���� ���, �޽��� ���
        {
            printf(" No Edge..\n");
            continue;
        }
        while(temp) // Edge�� ��� ���
        {
            printf("%d ", temp->Num_vertex);
            temp = temp->Edge_Vertex;
        }
        printf("\n");
    }
   printf("----------------------\n");
   printf("The number of Vertices: %d", head->Cnt_vertex); // ���Ե� Vertex ���� ���
}

void DepthFS(header* head,int num_v) // ���̿켱Ž�� �Լ�
{
     if(head->Cnt_vertex ==0) // Vertex �������� ���� ���, �޽��� ��� �� ����(��ó�� �˻�)
    {
        printf("Nothing to Search..\n\n");
        return ;
    }
    visited[num_v] = 1; // �湮 ǥ��
    printf("[%d]", num_v); // �ش� �� ���
    Edge* temp = NULL;
    for(temp = head->header_V[num_v]; temp; temp = temp->Edge_Vertex ){ // Vertex�� ���� Edge�� Ž��
        if(!visited[temp->Num_vertex]) // Edge�� ������ �湮���� ���� Vertex�� ���, �� Vertex �������� �ٽ� DFS ����
        {
            DepthFS(head, temp->Num_vertex);
        }
    }
}
void BreadthFS(header *head, int num_v) // �ʺ�켱Ž�� �Լ�
{
    if(head->Cnt_vertex ==0) // Vertex �������� ���� ���, �޽��� ��� �� ����(��ó�� �˻�)
    {
        printf("Nothing to Search..\n\n");
        return ;
    }
    int v = 0;
    front = 0, rear = 0; // ť�� front, rear �ʱ�ȭ
    Edge* temp;
    // Ž�������� ��ȣ ��� �� �湮 ǥ�� �� �� Vertex ��ȣ ť�� ����
    printf("[%d]", num_v);
    visited[num_v] = 1;
    enqueue(num_v);
    while(front != head->Cnt_vertex) // Vertex ������ŭ enqueue�� dequeue�� �̷����Ƿ� front�� ���Ե� Vertex ������ ���ٸ� Ž���� ��� �̷��� ��
    {
        v = dequeue(); // ť���� Ž���ϰ��� �ϴ� Vertex ��ȣ�� �����´�
        for(temp = head->header_V[v]; temp; temp = temp->Edge_Vertex ) // �ش� Vertex���� �����ϴ� Edge���� Ž��
        {
            if(!visited[temp->Num_vertex]) // �湮���� ���� Vertex�� ���, �� Vertex��ȣ�� ����ϰ�, ť�� ��ȣ�� ���� �� �湮 ǥ��
            {
                printf("[%d]", temp->Num_vertex);
                enqueue(temp->Num_vertex);
                visited[temp->Num_vertex] = 1;
            }
        }
    
    }
}
void enqueue(int num){ // ť�� ���� ���� �Լ�
    queue[++rear] = num;
}
int dequeue(){ // ť���� ���� ����, ��ȯ�ϴ� �Լ�
    return queue[++front];
}
void Init_visited() // visited �ʱ�ȭ �Լ�
{
    for(int i = 0; i< Max_size; i++) // visited ǥ�� �迭 �ʱ�ȭ
    {
        visited[i] = 0; 
    }
}

int DuplicateCheck(Edge* toCheck, int num) // �����Ϸ��� Edge�� �̹� �����ϴ��� Ȯ���ϴ� �Լ�
{   
    Edge* temp;
    for(temp = toCheck; temp; temp = temp->Edge_Vertex) // Edge �ߺ� Ȯ�� �˻�
    {
        if(temp->Num_vertex == num){return 1;} // �����ϰ��� �ϴ� Edge�� �̹� �����Ѵٸ�, 1 ��ȯ
    }
    return 0; // �˻� ��� �������� ������, 0 ��ȯ
}
