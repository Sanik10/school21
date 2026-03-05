import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.stream.Collectors;

public class AdultUsernames {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        List<User> users = new ArrayList<>();

        int userCount = readIntWithRetry(scanner);

        int validUsers = 0;
        while (validUsers < userCount && scanner.hasNextLine()) {
            String name = scanner.nextLine();

            int age = readIntWithRetry(scanner);

            if (age <= 0) {
                System.out.println("Incorrect input. Age <= 0");
            } else {
                users.add(new User(name, age));
                validUsers++;
            }
        }

        scanner.close();

        List<String> adultUsernames = users.stream()
                .filter(user -> user.getAge() >= 18)
                .map(User::getUsername)
                .collect(Collectors.toList());

        if (!adultUsernames.isEmpty()) {
            System.out.println(String.join(", ", adultUsernames));
        } else {
            System.out.println();
        }
    }

    private static int readIntWithRetry(Scanner scanner) {
        while (!scanner.hasNextInt()) {
            System.out.println("Could not parse a number. Please, try again");
            scanner.nextLine();
        }
        int value = scanner.nextInt();
        scanner.nextLine();
        return value;
    }
}
