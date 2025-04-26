/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Game.cpp
*/
/**
 * @file Game.cpp
 * @brief The Game.cpp
 * @author Christophe VANDEVOIR, Guillaume LECOCQ and Nicolas TORO
 */

#include "client/Client.hpp"

namespace Jetpack {
    /**
     * @brief Initializes the FX for the game
     * @throw JetpackError If the FX initialization fails
     */
	void Client::_initFx()
	{
		DEBUG << "Init fx";

		if (!_jetpackSoundStartBuffer.loadFromFile("assets/sounds/jetpack_start.wav"))
			throw JetpackError("Failed to load jetpack sound file.");
		_jetpackSoundStart.setBuffer(_jetpackSoundStartBuffer);
		_jetpackSoundStart.setLoop(false);
		_jetpackSoundStart.setVolume(100.f);

		if (!_jetpackSoundStartBuffer.loadFromFile("assets/sounds/jetpack_start.wav"))
			throw JetpackError("Failed to load jetpack sound file.");
		_jetpackSoundStart.setBuffer(_jetpackSoundStartBuffer);
		_jetpackSoundStart.setLoop(false);
		_jetpackSoundStart.setVolume(100.f);

		if (!_jetpackSoundDownBuffer.loadFromFile("assets/sounds/jetpack.ogg"))
			throw JetpackError("Failed to load jetpack sound file.");
		_jetpackSoundDown.setBuffer(_jetpackSoundDownBuffer);
		_jetpackSoundDown.setLoop(true);
		_jetpackSoundDown.setVolume(60.f);

		if (!_jetpackSoundUpBuffer.loadFromFile("assets/sounds/jetpack_lp.wav"))
			throw JetpackError("Failed to load jetpack sound file.");
		_jetpackSoundUp.setBuffer(_jetpackSoundUpBuffer);
		_jetpackSoundUp.setLoop(true);
		_jetpackSoundUp.setVolume(100.f);

		if (!_coinSoundBuffer.loadFromFile("assets/sounds/coin_pickup_1.wav"))
			throw JetpackError("Failed to load coin sound file.");
		_coinSound.setBuffer(_coinSoundBuffer);
		_coinSound.setLoop(false);
		_coinSound.setVolume(100.f);

		if (!_zappedSoundBuffer.loadFromFile("assets/sounds/dud_zapper_pop.wav"))
			throw JetpackError("Failed to load zapped sound file.");
		_zappedSound.setBuffer(_zappedSoundBuffer);
		_zappedSound.setLoop(false);
		_zappedSound.setVolume(100.f);

		if (!_firedSoundBuffer.loadFromFile("assets/sounds/dud_fire.ogg"))
			throw JetpackError("Failed to load fired sound file.");
		_firedSound.setBuffer(_firedSoundBuffer);
		_firedSound.setLoop(false);
		_firedSound.setVolume(100.f);
	}

    /**
     * @brief Initializes the music for the game
     * @throw JetpackError If the music initialization fails
     */
	void Client::_initMusic()
	{
		DEBUG << "Init music";

        /* Main menu music */
		if (!_menuMusic.openFromFile("assets/sounds/main_menu.ogg"))
			throw JetpackError("Failed to load music file.");
		_menuMusic.setVolume(30.f);
		_menuMusic.setLoop(true);
		_menuMusic.play();
		_menuMusicState = MusicState::PLAYING;

        /* Main music */
		if (!_gameMusic.openFromFile("assets/sounds/theme2.ogg"))
			throw JetpackError("Failed to load music file.");
		_gameMusic.setVolume(30.f);
		_gameMusic.setLoop(true);
        _gameMusicState = MusicState::NONE;
	}

