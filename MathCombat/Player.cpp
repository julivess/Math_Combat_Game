#include "Player.h"

Player::Player(QObject *parent)
    : QObject(parent)
{
    currentFrame = 0;

    movingLeft = false;
    movingRight = false;

    // ===== «¿√–”« ¿ —œ–¿…“Œ¬ =====

    // ’Ó‰¸·‡ ‚Ô‡‚Ó
    walkRightFrames.append(QPixmap(":/MathCombat/Resource/HeroRight1.png"));
    walkRightFrames.append(QPixmap(":/MathCombat/Resource/HeroRight2.png"));
    walkRightFrames.append(QPixmap(":/MathCombat/Resource/HeroRight3.png"));
    walkRightFrames.append(QPixmap(":/MathCombat/Resource/HeroRight4.png"));

    // ’Ó‰¸·‡ ‚ÎÂ‚Ó
    walkLeftFrames.append(QPixmap(":/MathCombat/Resource/HeroLeft1.png"));
    walkLeftFrames.append(QPixmap(":/MathCombat/Resource/HeroLeft2.png"));
    walkLeftFrames.append(QPixmap(":/MathCombat/Resource/HeroLeft3.png"));
    walkLeftFrames.append(QPixmap(":/MathCombat/Resource/HeroLeft4.png"));

    // Idle ÒÔ‡ÈÚ˚
    idleRight = QPixmap(":/MathCombat/Resource/HeroRight1.png");
    idleLeft = QPixmap(":/MathCombat/Resource/HeroLeft1.png");

    // —Ú‡ÚÓ‚˚È ÒÔ‡ÈÚ
    setPixmap(idleRight);

    // ===== “¿…Ã≈– ¿Õ»Ã¿÷»» =====

    animationTimer = new QTimer(this);

    connect(animationTimer,
            &QTimer::timeout,
            this,
            &Player::nextFrame);

    animationTimer->start(15);
}

Player::~Player()
{

}

void Player::moveRight()
{
    movingRight = true;
    movingLeft = false;

    moveBy(5, 0);
}

void Player::moveLeft()
{
    movingLeft = true;
    movingRight = false;

    moveBy(-5, 0);
}

void Player::startAnimation()
{
    if(!animationTimer->isActive())
    {
        animationTimer->start(120);
    }
}

void Player::stopAnimation()
{
    animationTimer->stop();

    if(movingRight)
    {
        setPixmap(idleRight);
    }

    if(movingLeft)
    {
        setPixmap(idleLeft);
    }
}

void Player::nextFrame()
{
    currentFrame++;

    // ===== ¿Õ»Ã¿÷»ﬂ ¬œ–¿¬Œ =====

    if(movingRight)
    {
        setPixmap(
            walkRightFrames[
                currentFrame % walkRightFrames.size()
            ]
        );
    }

    // ===== ¿Õ»Ã¿÷»ﬂ ¬À≈¬Œ =====

    if(movingLeft)
    {
        setPixmap(
            walkLeftFrames[
                currentFrame % walkLeftFrames.size()
            ]
        );
    }
}

