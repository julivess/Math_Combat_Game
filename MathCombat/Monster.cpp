#include "Monster.h"


Monster::Monster(Difficulty diff, QObject* parent)
	: QObject(parent), m_difficulty(diff)
{
	m_currentFrame = 0;

	// Спрайты в зависимости от сложности
	UpdateSprites();

	// Начальная картинка монмтра
	setPixmap(idleRight);

	animationTimer = new QTimer(this);

	// Таймер для обновления картинок монстра (Обновляется как только истекает timeout)
	connect(animationTimer, &QTimer::timeout, this, &Monster::nextFrame);
}

Monster::~Monster()
{
}

void Monster::startAnimation()
{
	if (!animationTimer->isActive())
		animationTimer->start(600);
}

void Monster::stopAnimation()
{
	animationTimer->stop(); // останавливает таймер
}

// Меняет картинки в порядке 1 -> 2 -> 3 -> 4 -> 5 -> 4 -> 3 -> 2 -> 1 -> ... и т.д.
void Monster::nextFrame()
{
	setPixmap(Frames[m_currentFrame]);

	if (m_animationForward)
	{
		m_currentFrame++;

		if (m_currentFrame >= Frames.size() - 1)
		{
			m_animationForward = false;
		}
	}
	else
	{
		m_currentFrame--;

		if (m_currentFrame <= 0)
		{
			m_animationForward = true;
		}
	}
}

Difficulty Monster::getDifficulty() const
{
	return m_difficulty;
}

/// Для каждого уровня сложности свой внешний вид монстра
void Monster::UpdateSprites()
{
	switch (m_difficulty) {
	case(Difficulty::Easy):
		Frames.append(QPixmap(":/MathCombat/Resource/MonsterLeftEasy.png"));
		Frames.append(QPixmap(":/MathCombat/Resource/MonsterLeft2Easy.png"));
		Frames.append(QPixmap(":/MathCombat/Resource/MonsterProfileEasy.png"));
		Frames.append(QPixmap(":/MathCombat/Resource/MonsterRight2Easy.png"));
		Frames.append(QPixmap(":/MathCombat/Resource/MonsterRightEasy.png"));

		idleRight = QPixmap(":/MathCombat/Resource/MonsterRightEasy.png");
		idleLeft = QPixmap(":/MathCombat/Resource/MonsterLeftEasy.png");
		break;
	case(Difficulty::Medium):
	  Frames.append(QPixmap(":/MathCombat/Resource/MonsterLeftMedium.png"));
		Frames.append(QPixmap(":/MathCombat/Resource/MonsterLeft2Medium.png"));
		Frames.append(QPixmap(":/MathCombat/Resource/MonsterProfileMedium.png"));
		Frames.append(QPixmap(":/MathCombat/Resource/MonsterRight2Medium.png"));
		Frames.append(QPixmap(":/MathCombat/Resource/MonsterRightMedium.png"));

		idleRight = QPixmap(":/MathCombat/Resource/MonsterRightMedium.png");
		idleLeft = QPixmap(":/MathCombat/Resource/MonsterLeftMedium.png");
		break;
	case(Difficulty::Hard):
	  Frames.append(QPixmap(":/MathCombat/Resource/MonsterLeftHard.png"));
		Frames.append(QPixmap(":/MathCombat/Resource/MonsterLeft2Hard.png"));
		Frames.append(QPixmap(":/MathCombat/Resource/MonsterProfileHard.png"));
		Frames.append(QPixmap(":/MathCombat/Resource/MonsterRight2Hard.png"));
		Frames.append(QPixmap(":/MathCombat/Resource/MonsterRightHard.png"));

		idleRight = QPixmap(":/MathCombat/Resource/MonsterRightHard.png");
		idleLeft = QPixmap(":/MathCombat/Resource/MonsterLeftHard.png");
		break;
	}
}