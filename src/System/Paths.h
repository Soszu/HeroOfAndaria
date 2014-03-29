#ifndef PATHS_H
#define PATHS_H

#include <QtCore>

namespace Data {
	const QString DataPreffix = "data";
	namespace Images {
		const QString Preffix               = DataPreffix + "/img";

		const QString MenuBackground        = Preffix + "/menuBackground.png";
		const QString MenuButtonsNormal     = Preffix + "/menuButtonsNormal.png";
		const QString MenuButtonsDark       = Preffix + "/menuButtonsDark.png";
		const QString SmallMenuButtonNormal = Preffix + "/smallMenuButtonNormal.png";
		const QString SmallMenuButtonDark   = Preffix + "/smallMenuButtonDark.png";
		const QString NextButtonNormal      = Preffix + "/nextButtonNormal.png";
		const QString NextButtonDark        = Preffix + "/nextButtonDark.png";
		const QString PrevButtonNormal      = Preffix + "/prevButtonNormal.png";
		const QString PrevButtonDark        = Preffix + "/prevButtonDark.png";
		const QString UpButtonNormal        = Preffix + "/upButtonNormal.png";
		const QString UpButtonDark          = Preffix + "/upButtonDark.png";
		const QString DownButtonNormal	    = Preffix + "/downButtonNormal.png";
		const QString DownButtonDark        = Preffix + "/downButtonDark.png";

		const QString TileGrass = Preffix + "/tileGrass.png";

		const QString BlacksmithButton = Preffix + "/blacksmithButton.png";
		const QString InnButton        = Preffix + "/innButton.png";
		const QString LeaveTownButton  = Preffix + "/leaveTownButton.png";
		const QString OpenPlaceButton  = Preffix + "/openPlaceButton.png";
		const QString TownBackground   = Preffix + "/townBackground.png";

		const QString TownPoor = Preffix + "/townPoor.png";
	}
}

#endif // PATHS_H
