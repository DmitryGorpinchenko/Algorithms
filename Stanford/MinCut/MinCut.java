import java.io.*;
import java.util.*;

class MinCut {
	
	public static int cut(ArrayList<Arc> edges, int n) {
		//mimic removing edges by swaping victim and 'current last element'
		//by maintaining 'size' variable
		int size = edges.size();
		UF uf = new UF(n);
		Random r = new Random();
		while(uf.cc_num() != 2) {
			int victim = r.nextInt(size);
			Arc e = edges.get(victim);
			edges.set(victim, edges.get(size - 1));
			edges.set(size - 1, e);
			size--;
			uf.union(e.v1, e.v2);
		}
		int cut_size = 0;
		for(Arc e : edges) {
			if(!uf.is_connected(e.v1, e.v2)) {
				cut_size++;
			}
		}
		return cut_size;
	}
	
	public static int min_cut(ArrayList<Arc> edges, int n, int T) {
		int min = Integer.MAX_VALUE;
		for(int i = 0; i < T; i++) {
			int curr = cut(edges, n);
			if(min > curr) {
				min = curr;
			}
		}
		return min;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader(args[0]));
		int n = Integer.parseInt(args[1]);
		int T = Integer.parseInt(args[2]);
		ArrayList<Arc> edges = new ArrayList<Arc>();
		for(int i = 0; i < n; i++) {
			String[] line = in.readLine().split("\\s+");
			for(int k = 1; k < line.length; k++) {
				int v = Integer.parseInt(line[k])-1;
				if(i < v) {
					edges.add(new Arc(i, v));
				}
			}
		}
		in.close();
		System.out.println("\nMin cut size = " + min_cut(edges, n, T));
	}
}
