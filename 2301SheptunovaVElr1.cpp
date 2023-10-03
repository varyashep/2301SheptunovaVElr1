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

void printList(Node* start, int& length) // âûâîä ñïèñêà
{
	cout << "Ñïèñîê: " << endl;
	Node* iterator = start->next;
	for (int i = 0; i < length; i++)
	{
		cout << iterator->number << " ";
		iterator = iterator->next;
	}
	cout << endl;
}

void addLastElem(Node* adder, Node* start, Node* end, int& length, int toAdd) //äîáàâëåíèå ýëåìåíòà â êîíåö ñïèñêà
{
	adder = new Node;
	adder->number = toAdd;
	end->previous->next = adder;
	adder->next = end;
	adder->previous = end->previous;
	end->previous = adder;
	length++;

}

void addFirstElem(Node* adder, Node* start, int& length, int toAdd) // äîáàâëåíèå ýëåìåíòà â íà÷àëî ñïèñêà
{
	adder = new Node;
	adder->number = toAdd;
	adder->next = start->next;
	start->next->previous = adder;
	start->next = adder;
	adder->previous = start;
	length++;

}

void deleteLastElem(Node* start, Node* end, int& length)  // óäàëåíèå ïîñëåäíåãî ýëåìåíòà
{
	Node* add = end->previous;
	end->previous = add->previous;
	add->previous->next = end;
	delete add;
	length--;

}

void deleteFirstElem(Node* start, int& length) // óäàëåíèå ïåðâîãî ýëåìåíòà
{
	Node* add = start->next;
	start->next = add->next;
	add->next->previous = start;
	delete add;
	length--;

}

void addElem(Node* start, Node* end, int& length, int index) // äîáàâëåíèå ýëåìåíòà ïî èíäåêñó
{
	
	if (index == 0) { // åñëè ýëåìåíò õîòÿò äîáàâèòü íà ïåðâîå ìåñòî
		Node* add = new Node;
		cout << "Ââåäèòå çíà÷åíèå íîâîãî ýëåìåíòà: ";
		int element;
		cin >> element;
		addFirstElem(add, start, length, element);
	}
	else if ((index < length) and (index > 0)) {
		int element;
		cout << "Ââåäèòå çíà÷åíèå íîâîãî ýëåìåíòà: ";
		cin >> element;
		if (index < ceil(length / 2)) { // divide and conquer method (åñëè èíäåêñ ìåíüøå ñðåäíåãî, èäåì ñ íà÷àëà)
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
		else { // åñëè èíäåêñ áîëüøå ñðåäíåãî, èäåì ñ êîíöà
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
		cout << "Îøèáêà, ââåäåí íåñóùåñòâóþùèé èíäåêñ" << endl;
	}
}

Node* getElem(Node* start, Node* end, int& length, int index) { // íàõîæäåíèå ýëåìåíòà ïî èíäåêñó
	if ((index < length) and (index >= 0)) {
		cout << "Çíà÷åíèå ýëåìåíòà ïî èíäåêñó " << index << ": ";

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
		cout << "Îøèáêà, ââåäåí íåñóùåñòâóþùèé èíäåêñ" << endl;
	}
}

void delElem(Node* start, Node* end, int& length, int index) { // óäàëåíèå ýëåìåíòà ïî èíäåêñó
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
		cout << "Îøèáêà, ââåäåí íåñóùåñòâóþùèé èíäåêñ" << endl;
	}

}

void clearList(Node* start, int& length) // î÷èùåíèå ñïèñêà
{
	Node* del = start->next;
	while (length != 0) {
		deleteFirstElem(start, length);
	}
	
}

void replaceElem(Node* start, Node* end, int& length, int index) { // çàìåíèòü ýëåìåíò ïî èíäåêñó
	if ((index < length) and (index >= 0)) {
		int newElem;
		cout << "Ââåäèòå íîâîå çíà÷åíèå ýëåìåíòà: ";
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
		cout << "Îøèáêà, ââåäåí íåñóùåñòâóþùèé èíäåêñ" << endl;
	}
}

void reverseList(Node*& start, Node*& end, int& length) // ïåðåâåðîò ñïèñêà
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

void insertList(Node* start, Node* end, int& length, bool& inserted, Node* startSecondList, Node* endSecondList, int& lengthSecondList, int index) { // âñòàâêà äðóãîãî ñïèñêà ïî îïðåäåëåííîìó èíäåêñó
	if ((index < length) and (index >= 0)) {
		cout << "Çíà÷åíèå ýëåìåíòà ïî èíäåêñó: " << index << endl;

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
		cout << "Îøèáêà, ââåäåí íåñóùåñòâóþùèé èíäåêñ" << endl;
	}
}

void insertListLast(Node* start, Node* end, int& length, bool& inserted, Node* startSecondList, Node* endLastList, int& lengthSecondList) // âñòàâêà âòîðîãî ñïèñêà â êîíöå
{
	startSecondList->next->previous = end->previous;
	end->previous->next = startSecondList->next;
	endLastList->previous->next = end;
	end->previous = endLastList->previous;
	length += lengthSecondList;
	inserted = true;
	printList(start, length);
}

void insertListFirst(Node* start, Node* end, int& length, bool& inserted, Node* startSecondList, Node* endSecondList, int& lengthSecondList) // âñòàâêà âòîðîãî ñïèñêà â íà÷àëå
{
	endSecondList->previous->next = start->next;
	start->next->previous = endSecondList->previous;
	start->next = startSecondList->next;
	startSecondList->next->previous = start;
	length += lengthSecondList;
	inserted = true;
	printList(start, length);
}

int* containsSecondList(Node* start, Node* end, Node* startSecondList, Node* endSecondList, int length, int lengthSecondList) // ïðîâåðêà íà ñîäåðæàíèå âòîðîãî ñïèñêà â îñíîâíîì 
{
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
		cout << "Âñòàâíîé ñïèñîê ñîäåðæèòñÿ â íà÷àëüíîì" << endl;
		return indexes;
	}
	else {
		cout << "Âñòàâíîé ñïèñîê íå ñîäåðæèòñÿ â íà÷àëüíîì" << endl;
		return 0;
	}
}

