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

class GameScene : public QGraphicsScene
{
	Q_OBJECT

public:
	explicit GameScene(std::vector<std::pair<Monster*, QPointF>> vectorMonsters, 
		                 QString BackgroundTheme, QObject* parent = nullptr);

	void keyPressEvent(QKeyEvent* event) override;
	void keyReleaseEvent(QKeyEvent* event) override;

signals:
	void CombatSignal();

private slots:
	void updateGame();

private:

	Player* m_player;

	QTimer* m_gameTimer;

	bool m_movingLeft;
	bool m_movingRight;

	bool m_combatBegin = false;

	std::vector<std::pair<Monster*, QPointF>> m_vectorMonsters;
};

#endif // GAMESCENE_H
