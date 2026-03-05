import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class StringFilter {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        List<String> originalList = new ArrayList<>();

        if (!scanner.hasNextInt()) {
            System.out.println("Ошибка ввода количества строк.");
            scanner.close();
            return;
        }

        int count = scanner.nextInt();
        scanner.nextLine();

        for (int i = 0; i < count; i++) {
            String line = scanner.nextLine();
            originalList.add(line);
        }

        String filterSubstring = scanner.nextLine();

        scanner.close();

        List<String> filteredList = filterStrings(originalList, filterSubstring);
        printListCustom(filteredList);
    }

    public static List<String> filterStrings(List<String> originalList, String substring) {
        List<String> resultList = new ArrayList<>();

        for (String item : originalList) {
            if (item.contains(substring)) {
                resultList.add(item);
            }
        }
        return resultList;
    }

    public static void printListCustom(List<String> list) {
        for (int i = 0; i < list.size(); i++) {
            System.out.print(list.get(i));
            if (i < list.size() - 1) {
                System.out.print(", ");
            }
        }
        System.out.println();
    }
}
