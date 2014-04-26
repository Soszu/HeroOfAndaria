#ifndef PATHS_H
#define PATHS_H

#include <QtCore>

namespace Data {
	enum class ImagePath : quint16 {

		MenuBackground,
		MenuButtonsNormal,
		MenuButtonsDark,
		SmallMenuButtonNormal,
		SmallMenuButtonDark,
		NextButtonNormal,
		NextButtonDark,
		PrevButtonNormal,
		PrevButtonDark,
		UpButtonNormal,
		UpButtonDark,
		DownButtonNormal,
		DownButtonDark,

		BottomPanelBackground,
		SidePanelBackground,
		PanelCloseButtonNormal,
		PanelCloseButtonDark,
		SkillsButtonNormal,
		SkillsButtonDark,
		QuestsButtonNormal,
		QuestsButtonDark,
		InventoryButtonNormal,
		InventoryButtonDark,
		HpBar,
		HpBarBackground,

		TileGrass,

		BlacksmithButton,
		InnButton,
		LeaveTownButton,
		OpenPlaceButton,
		TownBackground,

		TownPoor,

		LocationKennel,

		Player,
		Wolf,

		PlayerDead,
		WolfDead,

		Sword,

		EmptySlotNormal,
		EmptySlotDark,

		ItemNormal,
		ItemDark,

		ExchangeButtonNormal,
		ExchangeButtonDark,
	};

	QString path(ImagePath name);
}

#endif // PATHS_H
