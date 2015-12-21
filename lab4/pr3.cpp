#include <conio.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include <exception>
#include <stdexcept>
#include <limits>
#include <iostream>
#include <istream>
#include <fstream>
#include <bitset>
#include <cstddef>
using std::cout;
using std::endl;
using std::cin;
using namespace std;

void print_nibble(uint8_t nibble)
{
    char c;
    if (0 <= nibble && nibble <= 9)
        {
        c = '0' + nibble;
        cout << c;
        }
    else if (nibble <= 15)
    {
    c = 'A' + (nibble - 10);
    cout << c;
    }
    else cout<< "error";
}
void print_in_hex(uint8_t byte)
{

    print_nibble(byte >> 4);
    print_nibble(byte & 0x0F);
    cout << ' ';
}
void print_in_hex(const void* data, size_t size)
{

    for (int i = 0; i < size; i++)
        {
         if (i!=0 && i%16==0)
            cout<<"\n";
        print_in_hex(((uint8_t*) data)[i]);
        }
    cout<<"\n";
}


void print_bit(uint8_t bit)
{
    char c;
    if (bit == 0)
        {
        c = '0';
        cout << c;
        }
    else if (bit == 1)
    {
        c = '1';
        cout << c;
    }
    else cout<< "error";
}
void print_in_binary(uint8_t byte)
{
    for (int i=7;i>=0;i--)
         print_bit((byte>> i)&0x01);
    cout << ' ';
}
void print_in_binary(const void* data, size_t size)
{
        //cout << "data=" << data << ", size=" << size << '\n';
    for (int i = 0; i < size; i++)
        {
         if (i!=0 && i%4==0)
            cout<<"\n";
        print_in_binary(((uint8_t*) data)[i]);

        }
    cout<<"\n";
}

struct Student
{
    char name[16+1];
    int year;
    double sredbal;
    uint8_t pol : 1;  // 2 = 0010
    int prodkyrs;
    Student* starosta;
};
#define PRINT_INFO(name) \
    cout << "Адрес поля " #name ": " << & students[1].name << "\n"; \
    cout << "Смещение: " << offsetof(Student, name) << "\n"; \
    cout << "размер: " << sizeof(students[1].name) << "\n";\
    cout << "В 16-ом представлении\n";\
    print_in_hex(& students[1].name, sizeof(students[1].name)); \
    cout << "В 2-ом представлении\n"; \
    print_in_binary(& students[1].name,sizeof(students[1].name)); \
    cout<<"\n";

#define PRINT_ADDR(name) \
    cout << #name ": addr. "; \
    print_in_hex(offsetof(Student, name)); \
    cout << "- "; \
    print_in_hex(offsetof(Student, name) + sizeof(students[i].name) - 1); \
    cout << "\n"

int main()
 {

    setlocale(LC_ALL,"Russian");
    Student students[3];
    students[0] = Student{"Misha",2013,5,1,3,0};
    students[1] = Student{"Vasy",2013,4.5,1,2,&students[0]};
    students[2] = Student{"Dima",2013,3,1,1,&students[0]};
    cout << "Адресс массива; " << students << "\n";
    cout<< "\n";
    for (int i=0;i<3;++i)
    {
        cout << "Адрес элемента: " << & students[i] << "\n";
        cout << "Размер элемента: " << sizeof(students[i]) << "\n";
        cout<< "\n";

    }

    PRINT_INFO(name);
    PRINT_INFO(year);
    PRINT_INFO(sredbal);
    PRINT_INFO(prodkyrs);
    PRINT_INFO(starosta);
    for (int i = 0; i < 3; i++) {
        cout << "student[" << i << "]:\n";
        cout << "\n";
        cout << "x0 x1 x2 x3|x4 x5 x6 x7|x8 x9 xA xB|xC xD xE xF\n";
        print_in_hex(& students[i], sizeof(students[i]));
        cout << "\n";
        PRINT_ADDR(name);
        PRINT_ADDR(year);
        PRINT_ADDR(sredbal);
        PRINT_ADDR(prodkyrs);
        PRINT_ADDR(starosta);
        cout << "\n";
    }
 }





