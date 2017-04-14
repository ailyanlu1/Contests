package ccc17s3;

import java.util.Scanner;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class CCC17S3 { // only 9/15 points
	public static Scanner keyboard = new Scanner(System.in);

	public static void main(String[] args) {
		HashMap<Integer, ArrayList<int[]>> board = new HashMap<Integer, ArrayList<int[]>>();
		int n = keyboard.nextInt();
		int[] b = new int[n];
		int length = 0;
		int count = 0;
		for (int i = 0; i < n; i++) {
			b[i] = keyboard.nextInt();
		}
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				int sum = b[i] + b[j];
				ArrayList<int[]> list = board.get(sum);
				boolean duplicate = false;
				int[] arr = new int[2];
				arr[0] = i;
				arr[1] = j;
				if (list == null) {
					list = new ArrayList<int[]>(1);
				}
				for (int[] a:list) {
					if (a[0] == i || a[1] == j || a[1] == i || a[0] == j) {
						duplicate = true;
					}
				}
				if (!duplicate) {
					list.add(arr);
					board.put(sum, list);
				}
			}
		}
		for (int sum:board.keySet()) {
			int testLength = board.get(sum).size();
			if (testLength > length) {
				length = testLength;
			}
		}
		for (int sum:board.keySet()) {
			if (board.get(sum).size() == length) {
				count++;
			}
		}
		System.out.println(length + " " + count);
		
	} // main method
}
