#include "System/Item.h"

Item::Item()
{}

int Item::weight() const
{
	return base_->weight();
}

int Item::price() const
{
	return base_->price();
}
