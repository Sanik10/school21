package ru.springxo.domain.service;

import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Service;
import ru.springxo.datasource.model.UserEntity;
import ru.springxo.datasource.repository.UserRepository;
import ru.springxo.security.Role;

import java.util.Set;
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
        user.setRoles(Set.of(Role.USER));

        UserEntity saved = userRepository.save(user);
        return saved.getId();
    }

    public UserEntity authenticate(String login, String rawPassword) {
        UserEntity user = userRepository.findByLogin(login)
                .orElseThrow(() -> new IllegalArgumentException("Invalid login or password"));

        if (!passwordEncoder.matches(rawPassword, user.getPasswordHash())) {
            throw new IllegalArgumentException("Invalid login or password");
        }

        return user;
    }

    public UserEntity getById(UUID id) {
        return userRepository.findById(id)
                .orElseThrow(() -> new IllegalArgumentException("User not found"));
    }

    public UserEntity getByLogin(String login) {
        return userRepository.findByLogin(login)
                .orElseThrow(() -> new IllegalArgumentException("User not found"));
    }
}
