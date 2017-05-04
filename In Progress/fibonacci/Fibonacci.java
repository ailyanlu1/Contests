package fibonacci;

import java.util.Scanner;

public class Fibonacci { // 10/100 points
	
	private static long[] solutions;
	
	public static void main(String[] args) {
		Scanner keyboard = new Scanner(System.in);
		int n = keyboard.nextInt();
		solutions = new long[n+1];
		System.out.println(fib(n) % 1000000007);
	} // main method
	
	public static long fib (int n) {
		if (solutions[n] != 0) {
			return solutions[n];
		}
		if (n <= 1) {
			return n;
		} // if else
		solutions[n] =  fib(n-1) + fib(n-2);
		return solutions[n];
	} // fib method
}
