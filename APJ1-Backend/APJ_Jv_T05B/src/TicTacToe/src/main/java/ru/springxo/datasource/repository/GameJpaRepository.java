package ru.springxo.datasource.repository;

import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.CrudRepository;
import org.springframework.stereotype.Repository;
import ru.springxo.datasource.model.GameEntity;
import ru.springxo.domain.model.GameStatus;

import java.util.List;
import java.util.UUID;

@Repository
public interface GameJpaRepository extends CrudRepository<GameEntity, UUID> {

    Iterable<GameEntity> findByStatus(GameStatus status);

    @Query("""
            select g from GameEntity g
            where (g.winnerUserId = :userId and (g.playerXId = :userId or g.playerOId = :userId))
               or (g.status = :drawStatus and (g.playerXId = :userId or g.playerOId = :userId))
            order by g.createdAt desc
            """)
    List<GameEntity> findFinishedGamesByUserId(UUID userId, GameStatus drawStatus);

    @Query(
            value = """
                    WITH user_results AS (
                        SELECT
                            g.player_x_id AS user_id,
                            CASE
                                WHEN g.status = 'DRAW' THEN 'DRAW'
                                WHEN g.status = 'FINISHED' AND g.winner_user_id = g.player_x_id THEN 'WIN'
                                WHEN g.status = 'FINISHED' AND g.winner_user_id IS NOT NULL AND g.winner_user_id <> g.player_x_id THEN 'LOSS'
                                WHEN g.status = 'FINISHED' AND g.winner_user_id IS NULL AND g.opponent_type = 'COMPUTER' THEN 'WIN'
                                ELSE NULL
                            END AS result
                        FROM games g

                        UNION ALL

                        SELECT
                            g.player_o_id AS user_id,
                            CASE
                                WHEN g.status = 'DRAW' THEN 'DRAW'
                                WHEN g.status = 'FINISHED' AND g.winner_user_id = g.player_o_id THEN 'WIN'
                                WHEN g.status = 'FINISHED' AND g.winner_user_id IS NOT NULL AND g.winner_user_id <> g.player_o_id THEN 'LOSS'
                                WHEN g.status = 'FINISHED' AND g.winner_user_id IS NULL AND g.opponent_type = 'COMPUTER' THEN 'LOSS'
                                ELSE NULL
                            END AS result
                        FROM games g
                    ),
                    aggregated AS (
                        SELECT
                            user_id,
                            SUM(CASE WHEN result = 'WIN' THEN 1 ELSE 0 END) AS wins,
                            SUM(CASE WHEN result = 'LOSS' THEN 1 ELSE 0 END) AS losses,
                            SUM(CASE WHEN result = 'DRAW' THEN 1 ELSE 0 END) AS draws
                        FROM user_results
                        WHERE user_id IS NOT NULL AND result IS NOT NULL
                        GROUP BY user_id
                    )
                    SELECT
                        u.id AS userId,
                        u.login AS login,
                        CASE
                            WHEN (aggregated.losses + aggregated.draws) = 0
                                THEN aggregated.wins::double precision
                            ELSE aggregated.wins::double precision / (aggregated.losses + aggregated.draws)
                        END AS winRatio
                    FROM aggregated
                    JOIN users u ON u.id = aggregated.user_id
                    ORDER BY winRatio DESC
                    LIMIT ?1
                    """,
            nativeQuery = true
    )
    List<LeaderboardProjection> findTopPlayers(int limit);
}
