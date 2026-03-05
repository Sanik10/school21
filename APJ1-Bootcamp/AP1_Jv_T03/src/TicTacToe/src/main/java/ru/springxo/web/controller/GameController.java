package ru.springxo.web.controller;

import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.server.ResponseStatusException;
import ru.springxo.datasource.repository.GameRepository;
import ru.springxo.domain.model.Board;
import ru.springxo.domain.model.Game;
import ru.springxo.domain.service.TicTacToeService;
import ru.springxo.web.mapper.GameWebMapper;
import ru.springxo.web.model.GameDto;

import java.util.UUID;

@SuppressWarnings("unused")
@RestController
@RequestMapping("/game")
public class GameController {

    private final TicTacToeService ticTacToeService;
    private final GameRepository gameRepository;
    private final GameWebMapper mapper;

    public GameController(TicTacToeService ticTacToeService,
                          GameRepository gameRepository,
                          GameWebMapper mapper) {
        this.ticTacToeService = ticTacToeService;
        this.gameRepository = gameRepository;
        this.mapper = mapper;
    }

    @PostMapping("/{id}")
    public GameDto makeMove(
            @PathVariable("id") UUID id,
            @RequestBody GameDto gameDto
    ) {
        if (gameDto.getId() == null || !id.equals(gameDto.getId())) {
            throw new ResponseStatusException(
                    HttpStatus.BAD_REQUEST,
                    "Game ID in path and body must be the same"
            );
        }

        Game currentGame = mapper.toDomain(gameDto);

        Game previousGame = gameRepository.findById(id)
                .orElse(new Game(id, new Board(new int[3][3])));

        boolean valid = ticTacToeService.validateBoard(
                currentGame.getBoard(),
                previousGame.getBoard()
        );
        if (!valid) {
            throw new ResponseStatusException(
                    HttpStatus.BAD_REQUEST,
                    "Invalid board: previous moves were changed"
            );
        }

        if (ticTacToeService.isGameOver(currentGame.getBoard())) {
            gameRepository.save(currentGame);
            return mapper.toDto(currentGame);
        }

        int[] move = ticTacToeService.getNextMove(currentGame);
        int row = move[0];
        int col = move[1];

        int[][] matrix = currentGame.getBoard().getMatrix();

        if (row < 0 || row >= matrix.length ||
                col < 0 || col >= matrix[row].length ||
                matrix[row][col] != 0) {
            throw new ResponseStatusException(
                    HttpStatus.INTERNAL_SERVER_ERROR,
                    "Computed invalid move by AI"
            );
        }

        int[][] newMatrix = new int[matrix.length][];
        for (int i = 0; i < matrix.length; i++) {
            newMatrix[i] = matrix[i].clone();
        }
        newMatrix[row][col] = 1;

        Game updatedGame = new Game(
                currentGame.getId(),
                new Board(newMatrix)
        );

        Game saved = gameRepository.save(updatedGame);
        return mapper.toDto(saved);
    }
}
