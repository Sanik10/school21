import java.util.Scanner;

public class SortSelection {
    public static void main(String[] args) {
        int pointer = 0;
        Scanner input = new Scanner(System.in);

        while (true) {
            try {
                pointer = Integer.parseInt(input.nextLine());
                if (pointer <= 0) {
                    System.out.println("Input error. Size <= 0");
                    input.close();
                    return;
                }
                break;
            } catch (NumberFormatException e) {
                System.out.println("Could not parse a number. Please, try again");
            }
        }

        float[] array = new float[pointer];

        for (int i = 0; i < pointer; ) {
            try {
                array[i] = Float.parseFloat(input.next());
                i++;
            } catch (NumberFormatException e) {
                System.out.println("Could not parse a number. Please, try again");
            }
        }

        input.close();
        selectionSortFloat(array);

        for (int i = 0; i < array.length; i++) {
            System.out.print(array[i] + (i == array.length - 1 ? "" : " "));
        }
        System.out.println();
    }

    public static void selectionSortFloat(float[] arr) {
        int n = arr.length;

        for (int i = 0; i < n - 1; i++) {
            int minIndex = i;
            for (int j = i + 1; j < n; j++) {
                if (arr[j] < arr[minIndex]) {
                    minIndex = j;
                }
            }

            if (minIndex != i) {
                float temp = arr[i];
                arr[i] = arr[minIndex];
                arr[minIndex] = temp;
            }
        }
    }
}
