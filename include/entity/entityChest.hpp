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
	Inventory(int _id, int _size, std::vector<ItemType>& items);
	~Inventory() = default;
	inline std::vector<ItemType> getItems()
	{
		return items;
	}
};

class EntityChest : public BaseEntity
{
private:
	Inventory* chestInventory;
	std::string inventoryFilename;
	int inventorySize;
	int seed;
public:
	bool interactable = true;
	EntityChest(int _id, int _size, glm::vec3 _pos, std::string _inventoryFilename);
	~EntityChest() = default;

	void generateEmptyInventory();
	void generateRandomInventory();
	void generateInventoryFromFile();

	void setInventorySize(int _size);

	int getInventorySize();
	std::vector<ItemType> getInventoryItems();

	void openInventory();
	void saveInventory(std::string& _inventoryData);


	inline std::vector<ItemType> getChestInventoryItems()
	{
		return chestInventory->getItems();
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