package ru.springxo.web.model;

import java.util.UUID;

@SuppressWarnings("unused")
public class LeaderboardEntryDto {

    private UUID userId;
    private String login;
    private double winRatio;

    public LeaderboardEntryDto() {
    }

    public LeaderboardEntryDto(UUID userId, String login, double winRatio) {
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

    public void setUserId(UUID userId) {
        this.userId = userId;
    }

    public void setLogin(String login) {
        this.login = login;
    }

    public void setWinRatio(double winRatio) {
        this.winRatio = winRatio;
    }
}
