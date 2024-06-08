#include "Cointainers.h"
#include "Button.h"
#include "TextButton.h"

#include "Klasa.h"

#include <sstream>
#include <fstream>
#include <filesystem>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include <thread>
#include <chrono>

void Cointainers::drawAll(sf::RenderWindow& window)
{

	window.draw(m_keys);
	window.draw(m_instrument_name);
	window.draw(m_scale);
	window.draw(m_settings);
	window.draw(m_score);
	

	for (PianoWhiteKey& key : m_whiteKeys) {
		key.render(window);
	}
	for (PianoBlackKey& key : m_blackKeys) {
		key.render(window);
	}

	for (auto& pair : m_buttons) {
		TextButton& btn = pair.second;
		btn.render(window);
	}

	for (auto& pair : m_knobs) {
		Knob& knob = pair.second;
		knob.render(window);
	}

	//TEXTS

	std::ostringstream oss;
	oss << score;
	std::string scoreStr = "Score: " + oss.str();

	TextDisplay scoreText(
		760, 160, 40, sf::Color::Black, scoreStr
	);
	scoreText.render(window);

	TextDisplay volumeText(
		503, 340, 20, sf::Color::Black, "Volume"
	);
	volumeText.render(window);


	TextDisplay pitchText(
		510, 220, 20, sf::Color::Black, "Pitch"
	);
	pitchText.render(window);

	TextDisplay feedback(
		90, 220, 25, sf::Color::Black, m_feedbackSTR
	);
	feedback.render(window);

	TextDisplay feedback2(
		90, 250, 25, sf::Color::Black, m_feedback2STR
	);
	feedback2.render(window);

	TextDisplay pianoName(
		440, 2, 25, sf::Color::White, "Grand Piano"
	);
	pianoName.render(window);
}



Cointainers::Cointainers()
{

}

Cointainers::~Cointainers()
{
	m_whiteKeys.clear();
	m_blackKeys.clear();
}

void Cointainers::update(sf::RenderWindow& window)
{
	sf::Vector2i mousePosI = sf::Mouse::getPosition(window);
	sf::Vector2f mousePos(static_cast<float>(mousePosI.x), static_cast<float>(mousePosI.y));


	bool blackKeyActive = false;

	for (PianoBlackKey& key : m_blackKeys) {
		key.update(mousePos);
		if (key.button_state == BTN_HOVER || key.button_state == BTN_PRESS) {
			blackKeyActive = true;
		}

		if (key.isPressed()) {

			//this->m_sounds[key.getID()].play();
			playNote(key.getID());
			checkAnswer(key.getID());
		}

	}

	if (!blackKeyActive) {
		for (PianoWhiteKey& key : m_whiteKeys) {
			key.update(mousePos);

			if (key.isPressed()) {

				//this->m_sounds[key.getID()].play();
				playNote(key.getID());
				checkAnswer(key.getID());
			}
		}
	}

	for (auto& pair : m_buttons) {
		TextButton& btn = pair.second;
		btn.update(mousePos);
	}

	for (auto& pair : m_knobs) {
		Knob& knob = pair.second;
		knob.update(mousePos);
	}

	//LOAD FROM FILE
	if(m_buttons["LOAD_FILE"].isPressed()) {
		std::cout << "LOAD_FILE is pressed" << std::endl;
		//MIDI File

		for (int i = 0; i < m_KeysToVirtual.size(); i++) {
			m_pianoKeyWasPressed[i] = false;
		}

		m_feedbackSTR = "Playing midi...";
		m_feedback2STR = "";
		std::string fileName = "demo.txt";
		Klasa fileHandler;
		this->m_midiFile = fileHandler.readFile(fileName);


		this->m_midiStarted = true;

		m_clock.restart();
		m_elapsed = sf::Time::Zero;

		//reset
		for (int i = 0; i < this->m_pianoKeyWasPressedMIDI.size(); i++) {
			this->m_pianoKeyWasPressedMIDI[i] = false;
		}
		m_frame_counter = 0;
		m_noteCounterMIDI = 0;



	}

	//START GAME

	if (m_buttons["START_GAME"].isPressed()) {
		std::cout << "START_GAME is pressed" << std::endl;
		m_feedbackSTR = "Starting game...";
		m_feedback2STR = "";
		m_clock.restart();
		m_elapsed = sf::Time::Zero;
		m_gameStarted = true;


	}

	//KEYBOARD
	for (int i = 0; i < m_keyboardKeys.size(); i++) {
		if (sf::Keyboard::isKeyPressed(m_keyboardKeys[i])) {
			if (!m_keyboardWasPressed[i]) {
				//this->m_sounds[i+12].play();
				playNote(i + 12);
				m_keyboardWasPressed[i] = true;
				checkAnswer(i + 12);
			}
			if (m_keyboardKeysToVirtual[i].first) {
				m_whiteKeys[m_keyboardKeysToVirtual[i].second].setPressedColor();
			}
			else {
				m_blackKeys[m_keyboardKeysToVirtual[i].second].setPressedColor();
			}


		}
		else {
			m_keyboardWasPressed[i] = false;
			
		}
	}

	//GAME

	if (m_gameStarted) {
		m_elapsed += m_clock.restart();
		runRound();
		for (int i = 0; i < m_pianoKeyWasPressed.size(); i++) {
			if (m_pianoKeyWasPressed[i]) {

				if (m_KeysToVirtual[i].first) {
					m_whiteKeys[m_KeysToVirtual[i].second].setPressedColor();
				}
				else {
					m_blackKeys[m_KeysToVirtual[i].second].setPressedColor();
				}

			}

		}
	}

	//MIDI

	if (m_midiStarted) {
		m_elapsed += m_clock.restart();

		runMIDI();

	}
}

