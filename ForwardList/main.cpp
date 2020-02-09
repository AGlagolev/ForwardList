#include<iostream>
class Forwardlist
{
	class Element
	{
		int Data;
		Element* pNext;
		static int count; //статическая переменная (инициализируется за классом)
	public:
		/************************* GET&SET Element ***************************/
		const Element* getNext() const { return pNext; }
		const int getData() const { return Data; }

		/************************* CONSTRUCTORS Element***************************/		
		Element(int Data, Element* pNext = nullptr)
		{
			this->Data = Data;
			this->pNext = pNext;
			count++;
			std::cout << "EConstructor:\t" << this << std::endl;
		}

		/************************* DESTRUCTOR Element***************************/
		~Element()
		{
			count--;
			std::cout << "EDestructor:\t" << this << std::endl;
		}
		friend class Forwardlist;
	};

	int size;
	Element* Head;
public:
	

	/************************* METODS Forwardlist***************************/
			//ДОБАВЛЕНИЕ ЭЛЕМЕНТА В НАЧАЛО СПИСКА
	const Element* getHead() {return this->Head;}
	int getSize(){return this->size;}

	void push_front(int Data)
	{
		Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;
		size++;
	}

	//ДОБАВЛЕНИЕ ЭЛЕМЕНТА В КОНЕЦ СПИСКА
	void push_back(int Data)
	{
		Element* Temp = Head;
		if (Head == nullptr)
		{
			push_front(Data);
			return;
		}

		while (Temp->pNext != nullptr) Temp = Temp->pNext; // Переход на следующий элемент		
		
		Element* New = new Element(Data);
		Temp->pNext = New;
		size++;
	}

	// УДАЛЕНИЕ ЭЛЕМЕНТА С НАЧАЛА СПИСКА
	void pop_front()
	{
		Element* Temp = Head;
		Head = Temp->pNext;
		delete Temp;
		size--;
	}

	// УДАЛЕНИЕ ЭЛЕМЕНТА ИЗ КОНЦА СПИСКА
	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext != nullptr) Temp = Temp->pNext;// !!!!!!!!!!!!!!!!!!!!!!!!!!!!! Просмотр на несколько элементов вперед
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}

	//ДОБАВЛЕНИЕ ПО ИНДЕКСУ
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
		Element* New = new Element(Data); //1) Создаем элемент		
		for (int i = 0; i < index - 1; i++) Temp = Temp->pNext;//2) Доходим до нужной позиции в списке		
		New->pNext = Temp->pNext; //3)Вставляем новый элемент в список
		Temp->pNext = New;
		size++;
	}

	//УДАЛЕНИЕ ПО ИНДЕКСУ
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

	//ВЫВОД СТРУКТУРЫ НА ЭКРАН
	void print()
	{
		Element* Temp = Head; // Temp - итератор(указатель при помощи которого можно получить 
		//доступ к элементам структуры данных)
		int coun = 0;

		std::cout << "-------------------------------------------------------------" << std::endl;
		std::cout << "№" << "\t" << "Address" << "\t\t" << "Data" << "\t" << "pNext" << std::endl;
		std::cout << "-------------------------------------------------------------" << std::endl;
		while (Temp)
		{
			std::cout << coun << "\t" << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << std::endl;
			//std::cout << "-------------------------------------------------------------" << std::endl;
			Temp = Temp->pNext;// Переход на следующий элемент
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
		if (this == &that) return *this; // Исключение при  list1 = list1;		
		while (Head) pop_front(); // затераем предведущий список
		for (Element* Temp = that.Head; Temp != nullptr; Temp = Temp->pNext) push_back(Temp->Data); //Копируем данные в новые адреса
		
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
		std::cout << "LConstructor:\t" << this << std::endl;
		this->size = 0;
	}

	Forwardlist(std::initializer_list<int>il) :Forwardlist() // Контейнер - это объект в котором можно хранить данные 
		// Объект типа initializer_list - шаблонный класс который создается неявно компилятором при использовании {}, 
		// так как тип шаблонный <int> - указывает тип данных хранящихся в контейнере, il -это имя принимаемого параметра
		// У любого контейнера есть два метода begin и end
	{
		//std::cout << typeid(il.begin()).name() << std::endl; // запрос возвращает int const* - 
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
		std::cout << "ILConstructor" << std::endl;
	}
	// Создание листа на определенное количества элементов
	explicit Forwardlist(int number) :Forwardlist() // Делегирование конструкторов (до того как начнет работать один конструктор отработает другой) 
	// explicit запрещает неявное преобразование типа Forwardlist list1 = 5
	{
		
		while (number--) push_front(0);
		std::cout << "LConstructor:\t" << this << std::endl;
	}

	
	Forwardlist(const Forwardlist& that) :Forwardlist()  // Создает буферный объект класса и побитно копирует в него other
	{
		for (Element* Temp = that.Head; Temp != nullptr; Temp = Temp->pNext) push_back(Temp->Data);
		std::cout << "CopyConstructor" << this << std::endl;
	}

	Forwardlist(Forwardlist&& that) :Forwardlist()  // Создает буферный объект класса и побитно копирует в него other
	{
		this->Head = that.Head;
		this->size = that.size;		
		that.Head = nullptr;		
		std::cout << "MoveConstructor" << this << std::endl;
	}

	/************************* DESTRUCTOR Forwardlist***************************/
	~Forwardlist()
	{
		while (Head) pop_front(); // Destructor of elements
		std::cout << "LDestructor:\t" << this << std::endl;
	}
	friend Forwardlist operator+(const Forwardlist& left, const Forwardlist& right);
};


//#define DinDataStr
//#define BASE_CHECK
#define AM
int Forwardlist::Element::count = 0;// инициализация статической переменной

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
	//Forwardlist list3 = list1 + list2; // MoveConstructor(если отсутствует первый -CopyConstructor)
	//list3 = list2; // MoveAssignmentOperator(если отсутствует первый - CopyAssignmentOperator)
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

	/////////////////// Проверка записи случайных значений	
	//for (int i = 0; i < n; i++)
	//{
	//	list1[i] = rand() % 100;
	//}
	/////////////////// Проверка оператора []
	//for (int i = 0; i < n; i++)
	//{
	//	std::cout << list1[i] << "\t";
	//}
	//std::cout << std::endl;*/

#endif // BASE_CHECK

#ifdef AM
	int arr[] = { 3,5,8,10,23 };
	for (int i = 0; i < sizeof(arr)/sizeof(int); i++)
	{
		std::cout << arr[i] << "\t";
	}
	std::cout << std::endl;

	for(int i:arr) // повторяет предведущий цикл
	{
		std::cout << i << "\t";
	}
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

