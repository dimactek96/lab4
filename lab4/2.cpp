
/*a b a&b a|b a^b
0 0  0   0   0
0 1  0   1   1
1 0  0   1   1
1 1  1   1   0
*/

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
        //cout << "data=" << data << ", size=" << size << '\n';
    for (int i = 0; i < size; i++)
        {
         if (i!=0 && i%16==0)
            cout<<"\n";
        print_in_hex(((uint8_t*) data)[i]);

        }
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

    for (int i = 0; i < size; i++)
        {
         if (i!=0 && i%4==0)
            cout<<"\n";
        print_in_binary(((uint8_t*) data)[i]);

        }
   // cout<<"\n";
}

int main()
{
    setlocale(LC_ALL,"Russian");
    uint16_t x, y, z;
    char destvie;
    int a,b;
    while (cout<<"¬ведите два числа и операци(&,|,^) между ними:\n",cin>>x>>destvie>>y)
    {
        switch(destvie)
        {
    case '&':
        z = x & y;

        print_in_hex(& x,sizeof(x));
        cout<<"& ";
        print_in_hex(& y, sizeof(y));
        cout<<"= ";
        print_in_hex(& z, sizeof(z));
        cout << "\n";
        print_in_binary(& x, sizeof(x));
        cout<<"&\n";
        print_in_binary(& y, sizeof(y));
        cout<<"=\n";
        print_in_binary(& z, sizeof(z));
        cout << "\n";
        break;

    case '|':
        z = x | y;
        print_in_hex(& x,sizeof(x));
        cout<<"| ";
        print_in_hex(& y, sizeof(y));
        cout<<"= ";
        print_in_hex(& z, sizeof(z));
        cout << "\n";
        print_in_binary(& x, sizeof(x));
        cout<<"&\n";
        print_in_binary(& y, sizeof(y));
        cout<<"=\n";
        print_in_binary(& z, sizeof(z));
        cout << "\n";
        break;

        break;
    case '^':
        z = x ^ y;
        print_in_hex(& x,sizeof(x));
        cout<<"^ ";
        print_in_hex(& y, sizeof(y));
        cout<<"= ";
        print_in_hex(& z, sizeof(z));
        cout << "\n";
        print_in_binary(& x, sizeof(x));
        cout<<"&\n";
        print_in_binary(& y, sizeof(y));
        cout<<"=\n";
        print_in_binary(& z, sizeof(z));
        cout << "\n";
        break;
    default:
        cout<<"ќшибка ввода\n";
        }
   }
}
