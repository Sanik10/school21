package ru.springxo.domain.model;

import java.util.UUID;

public class Game {
    private final UUID id;
    private final Board board;

    public Game(UUID id, Board board) {
        this.id = id;
        this.board = board;
    }

    public UUID getId() {
        return id;
    }

    public Board getBoard() {
        return board;
    }
}
