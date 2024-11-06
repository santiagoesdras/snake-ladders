#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>

class Player {
private:
    std::string name;
    int position;

public:
    Player(const std::string& name);
    void setName(const std::string& name);
    std::string getName() const;
    int getPosition() const;
    void setPosition(int position);
    void move(int steps);
    void resetPosition();
};

#endif
