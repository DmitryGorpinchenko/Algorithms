class UF {

	private int N;
	private int[] parent;
	private int[] rank;
	private int cc_num;

	public UF(int N) {
		this.N = N;
		cc_num = N;
		parent = new int[N];
		rank = new int[N];
		for(int i = 0; i < N; i++) {
			parent[i] = i;
			rank[i] = 0;
		}
	}
	
	public int[] get_parent() {
		return parent;
	}
	
	public int cc_num() {
		return cc_num;
	}
	
	public boolean is_connected(int a, int b) {
		return find(a) == find(b);
	}
	
	public int find(int a) {
		if(parent[a] != a) {
			parent[a] = find(parent[a]);
		}
		return parent[a];
	}
	
	public void union(int a, int b) {
		int i_id = find(a);
		int j_id = find(b);
		if(i_id == j_id) {
			return;
		}
		--cc_num;
		if(rank[i_id] > rank[j_id]) {
			parent[j_id] = i_id;
		} else {
			parent[i_id] = j_id;
			if(rank[i_id] == rank[j_id]) {
				++rank[j_id];
			}
		}
	}
}
