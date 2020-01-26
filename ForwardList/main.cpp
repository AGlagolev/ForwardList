#include<iostream>
	class Forwardlist
	{
		class Element
		{
			int Data;
			Element* pNext;
			static int count; //статическая переменная (инициализируется за классом)
		public:
			Element(int Data, Element* pNext = nullptr)
			{
				this->Data = Data;
				this->pNext = pNext;
				count++;
				std::cout << "EConstructor:\t" << this << std::endl;
			}
			~Element()
			{
				count--;
				std::cout << "EDestructor:\t" << this << std::endl;
			}
			friend class Forwardlist;
		};


		Element* Head;
	public:
		Forwardlist()
		{
			this->Head = nullptr;
			std::cout << "LConstructor:\t" << this << std::endl;
		}
		~Forwardlist()
		{			
			//Element* Temp = Head; 
			//while (Temp)
			//{
			//	Temp = Temp->pNext;// Переход на следующий элемент
			//}
			std::cout << "LDestructor:\t" << this << std::endl;
		}
////////////////////////////////////////////////////////////////////////////
		void push_front(int Data)
		{
			Element* New = new Element(Data);
			New->pNext = Head;
			Head = New;
		}
		// Добавление элемента в конец списка
		void push_back(int Data)
		{
			Element* Temp = Head; 
			while (Temp->pNext != nullptr)
			{				
				Temp = Temp->pNext;// Переход на следующий элемент
			} 
			Element* New = new Element(Data);
			Temp->pNext = New;
		}
		// metods
		void print()
		{
			Element* Temp = Head; // Temp - итератор(указатель при помощи которого можно получить 
			//доступ к элементам структуры данных)
			while (Temp)
			{
				std::cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << std::endl;
				Temp = Temp->pNext;// Переход на следующий элемент
			}
		}
		// удаление элемента из начала списка
		void pop_front()
		{
			Element* Temp = Head; 
			Head = Temp->pNext;					
			delete Temp;
		}

		//// удаление элемента из конца списка
		//void pop_back()
		//{
		//	Element* Temp = Head;
		//	while(Temp->pNext != nullptr)
		//	{

		//	}
		//	
		//	delete Temp;
		//}

		void insert(int index, int Data)
		{
			if(index == 0)
			{
				push_front(Data);
				return;
			} 

			Element* Temp = Head;
			int y = 0;
			while(Temp->pNext != nullptr)
			{
				Temp = Temp->pNext;
				y++;
			}

			if (index >= y)
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
		}

	};

	int Forwardlist::Element::count = 0;// инициализация статической переменной
void main()
{
	setlocale(LC_ALL, "");

	int n;
	std::cout << "Input List size:"; std::cin >> n;
	Forwardlist fl;
	
	for (int i = 0; i < n; i++)
	{
		fl.push_front(rand() % 100);
	}
	fl.push_back(123);
	fl.print();
	/*std::cout << "--------------------------------------" << std::endl;
	fl.pop_front();
	fl.print();*/
	std::cout << "--------------------------------------" << std::endl;
	int index;
	int data;
	std::cout << "Input Index: "; std::cin >> index;
	std::cout << "Input value: "; std::cin >> data;
	fl.insert(index, data);
	fl.print();
}