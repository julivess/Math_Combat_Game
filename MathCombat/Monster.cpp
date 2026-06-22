#include "Monster.h"

Monster::Monster(Difficulty diff, QObject* parent)
    : QObject(parent), m_difficulty(diff)
{
    m_currentFrame = 0;

    movingLeft = false;
    movingRight = false;

    // Спрайты
    Frames.append(QPixmap(":/MathCombat/Resource/MonsterLeft.png"));
    Frames.append(QPixmap(":/MathCombat/Resource/MonsterLeft2.png"));
    Frames.append(QPixmap(":/MathCombat/Resource/MonsterProfile.png"));
    Frames.append(QPixmap(":/MathCombat/Resource/MonsterRight2.png"));
    Frames.append(QPixmap(":/MathCombat/Resource/MonsterRight.png"));

    idleRight = QPixmap(":/MathCombat/Resource/MonsterRight.png");
    idleLeft = QPixmap(":/MathCombat/Resource/MonsterLeft.png");

    setPixmap(idleRight);

    animationTimer = new QTimer(this);

    connect(animationTimer, &QTimer::timeout, this, &Monster::nextFrame);
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
        animationTimer->start(600);
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
    setPixmap(Frames[m_currentFrame]);

    if(m_animationForward)
    {
        m_currentFrame++;

        if(m_currentFrame >= Frames.size() - 1)
        {
            m_animationForward = false;
        }
    }
    else
    {
        m_currentFrame--;

        if(m_currentFrame <= 0)
        {
            m_animationForward = true;
        }
    }
}

Monster::Difficulty Monster::getDifficulty() const
{
    return m_difficulty;
}

void Monster::UpdateSprites()
{
  if (m_difficulty == Difficulty::Easy)
  {
    return;
  }
}