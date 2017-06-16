package ccc16j4_arrival_time;

import java.text.DecimalFormat;
import java.util.Scanner;

public class CCC16J4 {
    public static void main(String[] args) {
        Scanner keyboard = new Scanner(System.in);
        DecimalFormat timeFormat = new DecimalFormat("00");
        String depTime = keyboard.nextLine();
        int depTotalMin = totalMinutes(depTime);
        int minRemaining = 120;
        int currentTimeMin = depTotalMin;
        while (minRemaining > 0) {
            if ((currentTimeMin >= totalMinutes("07:00") && currentTimeMin < totalMinutes("10:00")) 
                    || (currentTimeMin >= totalMinutes("15:00") && currentTimeMin < totalMinutes("19:00"))) {
                currentTimeMin += 10;
            } // if else
            currentTimeMin += 10;
            minRemaining -= 10;
        } // while
        
        int finalHour = currentTimeMin/60;
        int finalMin = currentTimeMin - finalHour * 60;
        if (finalHour >= 24) {
            finalHour -= 24;
        } // if else
        System.out.println(timeFormat.format(finalHour) + ":" + timeFormat.format(finalMin));
    } // main method
    
    public static int totalMinutes(String timeStr) {
        int depHour = Integer.parseInt(timeStr.split(":")[0]);
        int depMin = Integer.parseInt(timeStr.split(":")[1]);
        return depHour * 60 + depMin;
    } // method totalMinutes
}
