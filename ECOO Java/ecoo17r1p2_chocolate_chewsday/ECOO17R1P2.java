package ecoo17r1p2_chocolate_chewsday;

import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class ECOO17R1P2 {
    private static final int NUM_OF_TEST_CASES = 10; // TODO CHANGE THIS TO THE NUMBER OF TEST CASES FOR THE QUESTION
    public static void main(String[] args) {
        Scanner fileScanner = new Scanner(new BufferedInputStream(System.in));
        for (int i = 0; i < NUM_OF_TEST_CASES; i++) {
            run(fileScanner);
        } // for i
    } // main method
    
    public static void run(Scanner f) { // if you change the method of reading input, then the parameter type may have to be changed
        int n = f.nextInt();
        f.nextLine();
        String line = f.nextLine();
        String[] names = new String[n];
        int[][] score = new int[n][4];
        int mi = 0;
        for (int i = 0; i < n; i++) {
            if (line.equals("*")) break;
            names[i] = line;
            line = f.nextLine();
            while (line.contains(" ")) {
                score[i][0] += Integer.parseInt(line.split(" ")[1]);
                score[i][1] += Integer.parseInt(line.split(" ")[2]);
                score[i][2] += Integer.parseInt(line.split(" ")[3]);
                score[i][3] = score[i][0] + score[i][1] + score[i][2];
                line = f.nextLine();
            }
            if (score[i][3] > score[mi][3]) mi = i;
        }
        ArrayList<Integer> wi = new ArrayList<Integer>();
        for (int i = 0; i < n; i++) {
            if (score[i][3] == score[mi][3]) wi.add(i);
        }
        if (wi.size() > 1) {
            int gi = wi.get(0);
            for (int i = 0; i < wi.size(); i++) {
                if (score[wi.get(i)][2] > score[gi][2]) {
                    gi = wi.get(i);
                }
            }
            ArrayList<Integer> newA = new ArrayList<Integer>();
            for (int i = 0; i < wi.size(); i++) {
                if (score[wi.get(i)][2] == score[gi][2]) {
                    newA.add(wi.get(i));
                }
            }
            wi = newA;
        }
        if (wi.size() > 1) {
            int gi = wi.get(0);
            for (int i = 0; i < wi.size(); i++) {
                if (score[wi.get(i)][1] > score[gi][1]) {
                    gi = wi.get(i);
                }
            }
            ArrayList<Integer> newA = new ArrayList<Integer>();
            for (int i = 0; i < wi.size(); i++) {
                if (score[wi.get(i)][1] == score[gi][1]) {
                    newA.add(wi.get(i));
                }
            }
            wi = newA;
        }
        if (wi.size() > 1) {
            int gi = wi.get(0);
            for (int i = 0; i < wi.size(); i++) {
                if (score[wi.get(i)][0] > score[gi][0]) {
                    gi = wi.get(i);
                }
            }
            ArrayList<Integer> newA = new ArrayList<Integer>();
            for (int i = 0; i < wi.size(); i++) {
                if (score[wi.get(i)][0] == score[gi][0]) {
                    newA.add(wi.get(i));
                }
            }
            wi = newA;
        }
        if (wi.size() > 1) {
            for (int i = 0; i < wi.size()-1; i++) {
                System.out.print(names[wi.get(i)] + ", ");
            }
            System.out.print(names[wi.get(wi.size() - 1)]);
        } else {
            System.out.print(names[wi.get(0)]);
        }
        System.out.println();
    } // run method
} // QuestionTwo class
