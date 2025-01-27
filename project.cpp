#include <iostream>
#include <fstream>
    using namespace std;

    const int MAX_PRODUCTS = 100;

    struct Product {
        int id;
        string name;
        string category;
        double price;
        int quantity;
    };

    Product inventory[MAX_PRODUCTS];
    int productCount = 0;

    void addProduct() {
    if (productCount >= MAX_PRODUCTS) {
        cout << "Inventory is full. Cannot add more products." << endl;
        return;
    }

    Product newProduct;
    cout << "Enter ID: ";
    cin >> newProduct.id;

    for (int i = 0; i < productCount; i++) {
        if (inventory[i].id == newProduct.id) {
            cout << "Error: A product with this ID already exists." << endl;
            return;
        }
    }

    cout << "Enter product name: ";
    cin >> newProduct.name;
    cout << "Enter product category: ";
    cin >> newProduct.category;
    cout << "Enter product price:$ ";
    cin >> newProduct.price;
    cout << "Enter product quantity: ";
    cin >> newProduct.quantity;

    if (newProduct.quantity < 50) {
        cout << "Low stock warning: Quantity is less than 50!" << endl;
    } else if (newProduct.quantity > 100) {
        cout << "Overstock warning: Quantity is more than 100!" << endl;
    }

    inventory[productCount] = newProduct;
    productCount++;
    cout << "Product added successfully!" << endl;
}


    void removeProduct() {
        int id;
        cout << "Enter product ID to remove: ";
        cin >> id;

        for (int i = 0; i < productCount; i++) {
            if (inventory[i].id == id) {
                for (int j = i; j < productCount - 1; j++) {
                    inventory[j] = inventory[j + 1];
                }
                productCount--;
                cout << "Product removed successfully!" << endl;
                return;
            }
        }

        cout << "Product not found." << endl;
    }

    void findProduct() {
        int id;
        cout << "Enter product ID to find: ";
        cin >> id;

        for (int i = 0; i < productCount; i++) {
            if (inventory[i].id == id) {
                cout << "ID: " << inventory[i].id << endl;
                cout << "Name: " << inventory[i].name << endl;
                cout << "Category: " << inventory[i].category << endl;
                cout << "Price: $ " << inventory[i].price << endl;
                cout << "Quantity: " << inventory[i].quantity << endl;
                return;
            }
        }

        cout << "Product not found." << endl;
    }

    void updateProduct() {
    int id;
    cout << "Enter product ID to update: ";
    cin >> id;

    for (int i = 0; i < productCount; i++) {
        if (inventory[i].id == id) {
            cout << "Enter new product name: ";
            cin >> inventory[i].name;
            cout << "Enter new product category: ";
            cin >> inventory[i].category;
            cout << "Enter new product price: $ ";
            cin >> inventory[i].price;
            cout << "Enter new product quantity: ";
            cin >> inventory[i].quantity;

            if (inventory[i].quantity < 50) {
                cout << "Low stock warning: Quantity is less than 50!" << endl;
            } else if (inventory[i].quantity > 100) {
                cout << "Overstock warning: Quantity is more than 100!" << endl;
            }

            cout << "Product updated successfully!" << endl;
            return;
        }
    }

    cout << "Product not found." << endl;
}


    void viewProducts() {
        if (productCount == 0) {
            cout << "No products in the inventory." << endl;
            return;
        }

        for (int i = 0; i < productCount; i++) {
            cout << "ID: " << inventory[i].id << endl;
            cout << "Name: " << inventory[i].name << endl;
            cout << "Category: " << inventory[i].category << endl;
            cout << "Price: $ " << inventory[i].price << endl;
            cout << "Quantity: " << inventory[i].quantity << endl;
            cout << "----------------------------------------" << endl;
        }
    }

    void saveInventoryToFile() {
        ofstream outFile("inventory.csv");

        if (!outFile) {
            cout << "Error opening file for writing." << endl;
            return;
        }

        outFile << "ID,Name,Category,Price,Quantity" << endl;
        for (int i = 0; i < productCount; i++) {
            outFile << inventory[i].id << ","
                    << inventory[i].name << ","
                    << inventory[i].category << ","
                    << inventory[i].price << ","
                    << inventory[i].quantity << endl;
        }

        outFile.close();
        cout << "Inventory saved to file successfully!" << endl;
    }

    void loadInventoryFromFile() {
        ifstream inFile("inventory.csv");

        if (!inFile) {
            cout << "Error opening file for reading." << endl;
            return;
        }

        string header;
        getline(inFile, header); 

        productCount = 0;
        while (inFile && productCount < MAX_PRODUCTS) {
            Product p;
            char comma;
            inFile >> p.id >> comma;
            getline(inFile, p.name, ',');
            getline(inFile, p.category, ',');
            inFile >> p.price >> comma >> p.quantity;

            if (inFile) {
                inventory[productCount++] = p;
            }
        }

        inFile.close();
        cout << "Inventory loaded from file successfully!" << endl;
    }

    int main() {
        char choice;
        do {
            cout << "\nInventory Management System" << endl;
            cout << "1. Add a product" << endl;
            cout << "2. Remove a product" << endl;
            cout << "3. Find a product" << endl;
            cout << "4. Update a product" << endl;
            cout << "5. View all products" << endl;
            cout << "6. Save inventory to file" << endl;
            cout << "7. Load inventory from file" << endl;
            cout << "Q. Quit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case '1':
                addProduct();
                break;
            case '2':
                removeProduct();
                break;
            case '3':
                findProduct();
                break;
            case '4':
                updateProduct();
                break;
            case '5':
                viewProducts();
                break;
            case '6':
                saveInventoryToFile();
                break;
            case '7':
                loadInventoryFromFile();
                break;
            case 'q':
            case 'Q':
                cout << "Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 'q' && choice != 'Q');

        return 0;
    }
