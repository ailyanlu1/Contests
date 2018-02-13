import java.util.Arrays;
import java.util.Scanner;

public class CCC17S2 {
    public static Scanner keyboard = new Scanner(System.in);
    
    public static void main(String[] args) {
        int n = keyboard.nextInt();
        int[] m = new int[n];
        for (int i = 0; i < n; i++) {
            m[i] = keyboard.nextInt();
        }
        Arrays.sort(m);
        int lo = (n - 1) / 2;
        int hi = lo + 1;
        for (int i = 0; i < n; i++) { 
            if (i % 2 == 0) System.out.print(m[lo--] + " ");
            else System.out.print(m[hi++] + " ");
        }
        System.out.println();
    } // main method
}
