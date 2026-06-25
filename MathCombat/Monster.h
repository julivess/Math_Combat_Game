#pragma once

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QVector>
#include <QPixmap>
#include <QTimer>

#include "Utils.h"

// Класс монстра. Поддерживает 3 уровня сложности монстра
class Monster : public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT

public:

	explicit Monster(Difficulty difficulty, QObject* parent = nullptr);
	~Monster();

	void startAnimation(); // Начать анимацию 
	void stopAnimation();  // Остановить анимацию

	void nextFrame(); // Показывает следующую картинку спрайта

	Difficulty getDifficulty() const; // Возвращает сложность монстра

private:
	Difficulty m_difficulty; // Сложность монстра

	void UpdateSprites(); // Добавляет спрайты по уровню сложности монстра

	QVector<QPixmap> Frames; // Вектор спрайтов

	QPixmap idleRight; // Смотрит вправо
	QPixmap idleLeft;  // Смотрит влево

	QTimer* animationTimer; // Таймер анимации

	int m_currentFrame; // Индекс текущей картинки в векторе 

	bool m_animationForward = true; // Монстр поворачивается вперет (true) или назад (false)
};
