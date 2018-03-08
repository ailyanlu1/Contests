import java.io.BufferedInputStream;
import java.util.HashMap;
import java.util.Scanner;

public class ECOO15R1P1 {
    private static final int NUM_OF_TEST_CASES = 10; // TODO CHANGE THIS TO THE NUMBER OF TEST CASES FOR THE QUESTION
    public static void main(String[] args) {
        Scanner fileScanner = new Scanner(new BufferedInputStream(System.in));
        for (int i = 0; i < NUM_OF_TEST_CASES; i++) {
            run(fileScanner);
        } // for i
    } // main method
    
    public static void run(Scanner f) { // if you change the method of reading input, then the parameter type may have to be changed
        HashMap<String, Integer> map = new HashMap<String, Integer>();
        String line;
        int time = 0;
        while (!(line = f.nextLine()).equals("end of box")) {
            if (map.containsKey(line))
                map.put(line, (map.get(line) + 1));
            else
                map.put(line, 1);
        }
        for (String key:map.keySet()) {
            if (key.equals("red")) {
                time += 16 * map.get(key);
            } else {
                time += 13 * Math.ceil((double) map.get(key)/7.0);
            }
        }
        System.out.println(time);
    } // run method
}
