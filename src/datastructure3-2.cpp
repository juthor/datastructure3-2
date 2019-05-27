//============================================================================
// Name        : datastructure3-2.cpp
// Author      : Hyunju Kim
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
using namespace std;

struct Node
{
	string info;
	Node* next;
};

class List
{
private:
	Node* topPtr;
	int sum;//전체 개수 세기위해 설정한 변수

public:
	List();
	~List();
	void insert(string);//리스트에 원소(문자열)를 삽입하는 함수
	void remove(string);//리스트에 원소(문자열)를 삭제하는 함수
	int size() const;//리스트 원소 개수 반환
	void print();//리스트의 원소들을 오름차순으로 출력하는 함수
};


List::List()//생성자
{
	topPtr=NULL;//topPtr값 NULL로 초기화
	sum=0;//sum값 0으로 초기화
}

List::~List()//소멸자
{
	Node* tmpPtr;

	while(topPtr!=NULL)
	{
		tmpPtr=topPtr;
		topPtr=topPtr->next;
		delete tmpPtr;
	}
}

void List::insert(string id)
{
	Node* tmpPtr;
	tmpPtr=new Node;

	tmpPtr->info=id;//tmpPtr이 가르키는 info값에 id값 넣기
	tmpPtr->next=topPtr;//topPtr이 가르키는 왼쪽에 저장
	topPtr=tmpPtr;//topPtr이 가르키는 값 변경
	sum++;//값을 입력받았으니까 증가
}

void List::remove(string id)
{
	Node* tmpPtr;
	tmpPtr=new Node;
	tmpPtr=topPtr;//나중에 다시 넣기 위해서 tmpPtr에 topPtr값 넣기

	for(int i=0; i<sum; i++)
	{
		if(tmpPtr->info==id && i==0)//첫 번째에서 발견되는 경우에는 topPtr을 건드려야함
		{
			topPtr=topPtr->next;//topPtr 위치 1칸 옮겨주기
			sum--;//하나 제거하니까 빼주기

			delete tmpPtr;//tmpPtr반환
			break;
		}

		else if(tmpPtr->info==id && i>0)
		{//2번째부터 발견이니까 i가 0보다 커야하고 pointer 1개 더만들어서 건드려야함
			Node* newtmpPtr;
			newtmpPtr=new Node;
			newtmpPtr=topPtr;//원래 topPtr값을 넣기 위해 설정한 임시변수

			while(1)
			{
				if(topPtr->next==tmpPtr)//newtmpPtr이 가르키는 next값이 tmpptr의 값과 같다면
				{
					topPtr->next=tmpPtr->next;//delete될 값인 tmpPtr이 가르키는 next값을 newtmpPtr에 넣어주기
					delete tmpPtr;

					sum--;//감소
					topPtr=newtmpPtr;//다시 원래 값 가르키도록 바꿈
					break;
				}
				//그게 아니라면 topPtr이 다음값 가르키는 값으로 바꿔서 반복
				else{ topPtr=topPtr->next;}
			}
			break;
		}

		else if(tmpPtr->info==id && tmpPtr->next==NULL)
		{//마지막 값이라면 연결할 Node필요 없으니까 바로지우기
			sum--;//sum값 감소
			delete tmpPtr;//반환
			break;
		}

		else
		{
			tmpPtr=tmpPtr->next;//없으니까 다시 돌기 위해 next값으로 바꿈
		}
	}
}


int List::size() const
{
	return sum;//반환
}


void List::print()
{

	Node* tmpPtr1=topPtr;//바꾸기 위해 tmpPtr1임시변수 생성
	Node* tmpPtr2;//바꾸기 위해 tmpPtr2임시변수 생성
	Node* tmpPtr=topPtr;//나중에 다시 넣어주기 위해 저장

	for(; tmpPtr1!= NULL; tmpPtr1=tmpPtr1->next)
	{//초기값 생략, tmpPtr1이 NULL이 아닐때까지, 조건문으로 다음값  가르키도록 반복
		for(tmpPtr2=topPtr; tmpPtr2!=NULL; tmpPtr2=tmpPtr2->next)
		{//tmpPtr2의 초기값을 topPtr로 두고 NULL이 아닐 때까지, 조건문으로 다음 값 가르키도록 반복

			if(tmpPtr1->info < tmpPtr2->info)
			{//info값으로 오름차순 정렬
				string tmp;//string타입 변수생성
				//swap개념으로 자리 바꾸기
				tmp=tmpPtr1->info;
				tmpPtr1->info=tmpPtr2->info;
				tmpPtr2->info=tmp;
			}
		}
	}


	while(topPtr!=NULL)
	{
		cout<<topPtr->info<<" ";
		topPtr=topPtr->next;//다음값 가르키는 값을 topPtr에 넣어서 가르키도록
	}
	cout<<endl;
	topPtr=tmpPtr;
	//다시 출력하게 할 수 있으니까 다시 맨 앞의 노드 가르키도록

}

int main(void)
{
	List L;
	string command;//명령어
	string st_id;//학번

	while(1)
	{
		cin>>command;
		if(command=="N")//학번이 id인 학생이 수강신청을 함
		{
			cin>>st_id;
			L.insert(st_id);
		}

		else if(command=="C")//학번이 id인 학생이 수강신청을 취소함
		{
			cin>>st_id;
			//st_id를 리스트에서 삭제=>L.remove(st_id) 출력
			L.remove(st_id);
		}

		else if(command=="S")//수강 학생수를 출력
		{
			//리스트의 원소 수를 출력
			cout<<L.size()<<endl<<endl;
		}

		else if(command=="P")//수강 학생들을 학번순서(오름차순)대로 출력
		{
			//리스트의 원소들을 오름차순으로 정렬
			L.print();
			cout<<endl;
		}

		else if(command=="Q")//끝내기
		{
			break;
		}
	}

	return 0;
}
