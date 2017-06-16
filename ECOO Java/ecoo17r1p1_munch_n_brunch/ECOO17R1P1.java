package ecoo17r1p1_munch_n_brunch;

import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class ECOO17R1P1 {
    private static final int NUM_OF_TEST_CASES = 10; // TODO CHANGE THIS TO THE NUMBER OF TEST CASES FOR THE QUESTION
    public static void main(String[] args) {
        Scanner fileScanner = new Scanner(new BufferedInputStream(System.in));
        for (int i = 0; i < NUM_OF_TEST_CASES; i++) {
            run(fileScanner);
        } // for i
    } // main method
    
    public static void run(Scanner f) { // if you change the method of reading input, then the parameter type may have to be changed
        // TODO insert code for question
        int cost = f.nextInt();
        double[] weights = {f.nextDouble(), f.nextDouble(), f.nextDouble(), f.nextDouble()};
        int[] numStudents = new int[4];
        int students = f.nextInt();
        int highest = 0;
        int total = 0;
        for (int i = 0; i < weights.length; i++) {
            numStudents[i] = (int) (weights[i] * (double) students);
            total += numStudents[i];
            if (weights[i] > weights[highest]) {
                highest = i;
            }
        }
        if (students > total) {
            numStudents[highest] += students - total;
        }
        int raised = numStudents[0] * 12 + numStudents[1] * 10 + numStudents[2] * 7 + numStudents[3] * 5;
        if (cost > ((double) raised / 2)) {
            System.out.println("YES");
        } else {
            System.out.println("NO");
        }
    } // run method
} // QuestionOne class
