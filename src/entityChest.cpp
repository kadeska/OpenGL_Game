#include "../include/entity/entityChest.hpp"
#include "../include/programLogger.hpp"
using ProgramLogger::log;
using ProgramLogger::LogLevel;
#include "../include/FileManager.hpp"
using FileManager::saveInventoryToFile;
using FileManager::readInventoryFromFile;

Inventory::Inventory(int _id, int _size, std::vector<ItemType>& items)
{
	this->inventoryID = _id;
	this->inventorySize = _size;
	this->items = items;

	
}

EntityChest::EntityChest(int _id, int _size, glm::vec3 _pos, std::string _inventoryFilename)
{
	log("creating EntityChest... ");
	generateEmptyInventory();
	this->setEntityID(_id);
	this->setEntityPosition(_pos);
	this->inventorySize = _size;
	this->inventoryFilename = _inventoryFilename;
}

void EntityChest::generateEmptyInventory()
{
	log("Creating empty inventory ... ");
	std::vector<ItemType> items = std::vector<ItemType>{ItemType::EMPTY};
	chestInventory = Inventory(this->getEntityID(), (int)items.size(), items);
}

void EntityChest::generateRandomInventory()
{
	log("creating random inventoy ... ");
	std::vector<ItemType> items = std::vector<ItemType>
	{ 
		ItemType::EMPTY,
		ItemType::FOOD,
		ItemType::GOLD
	};
	chestInventory = Inventory(this->getEntityID(), (int)items.size(), items);
}

void EntityChest::generateInventoryFromFile()
{
	log("Loading inventory from file ... ");
	// initialize an empty vector of items (inventory items)
	std::vector<ItemType> items = std::vector<ItemType>{ItemType::EMPTY};
	// data to be written from file
	std::string data;
	// read inventory file and load to data string
	readInventoryFromFile(this->inventoryFilename, data);
	// finaly set the chest inventory with the data string that was read from file
	this->chestInventory = Inventory(this->getEntityID(), (int)items.size(), items);
}

void EntityChest::setInventorySize(int _size)
{
	this->inventorySize = _size;
}

int EntityChest::getInventorySize()
{
	if(!inventorySize) 
	{
		log("Inventory size is zero! Have you initialized it yet?", LogLevel::WARNING);
		return -1;
	}
	return inventorySize;
}

void EntityChest::openInventory()
{
	for (ItemType item : getChestInventoryItems()) 
	{
		log("Inventory contents: " + std::to_string((int)item));
	}
}

void EntityChest::saveInventory(Inventory _inventory)
{
	std::string data = convertInventoryToString(*&_inventory.getItems());
	saveInventoryToFile(this->inventoryFilename, data);
}
