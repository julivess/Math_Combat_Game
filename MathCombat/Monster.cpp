#include "Monster.h"

Monster::Monster(Difficulty diff, QObject* parent)
    : QObject(parent), difficulty(diff)
{
    currentFrame = 0;

    movingLeft = false;
    movingRight = false;

    // Спрайты
    walkRightFrames.append(QPixmap(":/sprites/monster_right1.png"));
    walkRightFrames.append(QPixmap(":/sprites/monster_right2.png"));

    walkLeftFrames.append(QPixmap(":/sprites/monster_left1.png"));
    walkLeftFrames.append(QPixmap(":/sprites/monster_left2.png"));

    idleRight = QPixmap(":/sprites/monster_right1.png");
    idleLeft = QPixmap(":/sprites/monster_left1.png");

    setPixmap(idleRight);

    animationTimer = new QTimer(this);

    connect(animationTimer,
            &QTimer::timeout,
            this,
            &Monster::nextFrame);
}

Monster::~Monster()
{
}

void Monster::moveRight()
{
    movingRight = true;
    movingLeft = false;

    moveBy(2, 0);
}

void Monster::moveLeft()
{
    movingLeft = true;
    movingRight = false;

    moveBy(-2, 0);
}

void Monster::startAnimation()
{
    if (!animationTimer->isActive())
        animationTimer->start(150);
}

void Monster::stopAnimation()
{
    animationTimer->stop();

    if (movingRight)
        setPixmap(idleRight);

    if (movingLeft)
        setPixmap(idleLeft);
}

void Monster::nextFrame()
{
    currentFrame++;

    if (movingRight)
    {
        setPixmap(
            walkRightFrames[currentFrame % walkRightFrames.size()]
        );
    }

    if (movingLeft)
    {
        setPixmap(
            walkLeftFrames[currentFrame % walkLeftFrames.size()]
        );
    }
}