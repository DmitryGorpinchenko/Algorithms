#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <climits>

// allows quickly retrieve backward edges
class BipartateGraph {
    struct Edge;

public:
    explicit BipartateGraph(size_t n, size_t m)
        : n(n), 
        m(m), 
        graph(n + m + 2) 
    {
        for(int i = 0; i < n; ++i) {
            add_edge(n + m, i, true); // connect source to one side of bipartate graph
        }
        for(int i = n; i < m + n; ++i) {
            add_edge(i, n + m + 1, true); // connect other side to sink
        }
    }

    //assumes u from source and v from sink side
    void add_edge(int u, int v, bool internal=false) {
        // forward edges stored at even and backward at odd indices
        if(! internal) {
            v = v + n;
        }
        graph[u].push_back(edges.size());
        graph[v].push_back(edges.size() + 1);
        edges.insert(edges.end(), { 
            { u, v, 1, 0 },
            { v, u, 0, 0 } 
        });
    }

    int max_matching(std::vector<int>* match_ids);

private:
    struct Edge {
        int from; 
        int to; 
        int capacity; 
        int flow;
        
        int res() const {
            return capacity - flow;
        }
    };
    
    size_t size() const {
        return graph.size();
    }

    const std::vector<size_t>& get_ids(int from) const {
        return graph[from];
    }

    const Edge& get_edge(size_t id) const {
        return edges[id];
    }

    void add_flow(size_t id, int flow) {
        // To get a backward edge for a true forward one (id is even), we should get id + 1
        // to get a "backward" edge for a backward one (id is odd), id - 1 should be taken
        edges[id].flow += flow;
        edges[id ^ 1].flow -= flow;
    }
    
    bool bfs(int s, int t, int ids[]);    
    int max_flow(int s, int t);

    int m, n;

    // forward and backward edges
    std::vector<Edge> edges;

    // adj lists store indices of edges in the edges list
    std::vector<std::vector<size_t> > graph;
};

int BipartateGraph::max_matching(std::vector<int>* match_ids) {
    match_ids->resize(n, -1);
    int matching_size = max_flow(n + m, n + m + 1); 
    for(auto neigh_id : get_ids(n + m)) { //adj to source
        auto e = get_edge(neigh_id);
        if(e.flow != 1) {
            continue;
        }
        for(auto neigh_iid : get_ids(e.to)) {
            auto ee = get_edge(neigh_iid);
            if(ee.flow == 1) {
                (*match_ids)[ee.from] = ee.to - n + 1;
                break;
            }
        }
    }
    return matching_size;
}

int BipartateGraph::max_flow(int s, int t) {
    int flow = 0, v, path_flow;
    int parent_edge_ids[graph.size()];
    while(bfs(s, t, parent_edge_ids)) {
        path_flow = INT_MAX;
        v = t;
        while(v != s) {
            auto e = get_edge(parent_edge_ids[v]);
            path_flow = std::min(path_flow, e.res());
            v = e.from;
        }
        for(v = t; v != s; v = get_edge(parent_edge_ids[v]).from) {
            add_flow(parent_edge_ids[v], path_flow);
        }
        flow += path_flow;
    }
    return flow;
}

bool BipartateGraph::bfs(int s, int t, int ids[]) {
    bool visited[size()];
    memset(visited, 0, sizeof(visited));
    std::queue<int> q;
    q.push(s);
    visited[s] = true;
    while(! q.empty()) {
        int curr = q.front();
        q.pop();
        if(curr == t) {
            return true;
        }
        for(auto neigh_id : get_ids(curr)) {
            auto e = get_edge(neigh_id);
            if(! visited[e.to] && e.res() > 0) {
                q.push(e.to);
                ids[e.to] = neigh_id;
                visited[e.to] = true;
            }
        }
    }
    return false;     
}

using StockInfo = std::vector<std::vector<int> >;

StockInfo read_stock_info();
BipartateGraph construct_graph(const StockInfo& stock_info);

int main() {
    std::ios_base::sync_with_stdio(false);
    StockInfo stock_info = read_stock_info();
    BipartateGraph graph = construct_graph(stock_info);
    return 0;
}

StockInfo read_stock_info() {
    int n, k;
    std::cin >> n >> k;
    StockInfo stock_info(n, std::vector<int>(k));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < k; j++) {
            std::cin >> stock_info[i][j];
        }
    }
    return stock_info;
}

BipartateGraph construct_graph(const StockInfo& stock_info) {
    
}

