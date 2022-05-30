#include <stdio.h>
#include <stdlib.h>
#define Max_size 10

// 인접리스트의 Edge 노드 
typedef struct Edge
{
    int Num_vertex;
    struct Edge* Edge_Vertex;
}Edge;

// 인접리스트의 헤더 노드
typedef struct header{
    int Cnt_vertex;
    struct Edge* header_V[Max_size];
}header;

// Depth First Search를 위한 visited 배열
short visited[Max_size] = {0,};

// Breadth First Search를 위한 큐 배열
int queue[Max_size+1] = {0};
int front = 0, rear = 0;

// 큐 관련 함수
void enqueue(int num); // 큐에 값을 삽입하는 함수
int dequeue(); // 큐에서 값을 삭제하는 함수


// 함수 구현
void Initialize(header* head); // 그래프 초기화하는 함수
void freeGraph(header* head); // 인접리스트에 할당된 메모리를 모두 해제 
void InsertVertex(header* head); // Vertex 삽입하는 함수
void InsertEdge(header* head); // Edge 삽입하는 함수(방향 그래프로 구현)
Edge* Search(Edge *Vertex_S, int Point_E); // Edge 삽입 위치 탐색하는 함수
void PrintGraph(header* head); // 그래프 출력하는 함수
void DepthFS(header* head,int num_v); // DFS(깊이우선탐색)하는 함수(연결리스트가 아닐  
void BreadthFS(header *head, int num_v); // BFS(너비우선탐색)하는 함수
void Init_visited(); // visited 배열 초기화하는 함수
int DuplicateCheck(Edge* toCheck, int num); // Edge 삽입 시, 중복되는 종점이 있는지 확인하는 함수

int main()
{

    printf("[----- [김지민] [2021041068] -----]\n");

    header header = {.Cnt_vertex=0 };
    char command;
    int flag =0, m;

    do{
        // 메뉴 출력
        printf("\n\n");
        printf("----------------------------------------------------------------\n");
        printf("                         Graph Searches                         \n");
        printf("----------------------------------------------------------------\n");
        printf("      Initialize Graph   = z                                    \n");
        printf("      Insert Vertex      = v          Insert Edge         = e   \n");
        printf("      Depth First Search = d          Breadth First Search = b   \n");
        printf("      Print Graph        = p          Quit                = q   \n");
        printf("----------------------------------------------------------------\n");

        // 조작키 입력
        printf("Command : ");
        scanf(" %c", &command); // 앞에 공백을 두지 않으려면 버퍼 처리를 해줘야 함.

        // 조작키에 따른 동작 수행
        switch(command){
        case 'z': case 'Z': // z, Z 조작키 입력 시, Graph 초기화
            Initialize(&header);
            break;
        case 'v': case 'V': // v, V 조작키 입력 시, Vertex 삽입
            InsertVertex(&header);
            break;
        case 'e': case 'E': // e, E 조작키 입력 시, Edge 삽입
            InsertEdge(&header);
            break;
        case 'd': case 'D': // d, D 조작키 입력 시, 깊이우선탐색 및 동떨어진 정점이나 부분그래프 유무 파악
            Init_visited(); // visited Mark배열 초기화
            for(m =0, flag = 0; m < header.Cnt_vertex; m++){ // 동떨어진 정점과 부분그래프 유무 파악 
                if(!visited[m])
                {
                    DepthFS(&header, m); // 깊이우선탐색
                    printf("\n"); // 동떨어진 부분그래프 파악을 위한 출력
                    flag++;
                }
            }
            if(flag > 1){printf("이어지지 않은 부분그래프들이 존재하는 그래프입니다.\n\n");} // 동떨어진 정점 또는 부분그래프 존재 시, 메시지 출력
            break;
        case 'b': case 'B': // b, B 조작키 입력 시, 너비우선탐색 및 동떨어진 정점이나 부분그래프 유무 파악
            Init_visited(); // visited Mark배열 초기화
            for(m = 0, flag = 0; m < header.Cnt_vertex; m++){ // 동떨어진 정점과 부분그래프 유무 파악
                if(!visited[m]){
                    BreadthFS(&header, m); // 너비우선탐색
                    printf("\n"); // 동떨어진 부분그래프 파악을 위한 출력
                    flag++;
                }
            }
            if(flag > 1){printf("이어지지 않은 부분그래프들이 존재하는 그래프입니다.\n\n");} // 동떨어진 정점 또는 부분그래프 존재 시, 메시지 출력
            break;
        case 'p': case 'P': // p, P 조작키 입력 시, Graph 출력
            PrintGraph(&header);
            break;
        case 'q': case 'Q': // q, Q 조작키 입력 시, Graph에 할당된 메모리 해제 및 프로그램 종료
            freeGraph(&header);
            break;
        default: // 그 이외의 조작키 입력 시, 안내 메시지 출력
            printf("\n\n            Concentration!!    \n\n");
            break;
        }

    }while(command != 'q' && command != 'Q'); // 조작키 q, Q 입력 시, 프로그램 종료

    return 0;
}

