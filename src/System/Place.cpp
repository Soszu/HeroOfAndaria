#include "System/Place.h"

Place::Place(const QString &name)
	: name_(name)
{

}

QString Place::name() const
{
	return this->name_;
}