    /**
     * @brief Initializes the elements of the game
     * @throw JetpackError If the elements initialization fails
     */
	void Client::_initElements()
	{
		DEBUG << "Init elements";

        /* Player */
		if (!_player_texture.loadFromFile("assets/images/player_sprite_sheet.png")) {
			throw JetpackError("Failed to load player texture.");
		}
		_player_sprite.setTexture(_player_texture);
		sf::IntRect normalRect(0, 0, _player_texture.getSize().x / 4, _player_texture.getSize().y / 4);
		_player_sprite.setTextureRect(normalRect);
		_player_sprite.setScale(RATIO / (_player_texture.getSize().x / 4), RATIO / (_player_texture.getSize().y / 4));

        /* Coin */
        if (!_coin_texture.loadFromFile("assets/images/coins.png")) {
            throw JetpackError("Failed to load coin texture.");
        }
        _coin_sprite.setTexture(_coin_texture);
        _coin_animation.setTextureSize(_coin_texture.getSize());
        _coin_animation.addAnimation("normal", 6, {_coin_texture.getSize().x / 6, _coin_texture.getSize().y / 1}, {0, 0}, 8.0f, true);
        _coin_animation.setCurrentAnimation("normal");
        _coin_animation.play();
        _coin_sprite.setTextureRect(_coin_animation.getTextureRect());
        _coin_sprite.setScale(RATIO / (_coin_texture.getSize().x / 6), RATIO / (_coin_texture.getSize().y / 1));

        /* Zapper */
        if (!_zapper_texture.loadFromFile("assets/images/zapper_sprite_sheet.png")) {
            throw JetpackError("Failed to load zapper texture.");
        }
        _zapper_sprite.setTexture(_zapper_texture);
        _zapper_animation.setTextureSize(_zapper_texture.getSize());
        _zapper_animation.addAnimation("normal", 4, {_zapper_texture.getSize().x / 4, _zapper_texture.getSize().y / 1}, {0, 0}, 8.0f, true);
        _zapper_animation.setCurrentAnimation("normal");
        _zapper_animation.play();
        _zapper_sprite.setTextureRect(_zapper_animation.getTextureRect());
        _zapper_sprite.setScale(RATIO / (_zapper_texture.getSize().x / 4), RATIO / (_zapper_texture.getSize().y / 1));

		/* Lazer */
		if (!_laser_texture.loadFromFile("assets/images/laser_sprite_sheet.png")) {
			throw JetpackError("Failed to load laser texture.");
		}
		_laser_sprite.setTexture(_laser_texture);
		_laser_animation.setTextureSize(_laser_texture.getSize());
		_laser_animation.addAnimation("normal", 3, {_laser_texture.getSize().x / 3, _laser_texture.getSize().y / 1}, {0, 0}, 8.0f, true);
		_laser_animation.setCurrentAnimation("normal");
		_laser_animation.play();
		_laser_sprite.setTextureRect(_laser_animation.getTextureRect());
		_laser_sprite.setScale(RATIO / (_laser_texture.getSize().x / 3), RATIO / (_laser_texture.getSize().y / 1));

		/* Missile */
		if (!_missile_texture.loadFromFile("assets/images/missile_sprite_sheet.png")) {
			throw JetpackError("Failed to load missile texture.");
		}
		_missile_sprite.setTexture(_missile_texture);
		_missile_animation.setTextureSize(_missile_texture.getSize());
		_missile_animation.addAnimation("normal", 4, {_missile_texture.getSize().x / 4, _missile_texture.getSize().y / 1}, {0, 0}, 8.0f, true);
		_missile_animation.setCurrentAnimation("normal");
		_missile_animation.play();
		_missile_sprite.setTextureRect(_missile_animation.getTextureRect());
		_missile_sprite.setScale(RATIO / (_missile_texture.getSize().x / 4), RATIO / (_missile_texture.getSize().y / 1));
	}

    /**
     * @brief Initializes the SFML window and all game elements
     * @throw JetpackError If the SFML initialization fails
     */
	void Client::_initSfml()
	{
		DEBUG << "Init SFML";
		_window.create(sf::VideoMode({static_cast<uint>(WINDOW_WIDTH), static_cast<uint>(WINDOW_HEIGHT)}),
			"Jetpack Client", sf::Style::Close);
		_window.setFramerateLimit(60);

        /* Text */
		_font.loadFromFile("assets/jetpack_font.ttf");
		if (!_font.loadFromFile("assets/jetpack_font.ttf")) {
			throw JetpackError("Failed to load font file.");
		}
		_text.setFont(_font);
		_text.setCharacterSize(20);

        /* Background */
		_background_texture.loadFromFile("assets/images/background.png");
		if (!_background_texture.loadFromFile("assets/images/background.png")) {
			throw JetpackError("Failed to load background texture file.");
		}
		_background_sprite.setTexture(_background_texture);
		_background_sprite.setPosition(0.f, 0.f);
		_background_size = _background_texture.getSize().x;
		_background_sprite.setScale(1, WINDOW_HEIGHT / _background_texture.getSize().y);

        /* Other elements */
		_initFx();
		_initMusic();
		_initElements();
	}

