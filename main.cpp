#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <climits>
#include <algorithm>

using namespace std;

class node {
public:
	int index;
	int color;
	int parent;
	int distance;
	vector<int> children;
};

string visit(vector<node*> G, int R) {
	vector<node*> graph = G;
	map<int, string> distance;
	string result;
	int count = 0;
	int root = R;
	int min = INT_MAX;

	while (root < graph.size()) {
		queue<int> q;
		if (graph.at(root)->color == 0) {
			graph.at(root)->color = 1;
			graph.at(root)->distance = 0;
			graph.at(root)->parent = -1;
			q.push(root);
			while (!q.empty()) {
				int f = q.front();
				for (int i = 0; i < graph.at(f)->children.size(); i++) {
					int a = graph.at(f)->children.at(i);
					if (graph.at(a)->color == 0) {
						graph.at(a)->color = 1;
						graph.at(a)->distance = graph.at(f)->distance + 1;
						graph.at(a)->parent = f;
						q.push(a);
					}
				}

				q.pop();
				graph.at(f)->color = 2;
				count++;
			}
		}
		if (count != graph.size()) {
			return "disconnected";
		}
		int dis = 0;
		for (int i = 0; i < graph.size(); i++) {
			if (graph.at(i)->distance > dis) dis = graph.at(i)->distance;
		}
		if (distance.find(dis) == distance.end()) {
			distance.insert(pair<int, string>(dis, to_string(root) + " "));
		}
		else {
			string s = distance.find(dis)->second + to_string(root) + " ";
			distance.find(dis)->second = s;
		}
		if (min > dis) min = dis;

		for (int i = 0; i < graph.size(); i++) {
			graph.at(i)->color = 0;
			graph.at(i)->distance = 0;
			graph.at(i)->parent = -1;
			//graph.at(i)->children.clear();
		}
		root++;
		count = 0;
	}
	result = distance.at(min);
	return result;
}

int main() {
	vector <node*> graph;
	vector <string> result;
	int nodeSize;
	cin >> nodeSize;
	while (nodeSize > 0) {
		for (int i = 0; i < nodeSize; i++) {
			node* tmpNode = new node();
			tmpNode->index = i;
			tmpNode->color = 0;
			tmpNode->distance = 0;
			tmpNode->parent = -1;
			for (int j = 0; j < nodeSize; j++) {
				int node;
				cin >> node;
				if (node == 1) tmpNode->children.push_back(j);
			}
			graph.push_back(tmpNode);
		}
		string res = visit(graph,0);
		result.push_back(res);
		graph.clear();
		cin >> nodeSize;
	}

	for (int i = 0; i < result.size(); i++) {
		cout << result.at(i) << endl;
	}
	//for (int i = 0; i < nodeSize; i++) {
	//	cout << i << "|";
	//	for (int j = 0; j < graph.at(i)->children.size(); j++) {
	//		cout << graph.at(i)->children.at(j) << " ";
	//	}
	//	cout << endl;
	//}
	return 0;
}