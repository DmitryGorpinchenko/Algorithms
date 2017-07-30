#include <iostream>
#include <vector>

using namespace std;

class BinaryTree {
public:
	void Read();
	
	int size() const {
		return nodes.size();
	}
	
	void PreOrder(vector<int>* keys) const {
		PreOrder(0, keys);
	}
	
	void InOrder(vector<int>* keys) const {
		InOrder(0, keys);
	}
	
	void PostOrder(vector<int>* keys) const {
		PostOrder(0, keys);
	}
	
private:
	struct Node {
		int key;
		int l, r;
	};
	
	void PreOrder(int id, vector<int>* keys) const;
	void InOrder(int id, vector<int>* keys) const;
	void PostOrder(int id, vector<int>* keys) const;
	
	vector<Node> nodes;
};

void BinaryTree::Read() {
	int n;
	cin >> n;
	nodes.resize(n);
	for(auto& node : nodes) {
		cin >> node.key >> node.l >> node.r;
	}
}

void BinaryTree::PreOrder(int id, vector<int>* keys) const {
	if(id == -1) {
		return;
	}
	keys->push_back(nodes[id].key);
	PreOrder(nodes[id].l, keys);
	PreOrder(nodes[id].r, keys);
}
	
void BinaryTree::InOrder(int id, vector<int>* keys) const {
	if(id == -1) {
		return;
	}
	InOrder(nodes[id].l, keys);
	keys->push_back(nodes[id].key);
	InOrder(nodes[id].r, keys);
}
	
void BinaryTree::PostOrder(int id, vector<int>* keys) const {
	if(id == -1) {
		return;
	}
	PostOrder(nodes[id].l, keys);
	PostOrder(nodes[id].r, keys);
	keys->push_back(nodes[id].key);
}

void Print(const vector<int>& v);

int main() {
	ios_base::sync_with_stdio(false);
	BinaryTree tree;
	tree.Read();
	vector<int> in_order, pre_order, post_order;
	tree.InOrder(&in_order);
	tree.PreOrder(&pre_order);
	tree.PostOrder(&post_order);
	Print(in_order);
	Print(pre_order);
	Print(post_order);
	return 0;
}

void Print(const vector<int>& v) {
	for(auto& el : v) {
		cout << el << " ";
	}
	cout << endl;
}
