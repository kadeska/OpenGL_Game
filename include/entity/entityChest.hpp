#pragma once
#include "entity.hpp"

#include <string>

enum class ItemType 
{
	EMPTY,
	WOOD,
	STONE,
	IRON,
	GOLD,
	DIAMOND,
	FOOD,
	POTION,
	WEAPON,
	ARMOR
};

class Inventory 
{
private:
	int inventoryID;
	int inventorySize;
	std::vector<ItemType> items;
	
public:
	bool showInventory;
	Inventory(int _id, int _size, std::vector<ItemType>& _items) 
	{
		inventoryID = _id;
		inventorySize = _size;
		items = _items;
		//setShowInv(false);
	}
	Inventory() = default;
	~Inventory() = default;
	std::vector<ItemType> getItems()
	{
		return items;
	}
	int getInventoryID()
	{
		return inventoryID;
	}
	// returns whether the inventory should be shown or not
	bool showInv() { return showInventory; }
	// toggles the showInventory boolean
	void setShowInv(bool _showInv) 
	{
		showInventory = _showInv;
		//log("showInventory: " + std::to_string(showInventory));
	}
};

class EntityChest : public BaseEntity
{
private:
	std::vector<ItemType> initialInv = { ItemType::EMPTY };
	Inventory chestInventory;// = Inventory(-1, 0, initialInv);
	std::string inventoryFilename;
	int inventorySize;
	int seed;
	int texID = 2;
public:
	bool interactable = true;
	EntityChest() = default;
	EntityChest(int _id, int _size, glm::vec3 _pos, std::string _inventoryFilename);
	~EntityChest() = default;

	void generateEmptyInventory();
	void generateRandomInventory();
	void generateInventoryFromFile();

	void setInventorySize(int _size);

	int getInventorySize();

	void toggleInventory();
	void saveInventory(Inventory _inventory);

	inline int getTexID()
	{
		return texID;
	}

	Inventory& getChestInventory()
	{
		return chestInventory;
	}
	inline std::vector<ItemType> getChestInventoryItems()
	{
		return chestInventory.getItems();
	}

	inline void setInteractable(bool _interactable)
	{
		interactable = _interactable;
	}
	inline bool getInteractable()
	{
		return interactable;
	}

	inline std::string convertInventoryToString(std::vector<ItemType>& items)
	{
		std::string inventoryData;
		for (ItemType& item : items) {
			inventoryData += std::to_string(static_cast<int>(item)) + "\n";
		}
		return inventoryData;
	}
};