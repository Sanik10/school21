import java.util.Scanner;

public class TimeMachine {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int time = readSeconds(input);

        if (time < 0) {
            System.out.println("Incorrect time");
        } else {
            int hours = getHours(time);
            int minutes = getMinutes(time);
            int seconds = getSeconds(time);

            printTime(hours, minutes, seconds);
        }

        input.close();
    }

    public static int readSeconds(Scanner input) {
        int time = 0;

        while (true) {
            try {
                time = Integer.parseInt(input.next());
                break;
            } catch (NumberFormatException e) {
                System.out.println("Could not parse a number. Please, try again");
            }
        }

        return time;
    }

    public static int getHours(int totalSeconds) {
        return totalSeconds / 3600;
    }

    public static int getMinutes(int totalSeconds) {
        return (totalSeconds % 3600) / 60;
    }

    public static int getSeconds(int totalSeconds) {
        return totalSeconds % 60;
    }

    public static void printTime(int hours, int minutes, int seconds) {
        System.out.printf("%02d:%02d:%02d%n", hours, minutes, seconds);
    }
}