void getFirstEntry(Node* start, Node* end, Node* startSecondList, Node* endSecondList, int length, int lengthSecondList) { // èíäåêñ ïåðâîãî âõîæäåíèÿ âòîðîãî ñïèñêà â íà÷àëüíûé
	int* indexes = containsSecondList(start, end, startSecondList, endSecondList, length, lengthSecondList);

	if (indexes != 0) {
		cout << "Èíäåêñ ïåðâîãî âõîæäåíèÿ âòîðîãî ñïèñêà â îñíîâíîé: " << indexes[0] << endl;
	}
	else {
		cout << "Âòîðîé ñïèñîê íå âõîäèò â îñíîâíîé" << endl;
	}
	
}

void getLastEntry(Node* start, Node* end, Node* startSecondList, Node* endSecondList, int length, int lengthSecondList) // èíäåêñ ïîñëåäíåãî âõîæäåíèÿ âòîðîãî ñïèñêà â íà÷àëüíûé
{
	int* indexes = containsSecondList(start, end, startSecondList, endSecondList, length, lengthSecondList);

	if (indexes != 0) {
		cout << "Èíäåêñ ïîñëåäíåãî âõîæäåíèÿ âòîðîãî ñïèñêà â îñíîâíîé: " << indexes[lengthSecondList-1] << endl;
	}
	else {
		cout << "Âòîðîé ñïèñîê íå âõîäèò â îñíîâíîé" << endl;
	}
}

void swap(Node* start, Node* end, int& length, int indexFirst, int indexSecond) { // îáìåí ýëåìåíòîâ ïî èíäåêñàì
	int temp;
	Node* addFirst = getElem(start, end, length, indexFirst);
	Node* addSecond = getElem(start, end, length, indexSecond);
	temp = addFirst->number;
	addFirst->number = addSecond->number;
	addSecond->number = temp;

	printList(start, length);
}



void checkLength(int length) // ïðîâåðêà íà ïóñòîòó ñïèñêà
{
	if (length == 0)
		cout << "Ñïèñîê ïóñòîé"<<endl;
	else
		cout << "Ñïèñîê íå ïóñòîé"<<endl;
}