    /**
     * @brief Updates the game from the server responses
     */
	void Client::_updateFromResponse()
	{
		static std::unordered_map<int, std::function<void (const int &, const std::string &)>> response_handlers = {
			{CMD_ID_ID, [this](const int &code, const std::string &message)
                { handleCommandId(code, message); }},
			{CMD_MAP_ID, [this](const int &code, const std::string &message)
                { handleCommandMap(code, message); }},
			{CMD_PSEUDO_ID, [this](const int &code, const std::string &message)
                { handleCommandPseudo(code, message); }},
			{CMD_MOVE_ID, [this](const int &code, const std::string &message)
                { handleCommandMove(code, message); }},
			{CMD_CLIENTS_NB_ID, [this](const int &code, const std::string &message)
                { handleCommandClientsNb(code, message); }},
			{CMD_CLIENTS_STATS_ID, [this](const int &code, const std::string &message)
                { handleCommandClientsStats(code, message); }},
			{CMD_CLIENTS_POSITIONS_ID, [this](const int &code, const std::string &message)
                { handleCommandClientsPositions(code, message); }},
		};
		std::lock_guard<std::mutex> lock_response_queue(_response_queue_mutex);

		while (!_response_queue.empty()) {
			response_t response = _response_queue.front();
			_response_queue.pop();
			if (response_handlers.find(std::get<0>(response)) != response_handlers.end()) {
				response_handlers[std::get<0>(response)](std::get<1>(response), std::get<2>(response));
			} else {
				ERROR << "Invalid response id: " << std::get<0>(response);
			}
		}
	}

    /**
     * @brief Updates the animation of the game
     * @param deltaTime The time since the last frame
     */
	void Client::_updateAnimation(float deltaTime)
	{
		DEBUG << "Update animation";

		for (auto &player : _players) {
			player.second->getAnimation().update(deltaTime);

			if (player.second->isAlive() && /* Set player in jetpack mode */
            player.second->getPosition()[1] < NB_LINES -1 &&
            player.second->getPlayerState() != Player::PlayerState::JETPACK) {
				player.second->setPlayerState(Player::PlayerState::JETPACK);
			} else if (player.second->isAlive() && /* Set player in normal mode */
            player.second->getPosition()[1] == NB_LINES -1 &&
            player.second->getPlayerState() == Player::PlayerState::JETPACK) {
                if (player.second->getId() == _id)
                    _jetpackSoundDown.pause();
				player.second->setPlayerState(Player::PlayerState::NORMAL);
			} else if (player.second->getPlayerState() != Player::PlayerState::JETPACK && /* If a player is dead, set it invisible */
            player.second->getPlayerState() != Player::PlayerState::NORMAL &&
            !player.second->getAnimation().isPlaying()) {
                player.second->setVisible(false);
            }
		}
        _coin_animation.update(deltaTime);
        _zapper_animation.update(deltaTime);
		_laser_animation.update(deltaTime);
		_missile_animation.update(deltaTime);
	}

    /**
     * @brief Updates the menu
     * @param deltaTime The time since the last update
     */
    void Client::_updateMenu(UNUSED float deltaTime)
    {
        if (_nb_players > 1) {
            _gameState = GameState::GAME;
            if (_menuMusicState == MusicState::PLAYING) {
                _menuMusic.stop();
                _menuMusicState = MusicState::STOPPED;
                _gameMusic.play();
                _gameMusicState = MusicState::PLAYING;
            }
        } else {
            std::unique_lock<std::mutex> lock_commands_queue(_commands_queue_mutex);
            _commands_queue.push({"CLIENTS_NB"});
            lock_commands_queue.unlock();
        }
    }

