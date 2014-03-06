#ifndef ITEMBASE_H
#define ITEMBASE_H

class ItemBase
{
public:
	ItemBase();
	
	void setType(int type);
	int type() const;
	
	void setMinStrength(int strength);
	int minStrength() const;
	
	void setMinIntelligence(int intelligence);
	int minIntelligence() const;
	
private:
	int uid_;
	
	//TODO zmienić type na enuma.
	int type_;
	int minStrength_;
	int minIntelligence_;	
};

#endif // ITEMBASE_H
