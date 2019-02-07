/**

Implementation for Grid-aided algorithm to find minimum convex hull of Planar Points Set.

**/

#include<bits/stdc++.h>

using namespace std;

struct gridRaster{
	double top, bottom, start, end;
	vector < pair < double, double > > points;
	bool reject;
};

bool gridArrange( pair < double, double > pointA, pair < double, double > pointB)
{

    if (pointA.first == pointB.first )
        return pointA.second < pointB.second;

    return pointA.first > pointB.first;
}

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

    vector < vector < gridRaster > > space;
    double gridHeight = (topBoundary - bottomBoundary) / (double) gridSide;
    double gridWidth = (endBoundary - startBoundary) / (double) gridSide;

    for(int a = 0; a < gridSide; a++)
    {
    	vector < gridRaster > dimension;
    	space.push_back(dimension);
    	for(int b = 0; b < gridSide; b++)
    	{
    		gridRaster tess;
    		tess.top = tess.bottom = tess.start = tess.end = -1;
    		space[a].push_back(tess);
    	}
    }

    cout << gridWidth << endl << gridHeight << endl;

    cout << endl;

    space[0][0].top = topBoundary; space[0][0].start = startBoundary;
    space[0][0].end = space[0][0].start + gridWidth;
    space[0][0].bottom = space[0][0].top - gridHeight;

    for(int a = 0; a < space.size(); a++)
    {
    	space[a][0].top = topBoundary;
    	space[a][0].bottom = topBoundary - gridHeight;
    	space[0][a].start = startBoundary;
    	space[0][a].end = startBoundary + gridWidth;
    }


    vector < pair <double, double > > pStack(S);
    sort(pStack.begin(), pStack.end(), gridArrange);// greater < pair < double, double > >() );

    for(int a  = 0; a < pStack.size(); a++)
    {
        cout << pStack[a].first << " " << pStack[a].second << "\t";
    }

    cout << endl;

    for(int a = 0; a < space.size(); a++)
    {
    	for(int b = 0; b < space[a].size(); b++)
    	{
    		if(space[a][b].start == -1)
    		{
    			space[a][b].start = space[a-1][b].end;
    			space[a][b].end = space[a][b].start + gridWidth;
    		}
			if(space[a][b].top == -1)
    		{
    			space[a][b].top = space[a][b-1].bottom;
    			space[a][b].bottom = space[a][b].top - gridHeight;
    		}
			while(	pStack.back().first >= space[a][b].start &&
					pStack.back().first <= space[a][b].end &&
					pStack.back().second >= space[a][b].bottom &&
					pStack.back().second <= space[a][b].top 			)
			{
				space[a][b].points.push_back(pStack.back());
				pStack.pop_back();
			}
    	}
    }

    for(int a  = 0; a < space.size(); a++)
    {
    	for(int b = 0; b < space[a].size(); b++)
    	{
            cout << "\t" <<space[a][b].top << " " << space[a][b].bottom << " " << space[a][b].start << " " << space[a][b].end  << "\t";
            cout << "\t" << space[a][b].points.size() << "\t";
    	}
    	cout << endl;
    }

}
/*
25
1 1 2 4 8 9 3 4 6 5
7 8 9 8 6 2 0 8 2 7
9 7 1 0 5 1 0 6 4 7
4 8 9 3 7 1 6 7 1 3
3 3 7 9 5 2 0 7 0 2
1.8
1.8

	0		0		0		0		0
	0		0		0		0		0
	0		0		0		0		0
	0		0		0		0		0
	0		0		0		0		0

*/
