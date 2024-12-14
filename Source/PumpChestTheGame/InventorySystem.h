// Written by Juno Suwanduan

#ifndef INVENTORY_SYSTEM_H
#define INVENTORY_SYSTEM_H

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

class InventoryItem {
public:
    InventoryItem(const std::string& name, const std::string& description, int quantity, double weight);
    std::string GetName() const;
    std::string GetDescription() const;
    int GetQuantity() const;
    double GetWeight() const;
    void AddQuantity(int amount);
    void RemoveQuantity(int amount);
    void SetWeight(double newWeight);

private:
    std::string name;
    std::string description;
    int quantity;
    double weight;
};

class InventorySystem {
public:
    void AddItem(const InventoryItem& item);
    void RemoveItem(const std::string& itemName);
    InventoryItem* FindItem(const std::string& itemName);
    void DisplayInventory() const;
    double CalculateTotalWeight() const;
    void SaveInventory(const std::string& filename) const;
    void LoadInventory(const std::string& filename);

private:
    std::unordered_map<std::string, InventoryItem> items;
};

#endif