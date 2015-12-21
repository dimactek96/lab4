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
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;

struct CompareByLength {
    bool operator()( const char* s1, const char* s2 ) {
        if (strlen(s1) < strlen(s2)) {
            return true;
        } else {
            return false;
        }
    }
};
int main()
{
    setlocale(LC_ALL,"Russian");
    char name[256+1];

    char zapr_simv[] = {'*','"','<','>','?','|'};
    bool is_ok = true;
    while (true)
    {
        cout<<"Введите имя файла\n";
        cin>>name;
        for (int i = 0; i < sizeof(zapr_simv); i++)
        {
            if (strchr(name, zapr_simv[i]) != 0) {
                is_ok = false;
                break;
            }
        }
        if (is_ok) {
            char* p = strrchr(name, ':');
            if (p != 0) {
                int n = p - name;
                if (n != 1) {
                    is_ok = false;
                } else if (! isalpha(name[0])) {
                    is_ok = false;
                } else if (name[2] != '\\') {
                    is_ok = false;
                }
            }
        }
        if (is_ok) {
            int len = strlen(name);
            is_ok = false;
            if (name[len-4] == '.' &&
                tolower(name[len-3]) == 't' &&
                tolower(name[len-2]) == 'x' &&
                tolower(name[len-1]) == 't'
                ) {
                    is_ok = true;
                }
        }
        if (! is_ok) {
            cout<<"Ошибка в название файла\n";
            return 1;
        }
        FILE* f = fopen(name, "rb");
        assert(f != 0);
        assert(fseek(f, 0, SEEK_END) == 0);
        int filesize = ftell(f);

        char* a = new char[filesize+1];
        assert(fseek(f, 0, SEEK_SET) == 0);
        int read_total = 0;
        while (read_total < filesize) {
            int left_total = filesize - read_total;
            int read_now = fread(& a[read_total], 1, left_total, f);
            read_total += read_now;
        }
        assert(fclose(f) == 0);
        a[filesize] = '\0';

        cout<<"Введите строку для поиска файла\n";
        char stroka[256+1];
        string s;
        getline(cin, s);
        getline(cin, s);
        strcpy(stroka, s.c_str());
        int stroka_len = strlen(stroka);
        while (stroka[stroka_len-1] == '\n' || stroka[stroka_len-1] == '\r') {
            stroka[stroka_len-1] = '\0';
            stroka_len--;
        }
        bool is_match = false;
        for (int i = 0; i < filesize; i++) {
            if (a[i] == stroka[0]) {
                is_match = true;
                for (int j = 1; j < stroka_len; j++) {
                    if (a[i + j] != stroka[j]) {
                        is_match = false;
                        break;
                    }
                }
                if (is_match) {
                    cout << "Найденная строка: " << stroka << '\n';
                    break;
                }
            }
        }
        if (! is_match) {
            cout << "Совпадений нет\n";
        }
        const int n_sentences_max = 1000;
        char** sentences = new char*[n_sentences_max];
        int i_sentence = 0;
        int sent_start = 0;
        int state = 0;
        for (int i = 0; i <= filesize; i++) {
            char c = a[i];
            if (c == '\0' || (state == 2 && c != ' ')) {
                state = 0;
                int len = i - sent_start;
                sentences[i_sentence] = new char[len+1];
                memcpy(sentences[i_sentence], & a[sent_start], len);
                sentences[i_sentence][len] = '\0';
                i_sentence++;
                sent_start += len;
            } else if (state == 1) {
                if (c == ' ') {
                    state = 2;
                } else if (c == '.') {
                    state = 1;
                } else {
                    state = 0;
                }
            } else if (state == 0){
                if (c == '.') {
                    state = 1 ;
                }
            }
        }

        sort(sentences, &sentences[i_sentence], CompareByLength());

        FILE* fw = fopen("out.txt", "wb");
        assert(fw != 0);
        for (int i = 0; i < i_sentence; i++) {
            fprintf(fw, "%s\n", sentences[i]);
            delete[] sentences[i];
        }
        assert(fclose(fw) == 0);
        delete[] sentences;

        delete[] a;
    }

    return 0;
}

