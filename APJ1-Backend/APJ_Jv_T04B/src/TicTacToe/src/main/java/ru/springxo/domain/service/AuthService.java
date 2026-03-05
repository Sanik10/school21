package ru.springxo.domain.service;

import org.springframework.stereotype.Service;
import ru.springxo.web.model.SignUpRequest;

import java.nio.charset.StandardCharsets;
import java.util.Base64;
import java.util.UUID;

@Service
public class AuthService {

    private final UserService userService;

    public AuthService(UserService userService) {
        this.userService = userService;
    }

    public UUID signUp(SignUpRequest request) {
        return userService.register(request.getLogin(), request.getPassword());
    }

    public UUID authenticateFromHeader(String authorizationHeader) {
        if (authorizationHeader == null || !authorizationHeader.startsWith("Basic ")) {
            throw new IllegalArgumentException("Invalid Authorization header");
        }

        String base64Credentials = authorizationHeader.substring("Basic ".length());
        byte[] decodedBytes = Base64.getDecoder().decode(base64Credentials);
        String decoded = new String(decodedBytes, StandardCharsets.UTF_8);

        int colonIndex = decoded.indexOf(':');
        if (colonIndex == -1) {
            throw new IllegalArgumentException("Invalid credential format");
        }

        String login = decoded.substring(0, colonIndex);
        String password = decoded.substring(colonIndex + 1);

        return userService.authenticate(login, password);
    }
}
