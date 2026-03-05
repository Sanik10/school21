import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class AnimalList {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int petsCount = readIntWithRetry(scanner);
        scanner.nextLine();

        List<Animal> pets = new ArrayList<>();

        for (int i = 0; i < petsCount; i++) {
            String type = scanner.nextLine().toLowerCase();

            if (!type.equals("dog") && !type.equals("cat") && !type.equals("hamster") && !type.equals("guinea")) {
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

            switch (type) {
                case "dog":
                    pets.add(new Dog(name, age));
                    break;
                case "cat":
                    pets.add(new Cat(name, age));
                    break;
                case "hamster":
                    pets.add(new Hamster(name, age));
                    break;
                case "guinea":
                    pets.add(new GuineaPig(name, age));
                    break;
            }
        }

        for (Animal pet : pets) {
            if(pet instanceof Herbivore) {
                System.out.println(pet);
            }
        }

        for (Animal pet : pets) {
            if(pet instanceof Omnivore) {
                System.out.println(pet);
            }
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
}
