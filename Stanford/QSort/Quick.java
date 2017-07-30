class Quick {
	public static int comp;
	
	public static void sort(int[] a, Pivot pivot) {
		comp = 0;
		sort(a, 0, a.length - 1, pivot);
	} 
	
	private static void sort(int[] a, int l, int r, Pivot pivot) {
		if(r - l + 1 <= 1) {
			return;
		}
		comp += (r - l);
		int p = partition(a, l, r, pivot);
		sort(a, l, p - 1, pivot);
		sort(a, p + 1, r, pivot);
	} 
	
	private static int partition(int[] a, int l, int r, Pivot pivot) {
		swap(a, pivot.choose(a, l, r), l);
		int p = a[l], i = l + 1;
		for(int j = l + 1; j <= r; j++) {
			if(a[j] < p) {
				swap(a, i, j);
				i++;
			}
		}
		swap(a, l, i - 1);
		return i - 1;
	} 
	
	private static void swap(int[] a, int i, int j) {
		int tmp = a[i];
		a[i] = a[j];
		a[j] = tmp;
	}
}