#include <iostream>
#include <queue>
#include <vector>

struct Request {
	Request(int arrival_time, int process_time):
		arrival_time(arrival_time),
		process_time(process_time)
	{}

	int arrival_time;
	int process_time;
};

struct Response {
	Response(int start_time):
		start_time(start_time)
	{}
	
	int start_time;
};

class Buffer {
public:
	explicit Buffer(int size) : buff_size_(size) {}

	bool put(int finish_time) {
		if(finish_times_.size() < buff_size_) {
			finish_times_.push(finish_time);
			return true;
		}
		return false;
	}	
	
	bool HasNext() const {
		return !finish_times_.empty();
	}
	
	int next() const {
		return finish_times_.front();
	}
	
	int last() const {
		return finish_times_.back();
	}
	
	void RemoveNext() {
		finish_times_.pop();
	}
	
private:
	int buff_size_;
	std::queue<int> finish_times_;
};

class Server {
public:
	explicit Server(int buff_size) : buff_(buff_size) {}
	
	void Process(const Request& request) {
		while(buff_.HasNext() && request.arrival_time >= buff_.next()) {
			buff_.RemoveNext();
		}
		int start_time = buff_.HasNext() ? buff_.last() : request.arrival_time;
		if(!buff_.put(start_time + request.process_time)) {
			start_time = -1;
		}
		log(Response(start_time));
	}
	
	void ServeRequests(const std::vector<Request>& generator) {
		for(auto& req : generator) {
			Process(req);
		}
	}
	
	void PrintLog() const {
		for(auto& res : log_file_) {
			std::cout << res.start_time << std::endl;
		}
	}
	
private:
	void log(const Response& resp) {
		log_file_.push_back(resp);
	}

	Buffer buff_;
	std::vector<Response> log_file_;
};

void ReadRequests(std::vector<Request> *requests) {
	int count;
	std::cin >> count;
	for(int i = 0; i < count; ++i) {
		int arrival_time, process_time;
		std::cin >> arrival_time >> process_time;
		requests->push_back(Request(arrival_time, process_time));
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	int size;
	std::cin >> size;
	std::vector<Request> requests; 
	ReadRequests(&requests);
	Server server(size);
	server.ServeRequests(requests);
	server.PrintLog();
	return 0;
}
