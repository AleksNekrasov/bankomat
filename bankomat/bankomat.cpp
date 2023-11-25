// bankomat.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>


int switch_case(int f)                    // случайные суммы..
{
    switch (f)
    {
    case 0:
         return 100;
         break;
    case 1:
        return 200;
        break;
    case 2:
        return 500;
        break;
    case 3:
        return 1000;
        break;
    case 4:
        return 2000;
        break;
    case 5:
        return 5000;
        break;
    }
}

void filler_bin(std::vector<int>& bank,std::ofstream& file)   // заполнение  бинарного файла
{
    for (int i = 0; i < bank.size(); i++)
    {
        file.write(reinterpret_cast<char*>(&bank[i]), sizeof(int));
    }
}

void filler(std::vector<int>& bank)                          // заполнение банкомата случайными купюрами
{
    for (int i = 0; i < 1000 - bank.size(); ++i)
    {
        int f = rand() % 6;
        bank.push_back(switch_case(f));
    }
}

int cashback(int sum, int banknote, std::vector<int>& bank)               // выдача наличных банкоматом
{
    int cash = 0;                                 // количество купюр, определенного номинала.
    cash = sum / banknote;

    if (cash > 0)
    {
        for (auto i = bank.begin(); i != bank.end();)
        {
            if (bank.size() == 0)                      // если кончились купюры в банкомате 
            {
                return 1;
            }
            if (*i == banknote)                   // у меня был стандартный цикл for(int i = 0; i < bank.size(); i++)
            {                                     //  if(bank[i]== banknote) { bank.erase(i)}     - НО КОМПИЛЯТОР НА ЭТО РУГАЕТСЯ!!
                i = bank.erase(i);               // ТУТ Я НЕ ПОНИМАЮ ЛОГИКИ  как ЭТО i = удалению ячейки в банке, и ячейка удаляется..?
                cash --;
                if (cash == 0)
                {
                    return (sum % banknote);
                }
            }
            else
            {
                ++i;
            }
        }  
    }
    return (sum % banknote + cash * banknote);
}

int main()   
{
    std::srand(std::time(nullptr));
    std::vector <int> bank;             //вектор хранящихся купюр
    std::string path = "bank.bin";
    char sign;                          // символ- ввод пользователем '+' или '-'
    int sum = 0;                       // СУММА, ЗАПРАШИВАЕМАЯ ПОЛЬЗОВАТЕЛЕМ!!!
    int banknote = 0;                  // БАНКНОТЫ (номиналы) , ХРАНЯЩИЕСЯ В БАНКОМАТЕ
    int value;
    std::ifstream ifile(path, std::ios::binary);

    if (!ifile.is_open())
    {
        std::cerr << "File is NOT open!";
        return 1;
    }                                      
    while (ifile.read(reinterpret_cast<char*>(&value), sizeof(int))) 
    {
        bank.push_back(value);
    }

   
    ifile.close();
        std::ofstream file(path, std::ios::binary);   // создаем-открываем файл в бирарном виде

        if (!file.is_open())                          // проверка на открытие файла
        {
            std::cerr << "File is NOT open!";
            return 1;
        }

        std::cout << "enter the command + or -   :";
        std::cin >> sign;
        if (sign == '+')
        {
            filler(bank);                  // заполняем вектор-банк случайными купюрами
            filler_bin(bank, file);        // сохраняем все в бинарном файле.
        }

        else if (sign == '-')
        {
            do
            {
                std::cout << "enter an amount that is a multiple of 100: ";
                std::cin >> sum;
            } while (sum % 100 != 0);

            banknote = 5000;                             // вызываем фукцию для проверки наличия необходимых банкнот
            sum = cashback(sum, banknote, bank);         // для выдачи интересующей суммы.

            banknote = 2000;
            sum = cashback(sum, banknote, bank);

            banknote = 1000;
            sum = cashback(sum, banknote, bank);

            banknote = 500;
            sum = cashback(sum, banknote, bank);

            banknote = 200;
            sum = cashback(sum, banknote, bank);

            banknote = 100;
            sum = cashback(sum, banknote, bank);

            if (sum > 1)                                   // если нет в наличии нужных купюр для выдачи суммы                             
            {
                std::cout << " Sorry, the ATM does not have enough banknotes to dispense this amount.";
            }
            else if (sum == 1)                            // при заканчивании купюр в функции cashback  нам возвращается sum = 1;
            {
                std::cout << "there is not enough money in the ATM ";
            }
            else if (sum == 0)                             // если вся сумма в банкоматев наличии 
            {
                std::cout << "Take your money";
                filler_bin(bank, file);
            }


        }
        else std::cout << "unidentified command";
        file.close();
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
