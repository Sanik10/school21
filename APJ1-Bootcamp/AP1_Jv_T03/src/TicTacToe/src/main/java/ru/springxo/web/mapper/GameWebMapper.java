package ru.springxo.web.mapper;

import ru.springxo.domain.model.Board;
import ru.springxo.domain.model.Game;
import ru.springxo.domain.model.GameStatus;
import ru.springxo.domain.model.OpponentType;
import ru.springxo.web.model.BoardDto;
import ru.springxo.web.model.GameDto;

public class GameWebMapper {

    public GameDto toDto(Game game) {
        if (game == null) {
            return null;
        }

        BoardDto boardDto = new BoardDto(game.getBoard().getMatrix());
        GameDto dto = new GameDto(game.getId(), boardDto);

        dto.setPlayerXId(game.getPlayerXId());
        dto.setPlayerOId(game.getPlayerOId());
        dto.setOpponentType(game.getOpponentType() != null ? game.getOpponentType().name() : null);
        dto.setStatus(game.getStatus() != null ? game.getStatus().name() : null);
        dto.setCurrentTurnUserId(game.getCurrentTurnUserId());
        dto.setWinnerUserId(game.getWinnerUserId());

        return dto;
    }

    public Game toDomain(GameDto dto) {
        if (dto == null) {
            return null;
        }

        Board board = new Board(dto.getBoard().getMatrix());

        OpponentType opponentType = dto.getOpponentType() != null
                ? OpponentType.valueOf(dto.getOpponentType())
                : OpponentType.COMPUTER;

        GameStatus status = dto.getStatus() != null
                ? GameStatus.valueOf(dto.getStatus())
                : GameStatus.IN_PROGRESS;

        return new Game(
                dto.getId(),
                board,
                dto.getPlayerXId(),
                dto.getPlayerOId(),
                opponentType,
                status,
                dto.getCurrentTurnUserId(),
                dto.getWinnerUserId()
        );
    }
}
