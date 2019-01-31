/**

Implementation for Grid-aided algorithm to find minimum convex hull of Planar Points Set.

**/

#include<bits/stdc++.h>

using namespace std;

int main()
{
    vector < pair <double, double > > P; //Dynamic Array of Points P
    int setSize; // Size of the set of points to be given
    cin >> setSize;
    for(int a  = 0; a < setSize; a++)
    {
        double x, y;
        cin >> x >> y;
        P.push_back(make_pair(x, y)); // Adding points to the Dynamic Array P
    }
}
