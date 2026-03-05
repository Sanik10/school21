package ru.springxo.datasource.model;

public class BoardEntity {
    private int[][] matrix;

    public BoardEntity(int[][] matrix) {
        this.matrix = matrix;
    }

    public int[][] getMatrix() {
        return matrix;
    }
}
