#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Job {
	int w;
	int l;
	
	Job(int w, int l) : w(w), l(l) {}
	
	struct DiffComparator {
		bool operator() (const Job& j1, const Job& j2) {
			if(j1.w - j1.l == j2.w - j2.l) {
				return j1.w > j2.w;
			}
			return j1.w - j1.l > j2.w - j2.l;
		}	
	} static DiffComparator;
	
	struct RatioComparator {
		bool operator() (const Job& j1, const Job& j2) {
			return static_cast<double>(j1.w) / j1.l > static_cast<double>(j2.w) / j2.l;
		}
	} static RatioComparator;
};

template<typename Comparator>
long long ScheduleJobs(vector<Job>& jobs, Comparator comp);
long long ComputeCost(const vector<Job>& jobs);

int main() {
	int n, w, l;
	cin >> n;
	vector<Job> jobs;
	for(int i = 0; i < n; ++i) {
		cin >> w >> l;
		jobs.push_back(Job(w, l));
	}
	cout << ScheduleJobs(jobs, Job::DiffComparator) << endl;
	cout << ScheduleJobs(jobs, Job::RatioComparator) << endl;
	return 0;
}

template<typename Comparator>
long long ScheduleJobs(vector<Job>& jobs, Comparator comp) {
	sort(jobs.begin(), jobs.end(), comp);
	return ComputeCost(jobs);
}

long long ComputeCost(const vector<Job>& jobs) {
	long long time = 0;
	long long cost = 0;
	for(auto& j : jobs) {
		time += j.l;
		cost += j.w * time;
	}
	return cost;
}
