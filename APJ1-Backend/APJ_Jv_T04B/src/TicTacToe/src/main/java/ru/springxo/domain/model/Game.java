package ru.springxo.domain.model;

import java.util.UUID;

public class Game {

    private final UUID id;
    private final Board board;

    private final UUID playerXId;

    private final UUID playerOId;

    private final OpponentType opponentType;

    private final GameStatus status;

    private final UUID currentTurnUserId;

    private final UUID winnerUserId;

    @Deprecated
    public Game(UUID id, Board board) {
        this(
            id,
            board,
            null,
            null,
            OpponentType.COMPUTER,
            GameStatus.IN_PROGRESS,
            null,
            null
        );
    }

    public Game(UUID id,
                Board board,
                UUID playerXId,
                UUID playerOId,
                OpponentType opponentType,
                GameStatus status,
                UUID currentTurnUserId,
                UUID winnerUserId) {
        this.id = id;
        this.board = board;
        this.playerXId = playerXId;
        this.playerOId = playerOId;
        this.opponentType = opponentType;
        this.status = status;
        this.currentTurnUserId = currentTurnUserId;
        this.winnerUserId = winnerUserId;
    }

    public UUID getId() {
        return id;
    }

    public Board getBoard() {
        return board;
    }

    public UUID getPlayerXId() {
        return playerXId;
    }

    public UUID getPlayerOId() {
        return playerOId;
    }

    public OpponentType getOpponentType() {
        return opponentType;
    }

    public GameStatus getStatus() {
        return status;
    }

    public UUID getCurrentTurnUserId() {
        return currentTurnUserId;
    }

    public UUID getWinnerUserId() {
        return winnerUserId;
    }
}
