#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "SLib.h"


struct Vec2
{
	int x;
	int y;
	Vec2(int newY, int newX)
	{
		x = newX;
		y = newY;
	}
	Vec2()
	{
		x = 0;
		y = 0;
	}
};

class AdjacencyNodeHead;

class AdjacencyNode
{
public:
	AdjacencyNodeHead* adjacentTo;//int adjacentTo
	int value;


	AdjacencyNode(AdjacencyNodeHead* adjTo, int v)
	{
		adjacentTo = adjTo;
		value = v;
	}

	AdjacencyNode()
	{
		adjacentTo = nullptr;
		value = 0;
	}
};

class AdjacencyNodeHead
{
public:
	StringS name;
	Vector<AdjacencyNode> nodes;
	int shortestDistance;
	AdjacencyNodeHead* previus_Head;
	bool checked;
	bool toreset;

	AdjacencyNodeHead()
	{
		shortestDistance = -1;
		previus_Head = nullptr;
		checked = false;
		toreset = false;
	}

	AdjacencyNodeHead(StringS& s)
	{
		shortestDistance = -1;
		previus_Head = nullptr;
		name = s;
		checked = false;
		toreset = false;
	}
};

class AdjacencyList
{
public:
	Vector<AdjacencyNodeHead> Vec;

	void Add(StringS& tmpName)
	{
		AdjacencyNodeHead tmp(tmpName);
		Vec.push(tmp);
	}
};



struct GlobalData
{
	AdjacencyList mainList;
	SHash* hash = new SHash(131771);//131771 //11621
	int size_x;
	int size_y;
	char** arr;
};

StringS getString(GlobalData& gData, int y, int x)
{
	StringS result;
	result = "";
	while (true)
	{
		if (x > 0)
		{
			if ((gData.arr[y][x - 1] >= 65 && gData.arr[y][x - 1] <= 90) || (gData.arr[y][x - 1] >= 48 && gData.arr[y][x - 1] <= 57))
			{
				x--;
			}
			else
				break;
		}
		else
			break;

	};
	while (true)
	{
		if (x < gData.size_x)
		{
			if ((gData.arr[y][x] >= 65 && gData.arr[y][x] <= 90) || (gData.arr[y][x] >= 48 && gData.arr[y][x] <= 57))
			{
				result.append(gData.arr[y][x]);
				x++;
			}
			else
				break;
		}
		else
			break;

	};
	return result;
}


StringS getname(GlobalData& gData, int y, int x)
{
	StringS tmpName;
	int min_y;
	int max_y;
	int min_x;
	int max_x;
	y > 0 ? min_y = -1 : min_y = 0;
	y < (gData.size_y - 1) ? max_y = 1 : max_y = 0;
	x > 0 ? min_x = -1 : min_x = 0;
	x < (gData.size_x - 1) ? max_x = 1 : max_x = 0;
	for (int k = min_y; k <= max_y; k++)
	{
		for (int l = min_x; l <= max_x; l++)
		{
			if ((gData.arr[y + k][x + l] >= 65 && gData.arr[y + k][x + l] <= 90) || (gData.arr[y + k][x + l] >= 48 && gData.arr[y + k][x + l] <= 57))
			{
				tmpName = getString(gData, y + k, x + l);
				break;
			}
		}
	}
	return tmpName;
}


void createGraphNode(GlobalData& gData, int NodeBaseIndex, StringS& ToAdd, int value)
{
	int newIndex = gData.hash->FindIndexByName(ToAdd);
	AdjacencyNode node(&gData.mainList.Vec[newIndex], value);
	gData.mainList.Vec[NodeBaseIndex].nodes.push(node);
}