void Initialize(header* head){ // 초기화 함수
    if(head->Cnt_vertex!=0) // Vertex가 존재하다면, Edge 노드 삭제 및 초기화
    {
        freeGraph(head);
    }

    head->Cnt_vertex = 0; // 존재하는 Vertex 개수 초기화
    for(int i = 0; i < Max_size; i++){ // Vertex 번호 초기화
        head->header_V[i] = NULL;
        visited[i] = 0; // visited mark 초기화
    }

}

void freeGraph(header* head) // Edge노드에 할당된 메모리 모두 해제 및 초기화
{
    if(head->Cnt_vertex==0) // Vertex 존재하지 않을 경우, Edge가 없으므로 종료(전처리 검사)
    {
        return ;
    }
    Edge* temp = NULL;
    Edge* temp_B = NULL;
    for(int i = 0; i < head->Cnt_vertex; i++) // 존재하는 Vertex가 가진 Edge 모두 삭제
    {
        temp = head->header_V[i];
        temp_B = temp;
        while(temp) // Vertex마다 메모리 할당된 Edge노드 모두 삭제
        {
            temp = temp->Edge_Vertex;
            free(temp_B);
            temp_B = temp;
        }
        head->header_V[i] = NULL; // header노드들 초기화
    }
    return ;
}

void InsertVertex(header* head){ // Vertex 삽입하는 함수
    if(head->Cnt_vertex>=Max_size){ // 최대 Vertex 개수인 10을 넘어서려고 하면 메시지 출력 후 종료(전처리 검사)
        printf("Vertex의 최대 삽입 가능 개수는 10개입니다.\n\n");
        return;
    }
    
    // Vertex가 꽉 차지 않았을 경우, Vertex 삽입
    head->Cnt_vertex += 1;
}

void InsertEdge(header* head){
    int Point_S, Point_E; // 시점 번호, 종점 번호
    printf("삽입할 간선을 (시점, 종점) 형식으로 입력해주세요 : ");
    scanf("%d %d", &Point_S, &Point_E);
    if(Point_S >= head->Cnt_vertex) // 삽입되지 않은 Vertex를 시점으로 한 Edge를 삽입하려는 경우, 안내메시지 출력 후 종료(전처리 검사)
    {
        printf("No Vertex for number %d\n\n", Point_S);
        return ;
    }else if(Point_E >= head->Cnt_vertex) // 삽입되지 않은 Vertex를 종점으로 한 Edge를 삽입하려는 경우, 안내메시지 출력 후 종료(전처리 검사)
    {
        printf("No Vertex for number %d\n\n" ,Point_E);
        return ;
    }

    
    if(DuplicateCheck(head->header_V[Point_S],Point_E)==1) // 삽입하려는 Edge가 존재하면, 오류 메시지 출력 후 종료 (전처리 검사)
    {
        printf("The Edge to %d already exists.\n\n", Point_E);
        return;
    }

    // 인접리스트에 삽입할 Edge노드 생성 및 초기화
    Edge* EdgetoInsert_E = (Edge*)malloc(sizeof(Edge));
    EdgetoInsert_E->Num_vertex = Point_E;
    EdgetoInsert_E->Edge_Vertex = NULL;
    // 간선을 갖지 않거나 해당 시점으로부터 진출하는 Edge 중에 종점 번호가 가장 작을 경우, 맨 앞에 삽입
    if(head->header_V[Point_S] == NULL || head->header_V[Point_S]->Num_vertex > Point_E) 
    {
        EdgetoInsert_E->Edge_Vertex = head->header_V[Point_S];
        head->header_V[Point_S] = EdgetoInsert_E;
    }else{ // 중간 또는 마지막에 삽입될 경우
        Edge * SearchtoInsert = Search(head->header_V[Point_S], Point_E);
        EdgetoInsert_E->Edge_Vertex = SearchtoInsert->Edge_Vertex;
        SearchtoInsert->Edge_Vertex = EdgetoInsert_E;
    }
}

