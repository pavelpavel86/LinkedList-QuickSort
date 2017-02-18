// LinkedList+QuickSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>  
#include <stdlib.h>     /* srand, rand */
#include <time.h>  
#include <functional>
#include <string>
#include <unordered_map>
using namespace std;

class LinkedList
{
	public:
		LinkedList()
		{
			prev = NULL;
			next = NULL;
			data = NULL;
		}
		~LinkedList()
		{
			if (data != NULL)
			{
				delete data;
			}
		}

		void* getData()
		{
			return data;
		}
		void setData(void* dataIN)
		{
			data=dataIN;
		}
		LinkedList* getNext()
		{
			return next;
		}
		LinkedList* getPrev()
		{
			return prev;
		}
		void setNext(LinkedList* nextIN)
		{
			next=nextIN;
		}
		void setPrev(LinkedList* prevIN)
		{
			prev=prevIN;
		}
		int data_debug;
	private:
		LinkedList *next;
		LinkedList *prev;
		void *data;
};

void DeleteLinkedList(LinkedList* start)
{
	LinkedList* curr = start;
	LinkedList* curr_tmp = start;
	//delete everything
	while (curr != NULL)
	{
		curr_tmp = curr;
		cout << *(int *)(curr->getData()) << " ";
		curr = curr->getNext();
		delete curr_tmp;
	}
	cout << endl;
}
void PrintLinkedList(LinkedList* start)
{
	LinkedList* curr = start;
	//print everything
	while (curr != NULL)
	{
		cout << *(int *)(curr->getData())<<endl;
		curr = curr->getNext();
	}
	cout << endl;
}

int GetLengthLinkedList(LinkedList* start)
{
	int length = 0;
	LinkedList* curr = start;
	//print everything
	while (curr != NULL)
	{
		curr = curr->getNext();
		length++;
	}
	return length;
}
LinkedList* GetEndLinkedList(LinkedList* start)
{
	LinkedList* curr = start;
	while (curr->getNext() != NULL)
	{
		curr = curr->getNext();
	}
	return curr;
}

void QuickSortLinkedList(LinkedList** start, LinkedList** end)
{
	if (*start == NULL)
		return;
	if (*end == NULL)
		return;
	if (*start == *end)
		return;

	LinkedList* start_l = *start;
	LinkedList* start_r = (*start)->getNext();
	LinkedList* end_curr = *start;
	LinkedList* end_next = (*end)->getNext();
	LinkedList* start_prev = (*start)->getPrev();
	LinkedList* middle = *start;
	LinkedList* next = NULL;
	LinkedList* curr = (*start)->getNext();
	LinkedList* prev = *start;
	while (curr != end_next)
	{
		next = curr->getNext();
		if ((*(int*)(curr->getData())) < (*(int*)(middle->getData())))
		{
			if (curr->getNext() == end_next)
			{
				//curr->getPrev()->setNext(end_next);
				end_curr = curr->getPrev();
			}
			curr->getPrev()->setNext(curr->getNext());
			if (curr->getNext() != NULL)
				curr->getNext()->setPrev(curr->getPrev());
			curr->setNext(middle);
			curr->setPrev(middle->getPrev());
			if (middle->getPrev() == start_prev)
				start_l = curr;
			if (middle->getPrev() != NULL)
			{
				middle->getPrev()->setNext(curr);
			}
			middle->setPrev(curr);
		}
		else
		{
			curr->setPrev(end_curr);
			curr->setNext(end_next);
			end_curr->setNext(curr);
			end_curr = curr;
		}
		curr = next;
	}
	start_r = middle->getNext();
	//	cout << "start_l=" << (*(int*)(start_l->getData())) << endl;
	//	cout << "start_r=" << (*(int*)(start_r->getData())) << endl;
	*start = start_l;
	*end = end_curr;
	QuickSortLinkedList(&start_r, end);
	QuickSortLinkedList(start, &middle);

}

void QuickSortRemoveDuplicatesLinkedList(LinkedList** start, LinkedList** end)
{
	QuickSortLinkedList(start, end);
	LinkedList* curr = *start;
	LinkedList* prev = curr;
	while (curr->getNext() != NULL)
	{
		prev = curr;
		curr = curr->getNext();
		if ((*(int*)(curr->getData()))==(*(int*)(prev->getData())))
		{
			cout << "Hit duplicate " <<curr->data_debug<< endl;
			if (prev->getPrev() != NULL)
			{
				prev->getPrev()->setNext(curr);
				curr->setPrev(prev->getPrev());
				delete prev;
			}
			else
			{
				curr->setPrev(NULL);
				delete prev;
			}
				
		}
	}

}

void HashRemoveDuplicatesLinkedList(LinkedList** start, LinkedList** end)
{
	unordered_map<int, LinkedList*> hash;
	LinkedList* curr = *start;
	LinkedList* next = NULL;
	while (curr != NULL)
	{
		next = curr->getNext();
		int curr_int = *((int*)curr->getData());
		if (hash.count(curr_int)==0)
			hash[curr_int] = curr;
		else
		{
			cout << "Hit duplicate " << curr_int << endl;
			curr->getPrev()->setNext(next);
			if (next!=NULL)
				next->setPrev(curr->getPrev());
			delete curr;
		}

		curr = next;

	}

}

int main()
{
	/* initialize random seed: */
	srand(time(NULL));

	LinkedList* start = new LinkedList;
	int* tmp = NULL;
	tmp = new int;
	*tmp = rand();
	start->setData(tmp);
	start->data_debug = *tmp;
	LinkedList* curr=start;
	for (int i = 0; i < 10000; i++)
	{
		curr->setNext(new LinkedList);
		(curr->getNext())->setPrev(curr);
		curr = curr->getNext();
		tmp = new int;
		*tmp = rand();
		curr->data_debug = *tmp;
		curr->setData(tmp);
	}
	LinkedList* end=GetEndLinkedList(start);


	PrintLinkedList(start);
	QuickSortLinkedList(&start, &end);
	PrintLinkedList(start);

//	QuickSortRemoveDuplicatesLinkedList(&start, &end);
//	HashRemoveDuplicatesLinkedList(&start, &end);
//	PrintLinkedList(start);
//	cout << GetLengthLinkedList(start);
	DeleteLinkedList(start);
    return 0;
}

