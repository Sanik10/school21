package ru.springxo.di;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import ru.springxo.datasource.mapper.GameDatasourceMapper;
import ru.springxo.domain.service.MinimaxServiceImpl;
import ru.springxo.domain.service.TicTacToeService;
import ru.springxo.web.mapper.GameWebMapper;

@SuppressWarnings("unused")
@Configuration
public class AppConfig {

    @Bean
    public GameDatasourceMapper gameDatasourceMapper() {
        return new GameDatasourceMapper();
    }

    @Bean
    public TicTacToeService ticTacToeService() {
        return new MinimaxServiceImpl();
    }

    @Bean
    public GameWebMapper gameWebMapper() {
        return new GameWebMapper();
    }
}