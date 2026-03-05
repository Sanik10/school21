import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.Locale;

public class AnimalList {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        scanner.useLocale(Locale.US);
        int petsCount = readIntWithRetry(scanner);
        scanner.nextLine();

        List<Animal> pets = new ArrayList<>();

        for (int i = 0; i < petsCount; i++) {
            String type = scanner.nextLine().toLowerCase();

            if (!type.equals("dog") && !type.equals("cat")) {
                System.out.println("Incorrect input. Unsupported pet type");
                continue;
            }

            String name = scanner.nextLine();
            int age = readIntWithRetry(scanner);
            scanner.nextLine();

            if (age <= 0) {
                System.out.println("Incorrect input. Age <= 0");
                continue;
            }

            double mass = readDoubleWithRetry(scanner);
            scanner.nextLine();

            if (mass <= 0) {
                System.out.println("Incorrect input. Mass <= 0");
                continue;
            }

            switch (type) {
                case "dog":
                    pets.add(new Dog(name, age, mass));
                    break;
                case "cat":
                    pets.add(new Cat(name, age, mass));
                    break;
            }
        }

        for (Animal pet : pets) {
            System.out.println(pet);
        }

        scanner.close();
    }

    private static int readIntWithRetry(Scanner scanner) {
        while (!scanner.hasNextInt()) {
            System.out.println("Could not parse a number. Please, try again");
            scanner.nextLine();
        }
        return scanner.nextInt();
    }

    private static double readDoubleWithRetry(Scanner scanner) {
        while (!scanner.hasNextDouble()) {
            System.out.println("Could not parse a number. Please, try again");
            scanner.nextLine();
        }
        return scanner.nextDouble();
    }
}
