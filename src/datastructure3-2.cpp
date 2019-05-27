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
	int sum;//��ü ���� �������� ������ ����

public:
	List();
	~List();
	void insert(string);//����Ʈ�� ����(���ڿ�)�� �����ϴ� �Լ�
	void remove(string);//����Ʈ�� ����(���ڿ�)�� �����ϴ� �Լ�
	int size() const;//����Ʈ ���� ���� ��ȯ
	void print();//����Ʈ�� ���ҵ��� ������������ ����ϴ� �Լ�
};


List::List()//������
{
	topPtr=NULL;//topPtr�� NULL�� �ʱ�ȭ
	sum=0;//sum�� 0���� �ʱ�ȭ
}

List::~List()//�Ҹ���
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

	tmpPtr->info=id;//tmpPtr�� ����Ű�� info���� id�� �ֱ�
	tmpPtr->next=topPtr;//topPtr�� ����Ű�� ���ʿ� ����
	topPtr=tmpPtr;//topPtr�� ����Ű�� �� ����
	sum++;//���� �Է¹޾����ϱ� ����
}

void List::remove(string id)
{
	Node* tmpPtr;
	tmpPtr=new Node;
	tmpPtr=topPtr;//���߿� �ٽ� �ֱ� ���ؼ� tmpPtr�� topPtr�� �ֱ�

	for(int i=0; i<sum; i++)
	{
		if(tmpPtr->info==id && i==0)//ù ��°���� �߰ߵǴ� ��쿡�� topPtr�� �ǵ������
		{
			topPtr=topPtr->next;//topPtr ��ġ 1ĭ �Ű��ֱ�
			sum--;//�ϳ� �����ϴϱ� ���ֱ�

			delete tmpPtr;//tmpPtr��ȯ
			break;
		}

		else if(tmpPtr->info==id && i>0)
		{//2��°���� �߰��̴ϱ� i�� 0���� Ŀ���ϰ� pointer 1�� ������ �ǵ������
			Node* newtmpPtr;
			newtmpPtr=new Node;
			newtmpPtr=topPtr;//���� topPtr���� �ֱ� ���� ������ �ӽú���

			while(1)
			{
				if(topPtr->next==tmpPtr)//newtmpPtr�� ����Ű�� next���� tmpptr�� ���� ���ٸ�
				{
					topPtr->next=tmpPtr->next;//delete�� ���� tmpPtr�� ����Ű�� next���� newtmpPtr�� �־��ֱ�
					delete tmpPtr;

					sum--;//����
					topPtr=newtmpPtr;//�ٽ� ���� �� ����Ű���� �ٲ�
					break;
				}
				//�װ� �ƴ϶�� topPtr�� ������ ����Ű�� ������ �ٲ㼭 �ݺ�
				else{ topPtr=topPtr->next;}
			}
			break;
		}

		else if(tmpPtr->info==id && tmpPtr->next==NULL)
		{//������ ���̶�� ������ Node�ʿ� �����ϱ� �ٷ������
			sum--;//sum�� ����
			delete tmpPtr;//��ȯ
			break;
		}

		else
		{
			tmpPtr=tmpPtr->next;//�����ϱ� �ٽ� ���� ���� next������ �ٲ�
		}
	}
}


int List::size() const
{
	return sum;//��ȯ
}


void List::print()
{

	Node* tmpPtr1=topPtr;//�ٲٱ� ���� tmpPtr1�ӽú��� ����
	Node* tmpPtr2;//�ٲٱ� ���� tmpPtr2�ӽú��� ����
	Node* tmpPtr=topPtr;//���߿� �ٽ� �־��ֱ� ���� ����

	for(; tmpPtr1!= NULL; tmpPtr1=tmpPtr1->next)
	{//�ʱⰪ ����, tmpPtr1�� NULL�� �ƴҶ�����, ���ǹ����� ������  ����Ű���� �ݺ�
		for(tmpPtr2=topPtr; tmpPtr2!=NULL; tmpPtr2=tmpPtr2->next)
		{//tmpPtr2�� �ʱⰪ�� topPtr�� �ΰ� NULL�� �ƴ� ������, ���ǹ����� ���� �� ����Ű���� �ݺ�

			if(tmpPtr1->info < tmpPtr2->info)
			{//info������ �������� ����
				string tmp;//stringŸ�� ��������
				//swap�������� �ڸ� �ٲٱ�
				tmp=tmpPtr1->info;
				tmpPtr1->info=tmpPtr2->info;
				tmpPtr2->info=tmp;
			}
		}
	}


	while(topPtr!=NULL)
	{
		cout<<topPtr->info<<" ";
		topPtr=topPtr->next;//������ ����Ű�� ���� topPtr�� �־ ����Ű����
	}
	cout<<endl;
	topPtr=tmpPtr;
	//�ٽ� ����ϰ� �� �� �����ϱ� �ٽ� �� ���� ��� ����Ű����

}

int main(void)
{
	List L;
	string command;//��ɾ�
	string st_id;//�й�

	while(1)
	{
		cin>>command;
		if(command=="N")//�й��� id�� �л��� ������û�� ��
		{
			cin>>st_id;
			L.insert(st_id);
		}

		else if(command=="C")//�й��� id�� �л��� ������û�� �����
		{
			cin>>st_id;
			//st_id�� ����Ʈ���� ����=>L.remove(st_id) ���
			L.remove(st_id);
		}

		else if(command=="S")//���� �л����� ���
		{
			//����Ʈ�� ���� ���� ���
			cout<<L.size()<<endl<<endl;
		}

		else if(command=="P")//���� �л����� �й�����(��������)��� ���
		{
			//����Ʈ�� ���ҵ��� ������������ ����
			L.print();
			cout<<endl;
		}

		else if(command=="Q")//������
		{
			break;
		}
	}

	return 0;
}
