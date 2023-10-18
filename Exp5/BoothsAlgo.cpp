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
int toDecimal(vector<bool> &A, vector<bool> &Q, int size)
{
    vector<bool> temp;
    bool negative = false;
    int result = 0;
    size <<= 1;

    // Join A and Q
    temp.reserve(size);
    temp.insert(temp.end(), A.begin(), A.end());
    temp.insert(temp.end(), Q.begin(), Q.end());

    // Check if number is negative
    if (temp[0])
    {
        two_comp(temp);
        negative = true;
    }

    // Calculate decimal value
    for (bool bit : temp)
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

// Arthimetic Right shifts A, Q and Q-1 binary vectors
void ars(vector<bool> &A, vector<bool> &Q, vector<bool> &Q_1, int size)
{
    Q_1[0] = Q.back();
    for (int i = size - 1; i >= 1; i--)
        Q[i] = Q[i - 1];

    Q[0] = A.back();
    for (int i = size - 1; i >= 1; i--)
        A[i] = A[i - 1];
}

// Display value row-wise in table
void display(vector<bool> &M, vector<bool> &A, vector<bool> &Q, vector<bool> &Q_1, int size, string s)
{
    forn(M);
    cout << "\t";
    forn(A);
    cout << "\t";
    forn(Q);
    cout << "\t";
    forn(Q_1);
    cout << "\t";
    cout << s;
    cout << endl;
}

// Booth's Algorithm
void booth(vector<bool> &M, vector<bool> &A, vector<bool> &Q, vector<bool> &Q_1, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (!Q.back() && Q_1[0])
        {
            add(A, M, size);
            display(M, A, Q, Q_1, size, "Add A <- A + M");
        }
        else if (Q.back() && !Q_1[0])
        {
            sub(A, M, size);
            display(M, A, Q, Q_1, size, "Sub A <- A - M");
        }
        ars(A, Q, Q_1, size);
        display(M, A, Q, Q_1, size, "ARS A, Q, Q-1");
        cout << "-----------------------------------------------\n";
    }
}

int main()
{
    int m, q, counter, lm, lq;
    vector<bool> M, Q;

    // Get user input
    cout << "Enter two numbers: ";
    cin >> m >> q;

    // Convert numbers to binary form
    lm = toBinary(M, m);
    lq = toBinary(Q, q);

    // Resize binary vectors
    counter = (lm >= lq) ? lm : lq;
    M.insert(M.begin(), counter - lm, M[0]);
    Q.insert(Q.begin(), counter - lq, Q[0]);

    // Initialize Accumulator and Q-1
    vector<bool> A(counter, false), Q_1(1, false);

    // Format output in table form
    cout << "\n-----------------------------------------------\n";
    cout << "M\tA\tQ\tQ_1\tStep" << endl;
    cout << "-----------------------------------------------\n";
    display(M, A, Q, Q_1, counter, "Initial");
    cout << "-----------------------------------------------\n";
    // Perform Booth's Algorithm
    booth(M, A, Q, Q_1, counter);
    cout << "Answer: ";
    forn(A);
    forn(Q);
    cout << " = " << toDecimal(A, Q, counter) << endl;
    return 0;
}