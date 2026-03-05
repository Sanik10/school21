import java.util.Scanner;

public class TrianglePerimeter {
    public static void main(String[] args) {
        double x1 = 0, y1 = 0, x2 = 0, y2 = 0, x3 = 0, y3 = 0;

        Scanner input = new Scanner(System.in);

        while (true) {
            try {
                x1 = Double.parseDouble(input.next());
                y1 = Double.parseDouble(input.next());
                x2 = Double.parseDouble(input.next());
                y2 = Double.parseDouble(input.next());
                x3 = Double.parseDouble(input.next());
                y3 = Double.parseDouble(input.next());
                break;
            } catch (NumberFormatException e) {
                System.out.println("Could not parse a number. Please, try again");
            }
        }

        double side1 = Math.hypot(x2 - x1, y2 - y1);
        double side2 = Math.hypot(x3 - x2, y3 - y2);
        double side3 = Math.hypot(x1 - x3, y1 - y3);

        if (side1 + side2 <= side3 || side1 + side3 <= side2 || side2 + side3 <= side1) {
            System.out.println("It's not a triangle");
        } else {
            double perimeter = side1 + side2 + side3;
            System.out.printf("Perimeter: %.3f%n", perimeter);
        }

        input.close();
    }
}
