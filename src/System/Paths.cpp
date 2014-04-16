#include "System/Paths.h"

QString Data::path(ImagePath name)
{
	static const QString DataPreffix = QCoreApplication::applicationDirPath() + "/../data";

	static const QString ImgPreffix            = DataPreffix + "/img";

	static const QString MenuBackground        = ImgPreffix + "/menuBackground.png";
	static const QString MenuButtonsNormal     = ImgPreffix + "/menuButtonsNormal.png";
	static const QString MenuButtonsDark       = ImgPreffix + "/menuButtonsDark.png";
	static const QString SmallMenuButtonNormal = ImgPreffix + "/smallMenuButtonNormal.png";
	static const QString SmallMenuButtonDark   = ImgPreffix + "/smallMenuButtonDark.png";
	static const QString NextButtonNormal      = ImgPreffix + "/nextButtonNormal.png";
	static const QString NextButtonDark        = ImgPreffix + "/nextButtonDark.png";
	static const QString PrevButtonNormal      = ImgPreffix + "/prevButtonNormal.png";
	static const QString PrevButtonDark        = ImgPreffix + "/prevButtonDark.png";
	static const QString UpButtonNormal        = ImgPreffix + "/upButtonNormal.png";
	static const QString UpButtonDark          = ImgPreffix + "/upButtonDark.png";
	static const QString DownButtonNormal	    = ImgPreffix + "/downButtonNormal.png";
	static const QString DownButtonDark        = ImgPreffix + "/downButtonDark.png";

	static const QString BottomPanelBackground  = ImgPreffix + "/bottomPanel.png";
	static const QString SidePanelBackground    = ImgPreffix + "/sidePanel.png";
	static const QString PanelCloseButtonNormal = ImgPreffix + "/panelCloseButtonNormal.png";
	static const QString PanelCloseButtonDark   = ImgPreffix + "/panelCloseButtonDark.png";
	static const QString SkillsButtonNormal     = ImgPreffix + "/skillsButtonNormal.png";
	static const QString SkillsButtonDark	     = ImgPreffix + "/skillsButtonDark.png";
	static const QString QuestsButtonNormal     = ImgPreffix + "/questsButtonNormal.png";
	static const QString QuestsButtonDark       = ImgPreffix + "/questsButtonDark.png";
	static const QString InventoryButtonNormal  = ImgPreffix + "/inventoryButtonNormal.png";
	static const QString InventoryButtonDark    = ImgPreffix + "/inventoryButtonDark.png";
	static const QString HpBar                  = ImgPreffix + "/hpBar.png";
	static const QString HpBarBackground        = ImgPreffix + "/hpBarBackground.png";

	static const QString TileGrass = ImgPreffix + "/tileGrass.png";

	static const QString BlacksmithButton = ImgPreffix + "/blacksmithButton.png";
	static const QString InnButton        = ImgPreffix + "/innButton.png";
	static const QString LeaveTownButton  = ImgPreffix + "/leaveTownButton.png";
	static const QString OpenPlaceButton  = ImgPreffix + "/openPlaceButton.png";
	static const QString TownBackground   = ImgPreffix + "/townBackground.png";

	static const QString TownPoor = ImgPreffix + "/townPoor2.png";

	switch (name) {
		case ImagePath::MenuBackground:        return MenuBackground;
		case ImagePath::MenuButtonsNormal:     return MenuButtonsNormal;
		case ImagePath::MenuButtonsDark:       return MenuButtonsDark;
		case ImagePath::SmallMenuButtonNormal: return SmallMenuButtonNormal;
		case ImagePath::SmallMenuButtonDark:   return SmallMenuButtonDark;
		case ImagePath::NextButtonNormal:      return NextButtonNormal;
		case ImagePath::NextButtonDark:        return NextButtonDark;
		case ImagePath::PrevButtonNormal:      return PrevButtonNormal;
		case ImagePath::PrevButtonDark:        return PrevButtonDark;
		case ImagePath::UpButtonNormal:        return UpButtonNormal;
		case ImagePath::UpButtonDark:          return UpButtonDark;
		case ImagePath::DownButtonNormal:      return DownButtonNormal;
		case ImagePath::DownButtonDark:        return DownButtonDark;

		case ImagePath::BottomPanelBackground:  return BottomPanelBackground;
		case ImagePath::SidePanelBackground:    return SidePanelBackground;
		case ImagePath::PanelCloseButtonNormal: return PanelCloseButtonNormal;
		case ImagePath::PanelCloseButtonDark:   return PanelCloseButtonDark;
		case ImagePath::SkillsButtonNormal:     return SkillsButtonNormal;
		case ImagePath::SkillsButtonDark:       return SkillsButtonDark;
		case ImagePath::QuestsButtonNormal:     return QuestsButtonNormal;
		case ImagePath::QuestsButtonDark:       return QuestsButtonDark;
		case ImagePath::InventoryButtonNormal:  return InventoryButtonNormal;
		case ImagePath::InventoryButtonDark:    return InventoryButtonDark;
		case ImagePath::HpBar:                  return HpBar;
		case ImagePath::HpBarBackground:        return HpBarBackground;

		case ImagePath::TileGrass: return TileGrass;

		case ImagePath::BlacksmithButton: return BlacksmithButton;
		case ImagePath::InnButton:        return InnButton;
		case ImagePath::LeaveTownButton:  return LeaveTownButton;
		case ImagePath::OpenPlaceButton:  return OpenPlaceButton;
		case ImagePath::TownBackground:   return TownBackground;

		case ImagePath::TownPoor: return TownPoor;
	}

	return QString();
}