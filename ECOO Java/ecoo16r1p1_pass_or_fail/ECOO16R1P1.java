package ecoo16r1p1_pass_or_fail;

import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class ECOO16R1P1 {
    private static final int NUM_OF_TEST_CASES = 10; // TODO CHANGE THIS TO THE NUMBER OF TEST CASES FOR THE QUESTION
    public static void main(String[] args) {
        Scanner fileScanner = new Scanner(new BufferedInputStream(System.in));
        for (int i = 0; i < NUM_OF_TEST_CASES; i++) {
            run(fileScanner);
        } // for i
    } // main method
    
    public static void run(Scanner f) { // if you change the method of reading input, then the parameter type may have to be changed
        int[] w = new int[4];
        int n = 0;
        int p = 0;
        for (int i = 0; i < w.length; i++) {
            w[i] = f.nextInt();
        }
        n = f.nextInt();
        for (int i = 0; i < n; i++) {
            double avg = (f.nextInt() * w[0] + f.nextInt() * w[1] + f.nextInt() * w[2] + f.nextInt() * w[3])/100.0;
            if (avg >= 50) {
                p++;
            }
        }
        System.out.println(p);
        
    } // run method
} // test class
