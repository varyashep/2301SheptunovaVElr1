#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include <iomanip>
#include <chrono>
#define LANGUAGE 1251
#define INITADD 5

using namespace std;
using namespace std::chrono;

struct Node
{
	int number;
	struct Node* next;
	struct Node* previous;
};

void printList(Node* start, int& length) // ����� ������
{
	cout << "������: " << endl;
	Node* iterator = start->next;
	for (int i = 0; i < length; i++)
	{
		cout << iterator->number << " ";
		iterator = iterator->next;
	}
	cout << endl;
}

void addLastElem(Node* adder, Node* start, Node* end, int& length, int toAdd) //���������� �������� � ����� ������
{
	adder = new Node;
	adder->number = toAdd;
	end->previous->next = adder;
	adder->next = end;
	adder->previous = end->previous;
	end->previous = adder;
	length++;

}

void addFirstElem(Node* adder, Node* start, int& length, int toAdd) // ���������� �������� � ������ ������
{
	adder = new Node;
	adder->number = toAdd;
	adder->next = start->next;
	start->next->previous = adder;
	start->next = adder;
	adder->previous = start;
	length++;

}

void deleteLastElem(Node* start, Node* end, int& length)  // �������� ���������� ��������
{
	Node* add = end->previous;
	end->previous = add->previous;
	add->previous->next = end;
	delete add;
	length--;

}

void deleteFirstElem(Node* start, int& length) // �������� ������� ��������
{
	Node* add = start->next;
	start->next = add->next;
	add->next->previous = start;
	delete add;
	length--;

}

void addElem(Node* start, Node* end, int& length, int index) // ���������� �������� �� �������
{
	if (index == 0) { // ���� ������� ����� �������� �� ������ �����
		Node* add = new Node;
		cout << "������� �������� ������ ��������: ";
		int element;
		cin >> element;
		addFirstElem(add, start, length, element);
	}
	else if ((index < length) and (index > 0)) {
		int element;
		cout << "������� �������� ������ ��������: ";
		cin >> element;
		if (index < ceil(length / 2)) { // divide and conquer method (���� ������ ������ ��������, ���� � ������)
			Node* add = start->next;
			for (int i = 1; i < index; i++) {
				add = add->next;
			}
			Node* addNew = new Node;
			addNew->number = element;
			add->next->previous = addNew;
			addNew->next = add->next;
			add->next = addNew;
			addNew->previous = add;
		}
		else { // ���� ������ ������ ��������, ���� � �����
			Node* add = end->previous;
			for (int i = 1; i < length - index; i++) {
				add = add->previous;
			}
			Node* addNew = new Node;
			addNew->number = element;
			add->previous->next = addNew;
			addNew->previous = add->previous;
			addNew->next = add;
			add->previous = addNew;
		}
		length++;
	}
	else {
		cout << "������, ������ �������������� ������" << endl;
	}
}

Node* getElem(Node* start, Node* end, int& length, int index) { // ���������� �������� �� �������

	if ((index < length) and (index >= 0)) {

		if (index < ceil(length / 2)) {
			Node* add = start->next;
			for (int i = 0; i < index; i++) {
				add = add->next;
			}
			return add;
		}
		else {
			Node* add = end->previous;
			for (int i = 1; i < length - index; i++) {
				add = add->previous;
			}
			return add;
		}
	}
	else {
		cout << "������, ������ �������������� ������" << endl;
	}
}

void delElem(Node* start, Node* end, int& length, int index) { // �������� �������� �� �������
	
	if ((index < length) and (index >= 0)) {
		if (index < ceil(length / 2)) {
			Node* add = start->next;
			for (int i = 0; i < index; i++) {
				add = add->next;
			}
			Node* del = add;
			del->next->previous = del->previous;
			del->previous->next = del->next;
		}
		else {
			Node* add = end->previous;
			for (int i = 1; i < length - index; i++) {
				add = add->previous;
			}
			Node* del = add;
			del->next->previous = del->previous;
			del->previous->next = del->next;
		}
		length--;
	}
	else
	{
		cout << "������, ������ �������������� ������" << endl;
	}
}

void clearList(Node* start, int& length) // �������� ������
{
	Node* del = start->next;
	while (length != 0) {
		deleteFirstElem(start, length);
	}
}

