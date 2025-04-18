#pragma once
#include<vector>
#include<fstream>
#include<string>
#include<sstream>
class Intern
{
private:
	std::string Name;
	std::string Surname;
	std::string Profession;
	std::string BeginningDateTime;
	std::string FinishingDateTime;
	int Id;


public:

	Intern(const std::string& name, const std::string& surname, const std::string& profession, const std::string& beginningdatetime, const std::string finishingdatetime, const int& id) :Name(name),
		Surname(surname), Profession(profession), BeginningDateTime(beginningdatetime), FinishingDateTime(finishingdatetime), Id(id) {
	}


	void PrintInternInfo()const
	{
		std::cout << "isim:" << Name << "\n";
		std::cout << "soy isim:" << Surname << "\n";
		std::cout << "meslek:" << Profession << "\n";
		std::cout << "baslama tarihi:" << BeginningDateTime << "\n";
		std::cout << "bitis tarihi:" << FinishingDateTime << "\n";
		std::cout << "id:" << Id << "\n";
	};



	int GetId()const { return Id; };
	std::string GetName()const { return Name; }
	std::string GetSurName()const { return Surname; }
	std::string Getprofession()const { return Profession; }
	std::string GetBeginningDateTime()const { return BeginningDateTime; }
	std::string GetFÝnishingDateTime()const { return FinishingDateTime; }
};



bool IsValidDate(const std::string& date) {
	// Basit bir tarih kontrolü: MM.GG.YYYY formatýnda
	if (date.length() != 10) return false;
	if (date[2] != '.' || date[5] != '.') return false;

	for (int i = 0; i < date.length(); ++i) {
		if ((i != 2 && i != 5) && !isdigit(date[i])) {
			return false;
		}
	}

	return true;
}

void AddNewIntern(std::vector<Intern>& list)

{

	std::string Name1;
	std::string Surname1;
	std::string Profession1;
	std::string BeginningDateTime1;
	std::string FinishingDateTime1;
	int Id1;



	std::cout << "isim ekleyiniz:";
	std::cin >> Name1;

	std::cout << "soyisim ekleyiniz:";
	std::cin >> Surname1;

	std::cout << "meslek ekleyiniz:";
	std::cin >> Profession1;

	std::cout << "baslama tarihi ekleyiniz:";
	std::cin >> BeginningDateTime1;

	std::cout << "bitis tarihi ekleyiniz:";
	std::cin >> FinishingDateTime1;

	std::cout << "Id ekleyiniz:";
	std::cin >> Id1;


	if (!IsValidDate(BeginningDateTime1)) {
		std::cout << "Baþlangýç tarihi geçerli deðil!\n";
		return;
	}

	if (!IsValidDate(FinishingDateTime1)) {
		std::cout << "Bitiþ tarihi geçerli deðil!\n";
		return;
	}

	// Baþlangýç tarihinin geçerli olup olmadýðý
	// (Bu basit bir tarih karþýlaþtýrmasý, daha geliþmiþ tarih iþlemleri yapýlabilir)
	if (BeginningDateTime1 >= FinishingDateTime1) {
		std::cout << "Bitiþ tarihi, baþlangýç tarihinden önce olamaz!\n";
		return;
	}



	for (const Intern& intern : list) {
		if (intern.GetId() == Id1) {
			std::cout << "Bu ID'ye sahip bir stajyer zaten var!\n";
			return; 
		}
	}
	list.push_back(Intern(Name1, Surname1, Profession1, BeginningDateTime1, FinishingDateTime1, Id1));


}



void ShowMenu()
{
	std::cout << ">------------STAJYER MENUSU------------------<\n";
	std::cout << "1. Stajyer ekle" << "\n";
	std::cout << "2. Stajyer listesini sirala" << "\n";
	std::cout << "3. Cikis yap" << "\n";
	std::cout << "4. Dosya kaydet.\n ";
	std::cout << "5.Stajyer bilgileri sil.\n";
	std::cout << "Seciminizi yapiniz:";

}

void InternList(std::vector<Intern>& list)
{
	if (list.empty())
	{
		std::cout << "liste suanda bos.";

	}
	else
	{

		for (const Intern& intern : list)
		{
			intern.PrintInternInfo();
			std::cout << "-------------------------------------\n";

		}
	}





}



void SearchingIntern(int& Id, const std::vector<Intern> list)
{

	bool found = false;
	for (const Intern& intern : list)
	{

		if (intern.GetId() == Id)
		{
			intern.PrintInternInfo();
			found = true;
		}

	}
	if (!found)
	{
		std::cout << "aradiginiz id a-sahip bir stajyer bullunamadý";
	}



}



void saveFile(const std::vector<Intern>& list, const std::string& FileName)
{


	std::ofstream File(FileName);

	if (!File.is_open())
	{
		std::cout << "dosya acilamadi.";
		return;
	}


	for (const Intern& intern : list)
	{
		File <<"--------------------------\n"
			<<intern.GetName() << ",\n"
			<< intern.GetSurName() << ",\n"
			<< intern.Getprofession() << ",\n"
			<< intern.GetBeginningDateTime() << ",\n"
			<< intern.GetFÝnishingDateTime() << ",\n"
			<< intern.GetId() << "\n"
			<<"-----------------------------------";
	}
	File.close();
	std::cout << "stajyer bilgileri basarili bir sekilde dosyaya kaydedildi ";

}

void LoadFromFile(std::vector<Intern>& list, const std::string& filename)
{
	std::ifstream file(filename);

	if (!file.is_open())
	{
		std::cout << "Dosya bulunamadý veya açýlamadý.\n";
		return;
	}

	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string name, surname, profession, begin, finish, idStr;
		int id;

		std::getline(ss, name, ',');
		std::getline(ss, surname, ',');
		std::getline(ss, profession, ',');
		std::getline(ss, begin, ',');
		std::getline(ss, finish, ',');
		std::getline(ss, idStr, ',');

		try {
			id = std::stoi(idStr);
		}
		catch (...) {
			std::cout << "ID dönüþtürme hatasý. Satýr atlandý.\n";
			continue;
		}

		Intern intern(name, surname, profession, begin, finish, id);
		list.push_back(intern);
	}

	file.close();
	std::cout << "Stajyer bilgileri dosyadan yüklendi.\n";
}

void DeleteWithId(std::vector<Intern>& list, int& Id)
{


	bool found = false;
	for (auto it = list.begin(); it != list.end(); ++it)
	{

		if (it->GetId() == Id)
		{
			list.erase(it);
			std::cout << "ID:" << Id << "numarali stajyer silindi";
			found = true;
		}

	}
	if (!found)
	{
		std::cout << "aradiginiz id a-sahip bir stajyer bullunamadý";
	}




}