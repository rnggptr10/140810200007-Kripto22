/*
  Nama  : Rangga Putra
  NPM   : 140810200007
*/

#include <iostream>
#include <string>

using namespace std;

string encrypt(string text, int key)
{
    string result = "";
    // penelurusan char dalam string
    for (int i = 0; i < text.length(); i++)
    {
        // if (text[i] =
        // buat uppercase
        if (isupper(text[i]))
        {
            result += char(int(text[i] + key - 65) % 26 + 65);
        }
        // buat lowercase
        else if (islower(text[i]))
        {
            result += char(int(text[i] + key - 97) % 26 + 97);
        }
        else
            result.push_back(text[i]);
    }
    // return hasilnya
    return result;
}

string decrypt(string text, int key)
{
    string result = "";
    // penelurusan char dalam string
    for (int i = 0; i < text.length(); i++)
    {
        // if (text[i] =
        // buat uppercase
        if (isupper(text[i]))
        {
            result += char((int(text[i] - key - 65) % 26 + 26) % 26 + 65);
        }
        // buat lowercase
        else if (islower(text[i]))
        {
            result += char((int(text[i] - key - 97) % 26 + 26) % 26 + 97);
        }
        else
            result.push_back(text[i]);
    }
    // return hasilnya
    return result;
}

int main()
{
    string plaintext = "", cipherteks = " ";
    int key;
    cout << "Masukkan Kata: ";
    getline(cin, plaintext);
    cout << "Masukkan Kunci: ";
    cin >> key;
    cout << "\nPlaintext : " << plaintext;
    cout << "\nKunci: " << key;
    cipherteks = encrypt(plaintext, key);
    cout << "\nCipherteks: " << cipherteks;
    cout << "\nDekripsi: " << decrypt(cipherteks, key);
    return 0;
}