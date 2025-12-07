#pragma once

#include <string>

#include "entity.hpp"
#include "../inventory.hpp"


class EntityChest : public BaseEntity
{
private:
	int inventorySize = 0;
	Inventory chestInventory;
	std::string inventoryFilename;
	int seed = 0;
	int texID = 2;
public:
	bool interactable = true;
	EntityChest() = default;
	EntityChest(const int& _id, const int& _size, const glm::vec3& _pos, const std::string& _inventoryFilename);
	~EntityChest() = default;

	int getTextureID();

	void toggleInventory();
	
	void saveInventory(Inventory& _inventory);

	Inventory& getChestInventory();
	unsigned int getInventorySize();
	std::vector<Item>& getChestInventoryItems();

	void setInteractable(bool _interactable);
	bool getInteractable();
};