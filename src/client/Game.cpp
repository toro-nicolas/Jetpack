/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Game.cpp
*/
/**
 * @file Game.cpp
 * @brief The Game.cpp
 * @author Nicolas TORO
 */

#include "client/Client.hpp"

namespace Jetpack {
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
	}

	void Client::_initMusic()
	{
		DEBUG << "Init music";
		if (!_mainMenuMusic.openFromFile("assets/sounds/main_menu.ogg"))
			throw JetpackError("Failed to load music file.");
		_mainMenuMusic.setVolume(30.f);
		_mainMenuMusic.setLoop(true);
		_mainMenuMusic.play();
		_mainMenuMusicState = MusicState::PLAYING;

		if (!_mainMusic.openFromFile("assets/sounds/theme2.ogg"))
			throw JetpackError("Failed to load music file.");
		_mainMusic.setVolume(30.f);
		_mainMusic.setLoop(true);
	}

	void Client::_initElements()
	{
		DEBUG << "Init elements";

        /* Player */
		if (!_player_texture.loadFromFile("assets/images/player_sprite_sheet.png")) {
			throw JetpackError("Failed to load player texture.");
		}
		_player_sprite.setTexture(_player_texture);
		_player_sprite.setPosition(60.f, 300.f);
		sf::IntRect normalRect(0, 0, _player_texture.getSize().x / 4, _player_texture.getSize().y / 3);
		_player_sprite.setTextureRect(normalRect);
		_player_sprite.setScale(RATIO / (_player_texture.getSize().x / 4), RATIO / (_player_texture.getSize().y / 3));

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
	}

	void Client::_initSfml()
	{
		DEBUG << "Init SFML";
		_window.create(sf::VideoMode({static_cast<uint>(WINDOW_WIDTH), static_cast<uint>(WINDOW_HEIGHT)}),
			"Jetpack Client", sf::Style::Close);
		_window.setFramerateLimit(60);

		_font.loadFromFile("assets/jetpack_font.ttf");
		if (!_font.loadFromFile("assets/jetpack_font.ttf")) {
			throw JetpackError("Failed to load font file.");
		}
		_text.setFont(_font);
		_text.setCharacterSize(20);

		_background_texture.loadFromFile("assets/images/background.png");
		if (!_background_texture.loadFromFile("assets/images/background.png")) {
			throw JetpackError("Failed to load background texture file.");
		}
		_background_sprite.setTexture(_background_texture);
		_background_sprite.setPosition(0.f, 0.f);
		_background_size = _background_texture.getSize().x;
		_background_sprite.setScale(1, WINDOW_HEIGHT / _background_texture.getSize().y);

		_coin_texture.loadFromFile("assets/images/coins.png");
		if (!_coin_texture.loadFromFile("assets/images/coins.png")) {
			throw JetpackError("Failed to load coin texture file.");
		}
		_coin_sprite.setTexture(_coin_texture);
		_coin_sprite.setPosition(50.f, 50.f);

		_initFx();
		_initMusic();
		_initElements();
	}

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

	void Client::_updateAnimation(float deltaTime)
	{
		DEBUG << "Update animation";

		for (auto &player : _players) {
			player.second->getAnimation().update(deltaTime);

			if (player.second->getPosition()[1] < NB_LINES -1 && player.second->getPlayerState() != Player::PlayerState::JETPACK) {
				player.second->setPlayerState(Player::PlayerState::JETPACK);
			} else if (player.second->getPosition()[1] == NB_LINES -1 && player.second->getPlayerState() == Player::PlayerState::JETPACK) {
				_jetpackSoundDown.pause();
				_jetpackSoundDownState = MusicState::PAUSED;
				player.second->setPlayerState(Player::PlayerState::NORMAL);
			}
		}
        _coin_animation.update(deltaTime);
        _zapper_animation.update(deltaTime);
	}

	void Client::_update(UNUSED float deltaTime)
	{
		//DEBUG << "Update";

		/* Background */
		_background_pos -= BACKGROUND_SPEED * deltaTime;
		if (_background_pos <= -_background_size)
			_background_pos += _background_size;


		_updateAnimation(deltaTime);
		if (!_gameStarted) {
			if (_nb_players > 1) {
				_gameStarted = true;
				if (_mainMenuMusicState == MusicState::PLAYING) {
					_mainMenuMusic.stop();
					_mainMenuMusicState = MusicState::STOPPED;
					_mainMusic.play();
					_musicState = MusicState::PLAYING;
				}
			} else {
				std::unique_lock<std::mutex> lock_commands_queue(_commands_queue_mutex);
				_commands_queue.push({"CLIENTS_NB"});
				lock_commands_queue.unlock();
			}
		}
		if (_gameStarted) {
			std::unique_lock<std::mutex> lock_commands_queue(_commands_queue_mutex);
			_commands_queue.push({"CLIENTS_STATS"});
			_commands_queue.push({"CLIENTS_POSITIONS"});
			lock_commands_queue.unlock();
            for (auto &coin : _coins) {
                if (_players.find(_id) == _players.end() || coin->isCollected() || !_players[_id]->isAlive())
                    continue;
                if ((coin->getPosition()[0] > _players[_id]->getPosition()[0] * RATIO &&
                coin->getPosition()[0] < _players[_id]->getPosition()[0] * RATIO + RATIO &&
                coin->getPosition()[1] > _players[_id]->getPosition()[1] * RATIO - RATIO &&
                coin->getPosition()[1] < _players[_id]->getPosition()[1] * RATIO) ||
                (coin->getPosition()[0] >= _players[_id]->getPosition()[0] * RATIO &&
                coin->getPosition()[0] < _players[_id]->getPosition()[0] * RATIO + RATIO &&
                coin->getPosition()[1] - RATIO >= _players[_id]->getPosition()[1] * RATIO - RATIO &&
                coin->getPosition()[1] - RATIO < _players[_id]->getPosition()[1] * RATIO)) {
                    coin->setCollected(true);
                    _coinSound.play();
                }
            }
            for (auto &zapper : _zappers) {
                if (_players.find(_id) == _players.end() || _players[_id]->getPlayerState() == Player::PlayerState::ZAPPED)
                    continue;
                if ((zapper->getPosition()[0] > _players[_id]->getPosition()[0] * RATIO &&
                zapper->getPosition()[0] < _players[_id]->getPosition()[0] * RATIO + RATIO &&
                zapper->getPosition()[1] > _players[_id]->getPosition()[1] * RATIO - RATIO &&
                zapper->getPosition()[1] < _players[_id]->getPosition()[1] * RATIO) ||
                (zapper->getPosition()[0] >= _players[_id]->getPosition()[0] * RATIO &&
                zapper->getPosition()[0] < _players[_id]->getPosition()[0] * RATIO + RATIO &&
                zapper->getPosition()[1] - RATIO >= _players[_id]->getPosition()[1] * RATIO - RATIO &&
                zapper->getPosition()[1] - RATIO < _players[_id]->getPosition()[1] * RATIO)) {
                    _zappedSound.play();
                    _players[_id]->setPlayerState(Player::PlayerState::ZAPPED);
                }
            }
		}
	}

	void Client::_drawElements(UNUSED float deltaTime)
	{
		//DEBUG << "Draw elements";
        float score_pos_y = 0.f;

		/* Background */
		_background_sprite.setPosition(_background_pos, 0.f);
		_window.draw(_background_sprite);
		_background_sprite.setPosition(_background_size + _background_pos, 0.f);
		_window.draw(_background_sprite);

		/* Player */
		if (!_gameStarted) {
			_window.draw(_player_sprite);
		} else {
            if (_players.find(_id) == _players.end())
                return;

            _coin_sprite.setTextureRect(_coin_animation.getTextureRect());
            for (auto &coin : _coins) {
                float position_x = coin->getPosition()[0] - (_players[_id]->getPosition()[0] * RATIO);
                if (coin->isCollected() && position_x < -RATIO)
                    coin->setCollected(false);
                if (position_x < -RATIO)
                    position_x += (_map[0].size() * RATIO);
                if (coin->isCollected())
                    _coin_sprite.setColor({255, 255, 255, 50});
                else
                    _coin_sprite.setColor({255, 255, 255, 255});
                _coin_sprite.setPosition(position_x, coin->getPosition()[1]);
                _window.draw(_coin_sprite);
            }

            _zapper_sprite.setTextureRect(_zapper_animation.getTextureRect());
            for (auto &zapper : _zappers) {
                float position_x = zapper->getPosition()[0] - (_players[_id]->getPosition()[0] * RATIO);
                if (position_x < -RATIO)
                    position_x += (_map[0].size() * RATIO);
                _zapper_sprite.setPosition(position_x, zapper->getPosition()[1]);
                _window.draw(_zapper_sprite);
            }

			for (auto &player : _players) {
				_player_sprite.setTextureRect(player.second->getAnimation().getTextureRect());
				_player_sprite.setPosition(0, player.second->getPosition()[1] * RATIO);
				if (!player.second->isAlive()) {
					_player_sprite.setColor({255, 255, 255, 20});
                    _text.setFillColor({255, 255, 255, 20});
				} else if (player.second->getId() == _id) {
					_player_sprite.setColor({255, 255, 255, 255});
                    _text.setFillColor({255, 255, 255, 255});
				} else {
					_player_sprite.setColor({255, 255, 255, 100});
                    _text.setFillColor({255, 255, 255, 100});
				}
				_window.draw(_player_sprite);

                _text.setCharacterSize(14);
				_text.setString(player.second->getPseudo());
				_text.setPosition(5,
                    player.second->getPosition()[1] * RATIO - _text.getLocalBounds().height - 5);
				_window.draw(_text);

                if (player.second->isAlive())
                    _text.setFillColor(sf::Color::Green);
                else
                    _text.setFillColor(sf::Color::Red);
                _text.setCharacterSize(20);
                _text.setString(player.second->getPseudo() + ": " + std::to_string(player.second->getScore()));
                _text.setPosition(WINDOW_WIDTH - _text.getLocalBounds().width, score_pos_y);
                _window.draw(_text);
                score_pos_y += _text.getLocalBounds().height + 5;
			}

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
	}

	void Client::_analyseEvent()
	{
		sf::Event event{};

		//DEBUG << "Analyse event";
		while (_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				DEBUG << "Window closed";
				_window.close();
				std::lock_guard<std::mutex> lock(isRunningMutex);
				isRunning = false;
				return;
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Key::Escape) {
					DEBUG << "Escape pressed";
					// Je sais pas si on fait un menu pause
				}
				if (event.key.code == sf::Keyboard::Key::Space && !_jetpack) {
					DEBUG << "Space pressed";
					if (!_jetpack) {
						_jetpackSoundDown.pause();
						_jetpackSoundDownState = MusicState::PAUSED;
						_jetpackSoundUp.play();
						_jetpackSoundUpState = MusicState::PLAYING;
					}
					_jetpack = true;
					std::unique_lock<std::mutex> lock(_commands_queue_mutex);
					_commands_queue.push({"MOVE", "UP"});
					lock.unlock();
				}
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Key::Space && _jetpack) {
					DEBUG << "Space released";
					if (_jetpack) {
						_jetpackSoundUp.stop();
						_jetpackSoundUpState = MusicState::PAUSED;
						_jetpackSoundDown.play();
						_jetpackSoundDownState = MusicState::PLAYING;
					}
					_jetpack = false;
					std::unique_lock<std::mutex> lock(_commands_queue_mutex);
					_commands_queue.push({"MOVE", "DOWN"});
					lock.unlock();
				}
			}
		}
	}

	void Client::_gameThread()
	{
		DEBUG << "Game thread";
		sf::Clock clock;
		float deltaTime = 0.0f;

		while (isRunning && _window.isOpen()) {
			deltaTime = clock.restart().asSeconds();
			_updateFromResponse();
			_update(deltaTime);
			_window.clear();
			_drawElements(deltaTime);
			_window.display();
			_analyseEvent();
		}
        if (_window.isOpen()) {
            _window.close();
        }
	}
}