import java.util.Scanner;

public class Fibonacci {
    public static void main(String[] args) {
        long pointer = 0;

        Scanner input = new Scanner(System.in);

        while (true) {
            try {
                pointer = Long.parseLong(input.next());
                break;
            } catch (NumberFormatException e) {
                System.out.println("Could not parse a number. Please, try again");
            }
        }

        if (pointer > 92 || pointer < 0) {
            System.out.println("Too large n");
        } else {
            long result = fib((int) pointer);
            System.out.println(result);
        }

        input.close();
    }

    static long fib(int n) {
        if (n == 0) {
            return 0;
        }
        if (n == 1) {
            return 1;
        }
        return fib(n - 1) + fib(n - 2);
    }
}
