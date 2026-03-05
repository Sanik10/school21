package ru.springxo.datasource.repository;

import org.springframework.data.repository.CrudRepository;
import org.springframework.stereotype.Repository;
import ru.springxo.datasource.model.GameEntity;
import ru.springxo.domain.model.GameStatus;

import java.util.UUID;

@Repository
public interface GameJpaRepository extends CrudRepository<GameEntity, UUID> {
    Iterable<GameEntity> findByStatus(GameStatus status);
}
