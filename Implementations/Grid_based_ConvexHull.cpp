/**

Implementation for Grid-aided algorithm to find minimum convex hull of Planar Points Set.

**/

#include<bits/stdc++.h>
#include "..\Libraries\matplotlib\matplotlibcpp.h"

using namespace std;
namespace plt = matplotlibcpp;

const double INT_MIN_POSITIVE = 0.0000001;

struct pointInSpace{
    double X, Y;
    int gridX, gridY;
};

struct gridRaster{
	double top, bottom, start, end;
	vector < pointInSpace* > pointsInGrid;
	bool reject;
};

int cSumOfGridPoints(vector <gridRaster> &colRaster)
{
    int cSumFinal = 0;
    for(int a = 0; a < colRaster.size(); a++)
    {
        cSumFinal += colRaster[a].pointsInGrid.size();
    }
    return cSumFinal;
}

int rSumOfGridPoints(vector < vector <gridRaster> > &space, int colID)
{
    int rSumFinal = 0;
    for(int a = 0; a < space.size(); a++)
    {
        rSumFinal += space[a][colID].pointsInGrid.size();
    }
    return rSumFinal;
}

int main()
{
    vector < pointInSpace > S; //Dynamic Array of Points S
    int setSize; // Size of the set of points to be given
    cin >> setSize;

    for(int a  = 0; a < setSize; a++)
    {
        pointInSpace newPoint;
        // cin >> newPoint.X >> newPoint.Y;
        newPoint.X = rand() % 500;
        newPoint.Y = rand() % 500;
        S.push_back(newPoint); // Adding points to the Dynamic Array S
    }

    // We build a square grid so with equal number of rows and columns viz. R = C = sq. root ( setSize )
    int gridSide = sqrt(setSize);
    double topBoundary = (double) INT_MIN, endBoundary = (double) INT_MIN;
    double bottomBoundary = (double) INT_MAX, startBoundary = (double) INT_MAX;

    for(int a = 0; a < S.size(); a++)
    {
    	startBoundary = min(startBoundary, S[a].X);
    	endBoundary = max(endBoundary, S[a].X) + INT_MIN_POSITIVE;
    	bottomBoundary = min(bottomBoundary, S[a].Y);
    	topBoundary = max(topBoundary, S[a].Y) + INT_MIN_POSITIVE;
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

    for(int a = 0; a < S.size(); a++)
    {
        S[a].gridY = (S[a].Y - bottomBoundary) / gridHeight;
        S[a].gridX = (S[a].X - startBoundary) / gridWidth;
        space[S[a].gridX][S[a].gridY].pointsInGrid.push_back(&S[a]);
    }

    // cout << gridWidth << endl << gridHeight <<endl;

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
    	}
    }

    for(int a = 0; a < space.size(); a++)
    {
        int b = 0;
        int cSum = 0;
        int cSumFinal = cSumOfGridPoints(space[a]);
        // cout << "cSumFinal "<< a << ": " << cSumFinal << endl;
        while(b!= space[a].size())
        {
            int cSumNew = space[a][b].pointsInGrid.size() + cSum;
            if(cSum == 0 && cSumNew != 0)
            {
                space[a][b].reject = false;
            }
            else if(cSum == cSumFinal && cSumNew == cSumFinal)
            {
                space[a][b-1].reject = false;
                space[a][b].reject = true;
            }
            else
            {
                space[a][b].reject = true;
            }
            b++;
            cSum = cSumNew;
        }
        if(space[a].back().pointsInGrid.size() != 0 && space[a].back().reject)
            space[a].back().reject = false;
    }

    for(int a = 0; a < space.size(); a++)
    {
        int b = 0;
        int rSum = 0;
        int rSumFinal = rSumOfGridPoints(space, a);
        // cout << "rSumFinal "<< a << ": " << rSumFinal << endl;
        while(b!= space.size())
        {
            int rSumNew = space[b][a].pointsInGrid.size() + rSum;
            if(rSum == 0 && rSumNew != 0)
            {
                space[b][a].reject = false;
            }
            else if(rSum == rSumFinal && rSumNew == rSumFinal)
            {
                space[b-1][a].reject = false;
            }
            b++;
            rSum = rSumNew;
        }
        if(space.back()[a].pointsInGrid.size() != 0 && space.back()[a].reject)
            space.back()[a].reject = false;
    }

    vector <double> plotTrueVectX;
    vector <double> plotTrueVectY;
    vector <double> plotFalseVectX;
    vector <double> plotFalseVectY;

    for(int a  = 0; a < space.size(); a++)
    {
    	for(int b = 0; b < space[a].size(); b++)
    	{
            // cout << "\t" <<space[a][b].top << " " << space[a][b].bottom << " " << space[a][b].start << " " << space[a][b].end  << "\t";
            cout << "\t" << space[a][b].pointsInGrid.size() << "\t";
            if(space[a][b].pointsInGrid.size() > 0)
            {
                if(space[a][b].reject)
                {
                    for(int c = 0;c < space[a][b].pointsInGrid.size(); c++ )
                    {
                        plotTrueVectX.push_back(space[a][b].pointsInGrid[c]->X);
                        plotTrueVectY.push_back(space[a][b].pointsInGrid[c]->Y);
                    }
                }
                else
                {
                    for(int c = 0;c < space[a][b].pointsInGrid.size(); c++ )
                    {
                        plotFalseVectX.push_back(space[a][b].pointsInGrid[c]->X);
                        plotFalseVectY.push_back(space[a][b].pointsInGrid[c]->Y);
                    }
                }
            }
    	}
    	cout << endl;
    }

    plt::scatter(plotTrueVectX, plotTrueVectY, 5);
    plt::scatter(plotFalseVectX, plotFalseVectY, 5);
    plt::title("Grid-aided algorithm to find minimum convex hull of Planar Points Set");

    cout << endl;

    for(int a  = 0; a < space.size(); a++)
    {
    	for(int b = 0; b < space[a].size(); b++)
    	{
    		// cout << "\t" <<space[a][b].top << " " << space[a][b].bottom << " " << space[a][b].start << " " << space[a][b].end  << "\t";
            cout << "\t" << space[a][b].reject << "\t";
    	}
    	cout << endl;
    }
    plt::show();
}
/*
25
1 1 2 4 8 9 3 4 6 5
7 8 9 8 6 2 0 8 2 7
9 7 1 0 5 1 0 6 4 7
4 8 9 3 7 1 6 7 1 3
3 3 7 9 5 2 0 7 0 2
        2               2               0               2               1
        0               1               2               1               0
        1               1               0               1               1
        1               1               1               1               2
        0               1               0               1               2

        0               0               1               0               0
        1               0               0               0               1
        0               1               1               1               0
        0               1               0               1               0
        1               0               1               0               0
*/
