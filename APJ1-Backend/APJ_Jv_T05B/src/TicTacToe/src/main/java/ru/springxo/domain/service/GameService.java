package ru.springxo.domain.service;

import org.springframework.stereotype.Service;
import ru.springxo.datasource.repository.GameJpaRepository;
import ru.springxo.datasource.repository.GameRepository;
import ru.springxo.datasource.repository.LeaderboardProjection;
import ru.springxo.domain.model.Game;
import ru.springxo.domain.model.LeaderboardItem;

import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

@Service
public class GameService {

    private final GameRepository gameRepository;
    private final GameJpaRepository gameJpaRepository;

    public GameService(GameRepository gameRepository,
                       GameJpaRepository gameJpaRepository) {
        this.gameRepository = gameRepository;
        this.gameJpaRepository = gameJpaRepository;
    }

    public List<Game> getFinishedGamesForUser(UUID userId) {
        return gameRepository.findFinishedGamesByUser(userId);
    }

    public List<LeaderboardItem> getTopPlayers(int limit) {
        List<LeaderboardItem> result = new ArrayList<>();
        for (LeaderboardProjection projection : gameJpaRepository.findTopPlayers(limit)) {
            double ratio = projection.getWinRatio() != null ? projection.getWinRatio() : 0.0;
            result.add(new LeaderboardItem(
                    projection.getUserId(),
                    projection.getLogin(),
                    ratio
            ));
        }
        return result;
    }
}
