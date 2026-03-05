import java.util.Scanner;
import java.io.File;
import java.io.PrintWriter;
import java.io.FileNotFoundException;

public class MaxMinFinder {
    public static void main(String[] args) {
        Scanner consoleScanner = new Scanner(System.in);
        String filePath = consoleScanner.nextLine();

        File file = new File(filePath);
        if (!file.exists()) {
            System.out.println("Input error. File doesn't exist");
            consoleScanner.close();
            return;
        }

        Scanner fileScanner;
        try {
            fileScanner = new Scanner(file);
        } catch (FileNotFoundException e) {
            System.out.println("Input error. File doesn't exist");
            consoleScanner.close();
            return;
        }

        int size;
        try {
            size = Integer.parseInt(fileScanner.next());
        } catch (Exception e) {
            System.out.println("Input error. Size <= 0");
            fileScanner.close();
            consoleScanner.close();
            return;
        }

        if (size <= 0) {
            System.out.println("Input error. Size <= 0");
            fileScanner.close();
            consoleScanner.close();
            return;
        }

        double[] numbers = new double[size];

        int count = 0;
        while (count < size && fileScanner.hasNext()) {
            String token = fileScanner.next();
            try {
                double value = Double.parseDouble(token);
                numbers[count] = value;
                count++;
            } catch (NumberFormatException e) {
                // пропускаем некорректный токен
            }
        }

        fileScanner.close();
        consoleScanner.close();

        if (count < size) {
            System.out.println("Input error. Insufficient number of elements");
            return;
        }

        System.out.println(size);
        for (int i = 0; i < size; i++) {
            System.out.print(numbers[i]);
            if (i < size - 1) {
                System.out.print(" ");
            }
        }
        System.out.println();

        double min = numbers[0];
        double max = numbers[0];

        for (int i = 1; i < size; i++) {
            if (min > numbers[i]) {
                min = numbers[i];
            }
            if (max < numbers[i]) {
                max = numbers[i];
            }
        }

        try {
            PrintWriter writer = new PrintWriter("result.txt");
            writer.println(min + " " + max);
            writer.close();
            System.out.println("Saving min and max values in file");
        } catch (FileNotFoundException e) {
            // в задании не сказано, что делать, если нельзя создать result.txt
        }
    }
}