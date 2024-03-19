#include <iostream>
using namespace std;
int main(void) {
    int days;
    cin >> days;
    //cout << days << endl;
    int min = 0;
    int max = 0;

    for (int i = 0; i < days; i++)
    {
        int h1, h2, h3;
        cin >> h1 >> h2 >> h3;
        int add = h1 + h2 + (24 - h3);

        if (min == 0 && max == 0)
        {
            min = add;
            max = add;
        }
        else if (add < min)
        {
            min = add;
        }
        else if (add > max)
        {
            max = add;
        }
    }

    cout << min << endl;
    cout << max << endl;
    return 0;
}