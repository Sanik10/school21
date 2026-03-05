import java.util.Scanner;

public class AscendingOrder {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        int previousNumber = 0;
        int currentNumber;
        int position = 0;
        boolean anyNumberEntered = false;
        boolean ordered = true;

        if (input.hasNextInt()) {
            previousNumber = input.nextInt();
            anyNumberEntered = true;
            position = 1;

            while (input.hasNextInt()) {
                currentNumber = input.nextInt();
                position++;

                if (currentNumber < previousNumber) {
                    ordered = false;
                    break;
                }

                previousNumber = currentNumber;
            }
        }

        input.close();

        if (!anyNumberEntered) {
            System.out.println("Input error");
        } else if (!ordered) {
            System.out.println("The sequence is not ordered from the ordinal number of the number " + (position - 1));
        } else {
            System.out.println("The sequence is ordered in ascending order");
        }
    }
}
