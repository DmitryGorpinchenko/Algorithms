#include "set.h"
#include <algorithm>

using namespace std;

void NaiveSet::Add(int i) {
	set_.insert(i);
}

void NaiveSet::Del(int i) {
	set_.erase(i);
}

bool NaiveSet::Find(int i) const {
	return set_.find(i) != set_.end();
}

long long NaiveSet::Sum(int l, int r) const {
	long long init = 0;
	last_sum_ = accumulate(set_.lower_bound(l), set_.upper_bound(r), init);
	return last_sum_;
}

void SplaySet::Add(int i) {
	Node* left = nullptr;
	Node* right = nullptr;
	Node* new_node = nullptr;  
	Split(root_, i, left, right);
	if (right == nullptr || right->key != i) {
		new_node = new Node(i, i, nullptr, nullptr, nullptr);
	}
	root_ = Merge(Merge(left, new_node), right);
}

void SplaySet::Del(int i) {
	if(Find(i)) {
		Node* left = nullptr;
		Node* right = nullptr;
		Split(root_, i, left, right);
		if(right->r != nullptr) {
			right->r->p = nullptr;
		}
		Node* tmp = root_;
		root_ = Merge(left, right->r);
		//delete 'old root' after accessing right->r 
		//because 'right' is an alias to the old root
		delete tmp;
	}
}

bool SplaySet::Find(int i) const {
	Node* tmp = Find(root_, i);
	return tmp != nullptr && tmp->key == i;
}

long long SplaySet::Sum(int l, int r) const {
	Node* left = nullptr;
	Node* middle = nullptr;
	Node* right = nullptr;
	Split(root_, l, left, middle);
	Split(middle, r + 1, middle, right);
	last_sum_ = (middle == nullptr) ? 0ll : middle->sum;
	root_ = Merge(Merge(left, middle), right);
	return last_sum_;
}

void SplaySet::Update(Node* node) const {
	if(node == nullptr) {
		return;
	}
	node->sum = node->key + (node->l != nullptr ? node->l->sum : 0ll)
								 + (node->r != nullptr ? node->r->sum : 0ll);
	if(node->l != nullptr) {
		node->l->p = node;
	}
	if(node->r != nullptr) {
		node->r->p = node;
	}
}

void SplaySet::Rotate(Node* node) const {
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

bool SplaySet::Zig(Node* node) const {
	bool flag = false;
	if(node->p->p == nullptr) {
		Rotate(node);
		flag = true;
	}
	return flag;
}

bool SplaySet::ZigZig(Node* node) const {
	bool flag = false;
	if(node->p->l == node && node->p->p->l == node->p || 
		node->p->r == node && node->p->p->r == node->p) {
		Rotate(node->p);
		Rotate(node);
		flag = true;
	} 
	return flag;
}

void SplaySet::ZigZag(Node* node) const {
	Rotate(node);
	Rotate(node);
}

void SplaySet::Splay(Node*& root, Node* node) const {
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

SplaySet::Node* SplaySet::Find(Node*& root, int key) const {
	Node* node = root;
	Node* last = root;
	Node* next = nullptr;
	while(node != nullptr) {
		if(node->key >= key && (next == nullptr || node->key < next->key)) {
			next = node;
		}
		last = node;
		if(node->key == key) {
			break;      
		}
		if(node->key < key) {
			node = node->r;
		} else {
			node = node->l;
		}
	}
	Splay(root, last);
	return next;
}

void SplaySet::Split(Node* root, int key, Node*& left, Node*& right) const {
	right = Find(root, key);
	Splay(root, right);
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

SplaySet::Node* SplaySet::Merge(Node* left, Node* right) const {
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
