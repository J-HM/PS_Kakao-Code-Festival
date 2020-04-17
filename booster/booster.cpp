#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> XcheckPoints;
vector<int> YcheckPoints;
vector<int> verticalParallelLines;
vector<int> horizontalParallelLines;


void setParallelLines(vector<int>& parallelLines, vector<int> checkPoints)
{
	sort(checkPoints.begin(), checkPoints.end());
	for (int i = 0; i < checkPoints.size() - 1; i++)
		if (checkPoints[i] == checkPoints[i + 1])
			parallelLines.push_back(checkPoints[i]);
	parallelLines.erase(unique(parallelLines.begin(),parallelLines.end()),parallelLines.end());
}


int getDistance(int Apoint, int Bpoint)
{
	if (Apoint > Bpoint) return Apoint - Bpoint;
	else return Bpoint - Apoint;
}

bool isReachable(int ApointIndex, int BpointIndex, int maxHP)
{
	int distanceOfA, distanceOfB;
	int minDistanceOfA = 987654321;
	int minDistanceOfB = 987654321;

	int XApoint = XcheckPoints[ApointIndex - 1];
	int YApoint = YcheckPoints[ApointIndex - 1];
	int XBpoint = XcheckPoints[BpointIndex - 1];
	int YBpoint = YcheckPoints[BpointIndex - 1];
		
	for (int line : verticalParallelLines)
	{
		distanceOfA = getDistance(XApoint, line);
		if (minDistanceOfA > distanceOfA)
			minDistanceOfA = distanceOfA;
		
		distanceOfB = getDistance(XBpoint, line);
		if (minDistanceOfB > distanceOfB)
			minDistanceOfB = distanceOfB;
	}
	if (minDistanceOfA + minDistanceOfB <= maxHP) return true;
	
	for (int line : horizontalParallelLines)
	{
		distanceOfA = getDistance(YApoint, line);
		if (minDistanceOfA > distanceOfA)
			minDistanceOfA = distanceOfA;
		
		distanceOfB = getDistance(YBpoint, line);
		if (minDistanceOfB > distanceOfB)
			minDistanceOfB = distanceOfB;
	}
	if (minDistanceOfA + minDistanceOfB <= maxHP) return true;
	return false;
}


int main()
{
	int N, Q;
	cin >> N >> Q;
	
	for (int i = 0; i < N; i++)
	{
		int xTemp, yTemp;
		cin >> xTemp >> yTemp;
		XcheckPoints.push_back(xTemp);
		YcheckPoints.push_back(yTemp);
	}
	
	setParallelLines(verticalParallelLines, XcheckPoints);
	setParallelLines(horizontalParallelLines, YcheckPoints);
	
	
	vector<bool> output;
	for (int i = 0; i < Q; i++)
	{
		int ApointIndex, BpointIndex, maxHP;
		cin >> ApointIndex >> BpointIndex >> maxHP;
		output.push_back(isReachable(ApointIndex, BpointIndex, maxHP));
	}
	
	for (int i = 0; i < Q; i++)
	{
		if (output[i]) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
}