    /**
     * @brief Updates the game
     * @param deltaTime The time since the last update
     */
    void Client::_updateGame(UNUSED float deltaTime)
    {
        std::vector<std::array<std::size_t, 2>> coin_pos;
        std::vector<std::array<std::size_t, 2>> trap_pos;
        std::size_t players_real_alive = 0;
        std::size_t players_visual_alive = 0;
        std::size_t players_living = 0;

        std::unique_lock<std::mutex> lock_commands_queue(_commands_queue_mutex);
        _commands_queue.push({"CLIENTS_STATS"});
        _commands_queue.push({"CLIENTS_POSITIONS"});
        lock_commands_queue.unlock();

        if (_players.find(_id) == _players.end())
            return;

        /* Coins */
        coin_pos = {
            {static_cast<std::size_t>(std::floor(_players[_id]->getPosition()[0])), static_cast<std::size_t>(std::floor(_players[_id]->getPosition()[1]))},
            {static_cast<std::size_t>(std::ceil(_players[_id]->getPosition()[0])), static_cast<std::size_t>(std::floor(_players[_id]->getPosition()[1]))},
            {static_cast<std::size_t>(std::floor(_players[_id]->getPosition()[0])), static_cast<std::size_t>(std::ceil(_players[_id]->getPosition()[1]))},
            {static_cast<std::size_t>(std::ceil(_players[_id]->getPosition()[0])), static_cast<std::size_t>(std::ceil(_players[_id]->getPosition()[1]))}};

        for (const auto &coin : coin_pos) {
            if (!_players[_id]->isAlive())
                break;
            if (_map[coin[1]][coin[0]] == 'c' && !_coins[coin]->isCollected()) {
                _coins[coin]->setCollected(true);
                _coinSound.play();
            }
        }

        /* Traps */
        _winner = "";
        for (auto &player : _players) {
            if (player.second->isAlive())
                players_real_alive++;
            if (player.second->isVisible()) {
                players_visual_alive++;
                _winner = player.second->getPseudo();
            }
            if (player.second->getPlayerState() != Player::PlayerState::JETPACK
            && player.second->getPlayerState() != Player::PlayerState::NORMAL)
                continue;
            trap_pos = {
                {static_cast<std::size_t>(std::floor(player.second->getPosition()[0])), static_cast<std::size_t>(std::floor(player.second->getPosition()[1]))},
                {static_cast<std::size_t>(std::ceil(player.second->getPosition()[0])), static_cast<std::size_t>(std::floor(player.second->getPosition()[1]))},
                {static_cast<std::size_t>(std::floor(player.second->getPosition()[0])), static_cast<std::size_t>(std::ceil(player.second->getPosition()[1]))},
                {static_cast<std::size_t>(std::ceil(player.second->getPosition()[0])), static_cast<std::size_t>(std::ceil(player.second->getPosition()[1]))}};
            for (const auto &trap : trap_pos) {
                if (std::string_view(TRAP_LIST).find(_map[trap[1]][trap[0]]) != std::string_view::npos) {
                    if (player.second->getId() == _id) {
                        _jetpackSoundUp.stop();
                        _jetpackSoundDown.stop();
                        _traps[trap]->getSound().play();
                    }
                    player.second->setPlayerState(_traps[trap]->getPlayerState());
                    break;
                }
            }
            if (player.second->getPlayerState() == Player::PlayerState::JETPACK
            || player.second->getPlayerState() == Player::PlayerState::NORMAL)
                players_living++;
        }

        /* Check end game */
        if (_gameState == GameState::GAME && _players.size() > 1 && (
        (players_visual_alive < 2) || (players_real_alive <= 1 && players_living > 1)))
             _gameState = GameState::END;
        if (players_real_alive == 0)
            _winner = "";
    }

    /**
     * @brief Updates the client
     * @param deltaTime The time since the last update
     */
	void Client::_update(float deltaTime)
	{
		//DEBUG << "Update";
        _updateFromResponse();

		/* Background */
		_background_pos -= BACKGROUND_SPEED * deltaTime;
		if (_background_pos <= -_background_size)
			_background_pos += _background_size;

        /* Menu */
		if (_gameState == GameState::MAIN_MENU) {
            _updateMenu(deltaTime);
		}
        /* Game */
		if (_gameState == GameState::GAME) {
            _updateAnimation(deltaTime);
            _updateGame(deltaTime);
		}
	}

