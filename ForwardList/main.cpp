#include<iostream>
	class Forwardlist
	{
		class Element
		{
			int Data;
			Element* pNext;
			static int count; //����������� ���������� (���������������� �� �������)
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


		Element* Head;
	public:
/************************* CONSTRUCTORS ***************************/
		Forwardlist()
		{
			this->Head = nullptr;
			std::cout << "LConstructor:\t" << this << std::endl;
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
		//���������� �������� � ������ ������
		void push_front(int Data)
		{
			Element* New = new Element(Data);
			New->pNext = Head;
			Head = New;
		}

		//���������� �������� � ����� ������
		void push_back(int Data)
		{
			Element* Temp = Head; 
			while (Temp->pNext != nullptr)
			{				
				Temp = Temp->pNext;// ������� �� ��������� �������
			} 
			Element* New = new Element(Data);
			Temp->pNext = New;
		}

		// �������� �������� � ������ ������
		void pop_front()
		{
			Element* Temp = Head; 
			Head = Temp->pNext;					
			delete Temp;
		}

		// �������� �������� �� ����� ������
		void pop_back()
		{
			Element* Old = Head;
			while(Old->pNext != nullptr)
			{
				Old = Old->pNext;
			}
			Element* Temp = Head;
			while (Temp->pNext != Old)
			{
				Temp = Temp->pNext;
			}

			Temp->pNext = nullptr;
			delete Old;
			
		}

		//���������� �� �������
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

			//1) ������� �������
			Element* New = new Element(Data);
			//2) ������� �� ������ ������� � ������
			Temp = Head;
			for (int i = 0; i < index -1; i++)
			{
				Temp = Temp->pNext;
			}
			//3)��������� ����� ������� � ������
			New->pNext = Temp->pNext;
			Temp->pNext = New;
		}

		//�������� �� �������
		void erase(int index) 
		{
			Element* Old = Head;
			Element* Temp = Head;
		    if (index == 0)
			{
				Head = Head->pNext;
				delete Old;
				return;
			}			

			int y = 0;
			while (Old->pNext != nullptr)
			{
				Old = Old->pNext;
				y++;
			}

			if (index >= y)
			{
				while (Temp->pNext != Old)
				{
					Temp = Temp->pNext;
				}
				Temp->pNext = nullptr;
				delete Old;
				return;
			}
			
			Old = Head;
			for (int i = 0; i < index; i++)
			{
				Old = Old->pNext;
			}
			while (Temp->pNext != Old)
			{
				Temp = Temp->pNext;
			}
			Temp->pNext = Old->pNext;
			delete Old;
		}

		//����� ��������� �� �����
		void print()
		{
			Element* Temp = Head; // Temp - ��������(��������� ��� ������ �������� ����� �������� 
			//������ � ��������� ��������� ������)
			while (Temp)
			{
				std::cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << std::endl;
				Temp = Temp->pNext;// ������� �� ��������� �������
			}
		}
	};
#define DinDataStr

int Forwardlist::Element::count = 0;// ������������� ����������� ����������

void main()
{
	setlocale(LC_ALL, "");
#ifdef DinDataStr
	int n;
	std::cout << "Input List size:"; std::cin >> n;
	Forwardlist fl;
	for (int i = 0; i < n; i++)
	{
		fl.push_front(rand() % 100);
	}
		
	fl.print();	
	std::cout << "-----------------POP_BACK----------------" << std::endl;
	fl.pop_back();
	fl.print();
	std::cout << "-----------------ERASE----------------" << std::endl;
	int index;
	std::cout << "Input Index: "; std::cin >> index;
	fl.erase(index);
	fl.print();
#endif // DinDataStr
	
}