void getLength(int length) // îïðåäåëåíèå äëèíû ñïèñêà 
{
	cout << "Äëèíà ñïèñêà: " << length << endl;
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

	cout << "Çàïîëíèòå âòîðîé ñïèñîê (äëÿ äàëüíåéøåé ðàáîòû ñ äâóìÿ ñïèñêàìè)" << endl << endl; // çàïîëíåíèå ñïèñêà äëÿ äàëüíåéøåé âñòàâêè
	if (lengthSecond == 0)
	{
		cout << "Ââåäèòå ïåðâûé ýëåìåíò äëÿ äîáàâëåíèÿ â ñïèñîê: ";
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
		cout << "Âûáåðèòå: " << endl;
		cout << "1. Äîáàâèòü ýëåìåíò â êîíåö" << endl;
		cout << "2. Äîáàâèòü ýëåìåíò â íà÷àëî" << endl;
		cout << "3. Äîáàâèòü ýëåìåíò ïî èíäåêñó" << endl;
		cout << "0. Çàêîí÷èòü ââîä è ïåðåéòè ê îñíîâíîìó ñïèñêó" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cin >> choiceBegin;
		switch (choiceBegin)
		{
		case 1:
			int lastElem;
			cout << "Ââåäèòå ýëåìåíò äëÿ äîáàâëåíèÿ: ";
			cin >> lastElem;
			addLastElem(add, headSecond, tailSecond, lengthSecond, lastElem);
			break;
		case 2:
			int newElem;
			cout << "Ââåäèòå ýëåìåíò äëÿ äîáàâëåíèÿ: ";
			cin >> newElem;
			addFirstElem(add, headSecond, lengthSecond, newElem);
			break;
		case 3:
			int getIndex;
			cout << "Ââåäèòå èíäåêñ äëÿ äîáàâëåíèÿ: ";
			cin >> getIndex;
			addElem(headSecond, tailSecond, lengthSecond, getIndex);
			break;
		}
		printList(headSecond, lengthSecond);
	} while (choiceBegin != 0);
	cout << endl << "Îñíîâíîé ñïèñîê" << endl << endl;
	do
	{
		if (lengthMain == 0)
		{
			cout << "Ââåäèòå ïåðâûé ýëåìåíò äëÿ äîáàâëåíèÿ â ñïèñîê: ";
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
		cout << "Âûáåðèòå äåéñòâèå: " << endl;
		cout << "1. Äîáàâèòü ýëåìåíò â êîíåö ñïèñêà" << endl;
		cout << "2. Äîáàâèòü ýëåìåíò â íà÷àëî ñïèñêà" << endl;
		cout << "3. Óäàëèòü ïîñëåäíèé ýëåìåíò ñïèñêà" << endl;
		cout << "4. Óäàëèòü ïåðâûé ýëåìåíò ñïèñêà" << endl;
		cout << "5. Äîáàâèòü ýëåìåíò ïî èíäåêñó" << endl;
		cout << "6. Ïîëó÷èòü ýëåìåíò ïî èíäåêñó" << endl;
		cout << "7. Óäàëèòü ýëåìåíò ïî èíäåêñó" << endl;
		cout << "8. Ïîëó÷èòü ðàçìåð ñïèñêà" << endl;
		cout << "9. Óäàëèòü âñå ýëåìåíòû ñïèñêà" << endl;
		cout << "10. Çàìåíèòü ýëåìåíò ïî èíäåêñó" << endl;
		cout << "11. Ïðîâåðêà íà ïóñòîòó ñïèñêà" << endl;
		cout << "12. Ïîìåíÿòü ïîðÿäîê ýëåìåíòîâ íà îáðàòíûé" << endl;
		cout << "13. Âñòàâèòü ñïèñîê â ñïèñîê ïî èíäåêñó" << endl;
		cout << "14. Âñòàâèòü äðóãîé ñïèñîê â êîíåö" << endl;
		cout << "15. Âñòàâèòü äðóãîé ñïèñîê â íà÷àëî" << endl;
		cout << "16. Ïðîâåðèòü íà ñîäåðæàíèå îäíîãî ñïèñêà â äðóãîì" << endl;
		cout << "17. Ïîèñê ïåðâîãî âõîæäåíèÿ ñïèñêà â ñïèñîê" << endl;
		cout << "18. Ïîèñê ïîñëåäíåãî âõîæäåíèÿ ñïèñêà â ñïèñîê" << endl;
		cout << "19. Îáìåí äâóõ ýëåìåíòîâ ñïèñêà ïî èíäåêñàì" << endl;
		cout << "0. Çàâåðøèòü ðàáîòó" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			int lastElem;
			cout << "Ââåäèòå ýëåìåíò äëÿ äîáàâëåíèÿ: ";
			cin >> lastElem;
			addLastElem(add, headMain, tailMain, lengthMain, lastElem);
			break;
		case 2:
			int firstElem;
			cout << "Ââåäèòå ýëåìåíò äëÿ äîáàâëåíèÿ: ";
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
			cout << "Ââåäèòå èíäåêñ äëÿ äîáàâëåíèÿ: ";
			int indexAdd;
			cin >> indexAdd;
			addElem(headMain, tailMain, lengthMain, indexAdd);
			break;
		case 6:
			cout << "Ââåäèòå èíäåêñ ýëåìåíòà äëÿ ïîèñêà: ";
			int findIndex;
			cin >> findIndex;
			add = getElem(headMain, tailMain, lengthMain, findIndex);
			cout << add->number << endl;
			break;
		case 7:
			cout << "Ââåäèòå èíäåêñ äëÿ óäàëåíèÿ: ";
			int delIndex;
			cin >> delIndex;
			delElem(headMain, tailMain, lengthMain, delIndex);
			break;
		case 8:
			getLength(lengthMain);
			break;
		case 9:
			clearList(headMain, lengthMain);
			break;
		case 10:
			cout << "Ââåäèòå èíäåêñ ýëåìåíòà: ";
			cin >> findIndex;
			replaceElem(headMain, tailMain, lengthMain, findIndex);
			break;
		case 11:
			checkLength(lengthMain);
			break;
		case 12:
			reverseList(headMain, tailMain, lengthMain);
			break;
		case 13:
			cout << "Ââåäèòå èíäåêñ ýëåìåíòà, ïîñëå êîòîðîãî âñòàâèòü ñïèñîê: ";
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
			cout << "Ââåäèòå èíäåêñû ýëåìåíòîâ äëÿ ïåðåñòàíîâêè: ";
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
