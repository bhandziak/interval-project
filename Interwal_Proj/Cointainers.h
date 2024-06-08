#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <string>

#include "Button.h"
#include "TextButton.h"
#include "PianoWhiteKey.h"
#include "PianoBlackKey.h"
#include "Knob.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

class Cointainers {
private:
	std::vector<PianoWhiteKey> m_whiteKeys;
	std::vector <std::string> m_PitchOfWhiteKeys;

	std::vector<PianoBlackKey> m_blackKeys;
	std::vector <std::string> m_PitchOfBlackKeys;

	std::unordered_map<std::string, TextButton> m_buttons;
	std::unordered_map<std::string, Knob> m_knobs;

	std::vector<sf::Sound> m_sounds;

	std::vector<sf::SoundBuffer> m_buffers;

	std::vector<std::pair<int, int>>  m_game_intervals = {
		{24, 36}, {24, 31}, {26, 28}, {50, 55}, {30,38}
	};
	std::vector<int> whiteKeysIDs = { 0,2, 4,5,7,9,11, 12, 14, 16, 17, 19, 21, 23,  24, 26, 28, 29, 31, 33, 35 , 36, 38, 40, 41, 43, 45, 47 ,48, 50, 52, 53, 55, 57, 59, 60 };
	std::vector<int> blackKeysIDs = { 1,3,6,8,10,13, 15, 18, 20, 22 ,25, 27, 30, 32, 34, 37, 39, 42, 44, 46, 49, 51, 54, 56, 58 };

	std::vector<sf::Keyboard::Key> m_keyboardKeys = {
		sf::Keyboard::Key::Z, sf::Keyboard::Key::S, sf::Keyboard::Key::X, sf::Keyboard::Key::D, sf::Keyboard::Key::C, sf::Keyboard::Key::V, sf::Keyboard::Key::G, sf::Keyboard::Key::B, sf::Keyboard::Key::H, sf::Keyboard::Key::N, sf::Keyboard::Key::J, sf::Keyboard::Key::M,
		sf::Keyboard::Key::Q, sf::Keyboard::Key::Num2, sf::Keyboard::Key::W, sf::Keyboard::Key::Num3, sf::Keyboard::Key::E, sf::Keyboard::Key::R, sf::Keyboard::Key::Num5, sf::Keyboard::Key::T, sf::Keyboard::Key::Num6, sf::Keyboard::Key::Y, sf::Keyboard::Key::Num7, sf::Keyboard::Key::U,
		sf::Keyboard::Key::I, sf::Keyboard::Key::Num9, sf::Keyboard::Key::O, sf::Keyboard::Key::Num0, sf::Keyboard::Key::P, sf::Keyboard::Key::LBracket
	};

	std::vector<std::pair<bool, int>> m_KeysToVirtual = {
		{true, 0}, {false, 0}, {true, 1}, {false, 1}, {true, 2}, {true, 3}, {false, 2}, {true, 4}, {false, 3}, {true, 5}, { false, 4 }, {true, 6},
		{true, 7}, {false, 5}, {true, 8}, {false, 6}, {true, 9}, {true, 10}, {false, 7}, {true, 11}, {false, 8}, {true, 12}, { false, 9 }, {true, 13},
		{true, 14}, {false, 10}, {true, 15}, {false, 11}, {true, 16}, {true, 17}, {false, 12}, {true, 18}, {false, 13}, {true, 19}, { false, 14 }, {true, 20},
		{true, 21}, {false, 15}, {true, 22}, {false, 16}, {true, 23}, {true, 24}, {false, 17}, {true, 25}, {false, 18}, {true, 26}, { false, 19 }, {true, 27},
		{true, 28}, {false, 20}, {true, 29}, {false, 21}, {true, 30}, {true, 31}, {false, 22}, {true, 32}, {false, 23}, {true, 33}, { false, 24 }, {true, 34},
		{true, 35}
	};

	std::vector<std::pair<bool, int>> m_keyboardKeysToVirtual = {
		{true, 7}, {false, 5}, {true, 8}, {false, 6}, {true, 9}, {true, 10}, {false, 7}, {true, 11}, {false, 8}, {true, 12}, { false, 9 }, {true, 13},
		{true, 14}, {false, 10}, {true, 15}, {false, 11}, {true, 16}, {true, 17}, {false, 12}, {true, 18}, {false, 13}, {true, 19}, { false, 14 }, {true, 20},
		{true, 21}, {false, 15}, {true, 22}, {false, 16}, {true, 23}, {true, 24}
	};


	std::vector<bool> m_keyboardWasPressed;
	std::vector<bool> m_pianoKeyWasPressed;

	unsigned int m_current_round = 0;
	unsigned int m_answer = 0;
	int score = 0;

	bool m_gameStarted = false;

	sf::Clock m_clock;
	sf::Time m_elapsed;
	int m_frame_counter = 0;


	std::vector<std::vector<int>> m_midiFile;
	bool m_midiStarted = false;
	std::vector<bool> m_pianoKeyWasPressedMIDI;
	int m_noteCounterMIDI = 0;


	std::string m_feedbackSTR = "Hello!";
	std::string m_feedback2STR = "";
	std::vector<std::string> m_intervalsSTR = {
		"Unison", "Minor second", "Major second", "Minor third", "Major third", "Perfect fourth", "Tritone", "Perfect fifth", "Minor sixth", "Major sixth", "Minor seventh", "Major seventh", "Perfect octave"
	};
public:
	sf::RectangleShape m_instrument_name;
	sf::RectangleShape m_scale;
	sf::RectangleShape m_settings;
	sf::RectangleShape m_score;
	sf::RectangleShape m_keys;

	Cointainers();
	~Cointainers();

	void update(sf::RenderWindow& window);
	void setUp();
	void drawAll(sf::RenderWindow& window);


	void checkAnswer(int key);
	void runMIDI();
	void runRound();
	void playNote(int key);
};