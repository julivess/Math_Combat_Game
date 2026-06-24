#pragma once

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QVector>
#include <QPixmap>
#include <QTimer>

// Класс главного героя.
class Player : public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT

public:

	Player(QObject* parent);
	~Player();

	void moveLeft();	// Двигает героя влево с анимацией бега
	void moveRight(); // Двигает героя вправо с анимайией бега

	void startAnimation(); // Начинает анимацию бега
	void stopAnimation();  // Останавливает анимацию бега
	 
	void nextFrame(); // Меняет спрайт

private:
	QVector<QPixmap> walkRightFrames;  // Вектор спрайтов для бега вправо 
	QVector<QPixmap> walkLeftFrames;   // Вектор спрайтов для бега влево

	QPixmap idleRight;  // Стоит на месте смотрив право 
	QPixmap idleLeft;   // Стоит на месте смотрит влево

	QTimer* animationTimer;  // Nfqvth fybvfwbb

	int currentFrame;  // Индекс текущей картинки анимации
	bool movingLeft;   // Происходит движение влево 
	bool movingRight;  // Происходит движение вправо

};
