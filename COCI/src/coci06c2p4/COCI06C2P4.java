package coci06c2p4;

import java.util.Scanner;

public class COCI06C2P4 {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		int[] ans = new int[101];
		for (int i = 3; i <= n; i++) {
			int sSum = 0;
			for (int j = 1; j <= i-2; j++) {
				sSum += j * ((i-1)-j);
			}
			ans[i] = sSum;
		}
		int sum = 0;
		for (int i = 3; i <= n-1; i++) {
			sum += ans[i];
		}
		System.out.println(sum);
	}
}
