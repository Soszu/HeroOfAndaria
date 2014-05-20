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
	GElayout_(new QHBoxLayout()),
	rscrollarea_(new QScrollArea()),
	lscrollarea_(new QScrollArea())
{
	connect(l, &GraphicsEquipment::sigReset, r, &GraphicsEquipment::reset);
	connect(r, &GraphicsEquipment::sigReset, l, &GraphicsEquipment::reset);

	connect(this, &GraphicsEquipmentExchange::sigReset, l, &GraphicsEquipment::reset);
	connect(this, &GraphicsEquipmentExchange::sigReset, r, &GraphicsEquipment::reset);

	connect(this->exchangeButton_, &ImageButton::clicked, this, &GraphicsEquipmentExchange::exchange);
	connect(l, &GraphicsEquipment::sigActive, this, &GraphicsEquipmentExchange::setActive);
	connect(r, &GraphicsEquipment::sigActive, this, &GraphicsEquipmentExchange::setActive);

	this->layout_->addWidget(this->exchangeButton_);

	this->rscrollarea_->setWidget(r_);
	this->lscrollarea_->setWidget(l_);

	this->GElayout_->addWidget(this->lscrollarea_);
	this->GElayout_->addWidget(this->rscrollarea_);
	this->GElayout_->setSizeConstraint(QLayout::SetFixedSize);
	//this->GElayout_->addWidget(this->l_);
	//this->GElayout_->addWidget(this->r_);

	this->layout_->addLayout(this->GElayout_);
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
	this->layout_->setSizeConstraint(QLayout::SetFixedSize);
//	this->addLayout(this->layout_);
//	this->setSizePolicy(QLayout::SetMinAndMaxSize);
//	this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
//	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
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

QSize GraphicsEquipment::sizeHint() const
{
	return QSize(this->gButtons_[0]->sizeHint().width() * this->span_, this->gButtons_[0]->sizeHint().height() * this->gButtons_.size() / this->span_);
}

//
//void GraphicsEquipment::paintEvent(QPaintEvent *event)
//{
//	this->QScrollArea::paintEvent(event);
//}

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
		if (this->eq()->itemList().size() > this->gButtons_.size()) {
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

int GraphicsEquipment::span()
{
	return this->span_;
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
	this->setText("Empty");
}

SlotButton::SlotButton(GraphicsItem *gi, QWidget *parent) :
	ImageButton(gi->getImgPathNormal(),
	gi->getImgPathDark(),
	"",
	parent),
	gItem_(gi)
{
	if (gi == nullptr)
		this->setText("Empty");
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

void SlotButton::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	if (isDown() || !isEnabled() || hasFocus())
		painter.drawPixmap(rect(), *(this->darkImage()));
	else
		painter.drawPixmap(rect(), *(this->normalImage()));

	QFont font = QApplication::font();
	font.setPointSize(fontPointSize());
	if (hasFocus())
		font.setBold(true);

	QPen pen(Qt::black);
	painter.setPen(pen);
	painter.setFont(font);
	painter.drawText(rect(), Qt::AlignCenter, text());
}