void replaceElem(Node* start, Node* end, int& length, int index) { // �������� ������� �� �������
	if ((index < length) and (index >= 0)) {
		int newElem;
		cout << "������� ����� �������� ��������: ";
		cin >> newElem;
		if (index < ceil(length / 2)) {
			Node* add = start->next;
			for (int i = 0; i < index; i++) {
				add = add->next;
			}
			add->number = newElem;
		}
		else {
			Node* add = end->previous;
			for (int i = 1; i < length - index; i++) {
				add = add->previous;
			}
			add->number = newElem;
		}
	}
	else {
		cout << "������, ������ �������������� ������" << endl;
	}
	
}

void reverseList(Node*& start, Node*& end, int& length) // ��������� ������
{
	Node* add = start->next;
	Node* temp = new Node;
	for (int i = 1; i <= length; i++) {
		temp->next = add->next;
		temp->previous = add->previous;
		add->next = temp->previous;
		add->previous = temp->next;
		add = temp->next;
	}
	temp = start;
	start = end;
	end = temp;
	start->next = start->previous;
	start->previous = NULL;
	end->previous = end->next;
	end->next = NULL;
}

void insertList(Node* start, Node* end, int& length, bool& inserted, Node* startSecondList, Node* endSecondList, int& lengthSecondList, int index) { // ������� ������� ������ �� ������������� �������
	
	if ((index < length) and (index >= 0)) {
		cout << "�������� �������� �� �������: " << index << endl;

		if (index < ceil(length / 2)) {
			Node* add = start->next;
			for (int i = 0; i < index; i++) {
				add = add->next;
			}
			add->next->previous = endSecondList->previous;
			endSecondList->previous->next = add->next;
			startSecondList->next->previous = add;
			add->next = startSecondList->next;
		}
		else {
			Node* add = end->previous;
			for (int i = 1; i < length - index; i++) {
				add = add->previous;
			}
			add->next->previous = endSecondList->previous;
			endSecondList->previous->next = add->next;
			startSecondList->next->previous = add;
			add->next = startSecondList->next;
		}
		length += lengthSecondList;
		inserted = true;
		printList(start, length);
	}
	else {
		cout << "������, ������ �������������� ������" << endl;
	}
	
}

void insertListLast(Node* start, Node* end, int& length, bool& inserted, Node* startSecondList, Node* endLastList, int& lengthSecondList) // ������� ������� ������ � �����
{
	startSecondList->next->previous = end->previous;
	end->previous->next = startSecondList->next;
	endLastList->previous->next = end;
	end->previous = endLastList->previous;
	length += lengthSecondList;
	inserted = true;
}

void insertListFirst(Node* start, Node* end, int& length, bool& inserted, Node* startSecondList, Node* endSecondList, int& lengthSecondList) // ������� ������� ������ � ������
{
	endSecondList->previous->next = start->next;
	start->next->previous = endSecondList->previous;
	start->next = startSecondList->next;
	startSecondList->next->previous = start;
	length += lengthSecondList;
	inserted = true;
	
}

int* containsSecondList(Node* start, Node* end, Node* startSecondList, Node* endSecondList, int length, int lengthSecondList) // �������� �� ���������� ������� ������ � �������� 
{
	auto startTime = high_resolution_clock::now();
	bool contains = false;
	Node* curFirst = start->next;
	Node* curSecond = startSecondList->next;
	int iterator = 0;
	int* indexes = new int[lengthSecondList];
	int index = 0;
	while (iterator < lengthSecondList && curFirst->next != end->next) {
		if (curFirst->number == curSecond->number) {
			indexes[iterator] = index;
			curSecond = curSecond->next;
			curFirst = curFirst->next;
			iterator++;
			index++;
		}
		else {
			if (iterator == 0) {
				curFirst = curFirst->next;
				index++;
			}
			iterator = 0;
			curSecond = startSecondList->next;
		}
	}

	if (iterator == lengthSecondList) {
		contains = true;
	}
	if (contains) {
		cout << "�������� ������ ���������� � ���������" << endl;
		return indexes;
	}
	else {
		cout << "�������� ������ �� ���������� � ���������" << endl;
		return 0;
	}
	
}

