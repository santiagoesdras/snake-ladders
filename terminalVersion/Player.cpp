#include "Player.h"

Player::Player(const std::string& name) : name(name), position(0) {}

void Player::setName(const std::string& name) {
    this->name = name;
}

std::string Player::getName() const {
    return name;
}

int Player::getPosition() const {
    return position;
}

void Player::setPosition(int position) {
    this->position = position;
}

void Player::move(int steps) {
    position += steps;
}

void Player::resetPosition() {
    position = 0;
}