    /**
     * @brief Draws the elements of the menu
     */
    void Client::_drawMenu()
    {
        _text.setFillColor(sf::Color::White);
        _text.setCharacterSize(30);
        _text.setString("Missing players to start the game");
        _text.setPosition(WINDOW_WIDTH / 2 - _text.getLocalBounds().width / 2,
            WINDOW_HEIGHT / 2 - _text.getLocalBounds().height);
        _window.draw(_text);
        _text.setString("Waiting for players...");
        _text.setPosition(WINDOW_WIDTH / 2 - _text.getLocalBounds().width / 2,
            WINDOW_HEIGHT / 2 + 5);
        _window.draw(_text);
    }

    /**
     * @brief Draws the elements of the game
     */
    void Client::_drawGame()
    {
        float score_pos_y = 0.f;

        /* Coins */
        _coin_sprite.setTextureRect(_coin_animation.getTextureRect());
        for (auto &coin : _coins) {
            float position_x = coin.second->getPosition()[0] - (_players[_id]->getPosition()[0] * RATIO);
            if (coin.second->isCollected() && position_x < -RATIO)
                coin.second->setCollected(false);
            if (position_x < -RATIO)
                position_x += (_map[0].size() * RATIO);
            if (coin.second->isCollected())
                _coin_sprite.setColor({255, 255, 255, 50});
            else
                _coin_sprite.setColor({255, 255, 255, 255});
            _coin_sprite.setPosition(position_x, coin.second->getPosition()[1]);
            _window.draw(_coin_sprite);
        }

        /* Traps */
        _zapper_sprite.setTextureRect(_zapper_animation.getTextureRect());
        _laser_sprite.setTextureRect(_laser_animation.getTextureRect());
        _missile_sprite.setTextureRect(_missile_animation.getTextureRect());
        for (auto &trap : _traps) {
            float position_x = trap.second->getPosition()[0] - (_players[_id]->getPosition()[0] * RATIO);
            if (position_x < -RATIO)
                position_x += (_map[0].size() * RATIO);
            trap.second->getSprite().setPosition(position_x, trap.second->getPosition()[1]);
            _window.draw(trap.second->getSprite());
        }

        /* Players */
        for (auto &player : _players) {
            /* Scoreboard */
            if (player.second->isAlive())
                _text.setFillColor(sf::Color::Green);
            else
                _text.setFillColor(sf::Color::Red);
            _text.setCharacterSize(20);
            _text.setString(player.second->getPseudo() + ": " + std::to_string(player.second->getScore()));
            _text.setPosition(WINDOW_WIDTH - _text.getLocalBounds().width, score_pos_y);
            _window.draw(_text);
            score_pos_y += _text.getLocalBounds().height + 5;

            /* Player sprite */
            if (!player.second->isVisible())
                continue;
            _player_sprite.setTextureRect(player.second->getAnimation().getTextureRect());
            _player_sprite.setPosition(0, player.second->getPosition()[1] * RATIO);
            if (player.second->getId() == _id) {
                _player_sprite.setColor({255, 255, 255, 255});
                _text.setFillColor({255, 255, 255, 255});
            } else {
                _player_sprite.setColor({255, 255, 255, 100});
                _text.setFillColor({255, 255, 255, 100});
            }
            _window.draw(_player_sprite);

            /* Player name */
            _text.setCharacterSize(14);
            _text.setString(player.second->getPseudo());
            _text.setPosition(5,
                player.second->getPosition()[1] * RATIO - _text.getLocalBounds().height - 5);
            _window.draw(_text);
        }

        /* Game Pause */
        if (_players.size() < 2) {
            _text.setFillColor(sf::Color::White);
            _text.setCharacterSize(30);
            _text.setString("Missing players to continue the game");
            _text.setPosition(WINDOW_WIDTH / 2 - _text.getLocalBounds().width / 2,
                WINDOW_HEIGHT / 2 - _text.getLocalBounds().height);
            _window.draw(_text);
            _text.setString("Waiting for players...");
            _text.setPosition(WINDOW_WIDTH / 2 - _text.getLocalBounds().width / 2,
                WINDOW_HEIGHT / 2 + 5);
            _window.draw(_text);
        }
    }

