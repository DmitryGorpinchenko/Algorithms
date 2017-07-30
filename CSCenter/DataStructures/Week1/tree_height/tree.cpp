#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;

class Tree {
public:
	Tree(const vector<int>& parent);
	
	int height() const {
		return height_;
	}
	
	int size() const {
		return size_;
	}
	
	static void read(vector<int> *parent);
	
	static void write_balanced(int n);
	static void write_stump(int n);
	static void write_line(int n);
	
private:
	struct TreeNode {
		typedef shared_ptr<TreeNode> smart_ptr;
		
		int key;
		vector<smart_ptr> children_;
		
		TreeNode() : key(0) {}
	};
	
	typedef TreeNode::smart_ptr smart_ptr;
	
   /*
	 * this function needs to be inline to prevent recursion stack overflow
	 * so it is better to implicitly mark it as inline
	 */ 
	static int ComputeHeight(const smart_ptr& tree) {
		int h = 0;
		for(auto& child : tree->children_) {
			h = max(h, ComputeHeight(child));
		}
		return 1 + h; 
	}
	
	int size_;
	int height_;
	smart_ptr root_;
};

Tree::Tree(const vector<int>& parent) {
	size_ = parent.size();
	vector<smart_ptr> nodes(size_);
	for(auto& node : nodes) {
		node = smart_ptr(new TreeNode);
	}
	for(int i = 0; i < size_; i++) {
		if(parent[i] != -1) {
			nodes[parent[i]]->children_.push_back(nodes[i]);
		} else {
			root_ = nodes[i];
		}
	}
	height_ = ComputeHeight(root_);
}

void Tree::read(vector<int> *parent) {
	int n;
	cin >> n;
	parent->resize(n);
	for (auto& p : *parent) {
		cin >> p;
	}
}
	
void Tree::write_balanced(int n) {
	cout << n << endl;
	cout << -1 << " ";
	int count = -1;
	for(int i = 1; i < n; i++) {
		if(i % 2 != 0) {
			++count;
		}
		cout << count << " ";
	}
	cout << endl;
}
	
void Tree::write_stump(int n) {
	cout << n << endl;
	cout << -1 << " ";
	for(int i = 1; i < n; i++) {
		cout << 0 << " ";
	}
	cout << endl;
}

void Tree::write_line(int n) {
	cout << n << endl;
	for(int i = 0; i < n; i++) {
		cout << i - 1 << " ";
	}
	cout << endl;
}

int main() {
	ios::sync_with_stdio(false);
	
	//Tree::write_balanced(100000);
	//Tree::write_stump(100000);
	//Tree::write_line(100000);
	
	vector<int> parent;
	Tree::read(&parent);
	Tree tree(parent);
	cout << tree.height() << endl; 
	return 0;
}
