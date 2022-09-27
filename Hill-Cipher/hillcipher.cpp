// Nama : Rangga Putra
// NPM  : 140810200007
// Kelas: A

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// =========================================
// Sebagai kunci global batas ordo matriks
// =========================================
int key[3][3];

// =========================================
// Fungsi untuk modulo
// =========================================
int mod26(int x)
{
    return x >= 0 ? (x % 26) : 26 - (abs(x) % 26);
}

// =========================================
// Mencari determinan matriks
// =========================================
int findDet(int m[3][3], int n)
{
    int det;
    if (n == 2) // jika ordo matriks = 2
    {
        det = m[0][0] * m[1][1] - m[0][1] * m[1][0];
    }
    else
        det = 0; // invalid input
    return mod26(det);
}

// =========================================
// Mencari Invers Matriks
// =========================================
int findDetInverse(int R, int D = 26)
{
    int i = 0;
    int p[100] = {0, 1};
    int q[100] = {0}; // hasil bagi

    while (R != 0) // jika sisa tidak sama dengan 0
    {
        q[i] = D / R;
        int oldD = D;
        D = R;
        R = oldD % R;
        if (i > 1)
        {
            p[i] = mod26(p[i - 2] - p[i - 1] * q[i - 2]);
        }
        i++;
    }
    if (i == 1)
        return 1;
    else
        return p[i] = mod26(p[i - 2] - p[i - 1] * q[i - 2]);
}

// =========================================
// Untuk Mencari GCD
// =========================================
int gcd(int m, int n)
{
    if (n > m)
        swap(m, n);

    do
    {
        int temp = m % n;
        m = n;
        n = temp;
    } while (n != 0);

    return m;
}

// =========================================
// Perkalian Matrix Key dengan Blok-blok Plaintext
// =========================================
void multiplyMatrices(int a[1000][3], int a_rows, int a_cols, int b[1000][3], int b_rows, int b_cols, int res[1000][3])
{
    // Perkalian Matrix Key * Plaintext
    for (int i = 0; i < a_rows; i++)
    {
        for (int j = 0; j < b_cols; j++)
        {
            for (int k = 0; k < b_rows; k++)
            {
                res[i][j] += a[i][k] * b[k][j];
            }
            res[i][j] = mod26(res[i][j]);
        }
    }
}

// =========================================
// Untuk Mencari Key
// =========================================
void findKey()
{
    // deklarasi
    string plainteks, cipherteks;
    int key[2][2], det, detInv, adj[2][2], plainteksInv[2][2], plainMatrix[2][2], cipMatrix[2][2], counter;
    int p, c;
    int transpose[2][2];

    // input plainteks
    cout << "Masukkan Plainteks : ";
    cin.ignore();
    getline(cin, plainteks);

    // assign plainteks ke plainMatrix
    counter = 0;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            p = toupper(plainteks[counter]) - 65;
            plainMatrix[i][j] = p;
            counter++;
        }
    }

    // input cipherteks
    cout << "Masukkan Cipherteks : ";
    getline(cin, cipherteks);

    // assign cipherteks ke cipMatrix
    counter = 0;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            c = toupper(cipherteks[counter]) - 65;
            cipMatrix[i][j] = c;
            counter++;
        }
    }

    // determinan
    det = (plainMatrix[0][0] * plainMatrix[1][1]) - (plainMatrix[0][1] * plainMatrix[1][0]);
    if (gcd(det, 26) == 1)
    {
        // inverse dari determinan mod 26
        detInv = findDetInverse(det, 26);

        // menghitung adjoin
        adj[0][0] = plainMatrix[1][1];
        adj[0][1] = (-1) * plainMatrix[0][1];
        adj[1][0] = (-1) * plainMatrix[1][0];
        adj[1][1] = plainMatrix[0][0];

        // menghitung matriks invers dari plainteks
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                plainteksInv[i][j] = detInv * adj[i][j];
                if (plainteksInv[i][j] < 0)
                {
                    plainteksInv[i][j] = 26 - (abs(plainteksInv[i][j]) % 26);
                }
                else
                {
                    plainteksInv[i][j] = plainteksInv[i][j];
                    plainteksInv[i][j] = plainteksInv[i][j] % 26;
                }
            }
        }

        // Search key
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                key[i][j] = 0;
                for (int k = 0; k < 2; k++)
                {
                    key[i][j] += (plainteksInv[i][k] * cipMatrix[k][j]);
                }
                key[i][j] %= 26;
            }
        }

        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                transpose[j][i] = key[i][j];
            }
        }

        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                cout << (transpose[i][j]) << "\t";
            }
            cout << endl;
        }
    }
    else
    {
        cout << "Determinan tidak relatif " << endl;
        cout << "Key not found" << endl
             << endl;
    }
}

