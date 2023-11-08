#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Page Structure
struct Page
{
    int val, time;
};

// Displays currently available Frames
void display(vector<Page> &frames)
{
    for (Page &frame : frames)
        cout << frame.val << ' ';
    cout << endl;
}

int main()
{
    int nf, npr, minTime, minIndex;
    bool found = false;
    vector<Page> frames, pageref;

    // Get size of Frames and Page References from User
    cout << "\nEnter no. of Frames: ";
    cin >> nf;
    cout << "\nEnter no. of Page References: ";
    cin >> npr;

    // Initialize Frames with default values
    for (int i = -nf; i < 0; i++)
        frames.push_back({-1, i});


    // Get Page References from User
    pageref.reserve(npr);
    cout << "\nEnter " << npr << " Pages: ";
    for (int i = 0; i < npr; i++)
    {
        Page temp;
        cin >> temp.val;
        pageref.push_back(temp);
    }

    cout << "\nRequired\tFrames\n";
    for (int i = 0; i < npr; i++)
    {
        found = false;
        pageref[i].time = i;

        cout << pageref[i].val << "\t\t";
        for (Page &frame : frames)
        {
            if (frame.val == pageref[i].val)
            {
                found = true;
                frame.time = i;
            }
        }

        if (!found)
        {
            minTime = frames[0].time;
            minIndex = 0;
            for (int i = 1; i < nf; i++)
            {
                if (frames[i].time < minTime)
                {
                    minTime = frames[i].time;
                    minIndex = i;
                }
            }
            frames[minIndex] = pageref[i];
        }
        display(frames);
    }
    return 0;
}