void Cointainers::runMIDI() {
	float tempo = 0.07813f;


	while (m_elapsed >= sf::seconds(tempo) && m_noteCounterMIDI < m_midiFile.size()) {
		//reset
		for (int i = 0; i < this->m_pianoKeyWasPressedMIDI.size(); i++) {
			this->m_pianoKeyWasPressedMIDI[i] = false;
		}

		m_elapsed -= sf::seconds(tempo);

		for (int i = 0; i < this->m_midiFile[m_noteCounterMIDI].size(); i++) {
			playNote(m_midiFile[m_noteCounterMIDI][i]);

			m_pianoKeyWasPressedMIDI[m_midiFile[m_noteCounterMIDI][i]] = true;
		}

		m_noteCounterMIDI++;
	}


	//switch virtual key
	for (int i = 0; i < m_pianoKeyWasPressedMIDI.size(); i++) {
		if (m_pianoKeyWasPressedMIDI[i]) {

			if (m_KeysToVirtual[i].first) {
				m_whiteKeys[m_KeysToVirtual[i].second].setPressedColor();
			}
			else {
				m_blackKeys[m_KeysToVirtual[i].second].setPressedColor();
			}

		}

	}
}

void Cointainers::runRound() {
	//std::this_thread::sleep_for(std::chrono::seconds(3));
	std::vector<std::vector<int>> sounds_to_playIDs = {
			{m_game_intervals[m_current_round].first},
			{m_game_intervals[m_current_round].second},
			{m_game_intervals[m_current_round].second},
			{m_game_intervals[m_current_round].first},
			{m_game_intervals[m_current_round].first, m_game_intervals[m_current_round].second}
	};

	float secs = 2.f;

	while (m_elapsed >= sf::seconds(secs) && m_frame_counter < sounds_to_playIDs.size()) {
		m_elapsed -= sf::seconds(secs);



		for (int i = 0; i < sounds_to_playIDs[m_frame_counter].size();i++) {


			//m_sounds[sounds_to_playIDs[m_frame_counter][i]].play();
			playNote(sounds_to_playIDs[m_frame_counter][i]);
			if (m_frame_counter == 0) {
				m_pianoKeyWasPressed[sounds_to_playIDs[m_frame_counter][i]] = true;
			}
			
		}

		m_frame_counter++;
	};


}


void Cointainers::checkAnswer(int key) {
	if (m_gameStarted) {
		if (key == m_game_intervals[m_current_round].second) {

			int interval = m_game_intervals[m_current_round].second - m_game_intervals[m_current_round].first;
			if (interval <= 12) {
				m_feedback2STR = m_intervalsSTR[interval];
			}
			else {
				m_feedback2STR = "-";
			}

			if (m_current_round == m_game_intervals.size()-1) {
				//WIN
				m_current_round = 0;
				m_feedbackSTR = "Great, You won";
				m_feedback2STR = "it was " + m_feedback2STR;
			}
			else {
				//GOOD
				m_feedbackSTR = "Nice it was";

				m_current_round++;
				score += 3;

			}
			m_frame_counter = 0;
			m_elapsed = sf::Time::Zero;
			m_clock.restart();

			for (int i = 0; i < m_KeysToVirtual.size(); i++) {
				m_pianoKeyWasPressed[i] = false;
			}
		}
		else {
			//MISTAKE
			m_feedbackSTR = "Not really";
			m_feedback2STR = "please listen again";
			score -= 1;
			m_frame_counter = 0;
			m_elapsed = sf::Time::Zero;
		}
	}

}

void Cointainers::playNote(int key) {

	m_sounds[key].setVolume(m_knobs["VOLUME"].getValue());
	m_sounds[key].setPitch(m_knobs["PITCH"].getValue()/100 + 0.5);


	m_sounds[key].play();
};

