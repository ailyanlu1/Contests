package ccc17s3;

import java.util.Scanner;

public class CCC17S3 {
	public static Scanner keyboard = new Scanner(System.in);

	public static void main(String[] args) {
		int[] b = new int[2001];
		int[] s = new int[4001];
		int n = keyboard.nextInt();
		int length = 0;
		int count = 0;
		for (int i = 0; i < n; i++) {
			int l = keyboard.nextInt();
			b[l]++;
		}
		for (int i = 1 ; i < b.length; i++) {
	        if (b[i] > 0) {
	            for (int j = i; j < b.length; j++) {
	                if (i == j) s[i + j] += b[i] >> 1;
	                else if (b[j] > 0) s[i + j] += Math.min(b[i], b[j]);
	            }
	        }
	    }
	    for (int i = 1; i < s.length; i++) {
	        if (s[i] > length) {
	            length = s[i];
	            count = 1;
	        } else if (s[i] == length) {
	            count++;
	        }
	    }
		System.out.println(length + " " + count);	
	} // main method
} // CCC17S3
