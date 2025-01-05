#include <cmath>
#include <numeric>
#include <string>
#include <vector>
#include <random>
#include <iostream>

int ChooseFirstElement(int maximum)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    int min = 0;
    int max = maximum;

    std::uniform_int_distribution<> distrib(min, max);

    int randomNumber = distrib(gen);

    return randomNumber;
}

std::vector<int> Indexes(int n)
{
    std::vector<int> v;
    for (int i = 0; i < n; ++i)
    {
        v.push_back(i);
    }

    return v;
}

typedef struct Point2D 
{
	double x;
	double y;
};

double Distance(Point2D first, Point2D second)
{
    return pow(pow(first.x - second.x, 2.0) + pow(first.y - second.y, 2.0), 0.5);
}

void NearestNeighbor(std::vector<Point2D> points)
{
    std::vector<Point2D> pts = points;
    int currElemId = ChooseFirstElement(points.size() - 1);
    Point2D currElem = pts[currElemId];

    pts.erase(pts.begin() + currElemId);
    std::cout << "NearestNeighbor: (" << currElem.x << \
                                "," << currElem.y << ") ";

    while (!pts.empty())
    {
        int nearestNeighborId = 0;
        double distance = DBL_MAX;

        for (int i = 0; i < pts.size(); ++i)
        {
            double d = Distance(currElem, pts[i]);
            if (d <= distance)
            {
                nearestNeighborId = i;
                distance = d;
            }
        }

        currElemId = nearestNeighborId;
        currElem = pts[currElemId];
        pts.erase(pts.begin() + currElemId);
        std::cout << "(" << currElem.x << \
            "," << currElem.y << ") ";
    }
}

bool Dfs(int v, int target, std::vector<std::vector<int>>& adjMatrix, std::vector<bool>& visited) 
{
    if (v == target) 
    {
        return true;
    }

    visited[v] = true;
    
    for (int i = 0; i < adjMatrix.size(); i++) 
    {
        if (adjMatrix[v][i] == 1 && !visited[i]) 
        { 
            if (Dfs(i, target, adjMatrix, visited)) 
            {
                return true;
            }
        }
    }

    return false;
}

bool AreConnected(int start, int end, std::vector<std::vector<int>>& adjMatrix) 
{
    std::vector<bool> visited(adjMatrix.size(), false);
    return Dfs(start, end, adjMatrix, visited);
}

void ClosestPair(std::vector<Point2D> points)
{
    std::vector<std::vector<int>> edges(points.size(), std::vector<int>(points.size(), 0));
    for (int i = 0; i < edges.size(); ++i)
    {
        edges[i][i] = 1;
    }

    for (int i = 0; i < points.size() - 1; ++i)
    {
        double distance = DBL_MAX;
        int firstId = 0;
        int secondId = 0;

        for (int j = 0; j < points.size() - 1; ++j)
        {
            for (int k = j + 1; k < points.size(); ++k)
            {
                double d = Distance(points[j], points[k]);
                int sumJ = std::accumulate(edges[j].begin(), edges[j].end(), 0);
                int sumK = std::accumulate(edges[k].begin(), edges[k].end(), 0);
                if ((!edges[j][k]) && (!edges[k][j]) && (sumJ < 3) && (sumK < 3) && \
                    (!AreConnected(j, k, edges)) && d <= distance)
                {
                    distance = d;
                    firstId = j;
                    secondId = k;
                }
            }
        }
        edges[firstId][secondId] = 1;
        edges[secondId][firstId] = 1;
        std::cout << "(" << points[firstId].x << "," << points[firstId].y << ") ";
        std::cout << "(" << points[secondId].x << "," << points[secondId].y << ") " << std::endl;
    }
}

int main()
{
    std::vector<Point2D> v = { {1.0, 1.0}, {1.0, 2.0}, {3.0, 1.0}, {3.0, 2.0} };//square
    std::vector<Point2D> v2 = { {-3, 1}, {-2, 1}, {-1, 1}, {0, 1}, {1, 1}, {2, 1} };//line
    std::vector<Point2D> v3 = { {-3.0, 0.0}, {0.0, 0.0}, {3.0, 0.0}, {-3.0, 2.0}, { 0.0, 2.0 }, {3.0, 2.0} }; //parallelepiped
    //NearestNeighbor(v2);
    ClosestPair(v3);

	return 0;
}
