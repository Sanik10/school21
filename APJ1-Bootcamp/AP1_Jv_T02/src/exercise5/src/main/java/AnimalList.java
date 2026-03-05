import java.util.List;
import java.util.Optional;
import java.util.Scanner;
import java.util.stream.IntStream;

public class AnimalList {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int petsCount = readIntWithRetry(scanner);
        scanner.nextLine();

        List<Animal> pets = IntStream.range(0, petsCount)
                .mapToObj(i -> readPet(scanner))
                .flatMap(Optional::stream)
                .toList();

        AnimalIterator iterator = new AnimalIterator(pets);
        while (iterator.hasNext()) {
            System.out.println(iterator.next());
        }

        scanner.close();
    }

    private static int readIntWithRetry(Scanner scanner) {
        if (scanner.hasNextInt()) {
            return scanner.nextInt();
        } else {
            System.out.println("Could not parse a number. Please, try again");
            scanner.nextLine();
            return readIntWithRetry(scanner);
        }
    }

    private static Optional<Animal> readPet(Scanner scanner) {
        String type = scanner.nextLine().toLowerCase();
        if (!type.equals("dog") && !type.equals("cat")) {
            System.out.println("Incorrect input. Unsupported pet type");
            return Optional.empty();
        }

        String name = scanner.nextLine();
        int age = readIntWithRetry(scanner);
        scanner.nextLine();

        if (age <= 0) {
            System.out.println("Incorrect input. Age <= 0");
            return Optional.empty();
        }

        return type.equals("dog")
                ? Optional.of(new Dog(name, age))
                : Optional.of(new Cat(name, age));
    }
}
