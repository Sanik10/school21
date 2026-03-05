package ru.springxo.datasource.model;

import java.util.UUID;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentMap;

public class InMemoryGameStorage {
    private final ConcurrentMap<UUID, GameEntity> games = new ConcurrentHashMap<>();

    public GameEntity save(GameEntity game) {
        games.put(game.getId(), game);
        return game;
    }

    public GameEntity findById(UUID id) {
        return games.get(id);
    }
}
