#include<iostream>


class Forwardlist
{
	class Element
	{
		int Data;
		Element* pNext;
		static int count; //����������� ���������� (���������������� �� �������)
	public:
		/************************* GET&SET Element ***************************/
		const Element* getNext() const { return pNext; }
		const int getData() const { return Data; }

		/************************* OPERATORS Element ***************************/
		/*Element* operator++()
		{
			return this->pNext;
		}
			*/	
		/************************* CONSTRUCTORS Element***************************/		
		Element(int Data, Element* pNext = nullptr)
		{
			this->Data = Data;
			this->pNext = pNext;
			count++;
			//std::cout << "EConstructor:\t" << this << std::endl;
		}

		/************************* DESTRUCTOR Element***************************/
		~Element()
		{
			count--;
			//std::cout << "EDestructor:\t" << this << std::endl;
		}
		friend class Forwardlist;	
		Element& operator++(int)
		{
			*this = *this->pNext;
			return *this->pNext;
		}
	};

	int size;
	Element* Head;
public:
	
	
	/************************* METODS Forwardlist***************************/
			//���������� �������� � ������ ������
	const Element* getHead() {return this->Head;}
	int getSize(){return this->size;}

	void push_front(int Data)
	{
		Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;
		size++;
	}

	//���������� �������� � ����� ������
	void push_back(int Data)
	{
		Element* Temp = Head;
		if (Head == nullptr)
		{
			push_front(Data);
			return;
		}

		while (Temp->pNext != nullptr) Temp = Temp->pNext; // ������� �� ��������� �������		
		
		Element* New = new Element(Data);
		Temp->pNext = New;
		size++;
	}

	// �������� �������� � ������ ������
	void pop_front()
	{
		Element* Temp = Head;
		Head = Temp->pNext;
		delete Temp;
		size--;
	}

	// �������� �������� �� ����� ������
	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext != nullptr) Temp = Temp->pNext;// !!!!!!!!!!!!!!!!!!!!!!!!!!!!! �������� �� ��������� ��������� ������
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}

	//���������� �� �������
	void insert(int index, int Data)
	{
		if (index == 0)
		{
			push_front(Data);
			return;
		}

		if (index >= this->size)
		{
			push_back(Data);
			return;
		}

		Element* Temp = Head; 		
		Element* New = new Element(Data); //1) ������� �������		
		for (int i = 0; i < index - 1; i++) Temp = Temp->pNext;//2) ������� �� ������ ������� � ������		
		New->pNext = Temp->pNext; //3)��������� ����� ������� � ������
		Temp->pNext = New;
		size++;
	}

	//�������� �� �������
	void erase(int index)
	{
		Element* Temp = Head;
		if (index == 0)
		{
			pop_front();
			return;
		}

		if (index == size - 1)
		{
			pop_back();
			return;
		}

		if (index >= size)
		{
			std::cout << std::endl << "Error" << std::endl;
			return;
		}

		for (int i = 0; i < index - 1; i++)	Temp = Temp->pNext;

		Element* buffer = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete buffer;
		size--;
	}

	//����� ��������� �� �����
	void print()
	{
		//Element* Temp = Head; // Temp - ��������(��������� ��� ������ �������� ����� �������� 
		////������ � ��������� ��������� ������)
		int coun = 0;
		std::cout << "-------------------------------------------------------------" << std::endl;
		std::cout << "�" << "\t" << "Address" << "\t\t" << "Data" << "\t" << "pNext" << std::endl;
		std::cout << "-------------------------------------------------------------" << std::endl;
						
		for (Element* Temp = Head; Temp->pNext; (*Temp)++)
		{
			std::cout << coun << "\t" << *Temp << "\t" << Temp->Data << "\t" << *Temp->pNext << std::endl;
			coun++;			
		}
		std::cout << "\tcount = " << size << std::endl;		
	}
		
	/************************* OPERATORS Forwardlist***************************/	
	
	///////////////////////// []		
	int& operator [](int index)
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++) Temp = Temp->pNext;		
		return Temp->Data;
	}
	
	///////////////////////// =
	Forwardlist& operator=(const Forwardlist& that)
	{
		if (this == &that) return *this; // ���������� ���  list1 = list1;		
		while (Head) pop_front(); // �������� ����������� ������
		for (Element* Temp = that.Head; Temp != nullptr; Temp = Temp->pNext) push_back(Temp->Data); //�������� ������ � ����� ������
		
		std::cout << "CopyAssignmentOperator" << "\t" << this << std::endl;
		return *this;
	}
	///////////////////////// = MOVE
	Forwardlist& operator=(Forwardlist&& that)
	{
		this->Head = that.Head;
		this->size = that.size;
		that.Head = nullptr;
		std::cout << "MoveAssignmentOperator" << this << std::endl;
		return *this;
	}
	

	/************************* CONSTRUCTORS Forwardlist***************************/
	Forwardlist()
	{
		this->Head = nullptr;
		//std::cout << "LConstructor:\t" << this << std::endl;
		this->size = 0;
	}

	Forwardlist(std::initializer_list<int>il) :Forwardlist() // ��������� - ��� ������ � ������� ����� ������� ������ 
		// ������ ���� initializer_list - ��������� ����� ������� ��������� ������ ������������ ��� ������������� {}, 
		// ��� ��� ��� ��������� <int> - ��������� ��� ������ ���������� � ����������, il -��� ��� ������������ ���������
		// � ������ ���������� ���� ��� ������ begin � end
	{
		//std::cout << typeid(il.begin()).name() << std::endl; // ������ ���������� int const* - 
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
		//std::cout << "ILConstructor" << std::endl;
	}
	// �������� ����� �� ������������ ���������� ���������
	explicit Forwardlist(int number) :Forwardlist() // ������������� ������������� (�� ���� ��� ������ �������� ���� ����������� ���������� ������) 
	// explicit ��������� ������� �������������� ���� Forwardlist list1 = 5
	{
		
		while (number--) push_front(0);
		std::cout << "LConstructor:\t" << this << std::endl;
	}

	
	Forwardlist(const Forwardlist& that) :Forwardlist()  // ������� �������� ������ ������ � ������� �������� � ���� other
	{
		for (Element* Temp = that.Head; Temp != nullptr; Temp = Temp->pNext) push_back(Temp->Data);
		std::cout << "CopyConstructor" << this << std::endl;
	}

	Forwardlist(Forwardlist&& that) :Forwardlist()  // ������� �������� ������ ������ � ������� �������� � ���� other
	{
		this->Head = that.Head;
		this->size = that.size;		
		that.Head = nullptr;		
		//std::cout << "MoveConstructor" << this << std::endl;
	}

	/************************* DESTRUCTOR Forwardlist***************************/
	~Forwardlist()
	{
		while (Head) pop_front(); // Destructor of elements
		//std::cout << "LDestructor:\t" << this << std::endl;
	}
	friend Forwardlist operator+(const Forwardlist& left, const Forwardlist& right);
	//friend const Forwardlist::Element* operator++(Forwardlist::Element* w) ;
	friend std::ostream& operator<<(std::ostream& os, Forwardlist::Element& x);

	
};


