#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <climits>

// allows quickly retrieve backward edges
class FlowGraph {
    struct Edge;

public:
    explicit FlowGraph(size_t n)
        : graph(n) 
    {}

    void add_edge(int u, int v, int c) {
        // forward edges stored at even and backward at odd indices
        graph[u].push_back(edges.size());
        graph[v].push_back(edges.size() + 1);
        edges.insert(edges.end(), { 
            { u, v, c, 0 },
            { v, u, 0, 0 } 
        });
    }

    int max_flow(int s, int t);
    
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
    
    bool bfs(int s, int t, int ids[]);    

    // forward and backward edges
    std::vector<Edge> edges;

    // adj lists store indices of edges in the edges list
    std::vector<std::vector<size_t> > graph;
};

int FlowGraph::max_flow(int s, int t) {
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

bool FlowGraph::bfs(int s, int t, int ids[]) {
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

FlowGraph read_graph();

int main() {
    std::ios_base::sync_with_stdio(false);
    FlowGraph graph = read_graph();
    std::cout << graph.max_flow(0, graph.size() - 1) << std::endl;
    return 0;
}

FlowGraph read_graph() {
    int vertex_count, edge_count;
    std::cin >> vertex_count >> edge_count;
    FlowGraph graph(vertex_count);
    for(int i = 0; i < edge_count; ++i) {
        int u, v, capacity;
        std::cin >> u >> v >> capacity;
        graph.add_edge(u - 1, v - 1, capacity);
    }
    return graph;
}

