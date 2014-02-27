#ifndef CREATUREBASE_H
#define CREATUREBASE_H

class CreatureBase
{
public:
	CreatureBase();
	
	int healthPoints() const;
	int magicPoints() const;
	
	int strength() const;
	int endurance() const;
	int agility() const;

private:
	int uid;
	
	int healthPoints_;
	int magicPoints_;
	
	int strength_;
	int endurance_;
	int agility_;
};

#endif // CREATUREBASE_H
