package ru.springxo.web.controller;

import org.springframework.http.HttpStatus;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.server.ResponseStatusException;
import ru.springxo.datasource.repository.GameRepository;
import ru.springxo.domain.model.Board;
import ru.springxo.domain.model.Game;
import ru.springxo.domain.model.GameStatus;
import ru.springxo.domain.model.OpponentType;
import ru.springxo.domain.service.TicTacToeService;
import ru.springxo.web.mapper.GameWebMapper;
import ru.springxo.web.model.GameDto;
import ru.springxo.web.model.MoveRequest;

import java.util.List;
import java.util.UUID;
import java.util.stream.Collectors;

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

    private UUID getCurrentUserId() {
        Authentication auth = SecurityContextHolder.getContext().getAuthentication();
        if (auth == null || auth.getPrincipal() == null) {
            throw new ResponseStatusException(HttpStatus.UNAUTHORIZED, "No authenticated user");
        }
        return (UUID) auth.getPrincipal();
    }

    @PostMapping
    public GameDto createGame(@RequestParam OpponentType opponentType) {
        UUID currentUserId = getCurrentUserId();
        int[][] empty = new int[3][3];
        Board board = new Board(empty);

        UUID playerXId = null;
        UUID playerOId = null;
        GameStatus status;
        UUID currentTurnUserId;
        UUID winnerUserId = null;

        if (opponentType == OpponentType.HUMAN) {
            playerXId = currentUserId;
            status = GameStatus.WAITING_FOR_PLAYER;
            currentTurnUserId = currentUserId;
        } else if (opponentType == OpponentType.COMPUTER) {
            playerOId = currentUserId;
            status = GameStatus.IN_PROGRESS;
            currentTurnUserId = currentUserId;
        } else {
            throw new ResponseStatusException(HttpStatus.BAD_REQUEST, "Unsupported opponentType");
        }

        Game game = new Game(
                UUID.randomUUID(),
                board,
                playerXId,
                playerOId,
                opponentType,
                status,
                currentTurnUserId,
                winnerUserId
        );

        Game saved = gameRepository.save(game);
        return mapper.toDto(saved);
    }

    @GetMapping("/available")
    public List<GameDto> getAvailableGames() {
        List<Game> waiting = gameRepository.findByStatus(GameStatus.WAITING_FOR_PLAYER);

        return waiting.stream()
                .filter(g -> g.getOpponentType() == OpponentType.HUMAN)
                .map(mapper::toDto)
                .collect(Collectors.toList());
    }

    @PostMapping("/{id}/join")
    public GameDto joinGame(@PathVariable UUID id) {
        UUID currentUserId = getCurrentUserId();

        Game game = gameRepository.findById(id)
                .orElseThrow(() -> new ResponseStatusException(HttpStatus.NOT_FOUND, "Game not found"));

        if (game.getOpponentType() != OpponentType.HUMAN) {
            throw new ResponseStatusException(HttpStatus.BAD_REQUEST, "Cannot join a game vs computer");
        }

        if (game.getStatus() != GameStatus.WAITING_FOR_PLAYER) {
            throw new ResponseStatusException(HttpStatus.BAD_REQUEST, "Game is not waiting for a second player");
        }

        if (currentUserId.equals(game.getPlayerXId())) {
            throw new ResponseStatusException(HttpStatus.BAD_REQUEST, "You are already in this game");
        }

        Game updated = new Game(
                game.getId(),
                game.getBoard(),
                game.getPlayerXId(),    // X — создатель
                currentUserId,          // 0 — присоединившийся
                game.getOpponentType(),
                GameStatus.IN_PROGRESS,
                game.getPlayerXId(),    // первый ход — X
                null                    // победителя пока нет
        );

        Game saved = gameRepository.save(updated);
        return mapper.toDto(saved);
    }

    @GetMapping("/{id}")
    public GameDto getGame(@PathVariable UUID id) {
        Game game = gameRepository.findById(id)
                .orElseThrow(() -> new ResponseStatusException(HttpStatus.NOT_FOUND, "Game not found"));
        return mapper.toDto(game);
    }

    @PostMapping("/{id}/move")
    public GameDto makeMove(@PathVariable("id") UUID id,
                            @RequestBody MoveRequest move) {

        UUID currentUserId = getCurrentUserId();

        Game game = gameRepository.findById(id)
                .orElseThrow(() -> new ResponseStatusException(HttpStatus.NOT_FOUND, "Game not found"));

        if (game.getStatus() == GameStatus.WAITING_FOR_PLAYER) {
            throw new ResponseStatusException(HttpStatus.BAD_REQUEST, "Game is waiting for second player");
        }

        if (game.getStatus() == GameStatus.FINISHED || game.getStatus() == GameStatus.DRAW) {
            throw new ResponseStatusException(HttpStatus.BAD_REQUEST, "Game is already over");
        }

        Game updated;
        if (game.getOpponentType() == OpponentType.HUMAN) {
            updated = handleHumanMove(game, currentUserId, move);
        } else {
            updated = handleComputerMove(game, currentUserId, move);
        }

        Game saved = gameRepository.save(updated);
        return mapper.toDto(saved);
    }

    private Game handleHumanMove(Game game, UUID currentUserId, MoveRequest move) {
        UUID playerXId = game.getPlayerXId();
        UUID playerOId = game.getPlayerOId();

        if ((!currentUserId.equals(playerXId)) &&
                (!currentUserId.equals(playerOId))) {
            throw new ResponseStatusException(HttpStatus.FORBIDDEN, "You are not a player in this game");
        }

        if (game.getCurrentTurnUserId() == null ||
                !currentUserId.equals(game.getCurrentTurnUserId())) {
            throw new ResponseStatusException(HttpStatus.BAD_REQUEST, "Not your turn");
        }

        int symbol;
        if (currentUserId.equals(playerXId)) {
            symbol = 1; // X
        } else if (currentUserId.equals(playerOId)) {
            symbol = 2; // O
        } else {
            throw new ResponseStatusException(HttpStatus.FORBIDDEN, "Unknown player");
        }

        int[][] matrix = game.getBoard().getMatrix();
        int[][] newMatrix = copyMatrix(matrix);

        int row = move.getRow();
        int col = move.getCol();

        if (row < 0 || row >= 3 || col < 0 || col >= 3) {
            throw new ResponseStatusException(HttpStatus.BAD_REQUEST, "Move out of bounds");
        }
        if (newMatrix[row][col] != 0) {
            throw new ResponseStatusException(HttpStatus.BAD_REQUEST, "Cell is already occupied");
        }

        newMatrix[row][col] = symbol;

        int winnerSymbol = getWinnerSymbol(newMatrix);
        boolean hasMoves = hasMovesLeft(newMatrix);

        GameStatus newStatus;
        UUID winnerUserId = null;
        UUID nextTurnUserId = null;

        if (winnerSymbol != 0) {
            newStatus = GameStatus.FINISHED;
            winnerUserId = (winnerSymbol == 1) ? playerXId : playerOId;
        } else if (!hasMoves) {
            newStatus = GameStatus.DRAW;
        } else {
            newStatus = GameStatus.IN_PROGRESS;
            nextTurnUserId = currentUserId.equals(playerXId) ? playerOId : playerXId;
        }

        return new Game(
                game.getId(),
                new Board(newMatrix),
                playerXId,
                playerOId,
                game.getOpponentType(),
                newStatus,
                nextTurnUserId,
                winnerUserId
        );
    }

    private Game handleComputerMove(Game game, UUID currentUserId, MoveRequest move) {
        UUID humanId = game.getPlayerOId();

        if (humanId == null || !humanId.equals(currentUserId)) {
            throw new ResponseStatusException(HttpStatus.FORBIDDEN, "You are not a player in this game");
        }

        if (game.getCurrentTurnUserId() == null ||
                !currentUserId.equals(game.getCurrentTurnUserId())) {
            throw new ResponseStatusException(HttpStatus.BAD_REQUEST, "Not your turn");
        }

        int[][] matrix = game.getBoard().getMatrix();
        int[][] newMatrix = copyMatrix(matrix);

        int row = move.getRow();
        int col = move.getCol();

        if (row < 0 || row >= 3 || col < 0 || col >= 3) {
            throw new ResponseStatusException(HttpStatus.BAD_REQUEST, "Move out of bounds");
        }
        if (newMatrix[row][col] != 0) {
            throw new ResponseStatusException(HttpStatus.BAD_REQUEST, "Cell is already occupied");
        }

        newMatrix[row][col] = 2;

        int winnerSymbol = getWinnerSymbol(newMatrix);
        boolean hasMoves = hasMovesLeft(newMatrix);

        if (winnerSymbol == 2) {
            return new Game(
                    game.getId(),
                    new Board(newMatrix),
                    game.getPlayerXId(),
                    game.getPlayerOId(),
                    game.getOpponentType(),
                    GameStatus.FINISHED,
                    null,
                    humanId
            );
        }

        if (!hasMoves) {
            return new Game(
                    game.getId(),
                    new Board(newMatrix),
                    game.getPlayerXId(),
                    game.getPlayerOId(),
                    game.getOpponentType(),
                    GameStatus.DRAW,
                    null,
                    null
            );
        }

        Game tmpForAi = new Game(
                game.getId(),
                new Board(newMatrix),
                game.getPlayerXId(),
                game.getPlayerOId(),
                game.getOpponentType(),
                game.getStatus(),
                game.getCurrentTurnUserId(),
                game.getWinnerUserId()
        );

        int[] aiMove = ticTacToeService.getNextMove(tmpForAi);
        int aiRow = aiMove[0];
        int aiCol = aiMove[1];

        if (aiRow < 0 || aiRow >= 3 || aiCol < 0 || aiCol >= 3 || newMatrix[aiRow][aiCol] != 0) {
            throw new ResponseStatusException(
                    HttpStatus.INTERNAL_SERVER_ERROR,
                    "Computed invalid move by AI"
            );
        }

        newMatrix[aiRow][aiCol] = 1;

        winnerSymbol = getWinnerSymbol(newMatrix);
        hasMoves = hasMovesLeft(newMatrix);

        GameStatus newStatus;
        UUID winnerUserId = null;
        UUID nextTurnUserId = null;

        if (winnerSymbol == 1) {
            newStatus = GameStatus.FINISHED;
        } else if (winnerSymbol == 2) {
            newStatus = GameStatus.FINISHED;
            winnerUserId = humanId;
        } else if (!hasMoves) {
            newStatus = GameStatus.DRAW;
        } else {
            newStatus = GameStatus.IN_PROGRESS;
            nextTurnUserId = humanId;
        }

        return new Game(
                game.getId(),
                new Board(newMatrix),
                game.getPlayerXId(),
                game.getPlayerOId(),
                game.getOpponentType(),
                newStatus,
                nextTurnUserId,
                winnerUserId
        );
    }

    private int[][] copyMatrix(int[][] matrix) {
        int[][] copy = new int[matrix.length][];
        for (int i = 0; i < matrix.length; i++) {
            copy[i] = matrix[i].clone();
        }
        return copy;
    }

    private int getWinnerSymbol(int[][] b) {
        for (int row = 0; row < 3; row++) {
            if (b[row][0] != 0 &&
                    b[row][0] == b[row][1] &&
                    b[row][1] == b[row][2]) {
                return b[row][0];
            }
        }

        for (int col = 0; col < 3; col++) {
            if (b[0][col] != 0 &&
                    b[0][col] == b[1][col] &&
                    b[1][col] == b[2][col]) {
                return b[0][col];
            }
        }

        if (b[0][0] != 0 &&
                b[0][0] == b[1][1] &&
                b[1][1] == b[2][2]) {
            return b[0][0];
        }

        if (b[0][2] != 0 &&
                b[0][2] == b[1][1] &&
                b[1][1] == b[2][0]) {
            return b[0][2];
        }

        return 0;
    }

    private boolean hasMovesLeft(int[][] board) {
        for (int[] row : board) {
            for (int cell : row) {
                if (cell == 0) return true;
            }
        }
        return false;
    }
}