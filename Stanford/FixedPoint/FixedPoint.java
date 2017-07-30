class FixedPoint {
	public static int find(int[] a) {
		int lo = 0, hi = a.length;
		while(lo < hi) {
			int mid = lo + (hi - lo) / 2;
			if(a[mid] == mid) {
				return mid;
			} else if(a[mid] > mid) {
				hi = mid;
			} else {
				lo = mid + 1;
			}
		}
		return -1;
	}
}