#include <iostream>

using namespace std;

const int SIZE = 32;

enum commands
{
	INSERT = 1,
	SHOW_ELEMENT,
	SHOW_LIST,
	DELETE,
	EXIT 
};

class list_element
{
public:
	list_element(int val = 0, list_element* p = NULL, list_element* n = NULL):value(val), prev(p), next(n){}
	~list_element(){cout << "This Destructor\n";}
	void setPrev(list_element* new_prev){prev = new_prev;}
	void setNext(list_element* new_next){next = new_next;}
	int  getValue(){return value;}
	list_element* getPrev(){return prev;}
	list_element* getNext(){return next;}		
private:
	int value;
	list_element* prev;
	list_element* next;
};

class linked_list
{
public:
	linked_list(list_element* h):head(h){}	
	~linked_list();
	void print_list(void);
	void get_element_value(int number);
	void add_element(int where, list_element& elem);
	void del_element(int number);
	void setHead(list_element* new_element){head = new_element;}
	list_element* getHead(void){return head;}
private:
	list_element* head;
};

linked_list::~linked_list()
{
	cout << "Destructor\n";
	list_element *cursor = head;
	list_element *next = NULL;

	while(cursor)
	{
		next = cursor->getNext();
		delete cursor;
		cursor = next;
	}
	return;
}

void linked_list::get_element_value(int number)
{
	list_element* current = head;

	while (current->getNext() && number)
	{
		number--;
		current = current->getNext();
	}	
	if (!number)
		cout << "[*]Value of an element is: "<< current->getValue() << endl;
	else
		cout << "[-]There is no such element in the list\n";

	return;
}

void linked_list::print_list()
{
	list_element* cursor = head;

	if (!cursor)
		cout << "[*]The list is empty\n";
	while(cursor != 0)
	{
		cout << " =======\n|" << cursor->getValue() << "\t|\n =======" << endl;
		cursor = cursor->getNext();
	}
}

void linked_list::del_element(int number)
{
	list_element *cursor = head;

	if (number < 0)
	{
		cout << "[-]Specify positive number\n";
		return;
	}

	if (number == 0)
	{
		if (head->getNext())
		{
			head->getNext()->setPrev(0);
			cursor = head->getNext();
			delete head;
			head = cursor;
		}
		else
		{
			delete head;
			head = NULL;
		}
		cout << "[+]Deleting head of the list\n";
		return;
	}

	while (number > 0 && (cursor->getNext() != 0))
	{
		number--;
		cursor = cursor->getNext();
	}

	if (number != 0)
	{
		cout << "[-]The number you wish to delete is higher then the length of the list\n";
		return;
	}

	if (cursor->getNext())
		cursor->getNext()->setPrev(cursor->getPrev());
	cursor->getPrev()->setNext(cursor->getNext());
	delete cursor;

	cout << "[+]List element deleted\n";
	
	return;
}

void linked_list::add_element(int where, list_element& elem)
{
	list_element* cursor;

	if (!head)
	{
		head = &elem;
		cout << "[" << elem.getValue() <<"]First element of the new list" << endl;
		return;
	}
	
	cursor = head;
	if (where <= 0)
	{
		cout << "[" << elem.getValue() <<"]Prepend to the start of the list" << endl;
		elem.setPrev(0);
		elem.setNext(cursor);
		cursor->setPrev(&elem);
		head = &elem;
		return;
	}
	
	while(where > 0 && (cursor->getNext() != 0))
	{
		cursor = cursor->getNext();
		where--;
	}

	if (!where)
	{
		cout << "[" << elem.getValue() <<"]Inserted in the list\n";
		elem.setPrev(cursor->getPrev());
		cursor->getPrev()->setNext(&elem);
		elem.setNext(cursor);
		cursor->setPrev(&elem);
		return;
	}

	if (!(cursor->getNext()))
	{
		cout << "[" << elem.getValue() <<"]Appended to the end of the list\n";
		elem.setNext(0);
		elem.setPrev(cursor);
		cursor->setNext(&elem);
		return;
	}

}

int main(void)
{
	linked_list *list = new linked_list(NULL); 
	char command[SIZE] = "";

	cout << "You have an empty list\n";
	cout << "Choose operation:\n";
	cout << "===========================================\n";
	cout << "1.Insert element into a list\n";
	cout << "2.Get value from element\n";
	cout << "3.Print list\n";
	cout << "4.Delete element from the list\n";
	cout << "5.Exit the program\n";
	cout << "===========================================\n";

	while (fgets(command, SIZE, stdin) != 0)
	{
		switch(atoi(command))
		{
			case INSERT:
			{
				char value[SIZE] = "";
				cout << "[*]Set value to a new element:\n";
				fgets(value, SIZE, stdin);
				list_element *new_element = new list_element(atoi(value));
				
				if (list->getHead())
				{
					cout << "[?]On which position do you want to insert it?\n";
					char position[SIZE] = "";
					fgets(position, SIZE, stdin);
					list->add_element(atoi(position) - 1, *new_element);	
				}
				else
				{
					list->setHead(new_element);
				}
				break;
			}
			case SHOW_ELEMENT:
			{
				if (!list->getHead())
					cout << "[*]The list is empty\n";
				else
				{
					char number[SIZE] = "";
					cout << "[?]Value of which item do you want to get?\n";
					fgets(number, SIZE, stdin);
					list->get_element_value(atoi(number) - 1);
				}
				break;
			}
			case SHOW_LIST:
				list->print_list();
				break;
			case DELETE:
			{
				if (!list->getHead())
					cout << "[*]The list is empty\n";
				else
				{
					char position[SIZE] = "";
					cout << "[?]Which element would you like to delete?\n";
					fgets(position, SIZE, stdin);
					list->del_element(atoi(position) - 1);
				}
				break;
			}
			case EXIT:
				delete list;
				return 0;
			default:
				cout << "[-]Unknown command, please try again\n";
				break;
		}
		cout << "===========================================\n";
		cout << "[*]Enter a new command:\n";
		cout << "===========================================\n";
	}
	delete list;

	return 0;
}