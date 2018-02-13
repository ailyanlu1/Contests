import java.util.Scanner;

public class CCC16J2 {
    public static void main(String[] args) {
        Scanner keyboard = new Scanner(System.in);
        int[][] arr = new int[4][4];
        int[] colSum = new int[4];
        int[] rowSum = new int[4];
        boolean magic = true;
        
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                arr[i][j] = keyboard.nextInt();
                rowSum[i] += arr[i][j];
                colSum[j] += arr[i][j];
            } // for j        
        } // for i

        int check = rowSum[0];
        
        for (int n = 0; n < 4; n++) {
            if (rowSum[n] != check || colSum[n] != check) {
                magic = false;
                break;
            } // if else
        } // for n
        
        if (magic) {
            System.out.println("magic");
        } else {
            System.out.println("not magic");
        } // if else
    } // main method

}
