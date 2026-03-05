package ru.springxo.domain.service;

import ru.springxo.datasource.repository.GameRepository;
import ru.springxo.domain.model.Board;
import ru.springxo.domain.model.Game;

public class MinimaxServiceImpl implements TicTacToeService {

    private final GameRepository gameRepository;

    public MinimaxServiceImpl(GameRepository gameRepository) {
        this.gameRepository = gameRepository;
    }

    @Override
    public int[] getNextMove(Game game) {
        int[][] matrix = game.getBoard().getMatrix();
        int bestVal = -1000;
        int[] bestMove = {-1, -1};

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (matrix[i][j] == 0) {
                    matrix[i][j] = 1;
                    int moveVal = minimax(matrix, 0, false);
                    matrix[i][j] = 0;

                    if (moveVal > bestVal) {
                        bestMove[0] = i;
                        bestMove[1] = j;
                        bestVal = moveVal;
                    }
                }
            }
        }
        return bestMove;
    }

    private int minimax(int[][] board, int depth, boolean isMax) {
        int score = evaluate(board);

        if (score == 10) return score - depth;
        if (score == -10) return score + depth;
        if (!hasMovesLeft(board)) return 0;

        if (isMax) {
            int best = -1000;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == 0) {
                        board[i][j] = 1;
                        best = Math.max(best, minimax(board, depth + 1, false));
                        board[i][j] = 0;
                    }
                }
            }
            return best;
        } else {
            int best = 1000;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == 0) {
                        board[i][j] = 2;
                        best = Math.min(best, minimax(board, depth + 1, true));
                        board[i][j] = 0;
                    }
                }
            }
            return best;
        }
    }

    private int evaluate(int[][] b) {
        for (int row = 0; row < 3; row++) {
            if (b[row][0] != 0 &&
                    b[row][0] == b[row][1] &&
                    b[row][1] == b[row][2]) {

                if (b[row][0] == 1) {
                    return 10;
                } else {
                    return -10;
                }
            }
        }

        for (int col = 0; col < 3; col++) {
            if (b[0][col] != 0 &&
                    b[0][col] == b[1][col] &&
                    b[1][col] == b[2][col]) {

                if (b[0][col] == 1) {
                    return 10;
                } else {
                    return -10;
                }
            }
        }

        if (b[0][0] != 0 &&
                b[0][0] == b[1][1] &&
                b[1][1] == b[2][2]) {

            if (b[0][0] == 1) {
                return 10;
            } else {
                return -10;
            }
        }

        if (b[0][2] != 0 &&
                b[0][2] == b[1][1] &&
                b[1][1] == b[2][0]) {

            if (b[0][2] == 1) {
                return 10;
            } else {
                return -10;
            }
        }
        return 0;
    }

    private boolean hasMovesLeft(int[][] board) {
        for (int[] row : board) for (int cell : row) if (cell == 0) return true;
        return false;
    }

    @Override
    public boolean validateBoard(Board currentBoard, Board previousBoard) {
        int[][] current = currentBoard.getMatrix();
        int[][] previous = previousBoard.getMatrix();

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (previous[i][j] != 0 && current[i][j] != previous[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    @Override
    public boolean isGameOver(Board board) {
        return evaluate(board.getMatrix()) != 0 || !hasMovesLeft(board.getMatrix());
    }
}
