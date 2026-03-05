package ru.springxo.web.controller;

import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import ru.springxo.domain.service.AuthService;
import ru.springxo.web.model.SignUpRequest;

import java.util.Map;
import java.util.UUID;

@RestController
@RequestMapping("/auth")
public class AuthController {

    private final AuthService authService;

    public AuthController(AuthService authService) {
        this.authService = authService;
    }

    @PostMapping("/signup")
    public ResponseEntity<?> signUp(@RequestBody SignUpRequest request) {
        UUID userId = authService.signUp(request);
        return ResponseEntity.ok(Map.of("userId", userId.toString()));
    }

    @PostMapping("/login")
    public ResponseEntity<?> login(@RequestHeader("Authorization") String authorizationHeader) {
        UUID userId = authService.authenticateFromHeader(authorizationHeader);
        return ResponseEntity.ok(Map.of("userId", userId.toString()));
    }
}
