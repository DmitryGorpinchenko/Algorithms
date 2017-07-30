class Unimodal {
	//array a is assumed to be unimodal from 'lo' to 'hi'
	public static int findMax(int[] a, int lo, int hi) {
		if(hi - lo == 1 || a[lo] > a[lo + 1]) {
			return a[lo];
		}
		if(a[hi - 1] > a[hi - 2]) {
			return a[hi - 1];
		}
		lo++; hi--;
		int mid;
		while(true) {
			mid = lo + (hi - lo) / 2;
			if(a[mid] > a[mid - 1] && a[mid] > a[mid + 1]) {
				break;
			} else if(a[mid] > a[mid - 1] && a[mid] < a[mid + 1]) {
				lo = mid + 1;
			} else {
				hi = mid; //'hi' is not included
			}
		}
		return a[mid];
	}
}