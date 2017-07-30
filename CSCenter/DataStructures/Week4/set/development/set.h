#ifndef SET_H
#define SET_H

#include <set>

using namespace std;

class Set {
public:
	Set() : last_sum_(0) {}
	//classes used polymorphically should have virtual destructors
	virtual ~Set() {}
	
	virtual void Add(int i) = 0;
	virtual void Del(int i) = 0;
	virtual bool Find(int i) const = 0;
	virtual long long Sum(int l, int r) const = 0;
	
	//in header files only inline methods can be fully defined safely
	//see 'one-definition rule' for details
	long long last_sum() const {
		return last_sum_;
	}
	
protected:
	mutable long long last_sum_;
};

class NaiveSet : public Set {
public:
	virtual void Add(int i);
	virtual void Del(int i);
	virtual bool Find(int i) const;
	virtual long long Sum(int l, int r) const;
	
private:
	set<int> set_;
};

class SplaySet : public Set {
public:
	SplaySet() : root_(nullptr) {}	
	
	~SplaySet() {
		SplayFree(root_);
	}

	virtual void Add(int i);
	virtual void Del(int i);
	virtual bool Find(int i) const;
	virtual long long Sum(int l, int r) const;
	
private:
	struct Node {
		int key;       
		long long sum;
		Node *p, *l, *r;  
		
		Node(int key, long long sum, Node* p, Node* l, Node* r) : 
					key(key), sum(sum), p(p), l(l), r(r) {}
	};
	
	void SplayFree(Node* node) {
		if(node == nullptr) {
			return;
		}
		SplayFree(node->l);
		SplayFree(node->r);
		delete node;
	}
	
	void Update(Node* node) const;
	void Rotate(Node* node) const;
	bool Zig(Node* node) const;
	bool ZigZig(Node* node) const;
	void ZigZag(Node* node) const;
	void Splay(Node*& root, Node* node) const;
	Node* Find(Node*& root, int key) const;
	/* passing pointers by refs is essential here
	 * due to the need to set themselves inside 
	 * this function (not modify what they pointed to)
	 */
	void Split(Node* root, int key, Node*& left, Node*& right) const;
	Node* Merge(Node* left, Node* right) const;
	void Del(Node* node);
	
	/* 
	 * WARNING: proper 'copy constructor' and 'operator='
	 * are needed to make deep copies 
	 */
	mutable Node* root_;
};

#endif
