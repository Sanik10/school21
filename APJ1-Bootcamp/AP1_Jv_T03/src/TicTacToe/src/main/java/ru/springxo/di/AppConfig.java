package ru.springxo.di;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import ru.springxo.datasource.model.InMemoryGameStorage;
import ru.springxo.datasource.repository.GameRepository;
import ru.springxo.domain.service.MinimaxServiceImpl;
import ru.springxo.domain.service.TicTacToeService;
import ru.springxo.web.mapper.GameWebMapper;
import ru.springxo.datasource.mapper.GameDatasourceMapper;

@SuppressWarnings("unused")
@Configuration
public class AppConfig {

    @Bean
    public InMemoryGameStorage inMemoryGameStorage() {
        return new InMemoryGameStorage();
    }

    @Bean
    public GameDatasourceMapper gameDatasourceMapper() {
        return new GameDatasourceMapper();
    }

    @Bean
    public GameRepository gameRepository(InMemoryGameStorage storage,
                                         GameDatasourceMapper mapper) {
        return new GameRepository(storage, mapper);
    }

    @Bean
    public TicTacToeService ticTacToeService(GameRepository gameRepository) {
        return new MinimaxServiceImpl(gameRepository);
    }

    @Bean
    public GameWebMapper gameWebMapper() {
        return new GameWebMapper();
    }
}
