#include <iostream>
#include <vector>
#include <algorithm>
#define forn(vec)      \
    for (bool i : vec) \
    cout << i

using namespace std;

// Performs two's complement on binary vector
void two_comp(vector<bool> &vec)
{
    // Find the first "1" from LSB
    int i = vec.size() - 1;
    while (i >= 0 && !vec[i])
        i--;
    i--;

    // Flip remaining bits
    while (i >= 0)
    {
        vec[i] = !vec[i];
        i--;
    }
}

// Converts given number to binary vector
int toBinary(vector<bool> &vec, int n)
{
    bool negative = false;

    // Check if given number is negative
    if (n < 0)
    {
        n = -n;
        negative = true;
    }

    // Convert number to binary form
    while (n != 0)
    {
        vec.push_back(n & 1);
        n >>= 1;
    }
    vec.push_back(0); // Add Sign bit

    // Previous Orientation: [LSB . . . MSB]
    reverse(vec.begin(), vec.end());
    // Current Orientation: [MSB . . . LSB]

    // Convert negative number to two's complement form
    if (negative)
        two_comp(vec);

    return vec.size();
}

// Converts given binary vector to decimal number
int toDecimal(vector<bool> &A, int size)
{
    bool negative = false;
    int result = 0;

    // Check if number is negative
    if (A[0])
    {
        two_comp(A);
        negative = true;
    }

    // Calculate decimal value
    for (bool bit : A)
        result = (result << 1) + bit;

    return negative ? -result : result;
}

// Adds two binary vectors
void add(vector<bool> &A, vector<bool> &Q, int size)
{
    bool carry = false, sum;
    for (int i = size - 1; i >= 0; i--)
    {
        sum = A[i] ^ Q[i] ^ carry;
        carry = (A[i] & Q[i]) | (Q[i] & carry) | (carry & A[i]);
        A[i] = sum;
    }
}

// Subtracts two binary vectors
void sub(vector<bool> &A, vector<bool> &Q, int size)
{
    bool borrow = false, diff;
    for (int i = size - 1; i >= 0; i--)
    {
        diff = A[i] ^ Q[i] ^ borrow;
        borrow = (!A[i] & borrow) | (!A[i] & Q[i]) | (borrow & Q[i]);
        A[i] = diff;
    }
}

// Left shifts A and Q binary vectors
void ls(vector<bool> &A, vector<bool> &Q, int size)
{
    for (int i = 0; i < size; i++)
        A[i] = A[i + 1];
    A[size] = Q[0];
    for (int i = 0; i < size; i++)
        Q[i] = Q[i + 1];
}

// Display value row-wise in table
void display(vector<bool> &M, vector<bool> &A, vector<bool> &Q, int size, string s)
{
    forn(M);
    cout << "\t";
    forn(A);
    cout << "\t";
    forn(Q);
    cout << "\t";
    cout << s;
    cout << endl;
}

// Restoring Division Algorithm
void nonrestoringdiv(vector<bool> &M, vector<bool> &A, vector<bool> &Q, int size)
{
    for (int i = 0; i < size; i++)
    {
        ls(A, Q, size);
        display(M, A, Q, size + 1, "LS A, Q");
        sub(A, M, size + 1);
        display(M, A, Q, size + 1, "Sub A <- A - M");
        Q[size - 1] = !A[0];
        display(M, A, Q, size + 1, "Set Q0");

        if (A[0]) // A is negative
        {
            add(A, M, size + 1);
            display(M, A, Q, size + 1, "Add A <- A + M");
        }
        cout << "-----------------------------------------------\n";
    }
}

int main()
{
    int q, m, counter, lq, lm;
    vector<bool> Q, M;

    // Get user input
    cout << "Enter two numbers: ";
    cin >> q >> m;

    // Convert numbers to binary form
    lq = toBinary(Q, q);
    lm = toBinary(M, m);

    counter = lq;
    M.insert(M.begin(), counter - lm + 1, M[0]);

    // Initialize Accumulator
    vector<bool> A(counter + 1, false);

    cout << "\n-----------------------------------------------\n";
    cout << "M\tA\tQ\tStep" << endl;
    cout << "-----------------------------------------------\n";
    display(M, A, Q, counter + 1, "Initial");
    cout << "-----------------------------------------------\n";
    nonrestoringdiv(M, A, Q, counter);
    cout << "Remainder: ";
    forn(A);
    cout << " = " << toDecimal(A, counter + 1) << endl;
    cout << "Quotient: ";
    forn(Q);
    cout << " = " << toDecimal(Q, lq) << endl;
    return 0;
}