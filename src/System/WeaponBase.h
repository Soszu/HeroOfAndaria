#ifndef WEAPONBASE_H
#define WEAPONBASE_H

class WeaponBase
{
public:
	WeaponBase();
	
	void setBaseDamage(int damage);
	int baseDamage() const;
	
	void setHitRatio(int hitRatio);
	int hitRatio() const;
	
	//TODO zmienić type na enuma
	void setType(int type);
	int weaponType() const;
	
private:
	int uid_;
	
	int baseDamage_;
	int hitRatio_;
	int weaponType_;
};

#endif // WEAPONBASE_H
