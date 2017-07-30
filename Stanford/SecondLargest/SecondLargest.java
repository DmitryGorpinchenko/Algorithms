import java.util.*;

class SecondLargest {
	
	public static int comp;
	
	private static class Pair {
		int first, second;	

		Pair(int f, int s) {
			first = f;
			second = s;
		}
	}
	
	public static int find(int[] a) {
		comp = 0;
		return find(a, 0, a.length).second;
	}
	
	private static Pair find(int[] a, int lo, int hi) {
		if(hi - lo == 2) {
			comp++;
			return (a[lo] > a[lo + 1]) ? new Pair(a[lo], a[lo + 1]) : new Pair(a[lo + 1], a[lo]);
		}
		int mid = lo + (hi - lo) / 2;
		Pair p1 = find(a, lo, mid);
		Pair p2 = find(a, mid, hi);
		comp += 2;
		if(p1.first < p2.first) {
			return new Pair(p2.first, (p2.second > p1.first) ? p2.second : p1.first);
		} else {
			return new Pair(p1.first, (p1.second > p2.first) ? p1.second : p2.first);
		}
	}
	
	public static void test() {
		for(int n = 3; n < 20; n++) {
			int N = 1 << n;
			ArrayList<Integer> list = new ArrayList<>();
			for(int i = 0; i < N; i++) {
				list.add(i);
			}
			Collections.shuffle(list);
			int[] a = new int[N];
			for(int i = 0; i < N; i++) {
				a[i] = list.get(i);
			}
			if(SecondLargest.find(a) != N - 2) {
				System.out.println("FAILED");
				return;
			}
			System.out.println("Comparisons = " + comp + " Etalon = " + (N + n - 2));
		}
		System.out.println("PASSED");
	}
	
	public static void main(String[] args) {
		test();
	}
}