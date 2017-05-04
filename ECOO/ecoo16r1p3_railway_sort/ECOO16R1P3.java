package ecoo16r1p3_railway_sort;

import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class ECOO16R1P3 {
	private static final int NUM_OF_TEST_CASES = 10; // TODO CHANGE THIS TO THE NUMBER OF TEST CASES FOR THE QUESTION
	public static void main(String[] args) {
		Scanner fileScanner = new Scanner(new BufferedInputStream(System.in));
		for (int i = 0; i < NUM_OF_TEST_CASES; i++) {
			run(fileScanner);
		} // for i
	} // main method
	
	public static void run(Scanner f) { // if you change the method of reading input, then the parameter type may have to be changed
		// TODO insert code for question
		int n = f.nextInt();
		ArrayList<Integer> a = new ArrayList<Integer>(n);
		int cost = 0;
		int li = 0;
		for (int i = 0; i < n; i++) {
			a.add(f.nextInt());
			if (a.get(i) > a.get(li)) {
				li = i;
			}
		}
		int x = n;
		for (int i = li; i >= 0; i--) {
			if (a.get(i) == a.get(li)-1) {
				li = i;
				x--;
			}
		}
		for (int i = x-1; i >= 0; i--) {
			for (int j = 0; j < a.size(); j++) {
				if (a.get(j) == i) {
					a.add(0, a.remove(j));
					cost += j; 
				}
			}
		}
		System.out.println(cost);
	} // run method
} // QuestionThree class
