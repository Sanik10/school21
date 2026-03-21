package ru.springxo.domain.service;

import io.jsonwebtoken.Claims;
import org.springframework.http.HttpStatus;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.stereotype.Service;
import org.springframework.web.server.ResponseStatusException;
import ru.springxo.datasource.model.UserEntity;
import ru.springxo.security.JwtAuthentication;
import ru.springxo.security.JwtProvider;
import ru.springxo.security.JwtUtil;
import ru.springxo.web.model.JwtRequest;
import ru.springxo.web.model.JwtResponse;
import ru.springxo.web.model.RefreshJwtRequest;
import ru.springxo.web.model.SignUpRequest;

import java.util.UUID;

@Service
public class AuthService {

    private final UserService userService;
    private final JwtProvider jwtProvider;
    private final JwtUtil jwtUtil;

    public AuthService(UserService userService,
                       JwtProvider jwtProvider,
                       JwtUtil jwtUtil) {
        this.userService = userService;
        this.jwtProvider = jwtProvider;
        this.jwtUtil = jwtUtil;
    }

    public UUID signUp(SignUpRequest request) {
        return userService.register(request.getLogin(), request.getPassword());
    }

    public JwtResponse login(JwtRequest request) {
        UserEntity user = userService.authenticate(request.getLogin(), request.getPassword());
        String accessToken = jwtProvider.generateAccessToken(user);
        String refreshToken = jwtProvider.generateRefreshToken(user);
        return new JwtResponse("Bearer", accessToken, refreshToken);
    }

    public JwtResponse refreshAccessToken(RefreshJwtRequest request) {
        String refreshToken = request.getRefreshToken();

        if (!jwtProvider.validateRefreshToken(refreshToken)) {
            throw new ResponseStatusException(HttpStatus.UNAUTHORIZED, "Invalid refresh token");
        }

        Claims claims = jwtProvider.getClaims(refreshToken);
        UUID userId = UUID.fromString(claims.get("uid", String.class));
        UserEntity user = userService.getById(userId);

        String newAccessToken = jwtProvider.generateAccessToken(user);
        return new JwtResponse("Bearer", newAccessToken, refreshToken);
    }

    public JwtResponse refreshRefreshToken(RefreshJwtRequest request) {
        String refreshToken = request.getRefreshToken();

        if (!jwtProvider.validateRefreshToken(refreshToken)) {
            throw new ResponseStatusException(HttpStatus.UNAUTHORIZED, "Invalid refresh token");
        }

        Claims claims = jwtProvider.getClaims(refreshToken);
        UUID userId = UUID.fromString(claims.get("uid", String.class));
        UserEntity user = userService.getById(userId);

        String newAccessToken = jwtProvider.generateAccessToken(user);
        String newRefreshToken = jwtProvider.generateRefreshToken(user);

        return new JwtResponse("Bearer", newAccessToken, newRefreshToken);
    }

    public JwtAuthentication getJwtAuthentication() {
        if (SecurityContextHolder.getContext().getAuthentication() instanceof JwtAuthentication jwtAuth) {
            return jwtAuth;
        }
        return null;
    }
}
