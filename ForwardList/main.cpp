#include<iostream>
	class Forwardlist
	{
		class Element
		{
			int Data;
			Element* pNext;
			static int count; //����������� ���������� (���������������� �� �������)
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
			//	Temp = Temp->pNext;// ������� �� ��������� �������
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
		// ���������� �������� � ����� ������
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
		// metods
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
		// �������� �������� �� ������ ������
		void pop_front()
		{
			Element* Temp = Head; 
			Head = Temp->pNext;					
			delete Temp;
		}

		//// �������� �������� �� ����� ������
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

	};

	int Forwardlist::Element::count = 0;// ������������� ����������� ����������
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