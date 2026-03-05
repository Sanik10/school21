import java.util.List;

public class AnimalIterator implements BaseIterator<Animal> {
    private final List<Animal> animals;
    private int currentIndex = 0;

    public AnimalIterator(List<Animal> animals) {
        this.animals = animals;
    }

    @Override
    public Animal next() {
        return animals.get(currentIndex++);
    }

    @Override
    public boolean hasNext() {
        return currentIndex < animals.size();
    }

    @Override
    public void reset() {
        currentIndex = 0;
    }
}
