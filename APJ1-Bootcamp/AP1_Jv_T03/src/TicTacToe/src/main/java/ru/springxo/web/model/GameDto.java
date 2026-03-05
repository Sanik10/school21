package ru.springxo.web.model;

import java.util.UUID;

@SuppressWarnings("unused")
public class GameDto {
    private UUID id;
    private BoardDto board;

    public GameDto() {
    }

    public GameDto(UUID id, BoardDto board) {
        this.id = id;
        this.board = board;
    }

    public UUID getId() {
        return id;
    }

    public void setId(UUID id) {
        this.id = id;
    }

    public BoardDto getBoard() {
        return board;
    }

    public void setBoard(BoardDto board) {
        this.board = board;
    }
}
