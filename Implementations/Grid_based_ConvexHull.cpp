/**

Implementation for Grid-aided algorithm to find minimum convex hull of Planar Points Set.

**/

#include<bits/stdc++.h>

using namespace std;

int main()
{
    vector < pair <double, double > > S; //Dynamic Array of Points S
    int setSize; // Size of the set of points to be given
    cin >> setSize;

    for(int a  = 0; a < setSize; a++)
    {
        double x, y;
        cin >> x >> y;
        S.push_back(make_pair(x, y)); // Adding points to the Dynamic Array S
    }

    // We build a square grid so with equal number of rows and columns viz. R = C = sq. root ( setSize )
    int gridSide = sqrt(setSize);
    double topBoundary = (double) INT_MIN, endBoundary = (double) INT_MIN;
    double bottomBoundary = (double) INT_MAX, startBoundary = (double) INT_MAX;

    for(int a = 0; a < S.size(); a++)
    {
    	startBoundary = min(startBoundary, S[a].first);
    	endBoundary = max(endBoundary, S[a].first);
    	bottomBoundary = min(bottomBoundary, S[a].second);
    	topBoundary = max(topBoundary, S[a].second);
    }

}
