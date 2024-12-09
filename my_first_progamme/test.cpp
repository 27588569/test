#include <vector>
#include <limits.h>
#include <string>
#include <iostream>
using namespace std;
int main() {
	int NodeNUm, EdgeNum;
	cin >> NodeNUm >> EdgeNum;
	vector<vector<pair<int,int>>> graph1(NodeNUm);//�������
	vector<vector<pair<int,int>>> graph2(NodeNUm);//�������
	vector<int> Nodecount(NodeNUm, 0);//�ڵ����
	vector<int> ZeroNode;//���Ϊ0�ڵ�
	vector<int> Path;//��������
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
	}//��ʼ����Ƚڵ����
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
	} //�ж��Ƿ��л�
	int judge2 = (count == NodeNUm) ? 1 : 0;
	

	
	if (judge1 && judge2) 
	{for (int i = 0; i < NodeNUm; ++i) {  //���翪ʼ
		int x = Path[i];
		for (auto it : graph1[x]) {
			if (Start[it.first] < Start[x] + it.second)
				Start[it.first] = Start[x] + it.second;
		}
	}
	End[Path.back()] = Start[Path.back()];  //ĩβ�ڵ�����ʼʱ��ͬ���翪ʼʱ��
	for (int i = NodeNUm-1; i >=0; --i) {  //����ʼ
		int x = Path[i];
		for (auto it : graph2[x]) {
			if (End[it.first] > End[x] - it.second)
			{
				End[it.first] = End[x] - it.second;
			}
		}
	}
	//�ؼ�·�����ܺܶ࣬���йؼ������ȫ�����
		for (int i = 0; i < NodeNUm; ++i) {  //�жϻ
			for (auto it = graph1[i].rbegin(); it != graph1[i].rend();++it) {

				if (it->second == (End[it->first] - Start[i]))
					cout << "<" << i << ", " << it->first << ">" << endl;
			}
		}
		cout << "�ؼ�·���������Ϊ 1";
	}
	else
		cout << "�ؼ�·���������Ϊ 0";
	return 0;
}