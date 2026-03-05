package ru.springxo.datasource.model;

import jakarta.persistence.*;
import ru.springxo.domain.model.GameStatus;
import ru.springxo.domain.model.OpponentType;

import java.util.UUID;

@Entity
@Table(name = "games")
public class GameEntity {

    @Id
    @Column(name = "id", columnDefinition = "uuid", updatable = false, nullable = false)
    private UUID id;

    @Lob
    @Column(name = "board_state", nullable = false)
    private String boardState;

    @Column(name = "player_x_id")
    private UUID playerXId;

    @Column(name = "player_o_id")
    private UUID playerOId;

    @Enumerated(EnumType.STRING)
    @Column(name = "opponent_type", nullable = false)
    private OpponentType opponentType;

    @Enumerated(EnumType.STRING)
    @Column(name = "status", nullable = false)
    private GameStatus status;

    @Column(name = "current_turn_user_id")
    private UUID currentTurnUserId;

    @Column(name = "winner_user_id")
    private UUID winnerUserId;

    public GameEntity() {
    }

    @Deprecated
    public GameEntity(UUID id, String boardState) {
        this.id = id;
        this.boardState = boardState;
        this.opponentType = OpponentType.COMPUTER;
        this.status = GameStatus.IN_PROGRESS;
    }

    public UUID getId() {
        return id;
    }

    public String getBoardState() {
        return boardState;
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

    public void setId(UUID id) {
        this.id = id;
    }

    public void setBoardState(String boardState) {
        this.boardState = boardState;
    }

    public void setPlayerXId(UUID playerXId) {
        this.playerXId = playerXId;
    }

    public void setPlayerOId(UUID playerOId) {
        this.playerOId = playerOId;
    }

    public void setOpponentType(OpponentType opponentType) {
        this.opponentType = opponentType;
    }

    public void setStatus(GameStatus status) {
        this.status = status;
    }

    public void setCurrentTurnUserId(UUID currentTurnUserId) {
        this.currentTurnUserId = currentTurnUserId;
    }

    public void setWinnerUserId(UUID winnerUserId) {
        this.winnerUserId = winnerUserId;
    }
}
