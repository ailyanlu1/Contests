package ecoo16r2p1_palindrome_panic;

import java.io.BufferedInputStream;
import java.util.Scanner;

public class ECOO16R2P1 {
    private static final int NUM_OF_TEST_CASES = 10; // TODO CHANGE THIS TO THE NUMBER OF TEST CASES FOR THE QUESTION
    public static void main(String[] args) {
        Scanner fileScanner = new Scanner(new BufferedInputStream(System.in));
        for (int i = 0; i < NUM_OF_TEST_CASES; i++) {
            run(fileScanner);
        } // for i
    } // main method
    
    public static void run(Scanner f) { // if you change the method of reading input, then the parameter type may have to be changed
        String str = f.nextLine();
        int min = str.length()-1;
        for (int i = 0; i < str.length(); i++) {
            if (isPalindrome(0, str.length()-1-i, str) || isPalindrome(i, str.length()-1, str)) {
                min = i;
                break;
            }
        }
        System.out.println(min);
    } // run method
    
    private static boolean isPalindrome(int front, int back, String str) {
        while(front < back) {
            if (str.charAt(front) != str.charAt(back)) {
                return false;
            } else {
                front++;
                back--;
            }
        }
        return true;
    } // isPalindrome method
} // QuestionOne class
