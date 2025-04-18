#include<iostream>
#include"Intern.h"
int main()
{
	std::vector<Intern> list;
	LoadFromFile(list, "intern.txt");

	int choice;
	
	while (true)
	{
		ShowMenu();
		std::cin >> choice;


		switch (choice)
		{
		case 1:
		{
			AddNewIntern(list);
			break;
		}
		case 2:
		{
			InternList(list);
			break;
		}
		case 3:
		{
			std::cout << "cýkýs yapýlyor...............";
				return 0;
		}
		case 4:
			saveFile(list,"intern.txt");
			break;
		
		case 5: {
			int deleteId;
			std::cout << "Silmek istediðiniz stajyerin ID'sini girin: ";
			std::cin >> deleteId;
			DeleteWithId(list, deleteId);
			break;
		}

		default:
			std::cout << "gecersiz secim!!!!";
			
		}
    }
	




}