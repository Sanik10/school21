package ru.springxo.datasource.repository;

import org.springframework.stereotype.Repository;
import ru.springxo.datasource.mapper.GameDatasourceMapper;
import ru.springxo.datasource.model.GameEntity;
import ru.springxo.domain.model.Game;
import ru.springxo.domain.model.GameStatus;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.UUID;

@Repository
public class GameRepository {

    private final GameJpaRepository jpaRepository;
    private final GameDatasourceMapper mapper;

    public GameRepository(GameJpaRepository jpaRepository,
                          GameDatasourceMapper mapper) {
        this.jpaRepository = jpaRepository;
        this.mapper = mapper;
    }

    public Game save(Game game) {
        GameEntity entity = mapper.toEntity(game);
        GameEntity saved = jpaRepository.save(entity);
        return mapper.toDomain(saved);
    }

    public Optional<Game> findById(UUID id) {
        return jpaRepository.findById(id)
                .map(mapper::toDomain);
    }

    public List<Game> findByStatus(GameStatus status) {
        List<Game> result = new ArrayList<>();
        for (GameEntity entity : jpaRepository.findByStatus(status)) {
            result.add(mapper.toDomain(entity));
        }
        return result;
    }
}
