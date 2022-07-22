#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>

using namespace std;


int main()

{
	vector <pair<int, int>> agent;
	int tem, sum, a, num, prn = 0;
	srand(time(NULL));
	cout << "인자 개수 : ";
	cin >> num;
	//---------------------------------- 인자 생성
	for (int i = 0; i < num; i++)
	{
		int first, second;
		cin >> first >> second;
		agent.push_back(make_pair(first, second));
	}
	vector <vector<int>> list;
	//---------------------------------- 인자 순서 생성
	for (int i = 0; i < 10; i++)
	{
		int count = 0;
		vector<int> tems(num, 0);
		vector <int> input;
		while (count != num)
		{
			tem = rand() % num;
			if (tems[tem] == 0)
			{
				count++;
				tems[tem] = 1;
				input.push_back(tem);
			}
		}
		list.push_back(input);
	}
	//---------------------------------- 인자 우월성 선별
	for (int l = 0; l < 10000; l++)
	{
		prn++;
		vector <pair<int, int>> suporiority;
		for (int i = 0; i < 10; i++)
		{
			vector <int> sample = list[i];
			int sum = 0;
			for (int j = 0; j < num - 1; j++)
			{
				int tema = sample[j];
				int temb = sample[j + 1];
				int x = agent[tema].first - agent[temb].first;
				int y = agent[tema].second - agent[temb].second;
				sum += x * x + y * y;
			}
			suporiority.push_back(make_pair(sum, i));
		}
		sort(suporiority.begin(), suporiority.end());
		vector <vector<int>> selected_agent_struct;
		for (int i = 0; i < 3; i++)
		{
			selected_agent_struct.push_back(list[suporiority[i].second]);
		}
		//---------------------------------- 인자 번식
		vector <int> selected1;
		vector <int> selected2;
		vector <vector<int>>newlist;
		for (int i = 0; i < 5; i++)
		{
			int select2 = 0;
			int select1 = rand() % 3;
			while (1)
			{
				select2 = rand() % 3;
				if (select2 != select1)
				{
					break;
				}
			}
			selected1 = selected_agent_struct[select1];
			selected2 = selected_agent_struct[select2];
			int select_range_first = rand() % num;
			int select_range_second = 0;
			while (1)
			{
				select_range_first = rand() % num;
				if (select_range_second >= select_range_first)
				{
					break;
				}
			}
			vector <int> newagent1(num, -1);
			vector <int> newagent2(num, -1);
			for (int j = 0; j < select_range_second - select_range_first + 1; j++)
			{
				newagent1[select_range_first + j] = selected2[select_range_first + j];
				newagent2[select_range_first + j] = selected1[select_range_first + j];
			}
			for (int j = 0; j < num; j++)
			{
				for (int k = 0; k < num; k++)
				{
					if (find(newagent1.begin(), newagent1.end(), selected1[k]) == newagent1.end() && newagent1[j] == -1)
					{
						newagent1[j] = selected1[k];
						break;
					}
				}
				for (int k = 0; k < num; k++)
				{
					if (find(newagent2.begin(), newagent2.end(), selected2[k]) == newagent2.end() && newagent2[j] == -1)
					{
						newagent2[j] = selected2[k];
						break;
					}
				}
			}
			if (rand() % 5 == 1)
			{
				int random2 = 0;
				int random1 = rand() % num;
				while (1)
				{
					random2 = rand() % num;
					if (random2 > select1)
					{
						break;
					}
				}
				if (rand() % 2 == 1)
				{
					int tem = newagent1[random1];
					newagent1[random1] = newagent1[random2];
					newagent1[random2] = tem;
				}
				else
				{
					int tem = newagent2[random1];
					newagent2[random1] = newagent2[random2];
					newagent2[random2] = tem;
				}
			}
			newlist.push_back(newagent1);
			newlist.push_back(newagent2);
		}
		list = newlist;
		if (prn % 1000 == 0)
		{
			for (int e = 0; e < list.size(); e++)
			{
				for (int f = 0; f < list[e].size(); f++)
				{
					cout << list[e][f] << " ";
				}
				cout << "\n";
			}
			cout << "====== " << prn << " 번째 자손 =======\n";
		}
	}
}