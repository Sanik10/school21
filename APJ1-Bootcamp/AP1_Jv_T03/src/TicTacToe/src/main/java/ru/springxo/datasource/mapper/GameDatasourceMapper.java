package ru.springxo.datasource.mapper;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import ru.springxo.datasource.model.GameEntity;
import ru.springxo.domain.model.Board;
import ru.springxo.domain.model.Game;

public class GameDatasourceMapper {

    private final ObjectMapper objectMapper = new ObjectMapper();

    public GameEntity toEntity(Game domain) {
        String boardState = serializeMatrix(domain.getBoard().getMatrix());

        GameEntity entity = new GameEntity();
        entity.setId(domain.getId());
        entity.setBoardState(boardState);
        entity.setPlayerXId(domain.getPlayerXId());
        entity.setPlayerOId(domain.getPlayerOId());
        entity.setOpponentType(domain.getOpponentType());
        entity.setStatus(domain.getStatus());
        entity.setCurrentTurnUserId(domain.getCurrentTurnUserId());
        entity.setWinnerUserId(domain.getWinnerUserId());

        return entity;
    }

    public Game toDomain(GameEntity entity) {
        int[][] matrix = deserializeMatrix(entity.getBoardState());
        Board board = new Board(matrix);

        return new Game(
                entity.getId(),
                board,
                entity.getPlayerXId(),
                entity.getPlayerOId(),
                entity.getOpponentType(),
                entity.getStatus(),
                entity.getCurrentTurnUserId(),
                entity.getWinnerUserId()
        );
    }

    private String serializeMatrix(int[][] matrix) {
        try {
            return objectMapper.writeValueAsString(matrix);
        } catch (JsonProcessingException e) {
            throw new RuntimeException("Failed to serialize board matrix", e);
        }
    }

    private int[][] deserializeMatrix(String boardState) {
        try {
            return objectMapper.readValue(boardState, int[][].class);
        } catch (JsonProcessingException e) {
            throw new RuntimeException("Failed to deserialize board matrix", e);
        }
    }
}
