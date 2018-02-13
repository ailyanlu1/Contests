import java.util.Scanner;

public class CCC17S1 {
    public static Scanner keyboard = new Scanner(System.in);

    public static void main(String[] args) {
        int n = keyboard.nextInt();
        int[] a = new int[n];
        int[] b = new int[n];
        int aSum = 0;
        int bSum = 0;
        int day = 0;
        for (int i = 0; i < n; i++) {
            a[i] = keyboard.nextInt();
        }
        for (int i = 0; i < n; i++) {
            b[i] = keyboard.nextInt();
        }
        for (int i = 0; i < n; i++) {
            aSum += a[i];
            bSum += b[i];
            if (aSum == bSum) {
                day = i+1;
            }
        }
        System.out.println(day);
    } // main method
}