void getFirstEntry(Node* start, Node* end, Node* startSecondList, Node* endSecondList, int length, int lengthSecondList) { // ������ ������� ��������� ������� ������ � ���������
	int* indexes = containsSecondList(start, end, startSecondList, endSecondList, length, lengthSecondList);

	if (indexes != 0) {
		cout << "������ ������� ��������� ������� ������ � ��������: " << indexes[0] << endl;
	}
	else {
		cout << "������ ������ �� ������ � ��������" << endl;
	}
	
}

void getLastEntry(Node* start, Node* end, Node* startSecondList, Node* endSecondList, int length, int lengthSecondList) // ������ ���������� ��������� ������� ������ � ���������
{
	int* indexes = containsSecondList(start, end, startSecondList, endSecondList, length, lengthSecondList);

	if (indexes != 0) {
		cout << "������ ���������� ��������� ������� ������ � ��������: " << indexes[lengthSecondList-1] << endl;
	}
	else {
		cout << "������ ������ �� ������ � ��������" << endl;
	}
}

void swap(Node* start, Node* end, int& length, int indexFirst, int indexSecond) { // ����� ��������� �� ��������
	int temp;
	Node* addFirst = getElem(start, end, length, indexFirst);
	Node* addSecond = getElem(start, end, length, indexSecond);
	temp = addFirst->number;
	addFirst->number = addSecond->number;
	addSecond->number = temp;
}



void checkLength(Node* start, Node* end) // �������� �� ������� ������
{	
	Node* cur = start->next;
	if (cur == end)
		cout << "������ ������"<<endl;
	else
		cout << "������ �� ������"<<endl;
}

