class Inversions {
	
	private static long inv;
	
	public static long naiveCount(int[] a) {
		inv = 0;
		for(int i = 0; i < a.length; i++) {
			for(int j = i + 1; j < a.length; j++) {
				if(a[i] > a[j]) {
					inv++;
				}
			}
		}
		return inv;
	}
	
	public static long count(int[] a) {
		inv = 0;
		int[] aux = new int[a.length];
		count(a, 0, a.length, aux);
		return inv;
	}
	
	private static void count(int[] a, int lo, int hi, int[] aux) {
		if(hi - lo <= 1) {
			return;
		}
		int mid = lo + (hi - lo) / 2;
		count(a, lo, mid, aux);
		count(a, mid, hi, aux);
		merge(a, lo, mid, hi, aux);
	}
	
	private static void merge(int[] a, int lo, int mid, int hi, int[] aux) {
		for(int i = lo; i < hi; i++) {
			aux[i] = a[i];
		}
		int i = lo, j = mid, k = lo;
		while(i < mid && j < hi) {
			if(aux[i] <= aux[j]) {
				a[k++] = aux[i++];
			} else {
				a[k++] = aux[j++];
				inv += (mid - i);
			}
		}
		while(i < mid) {
			a[k++] = aux[i++];
		}
		while(j < hi) {
			a[k++] = aux[j++];
		}
	}
}