//#define DinDataStr
//#define BASE_CHECK
#define AM
int Forwardlist::Element::count = 0;// ������������� ����������� ����������

void print(int arr[])
{
	//for (int i : arr) // ��������� ����������� ����
	//{
	//	std::cout << i << "\t";
	//}
	//std::cout << std::endl;
}



void main()
{
	system("color 0F");
	setlocale(LC_ALL, "");
#ifdef DinDataStr
	int n;
	std::cout << "Input List size:"; std::cin >> n;
	Forwardlist fl;
	for (int i = 0; i < n; i++)
	{
		fl.push_front(rand() % 100);
	}
	int index;
	fl.print();

	/*std::cout << "-----------------POP_BACK----------------" << std::endl;
	fl.pop_back();
	fl.print();*/

	/*std::cout << "-----------------ERASE----------------" << std::endl;
	std::cout << "Input Index: "; std::cin >> index;
	fl.erase(index);
	fl.print();*/

	std::cout << "-----------------INSERT----------------" << std::endl;
	std::cout << "Input Index: "; std::cin >> index;
	fl.insert(index, 1230);
	fl.print();

#endif // DinDataStr

#ifdef BASE_CHECK
	
	Forwardlist list1 = { 2,3,4,5,5 }; // ILConstructor
	Forwardlist list2 = { 6,7,9 };
	//Forwardlist list3 = list1 + list2; // MoveConstructor(���� ����������� ������ -CopyConstructor)
	//list3 = list2; // MoveAssignmentOperator(���� ����������� ������ - CopyAssignmentOperator)
	Forwardlist list3;	
	std::cout << "-----------------list1----------------" << std::endl;
	list1.print();
	std::cout << "-----------------list2----------------" << std::endl;
	list2.print();	
    list3 = list1 + list2; 
	std::cout << "-----------------list3----------------" << std::endl;
	list3.print();
	
	/*//int n = 5;
	//Forwardlist list1(n);

	/////////////////// �������� ������ ��������� ��������	
	//for (int i = 0; i < n; i++)
	//{
	//	list1[i] = rand() % 100;
	//}
	/////////////////// �������� ��������� []
	//for (int i = 0; i < n; i++)
	//{
	//	std::cout << list1[i] << "\t";
	//}
	//std::cout << std::endl;*/

#endif // BASE_CHECK

#ifdef AM
	//int arr[] = { 3,5,8,10,23 };
	//for (int i = 0; i < sizeof(arr)/sizeof(int); i++)
	//{
	//	std::cout << arr[i] << "\t";
	//}
	//std::cout << std::endl;

	

	Forwardlist list1 = { 2,3,4,5,5 };
	list1.print();

	Forwardlist list2 = { 6,5,4,3,8 };
	list2.print();
	//Element
	/*auto && __range = list1;
	for (auto __begin = list1.getHead(), __end = nullptr; __begin != __end; ++__begin) 
	{
		Forwardlist::Element i = *__begin;
		std::cout << i << "\t";
	}*/


	//for (int i : list1) // ��������� ����������� ����
	//{
	//	std::cout << i << "\t";
	//}
	std::cout << std::endl;
#endif // AM

}

///////////////////////// friend +
Forwardlist operator+(const Forwardlist& left, const Forwardlist& right)
{
	std::cout << "GLOBAL+_BEGIN\t" << std::endl;
	Forwardlist cat;
	cat = left;
	for (const Forwardlist::Element* Temp = right.Head; Temp; Temp = Temp->getNext()) cat.push_back(Temp->getData());
	std::cout << "GLOBAL+_END\t" << std::endl << std::endl;
	return cat;
}
//const Forwardlist::Element* operator++(Forwardlist::Element& w)
//{
//	return w.getNext();
//}
//Forwardlist::Element* operator++(Forwardlist::Element* Temp)
//{
//
//}
std::ostream& operator<<(std::ostream& os, Forwardlist::Element& x) 
{
	os << x.getNext();
	return os;
}
