package ru.springxo.domain.model;

import java.util.Arrays;

@SuppressWarnings("unused")
public class Board {
    private final int[][] matrix;

    public Board(int[][] matrix) {
        this.matrix = Arrays.stream(matrix)
                .map(int[]::clone)
                .toArray(int[][]::new);
    }

    public int[][] getMatrix() {
        return matrix;
    }

    public int getCellValue(int row, int col) {
        return matrix[row][col];
    }
}
