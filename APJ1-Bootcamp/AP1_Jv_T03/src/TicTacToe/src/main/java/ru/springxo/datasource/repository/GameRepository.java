package ru.springxo.datasource.repository;

import ru.springxo.datasource.mapper.GameDatasourceMapper;
import ru.springxo.datasource.model.GameEntity;
import ru.springxo.datasource.model.InMemoryGameStorage;
import ru.springxo.domain.model.Game;

import java.util.Optional;
import java.util.UUID;

public class GameRepository {

    private final InMemoryGameStorage storage;
    private final GameDatasourceMapper mapper;

    public GameRepository(InMemoryGameStorage storage, GameDatasourceMapper mapper) {
        this.storage = storage;
        this.mapper = mapper;
    }

    public Game save(Game game) {
        GameEntity entity = mapper.toEntity(game);
        storage.save(entity);
        return mapper.toDomain(entity);
    }

    public Optional<Game> findById(UUID id) {
        GameEntity entity = storage.findById(id);
        return Optional.ofNullable(entity)
                .map(mapper::toDomain);
    }
}