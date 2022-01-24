#include <iostream>
#include <string>
#include <random>
#include <vector>
using namespace std;

struct Edge
{
	int key;
	int v_0;
	int v_1;
	string color;
};

int randomNum(int min, int max)
{
	random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<std::mt19937::result_type> dist(min,max); // distribution in range [1, 6]
    return dist(rng);
}
string getColor(int index)
{
	int size = 11;
	string colorArray[] = {"green", "yellow", "blue", "black", "red", "orange", "cyan", "grey", "white", "pink", "purple"};
	return colorArray[index];
}
void deleteFromVec(vector<string>& vec, string toBeDel)
{
	for (int i = 0; i < vec.size(); i++)
	{
		if(vec[i] == toBeDel)
		{
			vec[i] = vec[vec.size()-1];
			vec.pop_back();
			break;
		}
	}
}
int findEdge(int x, int y, const vector<vector<Edge>> &vec)
{
	int num =-1;
	for (int i = 0; i < vec[x].size(); i++)
	{
		if (vec[x][i].key == y)
		{
			num = i;
		}
	}
	return num;
}
int main()
{
	int edgeNum = randomNum(5, 10);
	int vertexNum = randomNum(3, 6);
	Edge tempEdge;
	vector<Edge> edgeVector;
	vector<Edge> dummyVector;
	vector<vector<Edge>> hashTable1;
	vector<vector<Edge>> hashTable2;
	vector<string> testUsedColor;
	vector<string> coloredEdgeVector;
	Edge currEdge, testEdge;
	int currentColor = 0;
	string newcolor;
	cout << "End points of the edges:" <<endl;
	for (int i = 0; i < edgeNum; i++)
	{
		tempEdge.key = i;
		tempEdge.color = "";
		tempEdge.v_0 = randomNum(0, vertexNum);
		tempEdge.v_1 = randomNum(0, vertexNum);
		edgeVector.push_back(tempEdge);
		cout << "("<<edgeVector[i].v_0 << ", "<<edgeVector[i].v_1 << ")" << endl;
	}
	cout << endl;
	for (int i = 0; i <= vertexNum; i++)
	{
		hashTable1.push_back(dummyVector);
		hashTable2.push_back(dummyVector);
	}
	for (int i = 0; i < hashTable1.size(); i++)
	{
		for (int j = 0; j < edgeVector.size(); j++)
		{
			if(edgeVector[j].v_0==i)
			{
				hashTable1[i].push_back(edgeVector[j]);
			}
			if (edgeVector[j].v_1 == i)
			{
				hashTable2[i].push_back(edgeVector[j]);
			}
		}
	}
	for (int i = 0; i < hashTable1.size(); i++)
	{
		for (int j = 0; j < hashTable1[i].size(); j++)
		{
			testUsedColor = coloredEdgeVector;
			currEdge = hashTable1[i][j];
			for (int k = 0; k < hashTable1[currEdge.v_0].size(); k++)
			{
				deleteFromVec(testUsedColor, hashTable1[currEdge.v_0][k].color);
			}
			for (int k = 0; k < hashTable1[currEdge.v_1].size(); k++)
			{
				deleteFromVec(testUsedColor, hashTable1[currEdge.v_1][k].color);
			}
			for (int k = 0; k < hashTable2[currEdge.v_0].size(); k++)
			{
				deleteFromVec(testUsedColor, hashTable2[currEdge.v_0][k].color);
			}
			for (int k = 0; k < hashTable2[currEdge.v_1].size(); k++)
			{
				deleteFromVec(testUsedColor, hashTable2[currEdge.v_1][k].color);
			}
			if (testUsedColor.size() == 0)
			{
				newcolor = getColor(currentColor);
				hashTable1[i][j].color = newcolor;
				hashTable2[currEdge.v_1][findEdge(currEdge.v_1,currEdge.key, hashTable2)].color = newcolor;
				coloredEdgeVector.push_back(newcolor);
				currentColor++;
			}
			else
			{
				hashTable1[i][j].color = testUsedColor[0];
				hashTable2[currEdge.v_1][findEdge(currEdge.v_1,currEdge.key, hashTable2)].color = testUsedColor[0];
			}

		}
	}
	cout << "Hash Table1: "<< endl;
	for (int i = 0; i < hashTable1.size(); i++)
	{
		//cout << endl;
		for (int j = 0; j < hashTable1[i].size(); j++)
		{
			cout << i << ". ("<< hashTable1[i][j].v_0 << " ," << hashTable1[i][j].v_1 <<")" << " color:" << hashTable1[i][j].color<< endl;
		}
		
	}
	cout << endl <<"Hash Table2: "<< endl;
	for (int i = 0; i < hashTable2.size(); i++)
	{
		//cout << endl;
		for (int j = 0; j < hashTable2[i].size(); j++)
		{
			cout << i << ". ("<< hashTable2[i][j].v_0 << " ," << hashTable2[i][j].v_1 <<")" << " color:" << hashTable2[i][j].color<< endl;
		}
		
	}
	cout << endl <<"Used colors list:" <<endl;
	for (int i = 0; i < coloredEdgeVector.size(); i++)
	{
		cout << i+1 << ". " << coloredEdgeVector[i] << endl;
	}
	return 0;
}