void zapytanie(GlobalData& gData, StringS& name1, StringS& name2, int typ)
{
	if (name1 == name2)
	{
		std::cout << "0" << std::endl;
		return;
	}
	AdjacencyNodeHead* start = &gData.mainList.Vec[gData.hash->FindIndexByName(name1)];
	start->shortestDistance = 0;
	start->toreset = true;

	Vector<AdjacencyNodeHead*>* toReset, *active, *checked;
	toReset = new Vector<AdjacencyNodeHead*>;
	active = new Vector<AdjacencyNodeHead*>;
	checked = new Vector<AdjacencyNodeHead*>;

	toReset->push(start);
	active->push(start);

	Vector<AdjacencyNodeHead*>* bufor;

	while (active->size() > 0)
	{
		for (size_t i = 0; i < active->size(); i++)
		{
			Vector<AdjacencyNode>* node = &((*active)[i]->nodes);
			for (size_t j = 0; j < node->size(); j++)
			{
				if ((*node)[j].adjacentTo->shortestDistance == -1 ||
					(*node)[j].adjacentTo->shortestDistance > (*active)[i]->shortestDistance + (*node)[j].value)
				{

					(*node)[j].adjacentTo->shortestDistance = (*active)[i]->shortestDistance + (*node)[j].value;
					(*node)[j].adjacentTo->previus_Head = (*active)[i];
					toReset->push((*node)[j].adjacentTo);
					(*node)[j].adjacentTo->toreset = true;

					if ((*node)[j].adjacentTo->checked == false)
					{
						(*checked).push((*node)[j].adjacentTo);
						(*node)[j].adjacentTo->checked = true;
					}
				}
			}
		}
		for (size_t i = 0; i < checked->size(); i++)
		{
			(*checked)[i]->checked = false;
		}
		active->clear();

		bufor = active;
		active = checked;
		checked = bufor;
	}

	AdjacencyNodeHead* smallest = &gData.mainList.Vec[gData.hash->FindIndexByName(name2)];

	if (typ == 0)
		std::cout << smallest->shortestDistance << std::endl;
	else
	{
		std::cout << smallest->shortestDistance << " ";


		Vector<StringS*> reverse;
		while (!(smallest->name == name1))
		{
			reverse.push(&(smallest->previus_Head->name));
			smallest = smallest->previus_Head;
		}
		int s = reverse.size();
		for (int i = 0; i < s -1; i++)
		{
			std::cout << *reverse[s - i - 2] << " ";
		}
		std::cout << std::endl;
	}

	for (size_t i = 0; i < toReset->size(); i++)
	{
		(*toReset)[i]->toreset = false;
		(*toReset)[i]->shortestDistance = -1;
	}
}

