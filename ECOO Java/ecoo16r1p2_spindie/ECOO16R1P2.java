import java.io.BufferedInputStream;
import java.util.HashSet;
import java.util.Scanner;

public class ECOO16R1P2 {
    private static final int NUM_OF_TEST_CASES = 10; // TODO CHANGE THIS TO THE NUMBER OF TEST CASES FOR THE QUESTION
    public static void main(String[] args) {
        Scanner fileScanner = new Scanner(new BufferedInputStream(System.in));
        for (int i = 0; i < NUM_OF_TEST_CASES; i++) {
            run(fileScanner);
        } // for i
    } // main method
    
    public static void run(Scanner f) { // if you change the method of reading input, then the parameter type may have to be changed
        int n = f.nextInt();
        HashSet<Double> s = new HashSet<Double>();
        for (int i = 0; i < n; i++) {
            s.add(f.nextDouble());
        }
        double[] t = new double[5];
        for (int i = 0; i < t.length; i++) {
            t[i] = f.nextDouble();
        }
        boolean[] b = new boolean[5];
        for (int i = 0; i < t.length; i++) {
            for (Double j: s) {
                for (Double k: s) {
                    if (s.contains((t[i]/j/k)) || s.contains((t[i]/j-k)) || s.contains(((t[i]-j)/k)) || s.contains((t[i]-j-k))) {
                        b[i] = true;
                    }
                }
            }
        }
        for (int i = 0; i < b.length; i++) {
            if (b[i]) {
                System.out.print("T");
            } else {
                System.out.print("F");
            }
        }
        System.out.println();
    } // run method
} // QuestionTwo class
