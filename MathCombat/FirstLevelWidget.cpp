#include "FirstLevelWidget.h"

FirstLevelWidget::FirstLevelWidget(QWidget *parent)
	: QWidget(parent)
	, m_ui(new Ui::FirstLevelWidgetClass())
{
	m_ui->setupUi(this);

	// Нужно чтобы сцена получала события с клавиатуры
	m_ui->graphicsView->setFocus();
	m_ui->graphicsView->setFocusPolicy(Qt::StrongFocus); 

	m_ui->graphicsView->setTransformationAnchor(
    QGraphicsView::NoAnchor);

	m_ui->graphicsView->setResizeAnchor(
    QGraphicsView::NoAnchor);

	m_scene = new GameScene(this);

	m_ui->graphicsView->setScene(m_scene);
}

FirstLevelWidget::~FirstLevelWidget()
{
	delete m_ui;
}
