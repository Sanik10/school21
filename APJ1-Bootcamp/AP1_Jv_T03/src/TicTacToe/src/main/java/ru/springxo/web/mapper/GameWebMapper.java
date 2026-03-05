package ru.springxo.web.mapper;

import ru.springxo.domain.model.Board;
import ru.springxo.domain.model.Game;
import ru.springxo.web.model.BoardDto;
import ru.springxo.web.model.GameDto;

public class GameWebMapper {

    public GameDto toDto(Game game) {
        if (game == null) {
            return null;
        }
        BoardDto boardDto = new BoardDto(game.getBoard().getMatrix());
        return new GameDto(game.getId(), boardDto);
    }

    public Game toDomain(GameDto dto) {
        if (dto == null) {
            return null;
        }
        Board board = new Board(dto.getBoard().getMatrix());
        return new Game(dto.getId(), board);
    }
}
