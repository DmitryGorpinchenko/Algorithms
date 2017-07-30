#include <iostream>
#include <memory>
#include <vector>
#include <stdlib.h>
#include <time.h> 

using namespace std;

class AbstractRope {
public:
	virtual ~AbstractRope() {}
	virtual void CutAndPaste(int i, int j, int k) = 0;
	virtual string GetString() const = 0;
	
	void Print() const {
		cout << GetString() << endl;
	}
};

class NaiveRope : public AbstractRope {
public:
	NaiveRope(const string& s) : s_(s) {}

	virtual void CutAndPaste(int i, int j, int k) {
		string t = s_.substr(0, i) + s_.substr(j + 1);
		s_ = t.substr(0, k) + s_.substr(i, j - i + 1) + t.substr(k);
	}

	virtual string GetString() const {
		return s_;
	}
	
private:
	string s_;	
};

class Rope : public AbstractRope {
public:
	Rope(const string& s) : root_(nullptr) {
		BuildRope(s);
	}

	~Rope() {
		FreeRope(root_);
	}
	
	virtual void CutAndPaste(int i, int j, int k) {
		Node *left, *mid, *right, *rest;
		//it's good to always initialize pointers
		left = mid = right = rest = nullptr;
		Split(root_, i, left, rest);
		Split(rest, j - i + 1, mid, right);
		Split(Merge(left, right), k, left, right);
		root_ = Merge(Merge(left, mid), right);
	}
	
	virtual string GetString() const {
		string s;
		CollectString(root_, &s);
		return s;	
	}
	
private:
	struct Node {
		char letter; 
		int size;     
		Node *p, *l, *r;  
		
		Node(char letter, int size, Node* p, Node* l, Node* r) : 
					letter(letter), size(size), p(p), l(l), r(r) {}
	};
	
	void FreeRope(Node* node) {
		if(node == nullptr) {
			return;
		}
		FreeRope(node->l);
		FreeRope(node->r);
		delete node;
	}
	
	void BuildRope(const string& s);
	void CollectString(Node* node, string* s) const;
	static void Update(Node* node);
	static void Rotate(Node* node);
	static bool Zig(Node* node);
	static bool ZigZig(Node* node);
	static void ZigZag(Node* node);
	static void Splay(Node*& root, Node* node);
	static Node* Merge(Node* left, Node* right);
	//NOTE: i is 0-based index 
	static void Split(Node* root, int i, Node*& left, Node*& right);
	static Node* Find(Node*& root, int i); 

	Node* root_;	
};

void Rope::BuildRope(const string& s) {
	int len = s.size();
	for(int i = 0; i < len; ++i) {
		Node* node = new Node(s[i], 1, nullptr, nullptr, nullptr);
		root_ = Merge(root_, node);
	}
}

void Rope::CollectString(Node* node, string* s) const {
	if(node == nullptr) {
		return;
	}
	CollectString(node->l, s);
	s->push_back(node->letter);
	CollectString(node->r, s);
}

void Rope::Update(Node* node) {
	if(node == nullptr) {
		return;
	}
	node->size = 1 + (node->l != nullptr ? node->l->size : 0ll)
						+ (node->r != nullptr ? node->r->size : 0ll);
	if(node->l != nullptr) {
		node->l->p = node;
	}
	if(node->r != nullptr) {
		node->r->p = node;
	}
}

void Rope::Rotate(Node* node) {
	Node* P = node->p;
	if(P == nullptr) {
		return;
	}
	Node* GP = node->p->p;
	if(P->l == node) {
		Node* tmp = node->r;
		node->r = P;
		P->l = tmp;
	} else {
		Node* tmp = node->l;
		node->l = P;
		P->r = tmp;
	}
	Update(P);
	Update(node);
	node->p = GP;
	if(GP != nullptr) {
		if(GP->l == P) {
			GP->l = node;
		} else {
			GP->r = node;
		}
	}
}

bool Rope::Zig(Node* node) {
	bool flag = false;
	if(node->p->p == nullptr) {
		Rotate(node);
		flag = true;
	}
	return flag;
}

bool Rope::ZigZig(Node* node) {
	bool flag = false;
	if(node->p->l == node && node->p->p->l == node->p || 
		node->p->r == node && node->p->p->r == node->p) {
		Rotate(node->p);
		Rotate(node);
		flag = true;
	} 
	return flag;
}

void Rope::ZigZag(Node* node) {
	Rotate(node);
	Rotate(node);
}

void Rope::Splay(Node*& root, Node* node) {
	if(node == nullptr) {
		return;
	}
	while(node->p != nullptr) {
		if(!Zig(node)) {
			if(!ZigZig(node)) {
				ZigZag(node);
			}
		}
	}
	root = node;
}

Rope::Node* Rope::Find(Node*& root, int i) {
	Node* node = root;
	while(node != nullptr) {
		int s = (node->l == nullptr) ? 0 : node->l->size;
		if(i == s) {
			break;
		} else if(i < s) {
			node = node->l;
		} else {
			node = node->r;
			i = i - s - 1; 
		}
	}
	Splay(root, node);
	return node;
}

void Rope::Split(Node* root, int i, Node*& left, Node*& right) {
	right = Find(root, i);
	if(right == nullptr) {
		left = root;
		return;
	}
	left = right->l;
	right->l = nullptr;
	if(left != nullptr) {
		left->p = nullptr;
	}
	Update(left);
	Update(right);
}

Rope::Node* Rope::Merge(Node* left, Node* right) {
	if(left == nullptr) {
		return right;
	}
	if(right == nullptr) {
		return left;
	}
	Node* min_right = right;
	while(min_right->l != nullptr) {
		min_right = min_right->l;
	}
	Splay(right, min_right); 
	right->l = left;
	Update(right);
	return right;
}

void StressTest();

int main() {
	//StressTest();
	ios_base::sync_with_stdio(0);
	string s;
	cin >> s;
	unique_ptr<AbstractRope> rope(new Rope(s));
	int actions_num;
	cin >> actions_num;
	for(int action_index = 0; action_index < actions_num; ++action_index) {
		int i, j, k;
		cin >> i >> j >> k;
		rope->CutAndPaste(i, j, k);
	}
	rope->Print();
	return 0;
}	

void StressTest() {
	int len = 30000;
	int q_num = 10000;
	int lowercase_offset = 97;
	int alphabet_size = 26;
	int T = 100;
	int i, j, k;
	for(int t = 1; t <= T; ++t) {
		srand(time(NULL));
		string s;
		for(int c = 0; c < len; ++c) {
			s.push_back(rand() % alphabet_size + lowercase_offset);
		}
		NaiveRope nrope(s);
		Rope rope(s);
		for(int q = 0; q < q_num; ++q) {
			i = rand() % (len / 2);
			j = i + rand() % (len / 2 + 2);
			k = rand() % (len - (j - i + 1));
			nrope.CutAndPaste(i, j, k);
			rope.CutAndPaste(i, j, k);
		}
		if(nrope.GetString() != rope.GetString()) {
			cout << "FAILED!!! Something went wrong!" << endl;
			return;
		}
		cout << "Number of trials done: " << t << endl;
	}
	cout << endl << "PASSED!!!" << endl;
}
