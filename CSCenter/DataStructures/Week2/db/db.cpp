#include <vector>
#include <iostream>

using namespace std;

class DB {
public:
	DB() : max_table_size_(0) {}
	
	int max_table_size() const {
		return max_table_size_;
	}
	
	void AddTable(int size);
	void MergeTables(int dest_id, int src_id);
	
private:
	struct Table {
		Table(int size): size(size), symlink(count), rank(0), parent(count) {
			count++;
		}
	
		static int count;
		int size, symlink, rank, parent;
	};
	
	int FindRoot(int table_id);

	int max_table_size_;
	vector<Table> tables_;
};

int DB::Table::count = 0;

void DB::AddTable(int size) {
	tables_.push_back(Table(size));
	max_table_size_ = max(size, max_table_size_);
}

void DB::MergeTables(int dest_id, int src_id) {
	int dest_root = FindRoot(dest_id);
	int src_root = FindRoot(src_id);
	if (dest_root != src_root) {
		dest_id = tables_[dest_root].symlink;
		src_id  = tables_[src_root].symlink;
		tables_[dest_id].size += tables_[src_id].size;
		tables_[src_id].size = 0;
		tables_[src_id].symlink = dest_id;
		max_table_size_ = max(max_table_size_, tables_[dest_id].size);
		if(tables_[dest_root].rank > tables_[src_root].rank) {
			tables_[src_root].parent = dest_root;
		} else {
			tables_[dest_root].parent = src_root;
			if(tables_[dest_root].rank == tables_[src_root].rank) {
				++tables_[src_root].rank;
			}
			tables_[src_root].symlink = dest_id;
		}
	}		
}

int DB::FindRoot(int table_id) {
	if(tables_[table_id].parent != table_id) {
		tables_[table_id].parent = FindRoot(tables_[table_id].parent);
	}
	return tables_[table_id].parent;
}

int main() {
	ios::sync_with_stdio(false);
	int n, m, size, dest_id, src_id;
	cin >> n >> m;
	DB db;
	for (int i = 0; i < n; i++) {
		cin >> size;
		db.AddTable(size);
	}
	for (int i = 0; i < m; i++) {
		cin >> dest_id >> src_id;
		--dest_id;
		--src_id;
		db.MergeTables(dest_id, src_id);
		cout << db.max_table_size() << endl;
	}
	return 0;
}