    /**
     * @brief Draws the elements of the end
     */
    void Client::_drawEnd()
    {
        std::string message;

        if (_winner.empty())
            message += " No winner";
        else
            message += " The winner is : " + _winner;
        _text.setFillColor(sf::Color::White);
        _text.setCharacterSize(30);
        _text.setString("Game end !");
        _text.setPosition(WINDOW_WIDTH / 2 - _text.getLocalBounds().width / 2,
            WINDOW_HEIGHT / 2 - _text.getLocalBounds().height - 5);
        _window.draw(_text);
        _text.setString(message);
        _text.setPosition(WINDOW_WIDTH / 2 - _text.getLocalBounds().width / 2,
            WINDOW_HEIGHT / 2);
        _window.draw(_text);
        _text.setString("Press ENTER to quit");
        _text.setPosition(WINDOW_WIDTH / 2 - _text.getLocalBounds().width / 2,
            WINDOW_HEIGHT / 2 + _text.getLocalBounds().height + 5);
        _window.draw(_text);
    }

    /**
     * @brief Draws the elements on the screen depending on the game state
     */
	void Client::_draw()
	{
		//DEBUG << "Draw";

		/* Background */
		_background_sprite.setPosition(_background_pos, 0.f);
		_window.draw(_background_sprite);
		_background_sprite.setPosition(_background_size + _background_pos, 0.f);
		_window.draw(_background_sprite);

		/* Player */
		if ( _gameState == GameState::MAIN_MENU) {
            _drawMenu();
		} else if (_gameState == GameState::GAME) {
            if (_players.find(_id) != _players.end())
                _drawGame();
		} else if (_gameState == GameState::END) {
            _drawEnd();
        }
	}

    /**
     * @brief Analyses the events of the game
     */
	void Client::_analyseEvent()
	{
		sf::Event event{};

		//DEBUG << "Analyse event";
		while (_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed || (_gameState == GameState::END &&
            event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Enter)) {
				DEBUG << "Window closed";
				_window.close();
				std::lock_guard<std::mutex> lock(isRunningMutex);
				isRunning = false;
				return;
			}
			if (event.type == sf::Event::KeyPressed) {
				/*if (event.key.code == sf::Keyboard::Key::Escape) {
					DEBUG << "Escape pressed";
				}*/
				if (event.key.code == sf::Keyboard::Key::Space && _gameState == GameState::GAME
                && _players.find(_id) != _players.end() && _players[_id]->isAlive()
                && !_jetpack) {
					DEBUG << "Space pressed";
					if (!_jetpack) {
						_jetpackSoundDown.pause();
						_jetpackSoundUp.play();
					}
					_jetpack = true;
					std::unique_lock<std::mutex> lock(_commands_queue_mutex);
					_commands_queue.push({"MOVE", "UP"});
					lock.unlock();
				}
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Key::Space && _gameState == GameState::GAME
                && _players.find(_id) != _players.end() && _players[_id]->isAlive()
                && _jetpack) {
					DEBUG << "Space released";
					if (_jetpack) {
						_jetpackSoundUp.stop();
						_jetpackSoundDown.play();
					}
					_jetpack = false;
					std::unique_lock<std::mutex> lock(_commands_queue_mutex);
					_commands_queue.push({"MOVE", "DOWN"});
					lock.unlock();
				}
			}
		}
	}

    /**
	 * @brief Thread for handling the game loop
     */
	void Client::_gameThread()
	{
		DEBUG << "Game thread";
		sf::Clock clock;
		float deltaTime = 0.0f;

		while (isRunning && _window.isOpen()) {
			deltaTime = clock.restart().asSeconds();
			_update(deltaTime);
			_window.clear();
			_draw();
			_window.display();
			_analyseEvent();
		}
        if (_window.isOpen()) {
            _window.close();
        }
	}
}