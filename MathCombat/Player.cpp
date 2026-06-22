#include "Player.h"

Player::Player(QObject* parent)
	: QObject(parent)
{
	currentFrame = 0;

	movingLeft = false;
	movingRight = false;

	// ===== ЗАГРУЗКА СПРАЙТОВ =====

	// Ходьба вправо
	walkRightFrames.append(QPixmap(":/MathCombat/Resource/HeroRight1.png"));
	walkRightFrames.append(QPixmap(":/MathCombat/Resource/HeroRight2.png"));
	walkRightFrames.append(QPixmap(":/MathCombat/Resource/HeroRight3.png"));
	walkRightFrames.append(QPixmap(":/MathCombat/Resource/HeroRight4.png"));

	// Ходьба влево
	walkLeftFrames.append(QPixmap(":/MathCombat/Resource/HeroLeft1.png"));
	walkLeftFrames.append(QPixmap(":/MathCombat/Resource/HeroLeft2.png"));
	walkLeftFrames.append(QPixmap(":/MathCombat/Resource/HeroLeft3.png"));
	walkLeftFrames.append(QPixmap(":/MathCombat/Resource/HeroLeft4.png"));

	// Idle спрайты
	idleRight = QPixmap(":/MathCombat/Resource/HeroRight1.png");
	idleLeft = QPixmap(":/MathCombat/Resource/HeroLeft1.png");

	// Стартовый спрайт
	setPixmap(idleRight);

	// ===== ТАЙМЕР АНИМАЦИИ =====

	animationTimer = new QTimer(this);

	connect(animationTimer, &QTimer::timeout, this, &Player::nextFrame);

	animationTimer->start(15);
}

Player::~Player()
{}

void Player::moveRight()
{
	if (x() + pixmap().width() < 1774)
	{
		movingRight = true;
		movingLeft = false;

		moveBy(5, 0);
	}
}

void Player::moveLeft()
{
	if (x() > 0)
	{
		movingLeft = true;
		movingRight = false;

		moveBy(-5, 0);
	}
}

void Player::startAnimation()
{
	if (!animationTimer->isActive())
	{
		animationTimer->start(120);
	}
}

void Player::stopAnimation()
{
	animationTimer->stop();

	if (movingRight)
	{
		setPixmap(idleRight);
	}

	if (movingLeft)
	{
		setPixmap(idleLeft);
	}
}

void Player::nextFrame()
{
	currentFrame++;

	// ===== АНИМАЦИЯ ВПРАВО =====

	if (movingRight)
	{
		setPixmap(
			walkRightFrames[
				currentFrame % walkRightFrames.size()
			]
		);
	}

	// ===== АНИМАЦИЯ ВЛЕВО =====

	if (movingLeft)
	{
		setPixmap(
			walkLeftFrames[
				currentFrame % walkLeftFrames.size()
			]
		);
	}
}

