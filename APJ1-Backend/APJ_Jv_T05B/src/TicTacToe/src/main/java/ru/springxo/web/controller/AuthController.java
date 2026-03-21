package ru.springxo.web.controller;

import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.server.ResponseStatusException;
import ru.springxo.datasource.model.UserEntity;
import ru.springxo.domain.service.AuthService;
import ru.springxo.domain.service.UserService;
import ru.springxo.security.JwtAuthentication;
import ru.springxo.web.model.JwtRequest;
import ru.springxo.web.model.JwtResponse;
import ru.springxo.web.model.RefreshJwtRequest;
import ru.springxo.web.model.SignUpRequest;

import java.util.List;
import java.util.Map;
import java.util.UUID;

@RestController
@RequestMapping("/auth")
public class AuthController {

    private final AuthService authService;
    private final UserService userService;

    public AuthController(AuthService authService,
                          UserService userService) {
        this.authService = authService;
        this.userService = userService;
    }

    @PostMapping("/signup")
    public ResponseEntity<?> signUp(@RequestBody SignUpRequest request) {
        UUID userId = authService.signUp(request);
        return ResponseEntity.ok(Map.of("userId", userId.toString()));
    }

    @PostMapping("/login")
    public JwtResponse login(@RequestBody JwtRequest request) {
        return authService.login(request);
    }

    @PostMapping("/token/access")
    public JwtResponse refreshAccessToken(@RequestBody RefreshJwtRequest request) {
        return authService.refreshAccessToken(request);
    }

    @PostMapping("/token/refresh")
    public JwtResponse refreshRefreshToken(@RequestBody RefreshJwtRequest request) {
        return authService.refreshRefreshToken(request);
    }

    @GetMapping("/me")
    public Map<String, Object> currentUser() {
        JwtAuthentication auth = authService.getJwtAuthentication();
        if (auth == null) {
            throw new ResponseStatusException(HttpStatus.UNAUTHORIZED, "No authenticated user");
        }

        UUID userId = (UUID) auth.getPrincipal();
        UserEntity user = userService.getById(userId);

        List<String> roles = user.getRoles().stream()
                .map(Enum::name)
                .toList();

        return Map.of(
                "id", user.getId().toString(),
                "login", user.getLogin(),
                "roles", roles
        );
    }
}
