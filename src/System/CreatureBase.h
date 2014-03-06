#ifndef CREATUREBASE_H
#define CREATUREBASE_H

class CreatureBase
{
public:
	CreatureBase();
	
	int baseHitPoints() const;
	int baseMagicPoints() const;
	
	int strength() const;
	int endurance() const;
	int agility() const;
	int intelligence() const;

private:
	int uid_;
	
	int baseHitPoints_;
	int baseMagicPoints_;
	
	int strength_;
	int endurance_;
	int agility_;
	int intelligence_;
};

#endif // CREATUREBASE_H