void createGraph(GlobalData& gData)
{
	long long counter;
	long long** tmpArr;
	tmpArr = new long long* [gData.size_y];
	for (long long i = 0; i < gData.size_y; i++)
		tmpArr[i] = new long long[gData.size_x];

	Vector<Vec2> to_ceck;
	Vec2 newVec;
	for (int i = 0; i < gData.size_y; i++)
	{
		for (int j = 0; j < gData.size_x; j++)
		{
			if (gData.arr[i][j] == '*')
			{
				newVec.y = i;
				newVec.x = j;
				to_ceck.push(newVec);
			}
			if (gData.arr[i][j] == '#')
				tmpArr[i][j] = -1;//path to check
			else if (gData.arr[i][j] == '*')
				tmpArr[i][j] = -2;//city
			else
			{
				tmpArr[i][j] = -3;//not a path
			}
		}
	}


	StringS name1;
	StringS name2;
	int NodeBaseIndex;

	Vector<Vec2>* tmp1;
	Vector<Vec2>* tmp2;
	Vector<Vec2>* bufor;
	Vector<Vec2> toresetCity;
	counter = 0;
	for (size_t i = 0; i < to_ceck.size(); i++)
	{
		tmp1 = new Vector<Vec2>;
		tmp2 = new Vector<Vec2>;
		to_ceck[i];
		long long X = counter;
		tmp1->push(to_ceck[i]);
		name1 = getname(gData, to_ceck[i].y, to_ceck[i].x);
		NodeBaseIndex = gData.hash->FindIndexByName(name1);


		tmpArr[to_ceck[i].y][to_ceck[i].x] = counter;
		toresetCity.push(Vec2(to_ceck[i].y, to_ceck[i].x));

		while (tmp1->size() != 0)
		{
			counter++;
			for (size_t j = 0; j < tmp1->size(); j++)
			{
				if ((*tmp1)[j].y > 0)
				{
					if (tmpArr[(*tmp1)[j].y - 1][(*tmp1)[j].x] == -2)
					{
						tmpArr[(*tmp1)[j].y - 1][(*tmp1)[j].x] = counter;
						name2 = getname(gData, (*tmp1)[j].y - 1, (*tmp1)[j].x);
						toresetCity.push(Vec2((*tmp1)[j].y - 1, (*tmp1)[j].x));
						createGraphNode(gData, NodeBaseIndex, name2, (int)(counter - X));
					}
					else if (tmpArr[(*tmp1)[j].y - 1][(*tmp1)[j].x] <= X && tmpArr[(*tmp1)[j].y - 1][(*tmp1)[j].x] != -3)
					{
						tmpArr[(*tmp1)[j].y - 1][(*tmp1)[j].x] = counter;
						tmp2->push(Vec2((*tmp1)[j].y - 1, (*tmp1)[j].x));
					}
				}
				if ((*tmp1)[j].y < gData.size_y - 1)
				{
					if (tmpArr[(*tmp1)[j].y + 1][(*tmp1)[j].x] == -2)
					{
						tmpArr[(*tmp1)[j].y + 1][(*tmp1)[j].x] = counter;
						name2 = getname(gData, (*tmp1)[j].y + 1, (*tmp1)[j].x);
						toresetCity.push(Vec2((*tmp1)[j].y + 1, (*tmp1)[j].x));
						createGraphNode(gData, NodeBaseIndex, name2, (int)(counter - X));
					}
					else if (tmpArr[(*tmp1)[j].y + 1][(*tmp1)[j].x] <= X && tmpArr[(*tmp1)[j].y + 1][(*tmp1)[j].x] != -3)
					{
						tmpArr[(*tmp1)[j].y + 1][(*tmp1)[j].x] = counter;
						tmp2->push(Vec2((*tmp1)[j].y + 1, (*tmp1)[j].x));
					}
				}
				if ((*tmp1)[j].x > 0)
				{

					if (tmpArr[(*tmp1)[j].y][(*tmp1)[j].x - 1] == -2)
					{
						tmpArr[(*tmp1)[j].y][(*tmp1)[j].x - 1] = counter;
						name2 = getname(gData, (*tmp1)[j].y, (*tmp1)[j].x - 1);
						toresetCity.push(Vec2((*tmp1)[j].y, (*tmp1)[j].x - 1));
						createGraphNode(gData, NodeBaseIndex, name2, (int)(counter - X));
					}
					else if (tmpArr[(*tmp1)[j].y][(*tmp1)[j].x - 1] <= X && tmpArr[(*tmp1)[j].y][(*tmp1)[j].x - 1] != -3)
					{
						tmpArr[(*tmp1)[j].y][(*tmp1)[j].x - 1] = counter;
						tmp2->push(Vec2((*tmp1)[j].y, (*tmp1)[j].x - 1));
					}
				}
				if ((*tmp1)[j].x < gData.size_x - 1)
				{
					if (tmpArr[(*tmp1)[j].y][(*tmp1)[j].x + 1] == -2)
					{
						tmpArr[(*tmp1)[j].y][(*tmp1)[j].x + 1] = counter;
						name2 = getname(gData, (*tmp1)[j].y, (*tmp1)[j].x + 1);
						toresetCity.push(Vec2((*tmp1)[j].y, (*tmp1)[j].x + 1));
						createGraphNode(gData, NodeBaseIndex, name2, (int)(counter - X));
					}
					else if (tmpArr[(*tmp1)[j].y][(*tmp1)[j].x + 1] <= X && tmpArr[(*tmp1)[j].y][(*tmp1)[j].x + 1] != -3)
					{
						tmpArr[(*tmp1)[j].y][(*tmp1)[j].x + 1] = counter;
						tmp2->push(Vec2((*tmp1)[j].y, (*tmp1)[j].x + 1));
					}
				}
			}
			bufor = tmp1;
			tmp1 = tmp2;
			tmp2 = bufor;
			tmp2->clear();
		}

		while (toresetCity.size() > 0)
		{
			Vec2 popped;
			popped = toresetCity.pop();
			tmpArr[popped.y][popped.x] = -2;
		}

		delete tmp1;
		delete tmp2;
	}
	for (int i = 0; i < gData.size_y; i++)
	{
		delete[] tmpArr[i];
	}
	delete[] tmpArr;
}

