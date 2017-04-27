package longest_common_subsequence;

import java.util.Scanner;

public class LCS {

	private static int process(int[] a, int[] b) {
		int[][] dp = new int[a.length + 1][b.length + 1];
		for (int i = 1; i <= a.length; i++)
			for (int j = 1; j <= b.length; j++) {
				if (a[i - 1] == b[j - 1])
					dp[i][j] = 1 + dp[i - 1][j - 1];
				else
					dp[i][j] = Math.max(dp[i - 1][j], dp[i][j - 1]);
			}
		return dp[a.length][b.length];
	}
	
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int[] a = new int[in.nextInt()];
		int[] b = new int[in.nextInt()];
		for (int i = 0; i < a.length; i++) {
			a[i] = in.nextInt();
		}
		for (int j = 0; j < b.length; j++) {
			b[j] = in.nextInt();
		}
		System.out.println(process(a, b));
	}
}
