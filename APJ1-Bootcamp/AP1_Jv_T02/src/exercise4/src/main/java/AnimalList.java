import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.concurrent.CompletableFuture;

public class AnimalList {
    public static void main(String[] args) {
        long programStart = System.currentTimeMillis();
        Scanner scanner = new Scanner(System.in);
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

            switch (type) {
                case "dog":
                    pets.add(new Dog(name, age));
                    break;
                case "cat":
                    pets.add(new Cat(name, age));
                    break;
            }
        }

        var futures = pets.stream()
            .map(pet -> CompletableFuture.runAsync(() -> {
                long startMs = System.currentTimeMillis() - programStart;
                pet.goToWalk();
                long endMs = System.currentTimeMillis() - programStart;
                System.out.printf("%s, start time %.2f, end time = %.2f%n",
                        pet, startMs / 1000.0, endMs / 1000.0);
            })).toList();

        CompletableFuture<Void> allFinished = CompletableFuture.allOf(
                futures.toArray(new CompletableFuture[0])
        );

        allFinished.join();
    }

    public static int readIntWithRetry(Scanner scanner) {
        while(!scanner.hasNextInt()) {
            System.out.println("Could not parse a number. Please, try again");
            scanner.nextLine();
        }
        return scanner.nextInt();
    }
}
