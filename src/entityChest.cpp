#include "../include/entity/entityChest.hpp"

#include "../include/programLogger.hpp"
using ProgramLogger::log;
using ProgramLogger::LogLevel;

#include "../include/inventoryManager.hpp"
InventoryManager inventoryManager = InventoryManager(10);


EntityChest::EntityChest(const int& _id, const int& _size, const glm::vec3& _pos, const std::string& _inventoryFilename)
{
	log("creating EntityChest with ID: " + std::to_string(_id));
	//generateEmptyInventory();
	setEntityID(_id);
	setEntityPosition(_pos);
	inventorySize = _size;
	inventoryFilename = _inventoryFilename;

	inventoryManager.createRandomInventoy(_id, chestInventory, _size);

}

unsigned int EntityChest::getInventorySize()
{
	if(chestInventory.getInventorySize() == 0)
	{
		log("Inventory size is zero! Have you initialized it yet?", LogLevel::ERROR);
		return -1;
	}
	return chestInventory.getInventorySize();
}

void EntityChest::toggleInventory()
{
	
	if(getChestInventory().canShowInventory())
	{
		log("Opening inventory of ID: " + std::to_string(getChestInventory().getInventoryID()));
		//getChestInventory().setShowInv(false);
		//toggleInv = false;
		for (Item item : getChestInventoryItems())
		{
			log("Inventory contents: " + std::to_string(item.getItemID()));
		}
		return;
	}
}

void EntityChest::saveInventory(Inventory& _inventory)
{
	log("Saving inventory of ID: " + std::to_string(_inventory.getInventoryID()));
	inventoryManager.saveInventory(_inventory);
}

int EntityChest::getTextureID()
{
	return texID;
}

Inventory& EntityChest::getChestInventory()
{
	return chestInventory;
}

std::vector<Item>& EntityChest::getChestInventoryItems()
{
	if (getChestInventory().getInventorySize() == 0) 
	{
		log("Inventory size is zero!", LogLevel::ERROR);
		static std::vector<Item> emptyItems;
		return emptyItems;
	}
	return getChestInventory().getInventoryArray();
}

void EntityChest::setInteractable(bool _interactable)
{
	interactable = _interactable;
}

bool EntityChest::getInteractable()
{
	return interactable;
}