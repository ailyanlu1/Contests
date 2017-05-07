package ecoo15r1p4_neanderthal_numbers;

import java.io.BufferedInputStream;
import java.util.Scanner;

public class ECOO15R1P4 {
	private static final int NUM_OF_TEST_CASES = 10; // TODO CHANGE THIS TO THE NUMBER OF TEST CASES FOR THE QUESTION
	private static final String[] words = {"ook", "ookook", "oog", "ooga", "ug", "mook", "mookmook", "oogam", "oogum", "ugug"};
	public static void main(String[] args) {
		Scanner fileScanner = new Scanner(new BufferedInputStream(System.in));
		for (int i = 0; i < NUM_OF_TEST_CASES; i++) {
			run(fileScanner);
		} // for i
	} // main method
	
	public static void run(Scanner f) { // if you change the method of reading input, then the parameter type may have to be changed
		String n = f.nextLine().trim();
		int[] solutions = new int[n.length()];
		for (int i = 0; i < solutions.length; i++) {
			String sub = n.substring(0, i+1);
			for (int j = 0; j < words.length; j++) {
				int index = sub.length() - words[j].length();
				if (index >= 0 && sub.substring(index).equals(words[j])) {
					if (index - 1 == -1) {
						solutions[i] += 1;
					} else {
						solutions[i] += solutions[index - 1];
					}
				}
			}
		}
		System.out.println(solutions[n.length()-1]);
	} // run method
} // QuestionFour2015 class
