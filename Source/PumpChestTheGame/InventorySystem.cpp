// Written by Juno Suwanduan

#include "InventorySystem.h"
#include <fstream>

InventoryItem::InventoryItem(const std::string& name, const std::string& description, int quantity, double weight)
    : name(name), description(description), quantity(quantity), weight(weight) {}

std::string InventoryItem::GetName() const {
    return name;
}

std::string InventoryItem::GetDescription() const {
    return description;
}

int InventoryItem::GetQuantity() const {
    return quantity;
}

double InventoryItem::GetWeight() const {
    return weight;
}

void InventoryItem::AddQuantity(int amount) {
    quantity += amount;
}

void InventoryItem::RemoveQuantity(int amount) {
    if (quantity >= amount) {
        quantity -= amount;
    }
}

void InventoryItem::SetWeight(double newWeight) {
    weight = newWeight;
}

void InventorySystem::AddItem(const InventoryItem& item) {
    items[item.GetName()] = item;
}

void InventorySystem::RemoveItem(const std::string& itemName) {
    items.erase(itemName);
}

InventoryItem* InventorySystem::FindItem(const std::string& itemName) {
    auto it = items.find(itemName);
    return (it != items.end()) ? &it->second : nullptr;
}

void InventorySystem::DisplayInventory() const {
    for (const auto& pair : items) {
        std::cout << "Item: " << pair.second.GetName() 
                  << "\nDescription: " << pair.second.GetDescription() 
                  << "\nQuantity: " << pair.second.GetQuantity() 
                  << "\nWeight: " << pair.second.GetWeight() << "\n\n";
    }
}

double InventorySystem::CalculateTotalWeight() const {
    double totalWeight = 0.0;
    for (const auto& pair : items) {
        totalWeight += pair.second.GetWeight() * pair.second.GetQuantity();
    }
    return totalWeight;
}

void InventorySystem::SaveInventory(const std::string& filename) const {
    std::ofstream file(filename);
    for (const auto& pair : items) {
        file << pair.second.GetName() << "," << pair.second.GetDescription() << "," 
             << pair.second.GetQuantity() << "," << pair.second.GetWeight() << "\n";
    }
    file.close();
}

void InventorySystem::LoadInventory(const std::string& filename) {
    std::ifstream file(filename);
    std::string name, description;
    int quantity;
    double weight;
    while (file >> name >> description >> quantity >> weight) {
        items[name] = InventoryItem(name, description, quantity, weight);
    }
    file.close();
}