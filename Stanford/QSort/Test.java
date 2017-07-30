import java.util.*;
import java.io.*;

class Test {
	public static void main(String[] args) throws IOException {
		String line;
		ArrayList<Integer> numbers = new ArrayList<>();
		BufferedReader br = new BufferedReader(new FileReader(args[0]));
		while((line = br.readLine()) != null) {
			numbers.add(Integer.parseInt(line));
		}
		int[] array = new int[numbers.size()];
		for(int i = 0; i < array.length; i++) {
			array[i] = numbers.get(i);
		}
		Quick.sort(array.clone(), new Pivot() {
			public int choose(int[] arr, int l, int r) {
				return l;
			}
		});
		System.out.println(Quick.comp);
		Quick.sort(array.clone(), new Pivot() {
			public int choose(int[] arr, int l, int r) {
				return r;
			}
		});
		System.out.println(Quick.comp);
		Quick.sort(array.clone(), new Pivot() {
			public int choose(int[] arr, int l, int r) {
				int m = l + (r - l) / 2;
				int median = m;
				int a = arr[l], b = arr[m], c = arr[r];
				if((a > b && a < c) || (a < b && a > c)) {
					median = l;
				} else if((c > a && c < b) || (c < a && c > b)) {
					median = r;
				}
				return median;
			}
		});
		System.out.println(Quick.comp);
	}
}