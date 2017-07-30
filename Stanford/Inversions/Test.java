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
		numbers = null;
		long startTime = System.nanoTime();
		//System.out.println(Inversions.naiveCount(array));
		System.out.println(Inversions.count(array));
		System.out.println("\nTiming: " + (System.nanoTime() - startTime) / 1000000000. + " seconds");
	}
}