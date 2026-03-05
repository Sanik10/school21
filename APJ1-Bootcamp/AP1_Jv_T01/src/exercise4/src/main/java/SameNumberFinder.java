import java.util.Scanner;

public class SameNumberFinder {
    public static void main(String[] args) {
        int pointer = 0;

        Scanner input = new Scanner(System.in);

        while (true) {
            try {
                pointer = Integer.parseInt(input.nextLine());
                break;
            } catch (NumberFormatException e) {
                System.out.println("Could not parse a number. Please, try again");
            }
        }

        if (pointer <= 0) {
            System.out.println("Input error. Size <= 0");
            input.close();
            return;
        }

        int[] array = new int[pointer];
        int j = 0;

        while (j < pointer) {
            try {
                array[j] = Integer.parseInt(input.next());
                j++;
            } catch (NumberFormatException e) {
                System.out.println("Could not parse a number. Please, try again");
            }
        }

        int[] sameArray = new int[pointer];
        int sameNumbers = 0;

        for (int i = 0; i < pointer; i++) {
            if(sameDigit(array[i])) {
                sameArray[sameNumbers] = array[i];
                sameNumbers++;
            }
        }

        if (sameNumbers > 0) {
            for (int i = 0; i < sameNumbers; i++) {
                System.out.print(sameArray[i]);
                if (i < sameNumbers - 1) {
                    System.out.print(" ");
                }
            }
            System.out.println();
        } else {
            System.out.println("There are no such elements");
        }

        input.close();
    }

    public static boolean sameDigit (int num) {
        num = Math.abs(num);
        int lastDigit = num % 10;
        int firstDigit = num;

        while (firstDigit >= 10) {
            firstDigit /= 10;
        }

        return lastDigit == firstDigit;
    }
}
