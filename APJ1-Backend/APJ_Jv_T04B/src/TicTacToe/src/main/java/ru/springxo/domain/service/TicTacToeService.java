package ru.springxo.domain.service;

import ru.springxo.domain.model.Board;
import ru.springxo.domain.model.Game;

public interface TicTacToeService {
    int[] getNextMove(Game game);
    boolean validateBoard(Board currentBoard, Board previousBoard);
    boolean isGameOver(Board board);
}
