package ru.springxo.web.model;

@SuppressWarnings("unused")
public class JwtRequest {

    private String login;
    private String password;

    public JwtRequest() {
    }

    public JwtRequest(String login, String password) {
        this.login = login;
        this.password = password;
    }

    public String getLogin() {
        return login;
    }

    public String getPassword() {
        return password;
    }

    public void setLogin(String login) {
        this.login = login;
    }

    public void setPassword(String password) {
        this.password = password;
    }
}
