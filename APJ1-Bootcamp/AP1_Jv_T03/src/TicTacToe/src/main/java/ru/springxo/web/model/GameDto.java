package ru.springxo.web.model;

import java.util.UUID;

@SuppressWarnings("unused")
public class GameDto {

    private UUID id;
    private BoardDto board;

    private UUID playerXId;
    private UUID playerOId;
    private String opponentType;     // "HUMAN" или "COMPUTER"
    private String status;           // "WAITING_FOR_PLAYER", "IN_PROGRESS", "DRAW", "FINISHED"
    private UUID currentTurnUserId;
    private UUID winnerUserId;

    public GameDto() {
    }

    public GameDto(UUID id, BoardDto board) {
        this.id = id;
        this.board = board;
    }

    public UUID getId() {
        return id;
    }

    public BoardDto getBoard() {
        return board;
    }

    public UUID getPlayerXId() {
        return playerXId;
    }

    public UUID getPlayerOId() {
        return playerOId;
    }

    public String getOpponentType() {
        return opponentType;
    }

    public String getStatus() {
        return status;
    }

    public UUID getCurrentTurnUserId() {
        return currentTurnUserId;
    }

    public UUID getWinnerUserId() {
        return winnerUserId;
    }

    public void setId(UUID id) {
        this.id = id;
    }

    public void setBoard(BoardDto board) {
        this.board = board;
    }

    public void setPlayerXId(UUID playerXId) {
        this.playerXId = playerXId;
    }

    public void setPlayerOId(UUID playerOId) {
        this.playerOId = playerOId;
    }

    public void setOpponentType(String opponentType) {
        this.opponentType = opponentType;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public void setCurrentTurnUserId(UUID currentTurnUserId) {
        this.currentTurnUserId = currentTurnUserId;
    }

    public void setWinnerUserId(UUID winnerUserId) {
        this.winnerUserId = winnerUserId;
    }
}
