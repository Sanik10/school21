import java.util.concurrent.TimeUnit;

public class Cat extends Animal {
    public Cat(String name, int age) {
        super(name, age);
    }

    @Override
    public String toString() {
        return "Cat name = " + getName() + ", age = " + getAge();
    }

    @Override
    public double goToWalk() {
        double walkTime = getAge() * 0.25;
        long walkMillis = Math.round(walkTime * 1000);

        try {
            TimeUnit.MILLISECONDS.sleep(walkMillis);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }

        return walkTime;
    }
}
