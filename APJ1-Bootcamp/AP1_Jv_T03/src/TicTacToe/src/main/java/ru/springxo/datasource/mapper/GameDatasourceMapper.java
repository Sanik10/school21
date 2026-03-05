package ru.springxo.datasource.mapper;

import ru.springxo.datasource.model.BoardEntity;
import ru.springxo.datasource.model.GameEntity;
import ru.springxo.domain.model.Board;
import ru.springxo.domain.model.Game;

public class GameDatasourceMapper {

    public GameEntity toEntity(Game domain) {
        BoardEntity boardEntity = new BoardEntity(domain.getBoard().getMatrix());
        return new GameEntity(domain.getId(), boardEntity);
    }

    public Game toDomain(GameEntity entity) {
        Board board = new Board(entity.getBoard().getMatrix());
        return new Game(entity.getId(), board);
    }
}
