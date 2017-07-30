import java.util.Random;

class Test {
	public static void test() {
		long start = System.nanoTime();
		int N = 100000;
		int[] a = new int[N];
		Random r = new Random();
		for(int t = 0; t < 1000000; t++) {
			int fixed = r.nextInt(a.length);
			for(int i = 0; i < fixed; i++) {
				a[i] = i - 1;
			}
			a[fixed] = fixed;
			for(int i = fixed + 1; i < a.length; i++) {
				a[i] = i + 1;
			}
			if(FixedPoint.find(a) != fixed) {
				System.out.println("FAILED!!!");
				return;
			}
		}
		System.out.println("PASSED!!!");
	}
	
	public static void main(String[] args) {
		test();
	}
}