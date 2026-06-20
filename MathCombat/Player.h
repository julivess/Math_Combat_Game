#pragma once

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QVector>
#include <QPixmap>
#include <QTimer>

class Player  : public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT

public:

	Player(QObject *parent);
	~Player();

	void moveLeft();
	void moveRight();

	void startAnimation();
	void stopAnimation();

	void nextFrame();

private:
	QVector<QPixmap> walkRightFrames;
	QVector<QPixmap> walkLeftFrames;

	QPixmap idleRight;
	QPixmap idleLeft;

	QTimer* animationTimer;

	int currentFrame;

	bool movingLeft;
	bool movingRight;

};
