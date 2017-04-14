package ccc16j1;

import java.util.Scanner;

public class CCC16J1 {
	public static void main(String[] args) {
		Scanner keyboard = new Scanner(System.in);
		String input = "";
		int wins = 0;
		for (int i = 1; i <= 6; i++) {
			String result = keyboard.nextLine();
			input += result;
			if (result.equals("W")) {
				wins ++;
			} // if else
		} // for i
		
		if (wins >= 5) {
			System.out.println(1);
		} else if (wins == 3 || wins == 4) {
			System.out.println(2);
		} else if (wins == 1 || wins == 2) {
			System.out.println(3);
		} else {
			System.out.println(-1);
		} // if else
	} // main method
}