// =========================================
// Untuk Mencari Matrix Invers
// =========================================
void findInverse(int m[3][3], int n, int m_inverse[3][3])
{
    int adj[3][3] = {0};

    int det = findDet(m, n); // ini menggunakan fungsi findDet(matrix , order_of_matrix)
    int detInverse = findDetInverse(det);

    if (n == 2) // jika ordo matrik 2x2
    {
        adj[0][0] = m[1][1];
        adj[1][1] = m[0][0];
        adj[0][1] = -m[0][1];
        adj[1][0] = -m[1][0];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            m_inverse[i][j] = mod26(adj[i][j] * detInverse);
        }
    }
}

// =========================================
// Fungsi Untuk Enkripsi
// =========================================
string encrypt(string plainT, int n)
{
    int plaintext[1000][3] = {0};  // plaintext
    int ciphertext[1000][3] = {0}; // cipher text
    int ptIter = 0;

    while (plainT.length() % n != 0)
    {
        plainT += "x"; // pad extra x, ini digunakan jika plaintext di module dengan matrik tidak sama dengan 0
    }
    int row = (plainT.length()) / n; // jumlah baris dalam plaintext

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // membagi plaintext ke nlok matriks berdasarkan n matriks kunci
            plaintext[i][j] = plainT[ptIter++] - 'a';
        }
    }

    multiplyMatrices(plaintext, row, n, key, n, n, ciphertext);

    // Ciphertext hasil dari fungsi diatas dipake dibawah ini
    string cipherT = "";
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cipherT += (ciphertext[i][j] + 'a');
        }
    }
    return cipherT;
}

// =========================================
// Fungsi Untuk Dekripsi
// =========================================
string decrypt(string cipherT, int n)
{
    int plaintext[1000][3] = {0};  // plaintext
    int ciphertext[1000][3] = {0}; // cipher text
    int ctIter = 0;

    int row = cipherT.length() / n; // banyak baris di chipertext

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // membagi plaintext ke blok matriks berdasarkan n matriks kunci
            ciphertext[i][j] = cipherT[ctIter++] - 'a';
        }
    }

    // Mencari Invers Matriks
    int k_inverse[3][3] = {0};
    findInverse(key, n, k_inverse);

    multiplyMatrices(ciphertext, row, n, k_inverse, n, n, plaintext);

    // Plaintext hasil dari fungsi diatas dipake dibawah ini
    string plainT = "";
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < n; j++)
        {
            plainT += (plaintext[i][j] + 'a');
        }
    }
    return plainT;
}

int main(void)
{
    bool menuActive = true;
    string pt, ct;
    int n;
    int pilih;

    while (menuActive)
    {
        cout << "\nProgram Hill Cipher" << endl;
        cout << "Menu : " << endl;
        cout << "1. Enkripsi" << endl;
        cout << "2. Dekripsi" << endl;
        cout << "3. Find Key" << endl;
        cout << "4. Exit" << endl;
        cout << "Pilih Menu : ";
        cin >> pilih;
        switch (pilih)
        {
        case 1:
            cout << "Masukkan kata   : ";
            cin >> pt;

            cout << "Masukkan ordo matriks harus nxn : ";
            cin >> n;

            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    cout << "Masukkan matriks[" << i + 1 << "][" << j + 1 << "]";
                    cin >> key[i][j];
                }
            }

            cout << "\nPlaintext  : " << pt << endl;

            ct = encrypt(pt, n);
            cout << "Hasil Enkripsi : " << ct << endl;
            break;
        case 2:
            cout << "Masukkan kata   : ";
            cin >> ct;

            cout << "Masukkan ordo matriks harus nxn : ";
            cin >> n;

            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    cout << "Masukkan matriks[" << i + 1 << "][" << j + 1 << "]";
                    cin >> key[i][j];
                }
            }

            cout << "\nChipertext  : " << ct << endl;
            cout << "Hasil Dekripsi : " << decrypt(ct, n) << endl;
            break;
        case 3:
            cout << endl;
            findKey();
            break;
        default:
            cout << "\nInvalid Input" << endl;
            break;
        }
    }
}