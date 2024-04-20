/**
 * circularQ.c
 *
 * School of Computer Science, 
 * Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;// 큐에 저장될 요소의 자료형을 정의

typedef struct {
	element queue[MAX_QUEUE_SIZE];// 큐를 구성하는 배열
	int front, rear;// 큐의 시작과 끝을 나타내는 인덱스
}QueueType;


QueueType *createQueue(); // 큐를 생성하고 초기화하는 함수
int freeQueue(QueueType *cQ);// 큐를 해제하는 함수
int isEmpty(QueueType *cQ);// 큐가 비어있는지 확인하는 함수
int isFull(QueueType *cQ);// 큐가 가득 찼는지 확인하는 함수
void enQueue(QueueType *cQ, element item);// 큐에 요소를 추가하는 함수
void deQueue(QueueType *cQ, element* item);// 큐에서 요소를 삭제하는 함수
void printQ(QueueType *cQ); // 큐의 내용을 출력하는 함수
void debugQ(QueueType *cQ);// 큐를 디버그하는 함수
element getElement();// 사용자로부터 요소를 입력 받는 함수

int main(void)
{
	printf("[-----[son seunghye] [2023078010]-----]\n");
	QueueType *cQ = createQueue();
	element data;
	char command;

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':// 삽입
			data = getElement();// 요소 입력 받음
			enQueue(cQ, data);// 큐에 삽입
			break;
		case 'd': case 'D':// 삭제
			deQueue(cQ, &data);// 큐에서 삭제
			break;
		case 'p': case 'P':// 출력
			printQ(cQ);// 큐의 내용 출력
			break;
		case 'b': case 'B': // 디버그
			debugQ(cQ); // 큐의 내용 디버그
			break;
		case 'q': case 'Q':// 종료
   	        freeQueue(cQ);// 큐 해제
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');// q나 Q를 입력받을 때까지 반복


	return 1;
}

QueueType *createQueue()
{
	QueueType *cQ;// 큐 포인터 선언
	cQ = (QueueType *)malloc(sizeof(QueueType));// 메모리 할당
    cQ->front = 0; // front 초기화
	cQ->front = 0;// rear 초기화
	cQ->rear = 0;// 생성된 큐 포인터 반환

	return cQ;
}

int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1;// 큐가 NULL이면 해제하지 않고 바로 종료
    free(cQ);// 큐 메모리 해제
    return 1;// 성공적으로 해제되었음을 반환
}

element getElement()
{
	element item;// 입력 받을 요소 변수 선언
	printf("Input element = ");// 사용자에게 요소 입력 요구
	scanf(" %c", &item);// 요소 입력 받음
	return item;// 입력 받은 요소 반환

}


int isEmpty(QueueType *cQ)
{
    return cQ->front == cQ->rear;// front와 rear가 같으면 큐가 비어있는 것으로 판단

}


int isFull(QueueType *cQ)
{
   return (cQ->rear+1)%MAX_QUEUE_SIZE==cQ->front;// rear 다음 위치가 front와 같으면 큐가 가득 찬 것으로 판단
}


void enQueue(QueueType *cQ, element item)
{
    if (isFull(cQ)){// 큐가 가득 찼을 경우
        printf("Queue is full\n");// 가득 찼음을 알리는 메시지 출력
        return;// 함수 종료
    }
    cQ->rear = (cQ->rear+1)%MAX_QUEUE_SIZE; // rear를 한 칸 뒤로 이동
    cQ->queue[cQ->rear] = item;// 새로운 요소 추가
}

void deQueue(QueueType *cQ, element *item)
{
    if (isEmpty(cQ)) {// 큐가 비어있을 경우
		printf("Queue is empty\n");// 비어있음을 알리는 메시지 출력
		return;
	}
	cQ->front = (cQ->front+1)%MAX_QUEUE_SIZE; // front를 한 칸 뒤로 이동
	*item = cQ->queue[cQ->front];// 삭제한 요소를 item에 저장
}


void printQ(QueueType *cQ)
{
	int i, first, last;// 반복문 및 인덱스 변수 선언

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;// 첫 번째 요소의 인덱스 계산
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE; // 마지막 요소의 인덱스 계산

	printf("Circular Queue : [");

	i = first;// 출력할 요소의 인덱스 초기화
	while(i != last){// 첫 번째부터 마지막 요소까지 반복
		printf("%3c", cQ->queue[i]);// 요소 출력
		i = (i+1)%MAX_QUEUE_SIZE;// 다음 요소의 인덱스 계산

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)// 큐의 모든 요소에 대해 반복
	{
		if(i == cQ->front) {// front에 해당하는 요소인 경우
			printf("  [%d] = front\n", i);
			continue;// 다음 요소로 넘어감
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); // 요소의 인덱스와 값 출력
 
	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);// front와 rear 출력

}