void getLength(Node* start, Node* end) // ����������� ����� ������ 
{
	auto startTime = high_resolution_clock::now();
	int getLength = 1;
	Node* cur = start->next;
	while (cur->next != end) {
		getLength++;
		cur = cur->next;
	}
	cout << "����� ������: " << getLength << endl;
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - startTime);
	cout << "����� ����������: " << duration.count() << endl;
}
int main()
{

	SetConsoleCP(LANGUAGE);
	SetConsoleOutputCP(LANGUAGE);

	int lengthMain = 0;
	int lengthSecond = 0;
	Node* headMain = new Node;
	Node* headSecond = new Node;
	Node* tailMain = new Node;
	Node* tailSecond = new Node;
	Node* add = NULL;
	int firstElem;
	int countAdded = 0;
	int choice;
	int choiceBegin;
	bool inserted = false;

	cout << "��������� ������ ������ (��� ���������� ������ � ����� ��������)" << endl << endl; // ���������� ������ ��� ���������� �������
	if (lengthSecond == 0)
	{
		cout << "������� ������ ������� ��� ���������� � ������: ";
		cin >> firstElem;
		add = new Node;
		add->number = firstElem;
		add->next = tailSecond;
		add->previous = headSecond;
		headSecond->next = add;
		tailSecond->previous = add;
		lengthSecond++;
		printList(headSecond, lengthSecond);
	}

	do {
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "��������: " << endl;
		cout << "1. �������� ������� � �����" << endl;
		cout << "2. �������� ������� � ������" << endl;
		cout << "3. �������� ������� �� �������" << endl;
		cout << "0. ��������� ���� � ������� � ��������� ������" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cin >> choiceBegin;
		switch (choiceBegin)
		{
		case 1:
			int lastElem;
			cout << "������� ������� ��� ����������: ";
			cin >> lastElem;
			addLastElem(add, headSecond, tailSecond, lengthSecond, lastElem);
			break;
		case 2:
			int newElem;
			cout << "������� ������� ��� ����������: ";
			cin >> newElem;
			addFirstElem(add, headSecond, lengthSecond, newElem);
			break;
		case 3:
			int getIndex;
			cout << "������� ������ ��� ����������: ";
			cin >> getIndex;
			addElem(headSecond, tailSecond, lengthSecond, getIndex);
			break;
		}
		printList(headSecond, lengthSecond);
	} while (choiceBegin != 0);
	cout << endl << "�������� ������" << endl << endl;
	do
	{
		if (lengthMain == 0)
		{
			cout << "������� ������ ������� ��� ���������� � ������: ";
			cin >> firstElem;
			add = new Node;
			add->number = firstElem;
			add->next = tailMain;
			add->previous = headMain;
			headMain->next = add;
			tailMain->previous = add;
			lengthMain++;
			printList(headMain, lengthMain);
		}

		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "�������� ��������: " << endl;
		cout << "1. �������� ������� � ����� ������" << endl;
		cout << "2. �������� ������� � ������ ������" << endl;
		cout << "3. ������� ��������� ������� ������" << endl;
		cout << "4. ������� ������ ������� ������" << endl;
		cout << "5. �������� ������� �� �������" << endl;
		cout << "6. �������� ������� �� �������" << endl;
		cout << "7. ������� ������� �� �������" << endl;
		cout << "8. �������� ������ ������" << endl;
		cout << "9. ������� ��� �������� ������" << endl;
		cout << "10. �������� ������� �� �������" << endl;
		cout << "11. �������� �� ������� ������" << endl;
		cout << "12. �������� ������� ��������� �� ��������" << endl;
		cout << "13. �������� ������ � ������ �� �������" << endl;
		cout << "14. �������� ������ ������ � �����" << endl;
		cout << "15. �������� ������ ������ � ������" << endl;
		cout << "16. ��������� �� ���������� ������ ������ � ������" << endl;
		cout << "17. ����� ������� ��������� ������ � ������" << endl;
		cout << "18. ����� ���������� ��������� ������ � ������" << endl;
		cout << "19. ����� ���� ��������� ������ �� ��������" << endl;
		cout << "0. ��������� ������" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			int lastElem;
			cout << "������� ������� ��� ����������: ";
			cin >> lastElem;
			addLastElem(add, headMain, tailMain, lengthMain, lastElem);
			break;
		case 2:
			int firstElem;
			cout << "������� ������� ��� ����������: ";
			cin >> firstElem;
			addFirstElem(add, headMain, lengthMain, firstElem);
			break;
		case 3:
			deleteLastElem(headMain, tailMain, lengthMain);
			break;
		case 4:
			deleteFirstElem(headMain, lengthMain);
			break;
		case 5:
			cout << "������� ������ ��� ����������: ";
			int indexAdd;
			cin >> indexAdd;
			addElem(headMain, tailMain, lengthMain, indexAdd);
			break;
		case 6:
			cout << "������� ������ �������� ��� ������: ";
			int findIndex;
			cin >> findIndex;
			add = getElem(headMain, tailMain, lengthMain, findIndex);
			cout << "�������� �������� �� ������� "<<findIndex<<": " << add->number << endl;
			break;
		case 7:
			cout << "������� ������ ��� ��������: ";
			int delIndex;
			cin >> delIndex;
			delElem(headMain, tailMain, lengthMain, delIndex);
			break;
		case 8:
			getLength(headMain, tailMain);
			break;
		case 9:
			clearList(headMain, lengthMain);
			break;
		case 10:
			cout << "������� ������ ��������: ";
			cin >> findIndex;
			replaceElem(headMain, tailMain, lengthMain, findIndex);
			break;
		case 11:
			checkLength(headMain, tailMain);
			break;
		case 12:
			reverseList(headMain, tailMain, lengthMain);
			break;
		case 13:
			cout << "������� ������ ��������, ����� �������� �������� ������: ";
			int insertIndex;
			cin >> insertIndex;
			insertList(headMain, tailMain, lengthMain, inserted, headSecond, tailSecond, lengthSecond, insertIndex);
			break;
		case 14:
			insertListLast(headMain, tailMain, lengthMain, inserted, headSecond, tailSecond, lengthSecond);
			break;
		case 15:
			insertListFirst(headMain, tailMain, lengthMain, inserted, headSecond, tailSecond, lengthSecond);
			break;
		case 16:
			containsSecondList(headMain, tailMain, headSecond, tailSecond, lengthMain, lengthSecond);
			break;
		case 17:
			getFirstEntry(headMain, tailMain, headSecond, tailSecond, lengthMain, lengthSecond);
			break;
		case 18:
			getLastEntry(headMain, tailMain, headSecond, tailSecond, lengthMain, lengthSecond);
			break;
		case 19:
			cout << "������� ������� ��������� ��� ������������: ";
			int index1;
			int index2;
			cin >> index1;
			cin >> index2;
			swap(headMain, tailMain, lengthMain, index1, index2);
			break;
		}
		printList(headMain, lengthMain);
	} while (choice != 0);


	return 0;
	_getch();
}