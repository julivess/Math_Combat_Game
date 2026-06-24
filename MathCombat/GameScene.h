#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include <QKeyEvent>
#include <QPointF>

#include "Player.h"
#include "Monster.h"
#include <vector>
#include <utility>

// класс сцены. Отображает главного героя, монстров и фон, обрабатывает нажатия на клавищи A и D
class GameScene : public QGraphicsScene
{
	Q_OBJECT

public:
	explicit GameScene(std::vector<std::pair<Monster*, QPointF>> vectorMonsters,
		QString BackgroundTheme, QPointF playerPos, QObject* parent = nullptr);

	~GameScene();

	void keyPressEvent(QKeyEvent* event) override;	// Обрабатывает события с клавиатуры (клавиша была зажата)
	void keyReleaseEvent(QKeyEvent* event) override;	// Обрабатывает событие с клавиатуры (клавиша была отпущена)


	bool AllMonstersDefeated(); // Вернет true если все монстры на сцене были побеждены
	void ContinueGame(); // Продолжит игру после победы над монстром

signals:
	void CombatSignal(Difficulty diff); //Сигнал о том что начался бой. diff - уровень сложности монстра. 
	//Отправляется когда происходит столкновение с монстром

private slots:
	void updateGame(); // Обновляет игру

private:

	Player* m_player;  // главный герой
	QTimer* m_gameTimer;  //Таймер для обновления сцены

	bool m_movingLeft;   // Идет ли главный герой влево в данный момент
	bool m_movingRight;  // Идет ли герой вправо в данный момент

	bool m_combatBegin = false;  // True если бой идет

	std::vector<std::pair<Monster*, QPointF>> m_vectorMonsters;  // Вектор всех монстров на сцене

	int numberDefeatedMonsters = 0; // количество побежденных монстров 
};

#endif // GAMESCENE_H