Edge* Search(Edge *Vertex_S, int Point_E) // Edge의 삽입할 위치를 탐색하는 함수
{
   Edge* temp = Vertex_S->Edge_Vertex;
   Edge* temp_B = Vertex_S;
   while(temp) // Edge를 오름차순으로 삽입하기 위해 위치 탐색
   {
        if(temp->Num_vertex > Point_E) // 존재하는 종점들 중에서 삽입할 종점 번호보다 큰 종점 앞에 삽입하기 위한 위치 탐색 
        {
            return temp_B;
        }
        temp_B = temp;
        temp = temp->Edge_Vertex;
   }
    return temp_B; // 삽입할 종점 번호가 존재하는 종점들보다 큰 것이므로 삽입할 위치인 마지막을 반환
}
void PrintGraph(header *head){ // 일정한 형식에 따라 Graph 출력
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
    for(int i = 0; i < head->Cnt_vertex; i++){ // Vertex마다 자기자신을 시점으로 하는 Edge 출력
        printf(" %d : ", i); // 시점 번호 출력
        temp = head->header_V[i];
        if(!temp) // Edge가 없을 경우, 메시지 출력
        {
            printf(" No Edge..\n");
            continue;
        }
        while(temp) // Edge를 모두 출력
        {
            printf("%d ", temp->Num_vertex);
            temp = temp->Edge_Vertex;
        }
        printf("\n");
    }
   printf("----------------------\n");
   printf("The number of Vertices: %d", head->Cnt_vertex); // 삽입된 Vertex 개수 출력
}

void DepthFS(header* head,int num_v) // 깊이우선탐색 함수
{
     if(head->Cnt_vertex ==0) // Vertex 존재하지 않을 경우, 메시지 출력 후 종료(전처리 검사)
    {
        printf("Nothing to Search..\n\n");
        return ;
    }
    visited[num_v] = 1; // 방문 표시
    printf("[%d]", num_v); // 해당 값 출력
    Edge* temp = NULL;
    for(temp = head->header_V[num_v]; temp; temp = temp->Edge_Vertex ){ // Vertex가 가진 Edge들 탐색
        if(!visited[temp->Num_vertex]) // Edge의 종점이 방문하지 않은 Vertex일 경우, 그 Vertex 기준으로 다시 DFS 진행
        {
            DepthFS(head, temp->Num_vertex);
        }
    }
}
void BreadthFS(header *head, int num_v) // 너비우선탐색 함수
{
    if(head->Cnt_vertex ==0) // Vertex 존재하지 않을 경우, 메시지 출력 후 종료(전처리 검사)
    {
        printf("Nothing to Search..\n\n");
        return ;
    }
    int v = 0;
    front = 0, rear = 0; // 큐의 front, rear 초기화
    Edge* temp;
    // 탐색시점의 번호 출력 및 방문 표시 후 그 Vertex 번호 큐에 삽입
    printf("[%d]", num_v);
    visited[num_v] = 1;
    enqueue(num_v);
    while(front != head->Cnt_vertex) // Vertex 개수만큼 enqueue와 dequeue가 이뤄지므로 front가 삽입된 Vertex 개수와 같다면 탐색이 모두 이뤄진 것
    {
        v = dequeue(); // 큐에서 탐색하고자 하는 Vertex 번호를 가져온다
        for(temp = head->header_V[v]; temp; temp = temp->Edge_Vertex ) // 해당 Vertex에서 진출하는 Edge들을 탐색
        {
            if(!visited[temp->Num_vertex]) // 방문하지 않은 Vertex일 경우, 그 Vertex번호를 출력하고, 큐에 번호를 저장 및 방문 표시
            {
                printf("[%d]", temp->Num_vertex);
                enqueue(temp->Num_vertex);
                visited[temp->Num_vertex] = 1;
            }
        }
    
    }
}
void enqueue(int num){ // 큐에 값을 쓰는 함수
    queue[++rear] = num;
}
int dequeue(){ // 큐에서 값을 삭제, 반환하는 함수
    return queue[++front];
}
void Init_visited() // visited 초기화 함수
{
    for(int i = 0; i< Max_size; i++) // visited 표시 배열 초기화
    {
        visited[i] = 0; 
    }
}

int DuplicateCheck(Edge* toCheck, int num) // 삽입하려는 Edge가 이미 존재하는지 확인하는 함수
{   
    Edge* temp;
    for(temp = toCheck; temp; temp = temp->Edge_Vertex) // Edge 중복 확인 검사
    {
        if(temp->Num_vertex == num){return 1;} // 삽입하고자 하는 Edge가 이미 존재한다면, 1 반환
    }
    return 0; // 검사 결과 존재하지 않으면, 0 반환
}
