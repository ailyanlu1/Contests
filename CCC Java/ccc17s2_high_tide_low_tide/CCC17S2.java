package ccc17s2_high_tide_low_tide;

import java.util.Arrays;
import java.util.Scanner;

public class CCC17S2 {
    public static Scanner keyboard = new Scanner(System.in);
    
    public static void main(String[] args) {
        int n = keyboard.nextInt();
        Integer[] m = new Integer[n];
        for (int i = 0; i < n; i++) {
            m[i] = keyboard.nextInt();
        }
        Arrays.sort(m);
        if (n%2 == 1) {
            System.out.print(m[(n-1)/2] + " ");
            for (int i = (n-1)/2 + 1; i < n; i++) {
                System.out.print(m[i] + " " +  m[n-i-1] + " ");
            }
        } else {
            for (int i = (n-1)/2; i >= 0; i--) {
                System.out.print(m[i] + " " +  m[n-i-1] + " ");
            }
        }
    } // main method
}
