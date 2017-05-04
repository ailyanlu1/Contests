package ecoo17r1p3_mountain_view;

import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class ECOO17R1P3 {
	private static final int NUM_OF_TEST_CASES = 10; // TODO CHANGE THIS TO THE NUMBER OF TEST CASES FOR THE QUESTION

	public static void main(String[] args) {
		Scanner fileScanner = new Scanner(new BufferedInputStream(System.in));
		for (int i = 0; i < NUM_OF_TEST_CASES; i++) {
			run(fileScanner);
		} // for i
	} // main method

	public static void run(Scanner f) { // if you change the method of reading input, then the parameter type may have to be changed
		int numMountains = f.nextInt();

		int[] mountains = new int[numMountains];

		for (int i = 0; i < mountains.length; i++) {
			mountains[i] = f.nextInt();
		}
		
		int[] answers = new int[numMountains];
		
		int bigCounter = 0;
		int returnAnswer = 0;
		for (int i = 0; i < numMountains; i++) {
			double maxSlope = Integer.MIN_VALUE;
			int counter = 0;
			for (int row = i+1; row < numMountains; row++) {
				if (maxSlope < ((double)(mountains[row]-mountains[i])/(double)(row-i))){
					maxSlope = ((double)(mountains[row]-mountains[i])/(double)(row-i));
					counter++;
					answers[row]++;
				}
			}
			counter += answers[i];
			if (counter > bigCounter){
				bigCounter = counter;
				returnAnswer = i+1;
			}
		}	
		System.out.println(returnAnswer);
	} // run method
} // QuestionThree class
