import java.util.Scanner;

public class Mean {
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

        for (int i = 0; i < pointer; ) {
            try {
                array[i] = Integer.parseInt(input.next());
                i++;
            } catch (NumberFormatException e) {
                System.out.println("Could not parse a number. Please, try again");
            }
        }

        int sumNeg = 0;
        int countNeg = 0;

        for (int i = 0; i < pointer; i++) {
            if (array[i] < 0) {
                countNeg++;
                sumNeg += array[i];
            }
        }

        if (countNeg > 0) {
            System.out.println(sumNeg/countNeg);
        } else {
            System.out.println("There are no negative elements");
        }

        input.close();
    }
}
