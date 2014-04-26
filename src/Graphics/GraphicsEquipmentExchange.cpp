#include "Graphics/GraphicsEquipmentExchange.h"

#include "System/Paths.h"
#include "Graphics/GraphicsFactory.h"
GraphicsEquipmentExchange::GraphicsEquipmentExchange()
{

}
GraphicsEquipmentExchange::GraphicsEquipmentExchange(GraphicsEquipment *l, GraphicsEquipment *r) :
	l_(l),
	r_(r),
	active_(nullptr),
	exchangeButton_(new ImageButton(Data::path(Data::ImagePath::ExchangeButtonNormal),
	Data::path(Data::ImagePath::ExchangeButtonDark),
	"",
	this)),
	layout_(new QVBoxLayout(this)),
	GElayout_(new QHBoxLayout())
{
	connect(l, &GraphicsEquipment::sigReset, r, &GraphicsEquipment::reset);
	connect(r, &GraphicsEquipment::sigReset, l, &GraphicsEquipment::reset);

	connect(this, &GraphicsEquipmentExchange::sigReset, l, &GraphicsEquipment::reset);
	connect(this, &GraphicsEquipmentExchange::sigReset, r, &GraphicsEquipment::reset);

	connect(this->exchangeButton_, &ImageButton::clicked, this, &GraphicsEquipmentExchange::exchange);
	connect(l, &GraphicsEquipment::sigActive, this, &GraphicsEquipmentExchange::setActive);
	connect(r, &GraphicsEquipment::sigActive, this, &GraphicsEquipmentExchange::setActive);

	this->layout_->addWidget(this->exchangeButton_);

	this->layout_->addWidget(this->l_);
	this->layout_->addWidget(this->r_);

	//this->layout_->addLayout(this->GElayout_);
}

GraphicsEquipment * GraphicsEquipmentExchange::notActive()
{
	if (this->active_ == nullptr)
		return active_;
	if (this->active_ == this->l_)
		return this->r_;
	if (this->active_ == this->r_)
		return this->l_;
	return nullptr;
}

void GraphicsEquipmentExchange::exchange()
{
	if ((this->active_ == nullptr)
		|| (this->active_->activeSlot() == nullptr)
		|| (this->active_->activeSlot()->gItem() == nullptr)){
		return;
	}
	GraphicsEquipment *from = this->active_;
	GraphicsEquipment *to = this->notActive();
	if (to->receiveItem(from, from->activeSlot()->gItem())) {
		from->removeItem(from->activeSlot());
	}
	emit sigReset();
}

void GraphicsEquipmentExchange::setActive(GraphicsEquipment *active)
{
	this->active_ = active;
}


/*
 *	GraphicsEquipment
 */

GraphicsEquipment::GraphicsEquipment(EquipmentCarrier *eq, int span, QWidget *parent) :
	QWidget(parent),
	eq_(eq),
	activeSlot_(nullptr),
	layout_(new QGridLayout(this)),
	buttonMapper_(new QSignalMapper(this)),
	span_(span)
{
	this->layout_->setHorizontalSpacing(0);
	this->layout_->setVerticalSpacing(0);
	for (auto i : eq->itemList()) {
		this->addSlot(GraphicsFactory::get(i));
	}
	int free = span_ - (eq_->itemList().size() % span_);
	for (int i = 0; i < free; i++) {
		this->addSlot(nullptr);
	}
	connect(
		this->buttonMapper_,
		static_cast<void (QSignalMapper::*)(QWidget *)>(&QSignalMapper::mapped),
		this,
		&GraphicsEquipment::processClick
	);
}

void GraphicsEquipment::paintEvent(QPaintEvent *event)
{
	this->QWidget::paintEvent(event);
}

void GraphicsEquipment::rearrangeSlots()
{
}

void GraphicsEquipment::addSlot(GraphicsItem *gi)
{
	SlotButton *sb;
	if (gi != nullptr)
		sb = new SlotButton(gi, this);
	else
		sb = new SlotButton(this);

	//connect(sb, &SlotButton::clicked, this->buttonMapper_, &QSignalMapper::map);
	connect(sb, SIGNAL(clicked()), this->buttonMapper_, SLOT(map()));
	this->buttonMapper_->setMapping(sb, sb);

	this->gButtons_.append(sb);

	int row = this->layout_->count()/this->span_;
	int col = this->layout_->count() % this->span_;
	this->layout_->addWidget(sb, row, col);
}

EquipmentCarrier * GraphicsEquipment::eq()
{
	return this->eq_;
}

void GraphicsEquipment::processClick(QWidget *sB)
{
	activeSlot_ = static_cast<SlotButton *>(sB);
	emit sigReset();
	emit sigActive(this);
}

void GraphicsEquipment::reset()
{
	this->activeSlot_ = nullptr;
}

bool GraphicsEquipment::receiveItem(GraphicsEquipment *from, GraphicsItem *gItem)
{
	if (moveItem(from->eq(), this->eq(), gItem->item())) {
		if (this->eq()->itemList().size() == this->gButtons_.size()) {
			addSlot(gItem);
			for (int i = 0; i < this->span_-1; i++) {
				addSlot(nullptr);
			}
			this->rearrangeSlots();
		}
		else {
			for (auto sb : this->gButtons_) {
				if (sb->gItem() == nullptr) {
					sb->setGItem(gItem);
					break;
				}
			}
		}
		return true;
	}
	return false;
}

void GraphicsEquipment::removeItem(SlotButton *sb)
{
	sb->setGItem(nullptr);
}


SlotButton *GraphicsEquipment::activeSlot()
{
	return this->activeSlot_;
}

/*
 *	Slot Button
 */

SlotButton::SlotButton(QWidget *parent) :
	ImageButton(Data::path(Data::ImagePath::EmptySlotNormal),
	Data::path(Data::ImagePath::EmptySlotDark),
	"",
	parent),
	gItem_(nullptr)
{
}

SlotButton::SlotButton(GraphicsItem *gi, QWidget *parent) :
	ImageButton(gi->getImgPathNormal(),
	gi->getImgPathDark(),
	"",
	parent),
	gItem_(gi)
{
}

void SlotButton::setGItem(GraphicsItem *gi)
{
	if (gi != nullptr) {
		this->loadImages(gi->getImgPathNormal(), gi->getImgPathDark());
		this->setText("");
		this->gItem_ = gi;
	} else {
		this->gItem_ = nullptr;
		this->setText("Empty");
		this->loadImages(Data::path(Data::ImagePath::EmptySlotNormal),
			Data::path(Data::ImagePath::EmptySlotDark));

	}
}

GraphicsItem * SlotButton::gItem()
{
	return this->gItem_;
}
