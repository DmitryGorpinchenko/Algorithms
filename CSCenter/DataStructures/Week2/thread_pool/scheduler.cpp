#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Task {
public:
	Task(int duration) : duration_(duration) {}

	int duration() const {
		return duration_;
	}	
	
private:
	int duration_;
};	

class Thread {
public:	
	explicit Thread()	: id_(count++), timer_(0) {}
	
	void BeginExecution() {
		//some code
	}
	
	void SetProgramCounter(const Task& task) {
		timer_ += task.duration();
	}
	
	int id() const {
		return id_;
	}
	
	long long timer() const {
		return timer_;
	}
	
	bool operator < (const Thread& other) const {
		return timer_ > other.timer_ || (timer_ == other.timer_ && id_ > other.id_);
	}
	
private:	
	static int count;
		
	int id_;
	long long timer_;
};

int Thread::count = 0;

class Scheduler {
public:
	explicit Scheduler(int pool_size) {
		for(int i = 0; i < pool_size; i++) {
			pool_.push(Thread());
		}
	}
	
	void ScheduleTasks(const vector<Task>& job_list) {
		for(auto& task : job_list) {	
			Thread free_thread = pool_.top();
			pool_.pop();
			Log(free_thread.id(), free_thread.timer());
			free_thread.SetProgramCounter(task);
			free_thread.BeginExecution(); //call dummy method for more realistic simulation
			pool_.push(free_thread);
		}
	}
	
	void PrintLog() const {
		for(auto& entry : log_) {
			cout << entry.first << " " << entry.second << endl;
		}
	}
	
private:
	void Log(int id, long long start_time) {
		log_.push_back(make_pair(id, start_time));
	}
	
	priority_queue<Thread> pool_;
	vector<pair<int, long long> > log_;
};

int main() {
	ios::sync_with_stdio(false);
	int n, m, duration;
	cin >> n >> m;
	vector<Task> job_list;
	for(int i = 0; i < m; i++) {
		cin >> duration;
		job_list.push_back(Task(duration));
	}
	Scheduler scheduler(n);
	scheduler.ScheduleTasks(job_list);
	scheduler.PrintLog();
	return 0;
}
