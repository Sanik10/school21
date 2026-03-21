package ru.springxo.domain.model;

import java.util.UUID;

public class LeaderboardItem {

    private final UUID userId;
    private final String login;
    private final double winRatio;

    public LeaderboardItem(UUID userId, String login, double winRatio) {
        this.userId = userId;
        this.login = login;
        this.winRatio = winRatio;
    }

    public UUID getUserId() {
        return userId;
    }

    public String getLogin() {
        return login;
    }

    public double getWinRatio() {
        return winRatio;
    }
}
