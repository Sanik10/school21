import java.util.concurrent.TimeUnit;

public class Dog extends Animal {
    public Dog(String name, int age) {
        super(name, age);
    }

    @Override
    public String toString() {
        return "Dog name = " + getName() + ", age = " + getAge();
    }

    @Override
    public double goToWalk() {
        double walkTime = getAge() * 0.5;
        long walkMillis = Math.round(walkTime*1000);

        try {
            TimeUnit.MILLISECONDS.sleep(walkMillis);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }

        return walkTime;
    }
}
