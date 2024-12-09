#include <vector>
#include <limits.h>
#include <string>
#include <iostream>
using namespace std;
int main() {
	int NodeNUm, EdgeNum;
	cin >> NodeNUm >> EdgeNum;
	vector<vector<pair<int,int>>> graph1(NodeNUm);//储存入边
	vector<vector<pair<int,int>>> graph2(NodeNUm);//储存出边
	vector<int> Nodecount(NodeNUm, 0);//节点入度
	vector<int> ZeroNode;//入度为0节点
	vector<int> Path;//拓扑排序
	vector<int> Start(NodeNUm, 0);
	vector<int> End(NodeNUm, INT_MAX);
	int count = 0;
	int x, y,val;
	for (int i = 0; i < EdgeNum; ++i) {
		cin >> x >> y>>val;
		graph1[x].emplace_back(y,val);
		graph2[y].emplace_back(x,val);
		Nodecount[y] += 1;
	}
	for (int i = 0; i < NodeNUm; ++i) {
		if (Nodecount[i] == 0) {
			ZeroNode.emplace_back(i);
			count += 1;
		}
	}//初始零入度节点入队
	int judge1 = 1;
	while (ZeroNode.size() != 0) {
		int m = ZeroNode[0];
		ZeroNode.erase(ZeroNode.begin());
		Path.emplace_back(m);
		for (auto it : graph1[m])
		{
			Nodecount[it.first] -= 1;
			if (Nodecount[it.first] == 0)
			{
				ZeroNode.emplace_back(it.first);
				count += 1;
			}
			if (Nodecount[it.first] < 0)
			{
				judge1 = 0;
				break;
			}
		}
	} //判断是否有环
	int judge2 = (count == NodeNUm) ? 1 : 0;
	

	
	if (judge1 && judge2) 
	{for (int i = 0; i < NodeNUm; ++i) {  //最早开始
		int x = Path[i];
		for (auto it : graph1[x]) {
			if (Start[it.first] < Start[x] + it.second)
				Start[it.first] = Start[x] + it.second;
		}
	}
	End[Path.back()] = Start[Path.back()];  //末尾节点最晚开始时间同最早开始时间
	for (int i = NodeNUm-1; i >=0; --i) {  //最晚开始
		int x = Path[i];
		for (auto it : graph2[x]) {
			if (End[it.first] > End[x] - it.second)
			{
				End[it.first] = End[x] - it.second;
			}
		}
	}
	//关键路径可能很多，所有关键活动都会全部输出
		for (int i = 0; i < NodeNUm; ++i) {  //判断活动
			for (auto it = graph1[i].rbegin(); it != graph1[i].rend();++it) {

				if (it->second == (End[it->first] - Start[i]))
					cout << "<" << i << ", " << it->first << ">" << endl;
			}
		}
		cout << "关键路径分析结果为 1";
	}
	else
		cout << "关键路径分析结果为 0";
	return 0;
}