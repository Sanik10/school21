package ru.springxo.datasource.repository;

import java.util.UUID;

public interface LeaderboardProjection {

    UUID getUserId();

    String getLogin();

    Double getWinRatio();
}
