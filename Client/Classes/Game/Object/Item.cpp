#include "Item.h"
USING_NS_CC;
Item::Item()
{

}

Item::~Item()
{

}

Item* Item::create(ValueMap def)
{
	auto item = new Item();
	if (item && item->initWithMap(def))
	{
		return item;
	}

	return nullptr;
}

Item* Item::create(int id, TYPE typeId, std::string name, std::string des, std::string textureName, int norPrice, float specPrice)
{
	auto item = new Item();
	if (item && item->init(id, typeId, name, des, textureName, norPrice, specPrice));
	{
		return item;
	}
}

bool Item::init(int id, TYPE typeId,  std::string name, std::string des, std::string textureName, int norPrice, float specPrice)
{
	this->setId(id);
	setName(name);
	setType(typeId);
	setDes(des);
	setTextureName(textureName);
	setNorPrice(norPrice);
	setSpecPrice(specPrice);
	return true;
}

bool Item::initWithMap(ValueMap def)
{
	this->setId(def["ID"].asInt());
	this->setType(def["TypeId"].asInt());
	this->setName(def["Name"].asString());
	this->setDes(def["Des"].asString());
	this->setTextureName(def["Texture"].asString());
	this->setNorPrice(def["NorPrice"].asInt());
	this->setSpecPrice(def["SpecPrice"].asFloat());

	return true;
}