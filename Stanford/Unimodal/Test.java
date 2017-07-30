class Test {
	public static void simpleTests() {
		System.out.println(Unimodal.findMax(new int[] {1, 2, 3, 4, 5, 6, 34, 33, 32, 1}, 0, 10) == 34 ? "PASSED" : "FAILED");
		System.out.println(Unimodal.findMax(new int[] {1, 2, 3, 4, 5, 6, 4, 3, 1}, 0, 9) == 6 ? "PASSED" : "FAILED");
		System.out.println(Unimodal.findMax(new int[] {10, 8, 7, 6, 4, 3, 1}, 0, 7) == 10 ? "PASSED" : "FAILED");
		System.out.println(Unimodal.findMax(new int[] {1, 10, 8, 7, 6, 4, 3, 1}, 0, 8) == 10 ? "PASSED" : "FAILED");
		System.out.println(Unimodal.findMax(new int[] {1}, 0, 1) == 1 ? "PASSED" : "FAILED");
		System.out.println(Unimodal.findMax(new int[] {1, 2, 3, 4, 5, 100}, 0, 6) == 100 ? "PASSED" : "FAILED");
		System.out.println(Unimodal.findMax(new int[] {1, 2, 3, 4, 5, 100, 99}, 0, 7) == 100 ? "PASSED" : "FAILED");	
	}
	
	public static void largerTest() {
		int[] a = new int[100000001];
		for(int i = 0; i <= 50000000; i++) {
			a[i] = i;
		}
		for(int i = 50000001; i < a.length; i++) {
			a[i] = 50000000 - i;
		}
		//simulate different positions wrt to the begining for the max element of the array
		for(int t = 0; t <= 50000000; t++) {
			long start = System.nanoTime();
			if(Unimodal.findMax(a, t, 50000001 + t) != 50000000) {
				System.out.println("FAILED!!!");
				return;
			}
		}
		System.out.println("PASSED!!!");
	}
	
	public static void main(String[] args) {
		//simpleTests();
		largerTest();
	}
}