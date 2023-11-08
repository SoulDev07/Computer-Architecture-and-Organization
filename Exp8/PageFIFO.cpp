#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Displays currently available Frames 
void display(vector<int> &frames, bool page_hit = false)
{
    if (page_hit)
        cout << '*';
    for (int i : frames)
        cout << i << ' ';
    cout << endl;
}

int main()
{
    int nf, npr, tbr = 0;

    // Get size of Frames and Page References from User
    cout << "\nEnter no. of Frames: ";
    cin >> nf;
    cout << "\nEnter no. of Page References: ";
    cin >> npr;

    vector<int> frames(nf, -1), pageref(npr, 0);

    // Get Page References from User
    cout << "\nEnter " << npr << " Pages: ";
    for (int i = 0; i < npr; i++)
        cin >> pageref[i];

    cout << "\nRequired\tFrames\n";
    for (int val : pageref)
    {
        cout << val << "\t\t";
        // Check if required Page Reference is not available in our Frames
        if (find(frames.begin(), frames.end(), val) == frames.end())
        {
            frames[tbr] = val; // Replace old page with new page
            tbr = (tbr + 1) % nf;
            display(frames);
        }
        // Else its a Page Hit
        else
            display(frames, true);
    }
    return 0;
}