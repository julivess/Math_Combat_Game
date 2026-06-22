#include "GameScene.h"

GameScene::GameScene(std::vector<std::pair<Monster*, QPointF>> vectorMonsters, QString BackgroundTheme, QObject* parent)
	: QGraphicsScene(parent), m_vectorMonsters(vectorMonsters)
{

	m_movingLeft = false;
	m_movingRight = false;

	// ===== ФОН =====

	QPixmap background(BackgroundTheme);

	addPixmap(background);

	setSceneRect(background.rect());
	// ===== ИГРОК =====

	m_player = new Player(this);
	addItem(m_player);
	m_player->setPos(120, 550);

	// ===== МОНСТЕР =====
	//m_monster = new Monster(Monster::Difficulty::Easy, this);

	for (auto monster : m_vectorMonsters)
	{
		addItem(monster.first);
		monster.first->setPos(monster.second);
		monster.first->startAnimation();
	}

	// ===== GAME LOOP =====

	m_gameTimer = new QTimer(this);
	connect(m_gameTimer, &QTimer::timeout, this, &GameScene::updateGame);

	m_gameTimer->start(15);
}

// =====================================================
// ОБНОВЛЕНИЕ ИГРЫ
// =====================================================

void GameScene::updateGame()
{
	// ===== ДВИЖЕНИЕ ВПРАВО =====

	if (m_movingRight)
	{
		m_player->moveRight();
		m_player->startAnimation();
		//m_monster->moveLeft();
	}

	// ===== ДВИЖЕНИЕ ВЛЕВО =====

	if (m_movingLeft)
	{
		m_player->moveLeft();
		m_player->startAnimation();
		//m_monster->moveRight();
	}

	// ===== ЕСЛИ НЕ ДВИГАЕТСЯ =====

	if (!m_movingLeft && !m_movingRight)
	{
		m_player->stopAnimation();
	}

	QList<QGraphicsItem*> collisions =
		m_player->collidingItems();

	for (QGraphicsItem* item : collisions)
	{
		Monster* monster =
			dynamic_cast<Monster*>(item);

		if (monster)
		{
			qDebug() << "Столкновение!";

			emit CombatSignal();

			m_combatBegin = true;
			m_movingLeft = false;
			m_movingRight = false;
			return;
		}
	}

}

// =====================================================
// НАЖАТИЕ КЛАВИШ
// =====================================================

void GameScene::keyPressEvent(QKeyEvent* event)
{
	// если идет бой - не обрабатываем события с клавиатуры
	if (m_combatBegin)
	{
		return;
	}
	// Чтобы событие не спамилось
	if (event->isAutoRepeat())
	{
		return;
	}

	// ===== D =====

	if (event->key() == Qt::Key_D)
	{
		m_movingRight = true;
	}

	// ===== A =====

	if (event->key() == Qt::Key_A)
	{
		m_movingLeft = true;
	}


	QGraphicsScene::keyPressEvent(event);
}

// =====================================================
// ОТПУСКАНИЕ КЛАВИШ
// =====================================================

void GameScene::keyReleaseEvent(QKeyEvent* event)
{
	if (event->isAutoRepeat())
	{
		return;
	}

	// ===== D =====

	if (event->key() == Qt::Key_D)
	{
		m_movingRight = false;
	}

	// ===== A =====

	if (event->key() == Qt::Key_A)
	{
		m_movingLeft = false;
	}

	QGraphicsScene::keyReleaseEvent(event);
}
