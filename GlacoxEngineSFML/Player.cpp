#include "Player.hpp"
#include "Behaviour.hpp"
#include <SFML/Graphics/CircleShape.hpp>

Player::Player(const sf::Vector2f& position, Behaviour* behaviour, Team team) :
    mState(Context::State::Idle),
    mBehaviour(behaviour),
    mHeldBall(nullptr),
    mTeam(team),
    mInitialPosition(position)
{
    mSize = 50.f;
    mSpeed = 200.f;
    mInitialSpeed = mSpeed;
    

    sf::CircleShape* shape = new sf::CircleShape(10);
    shape->setRadius(mSize / 2.f);
    if (mTeam == Team::TeamA)
        mColor = sf::Color::Green;
    else
        mColor = sf::Color::Red;

    shape->setFillColor(mColor);
    shape->setOrigin(mSize / 2.f, mSize / 2.f);
    shape->setPosition(position);

    mShape = shape;
    mInitialColor = mColor;
}

Player::~Player() {
}

void Player::Update() {
    Entity::Update();
    mBehaviour->Update(this);
}

void Player::catchBall(Ball* ball) {
    if (ball && ball->isFree()) {
        mHeldBall = ball;
        ball->setHolder(this);
    }
}

void Player::releaseBall() {
    if (mHeldBall) {
        mHeldBall->setHolder(nullptr);
        mHeldBall = nullptr;
    }
}

void Player::resetToInitialPosition() {
    setPosition(mInitialPosition);
    setState(Context::State::Idle);
    if (hasBall()) {
        releaseBall();
    }
}

Context::State Player::getState() const {
    return mState;
}

void Player::setState(Context::State new_state) {
    mState = new_state;
}

void Player::setColor(sf::Color color) {

    mColor = color;
    mShape->setFillColor(mColor);
}