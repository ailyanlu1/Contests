package ccc16j5s2_tandem_bicycle;

import java.util.Arrays;
import java.util.Scanner;

public class CCC16J5S2 {
    public static void main(String[] args) {
        Scanner keyboard = new Scanner(System.in);
        int question = keyboard.nextInt();
        int numCitizens = keyboard.nextInt();
        Integer[] countryD = new Integer[numCitizens];
        Integer[] countryP = new Integer[numCitizens];
        int sum = 0;
        
        for (int i = 0; i < numCitizens; i++) {
            countryD[i] = keyboard.nextInt();
        } // for i
        for (int j = 0; j < numCitizens; j++) {
            countryP[j] = keyboard.nextInt();
        } // for j
        
        Arrays.sort(countryD);
        Arrays.sort(countryP);
        
        if (question == 1) {
            for (int k = 0; k < numCitizens; k++) {
                sum += max(countryD[k], countryP[k]);
            } // for k
        } else {
            for (int k = 0; k < numCitizens; k++) {
                sum += max(countryD[k], countryP[numCitizens - k - 1]);
            } // for k
        } // if else
        System.out.println(sum);        
    } // main method
    
    public static int max(int a, int b) {
        if (a > b) {
            return a;
        }
        return b;
    } // max method

}
