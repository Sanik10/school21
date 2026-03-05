package ru.springxo.datasource.model;

import java.util.UUID;

@Entity
@Table(name = "games")
public class GameEntity {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(name = "board_state", nullable = false, length = 9)
    private String boardState;

    public GameEntity() {
    }

    public GameEntity(Long id, String boardState) {
        this.id = id;
        this.boardState = boardState;
    }

    public Long getId() {
        return id;
    }

    public String getBoardState() {
        return boardState;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public void setBoardState(String boardState) {
        this.boardState = boardState;
    }
}