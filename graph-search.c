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

// Breath First Search�� ���� ť �迭
int queue[Max_size+1] = {0};
int front = 0, rear = 0;


// �Լ� ����
void Initialize(header* head); // �׷��� �ʱ�ȭ�ϴ� �Լ�
void freeGraph(header* head); // ��������Ʈ�� �Ҵ�� �޸𸮸� ��� ���� 
void InsertVertex(header* head); // Vertex �����ϴ� �Լ�



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
        printf("      Depth First Search = d          Breath First Search = b   \n");
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
            break;
        case 'd': case 'D': // d, D ����Ű �Է� ��, ���̿켱Ž�� �� �������� �����̳� �κб׷��� ���� �ľ�
            break;
        case 'b': case 'B': // b, B ����Ű �Է� ��, �ʺ�켱Ž�� �� �������� �����̳� �κб׷��� ���� �ľ�
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

