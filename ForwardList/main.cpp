#include<iostream>
	class Forwardlist
	{
		class Element
		{
			int Data;
			Element* pNext;
			static int count; //статическая переменная (инициализируется за классом)
		public:
			/************************* CONSTRUCTORS ***************************/
			Element(int Data, Element* pNext = nullptr)
			{
				this->Data = Data;
				this->pNext = pNext;
				count++;
				std::cout << "EConstructor:\t" << this << std::endl;
			}
			/************************* DESTRUCTOR ***************************/
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
/************************* CONSTRUCTORS ***************************/
		Forwardlist()
		{
			this->Head = nullptr;
			std::cout << "LConstructor:\t" << this << std::endl;
			this->size = 0;
		}
/************************* DESTRUCTOR ***************************/
		~Forwardlist()
		{				
			Element* Temp = Head;
			Element* Old = Head;
			
			while (Temp->pNext != nullptr)
			{
				Old = Temp;
				Temp = Temp->pNext;
				delete Old;
			}			
			delete Temp;
			std::cout << "LDestructor:\t" << this << std::endl;
		}

		
/************************* METODS ***************************/
		//ДОБАВЛЕНИЕ ЭЛЕМЕНТА В НАЧАЛО СПИСКА
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
			if (Head = nullptr)
			{
				push_front(Data);
				return;
			}

			Element* Temp = Head; 
			while (Temp->pNext != nullptr)
			{				
				Temp = Temp->pNext;// Переход на следующий элемент
			} 
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
			while (Temp->pNext->pNext = nullptr) // !!!!!!!!!!!!!!!!!!!!!!!!!!!!! Просмотр на несколько элементов вперед
			{
				Temp = Temp->pNext;
			}

			delete Temp->pNext;
			Temp->pNext = nullptr;
			size--;
		}

		//ДОБАВЛЕНИЕ ПО ИНДЕКСУ
		void insert(int index, int Data)
		{
			if(index == 0)
			{
				push_front(Data);
				return;
			} 

			Element* Temp = Head;
			
			if (index >= this->size)
			{
				push_back(Data);
				return;
			}

			//1) Создаем элемент
			Element* New = new Element(Data);
			//2) Доходим до нужной позиции в списке
			Temp = Head;
			for (int i = 0; i < index -1; i++)
			{
				Temp = Temp->pNext;
			}
			//3)Вставляем новый элемент в список
			New->pNext = Temp->pNext;
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

			if (index >= size)
			{				
				pop_back();
				return;
			}			
			
			for (int i = 0; i < index-1; i++)
			{
				Temp = Temp->pNext;
			}
			
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
			while (Temp)
				
			{				
				std::cout << coun << "\t"<< Temp <<"\t" << Temp->Data << "\t" << Temp->pNext << std::endl;
				std::cout << "-------------------------------------------------------------" << std::endl;
				Temp = Temp->pNext;// Переход на следующий элемент
				coun++;
			}
			std::cout << "\tcount = " << size << std::endl;
		}
	};
#define DinDataStr

int Forwardlist::Element::count = 0;// инициализация статической переменной

void main()
{
	system("color 0A");
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
	std::cout << "-----------------POP_BACK----------------" << std::endl;
	fl.pop_back();
	fl.print();
	std::cout << "-----------------ERASE----------------" << std::endl;	
	std::cout << "Input Index: "; std::cin >> index;
	fl.erase(index);
	fl.print();
	std::cout << "-----------------INSERT----------------" << std::endl;
	std::cout << "Input Index: "; std::cin >> index;
	fl.insert(index,1230);
	fl.print();
#endif // DinDataStr
	
}