int main()
{
	std::cout.sync_with_stdio(false);
	StringS tmpName;
	char ch;
	GlobalData gData;
	std::cin >> gData.size_x;
	std::cin >> gData.size_y;
	gData.arr = new char* [gData.size_y];

	for (int i = 0; i < gData.size_y; i++)
		gData.arr[i] = new char[gData.size_x];

	ch = getchar();
	for (int i = 0; i < gData.size_y; i++)
	{
		for (int j = 0; j < gData.size_x; j++)
		{
			ch = getchar();
			gData.arr[i][j] = ch;
		}
		ch = getchar();
	}

	for (int i = 0; i < gData.size_y; i++)
	{
		for (int j = 0; j < gData.size_x; j++)
		{
			if (gData.arr[i][j] == '*')
			{
				tmpName = getname(gData, i, j);
				//cout << i << "," << j << " " << tmpName << " ";
				gData.mainList.Add(tmpName);
				gData.hash->toHash(tmpName);
			}
		}
	}
	createGraph(gData);

	StringS name1;
	StringS name2;
	StringS tmpLength;
	int length;
	int iloscLinLotniczych;

	std::cin >> iloscLinLotniczych;
	getchar();

	for (int i = 0; i < iloscLinLotniczych; i++)
	{

		name1 = "";
		name2 = "";
		tmpLength = "";
		//cout << "A";

		ch = getchar();
		while (ch != ' ')
		{
			name1.append(ch);
			//cout << endl << name1 << endl;
			ch = getchar();
		}
		ch = getchar();
		while (ch != ' ')
		{
			name2.append(ch);
			//cout << endl << name2 << endl;
			ch = getchar();
		}
		ch = getchar();
		while (ch != '\n')
		{
			tmpLength.append(ch);
			//cout << endl << tmpLength << endl;
			ch = getchar();
		}
		length = tmpLength.toInt();
		//cout << endl << length << endl;
		if (gData.hash->FindIndexByName(name1) == -1)
		{
			std::cout << std::endl << "cant find " << name1 << std::endl;
			std::cout << name1.length() << std::endl;
			exit(1);
		}
		createGraphNode(gData, gData.hash->FindIndexByName(name1), name2, length);
	}

	int iloscPytan;
	std::cin >> iloscPytan;
	getchar();
	for (int i = 0; i < iloscPytan; i++)
	{
		name1 = "";
		name2 = "";
		tmpLength = "";
		//cout << "A";

		ch = getchar();
		while (ch != ' ')
		{
			name1.append(ch);
			//cout << endl << name1 << endl;
			ch = getchar();
		}
		ch = getchar();
		while (ch != ' ')
		{
			name2.append(ch);
			//cout << endl << name2 << endl;
			ch = getchar();
		}
		ch = getchar();
		while (ch != '\n')
		{
			tmpLength.append(ch);
			//cout << endl << tmpLength << endl;
			ch = getchar();
		}
		length = tmpLength.toInt();
		//cout << endl << length << endl;
		zapytanie(gData, name1, name2, length);
	}
}