#include "PreviewWidget.h"

PreviewWidget::PreviewWidget(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::PreviewWidgetClass())
{
	ui->setupUi(this);
	connect(ui->buttonMewPlay, &QPushButton::clicked, this, &PreviewWidget::StartNewGame);

}

PreviewWidget::~PreviewWidget()
{
	delete ui;
}
