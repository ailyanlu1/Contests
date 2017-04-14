package ccc16j3;

import java.util.Scanner;

public class CCC16J3 {  // this is cubic time so it's quite slow
						// still finishes within the time limit though
	public static void main(String[] args) {
		Scanner keyboard = new Scanner(System.in);
		String word = keyboard.nextLine();
		int length = 1;
		for (int i = 0; i < word.length(); i++) {
			for (int j = i + 1; j <= word.length(); j++) {
				int temp = palindrome(word.substring(i, j));
				if (temp > length) {
					length = temp;
				} // if else
			} // for j
		} // for i
		System.out.println(length);
	} // main method
	
	public static int palindrome(String word) {
		for (int i = 0; i < word.length()/2; i++) {
			if (word.charAt(i) != word.charAt(word.length() - i - 1)) {
				return 1;
			} // if else
		} // for i
		return word.length();
	} // palindrome method

}
