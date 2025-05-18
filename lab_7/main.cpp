#include "inputCheck.h"
#include "header.h"
#include "generate.h"
#include <iostream>
#include <locale>


using namespace mylib;
using namespace generate;
using namespace std;

int main(){
    setlocale(LC_ALL,"RU");
    HashTable ht;
    cout << "30.\tСоздать хеш-таблицу со случайными строковыми ключами и найти запись с наименьшей длиной ключа." << endl;
    while (true){
        cout << "Выберите действие:\n"
                "1- Ввести ключ\n"
                "2- Найти самый короткий ключ\n"
                "3- Вывести всю хэш-таблицу\n"
                "4- Выйти" << endl;
        int solution=checkYourSolution(4);
        if(solution==1){
            cout << "Введите количество ключей(случайные строки с кол-вом символов от 1 до 10):" << endl;
            int solutionStr= checkTryToInputMaxSizeOfSmth();
            string rstr;
            for (int i = 1; i <= solutionStr; i++) {
                rstr= generateRandomString(10);
                ht.insert(rstr);
            }

        }
        else if(solution==2){
            ht.findShortestKey();
        }
        else if(solution==3){
            ht.print();
        }
        else{
            cout << "Произошёл выход." << endl;
            break;
        }
    }

}
// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.