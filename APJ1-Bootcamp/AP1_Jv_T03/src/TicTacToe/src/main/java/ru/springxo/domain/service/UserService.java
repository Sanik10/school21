package ru.springxo.domain.service;

import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Service;
import ru.springxo.datasource.model.UserEntity;
import ru.springxo.datasource.repository.UserRepository;

import java.util.UUID;

@Service
public class UserService {

    private final UserRepository userRepository;
    private final PasswordEncoder passwordEncoder;

    public UserService(UserRepository userRepository,
                       PasswordEncoder passwordEncoder) {
        this.userRepository = userRepository;
        this.passwordEncoder = passwordEncoder;
    }

    public UUID register(String login, String rawPassword) {
        userRepository.findByLogin(login).ifPresent(u -> {
            throw new IllegalArgumentException("Login already used");
        });

        UserEntity user = new UserEntity();
        user.setLogin(login);
        user.setPasswordHash(passwordEncoder.encode(rawPassword));

        UserEntity saved = userRepository.save(user);
        return saved.getId();
    }

    public UUID authenticate(String login, String rawPassword) {
        UserEntity user = userRepository.findByLogin(login)
                .orElseThrow(() -> new IllegalArgumentException("Invalid login or password"));

        if (!passwordEncoder.matches(rawPassword, user.getPasswordHash())) {
            throw new IllegalArgumentException("Invalid login or password");
        }

        return user.getId();
    }
}
