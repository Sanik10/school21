package ru.springxo.security;

import io.jsonwebtoken.Claims;
import org.springframework.stereotype.Component;

import java.util.Collection;
import java.util.Collections;
import java.util.UUID;
import java.util.stream.Collectors;

@Component
public class JwtUtil {

    public JwtAuthentication createAuthentication(Claims claims) {
        String uid = claims.get("uid", String.class);
        UUID userId = UUID.fromString(uid);

        Object rolesObj = claims.get("roles");
        Collection<Role> roles = Collections.emptyList();

        if (rolesObj instanceof Collection<?> collection) {
            roles = collection.stream()
                    .map(Object::toString)
                    .map(Role::valueOf)
                    .collect(Collectors.toSet());
        }

        return new JwtAuthentication(userId, roles, true);
    }
}
