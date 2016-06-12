#ifndef __ITEM__H__
#define __ITEM__H__
#include "cocos2d.h"
USING_NS_CC;
class Item
{
public:
	enum TYPE
	{
		GAME,
		SHOP

	};
	Item();
	~Item();
	static Item* create(ValueMap def);
	static Item* create(int id, TYPE typeId, std::string name, std::string des, std::string textureName, int norPrice, float specPrice);

	bool init(int id, TYPE typeId , std::string name, std::string des, std::string textureName, int norPrice, float specPrice);
	bool initWithMap(ValueMap def);

	void setName(std::string name){ name_ = name; };
	std::string getName() const { return name_; }

	void setType(int typeId){ type_ = (TYPE)typeId; }
	TYPE getType() const { return type_; }

	void setId(int id){ id_ = id; }
	int getId() const { return id_; }

	void setDes(std::string des){ des_ = des; }
	std::string getDes()const { return des_; }

	void setNorPrice(int norPrice){ norPrice_ = norPrice; }
	int getNorPrice() const { return norPrice_; }

	void setSpecPrice(float price) { specPrice_ = price; }
	float getSpecPrice()const{ return specPrice_; }

	void setTextureName(std::string name){ textureName_ = name; }
	std::string getTextureName()const{ return textureName_; }

private:
	int id_;
	int norPrice_;
	float specPrice_;
	TYPE type_;
	std::string des_;
	std::string name_;
	std::string textureName_;
};
#endif