void Cointainers::setUp()
{
	this->m_PitchOfWhiteKeys = {"C2", "D2", "E2", "F2", "G2", "A2", "B2", "C3", "D3", "E3", "F3", "G3", "A3", "B3", "C4", "D4", "E4", "F4", "G4", "A4", "B4", "C5", "D5", "E5", "F5", "G5", "A5", "B5", "C6", "D6", "E6", "F6", "G6", "A6", "B6", "C7"};
	this->m_PitchOfBlackKeys = {"Db2", "Eb2", "Gb2", "Ab2", "Bb2", "Db3", "Eb3", "Gb3", "Ab3", "Bb3", "Db4", "Eb4", "Gb4", "Ab4", "Bb4", "Db5", "Eb5", "Gb5", "Ab5", "Bb5","Db6", "Eb6", "Gb6", "Ab6", "Bb6" };

	//Generowanie rund
	Klasa genIntervals;
	this->m_game_intervals = genIntervals.createGameIntervals(6);


	for (int i = 0; i < m_keyboardKeys.size(); i++) {
		m_keyboardWasPressed.push_back(false);
	}
	for (int i = 0; i < m_KeysToVirtual.size(); i++) {
		m_pianoKeyWasPressed.push_back(false);
	}
	for (int i = 0; i < 61; i++) {
		m_pianoKeyWasPressedMIDI.push_back(false);
	}



	for (int i = 0; i < 61; i++) {

		sf::SoundBuffer buffer;
		this->m_buffers.push_back(buffer);

		sf::Sound sound;
		this->m_sounds.push_back(sound);

	}
	
	sf::Font font;
	if (!font.loadFromFile("Assets/Fartage.ttf")) {
		std::cerr << "Error loading font!" << std::endl;
	};

	sf::RectangleShape keys(sf::Vector2f(1000, 150));
	keys.setPosition(0, 450);
	keys.setFillColor(sf::Color(25,25,25));

	this->m_keys = keys;


	sf::RectangleShape instrument_name(sf::Vector2f(500, 35));
	instrument_name.setPosition(250, 0);
	instrument_name.setFillColor(sf::Color(100, 100, 100,160));

	this->m_instrument_name = instrument_name;


	sf::RectangleShape scale(sf::Vector2f(350, 300));
	scale.setPosition(35, 100);
	scale.setFillColor(sf::Color(100, 100, 100, 160));

	this->m_scale = scale;

	sf::RectangleShape settings(sf::Vector2f(250, 300));
	settings.setPosition(415, 100);

	settings.setFillColor(sf::Color(100, 100, 100, 160));

	this->m_settings = settings;


	sf::RectangleShape score(sf::Vector2f(250, 300));
	score.setPosition(715, 100);

	score.setFillColor(sf::Color(100, 100, 100, 160));

	this->m_score = score;

	
	//WHITE KEYS

	for (std::size_t i = 0; i < m_PitchOfWhiteKeys.size(); ++i) {
		PianoWhiteKey whiteKey(whiteKeysIDs[i], m_keys.getPosition().x + (i + 1) * 26, m_keys.getPosition().y + 10, m_PitchOfWhiteKeys[i]);

		std::string pathTmp = "Assets/piano-good/" + whiteKey.getPitch() + ".ogg";

		this->m_buffers[whiteKey.getID()].loadFromFile(pathTmp);
		this->m_sounds[whiteKey.getID()].setBuffer(this->m_buffers[whiteKey.getID()]);

		m_whiteKeys.push_back(whiteKey);
	}

	//BLACK KEYS

	int correctPlacent = 0;

	for (std::size_t i = 0; i < m_PitchOfBlackKeys.size(); ++i) {
		if (i % 5 == 2 || i % 5 == 0) correctPlacent++;

		PianoBlackKey blackKey(blackKeysIDs[i], m_keys.getPosition().x + (correctPlacent + i) * 26 + 15, m_keys.getPosition().y + 10, m_PitchOfBlackKeys[i]);

		std::string pathTmp = "Assets/piano-good/" + blackKey.getPitch() + ".ogg";

		this->m_buffers[blackKey.getID()].loadFromFile(pathTmp);

		this->m_sounds[blackKey.getID()].setBuffer(this->m_buffers[blackKey.getID()]);


		m_blackKeys.push_back(blackKey);
	}

	//LOAD FROM FILE BTN

	TextButton loadFromFileBtn(
		770, 320, 150, 30, 15, sf::Color(215, 235, 242), sf::Color(187, 222, 234), sf::Color(133, 176, 189), "Load From File"
	);

	this->m_buttons["LOAD_FILE"] = loadFromFileBtn;

	//START GAME

	TextButton startGameBtn(
		770, 260, 150, 30, 15, sf::Color(215, 235, 242), sf::Color(187, 222, 234), sf::Color(133, 176, 189), "Start Game"
	);

	this->m_buttons["START_GAME"] = startGameBtn;


	//KNOB

	Knob volume_knob(
		535, 310, 30, sf::Color(215, 235, 242), sf::Color(187, 222, 234), sf::Color(133, 176, 189)
	);

	this->m_knobs["VOLUME"] = volume_knob;
	this->m_knobs["VOLUME"].setValue(50);

	//PITCH

	Knob pitch_knob(
		535, 190, 30, sf::Color(215, 235, 242), sf::Color(187, 222, 234), sf::Color(133, 176, 189)
	);

	this->m_knobs["PITCH"] = pitch_knob;
	this->m_knobs["PITCH"].setValue(50);
}

