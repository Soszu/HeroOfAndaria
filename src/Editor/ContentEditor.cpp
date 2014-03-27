#include "Editor/ContentEditor.h"

ContentEditor::ContentEditor(const QString& name) : name_(name)
{
}

QString ContentEditor::name() const
{
	return name_;
}

QWidget * ContentEditor::widget() const
{
	return widget_;
}
