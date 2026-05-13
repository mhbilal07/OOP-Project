
/* 
hi, this is an optimized poduction and management system for beverage manufacturers,
We will be targeting Coca-Cola Company, Pepsi Co, Nestlé but for this project we are taking 
algerian manufacturer "Hamoud Boualem" as a reference.
It's better to take a look at "https://hamoud-boualem.com/en/" before diving into code :)

M Hassan Bilal - 70150085


*/


#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <windows.h>

using namespace std;

void setConsoleColor(int colorCode) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorCode);
}
// below part is just for text color changing;
/*
Codes for, setConsoleColor(x), where "x" can beany of integer from below,
0	Black	
1	Blue	
2	Green
3	Aqua (Cyan)
4	Red	
5	Purple (Magenta)	
6	Yellow (Brown)	
7	White (Gray)	
8	Gray (Dark Gray)	
9	Bright Blue	
10	Bright Green
11	Bright Aqua	
12	Bright Red	
13	Bright Purple	
14	Bright Yellow	
15	Bright White
*/

class Stock {
protected:
    int stockID;
    string name;
    string category;
    int quantity;
    int reorderLevel;

public:
    Stock(int id = 0, string itemName = "", string itemCategory = "", int qty = 0, int reorderLvl = 0)
        : stockID(id), name(itemName), category(itemCategory), quantity(qty), reorderLevel(reorderLvl) {}

    bool checkStock() const {
        return quantity <= reorderLevel;
    }

    void updateStock(int amount) {
        int newQuantity = quantity + amount;
        if (newQuantity < 0) {
            cout << "Error: Stock cannot be negative!" << endl;
        } else {
            quantity = newQuantity;
        }
    }

    int getQuantity() const { return quantity; }
    string getCategory() const { return category; } // New Method Added

   virtual void displayStock() const =0;
   
    void saveToFile(ofstream& file) const {
        file << stockID << "," << name << "," << category << "," << quantity << "," << reorderLevel << endl;
    }
    void saveToFile2(ofstream& file) const {
        file << stockID <<endl << name <<endl << category <<endl << quantity <<endl << reorderLevel << endl<<endl<<endl;
    }

    void loadFromFile(ifstream& file) {
        getline(file, name, ',');
        getline(file, category, ',');
        file >> stockID >> quantity >> reorderLevel;
        file.ignore();
    }
};

class RawMaterial : public Stock {
public:
    RawMaterial(int id = 0, string itemName = "", int qty = 0, int reorderLvl = 0)
        : Stock(id, itemName, "Raw Material", qty, reorderLvl) {}
        
        void displayStock() const override {
        cout << "Raw Material Stock" << endl;
        cout << "Stock ID: " << stockID << endl;
        cout << "Name: " << name << endl;
        cout << "Category: " << category << endl;
        cout << "Quantity: " << quantity << endl;
        cout << "Reorder Level: " << reorderLevel << endl;
    }
};

class FinishedProduct : public Stock {
private:
    float pricePerUnit;

public:
    FinishedProduct(int id = 0, string itemName = "", int qty = 0, int reorderLvl = 0, float price = 0.0)
        : Stock(id, itemName, "Finished Product", qty, reorderLvl), pricePerUnit(price) {}

      void displayStock() const override {
        cout << "Finished Product Stock" << endl;
        cout << "Stock ID: " << stockID << endl;
        cout << "Name: " << name << endl;
        cout << "Category: " << category << endl;
        cout << "Quantity: " << quantity << endl;
        cout << "Reorder Level: " << reorderLevel << endl;
        cout << "Price per Unit: $" << pricePerUnit << endl;
    }

    void saveToFile(ofstream& file) const {
        Stock::saveToFile(file);
        file << pricePerUnit << endl;
    }
};
class StockManagement {
private:
    Stock** stockArray;
    int stockCount;
    int capacity;

public:
    StockManagement(int initialCapacity = 10)
        : stockCount(0), capacity(initialCapacity) {
        stockArray = new Stock*[capacity];
    }

    ~StockManagement() {
        for (int i = 0; i < stockCount; i++) {
            delete stockArray[i];
        }
        delete[] stockArray;
    }

    void addStock(Stock* newStock) {
        if (stockCount == capacity) {
            capacity *= 2;
            Stock** temp = new Stock*[capacity];
            for (int i = 0; i < stockCount; i++) {
                temp[i] = stockArray[i];
            }
            delete[] stockArray;
            stockArray = temp;
        }
        stockArray[stockCount++] = newStock;
    }

    void viewStock() const {
        for (int i = 0; i < stockCount; i++) {
            cout << "--- Stock Item " << (i + 1) << " ---" << endl;
            stockArray[i]->displayStock();
            cout << endl;
        }
    }

    Stock* getStockByID(int id) const {
        for (int i = 0; i < stockCount; i++) {
            if (id == i + 1) {
                return stockArray[i];
            }
        }
        return NULL;
    }

    void updateStockQuantity(int id, int amount) {
        Stock* stockItem = getStockByID(id);
        if (stockItem != NULL) {
            stockItem->updateStock(amount);
            cout << "Stock updated successfully!" << endl;
        } else {
            cout << "Stock ID not found!" << endl;
        }
    }

    void viewStockByCategory(const string& category) const {
        bool found = false;
        for (int i = 0; i < stockCount; i++) {
            if (stockArray[i]->getCategory() == category) {
                stockArray[i]->displayStock();
                cout << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No stock items found in the category: " << category << endl;
        }
    }

     void saveAllToFile(const string& filename) const {
    try {
        ofstream file(filename.c_str());
        if (!file) {
            throw runtime_error("Error: Unable to open file for writing.");
        }
        for (int i = 0; i < stockCount; i++) {
            stockArray[i]->saveToFile(file);
        }
        file.close();
        cout << "Stock data successfully saved to " << filename << endl;
    } catch (const runtime_error& e) {
        cerr << "File operation failed: " << e.what() << endl;
    }
}
     void saveAllToFile2(const string& filename) const {
        ofstream file(filename.c_str());
        if (!file) {
            throw runtime_error("Error: Unable to open file for writing.");
        }
        file<<"\t\t Report"<<endl;
          file<<"\t----------------------"<<endl;
        for (int i = 0; i < stockCount; i++) {
            stockArray[i]->saveToFile2(file);
        }
    }
     int getStockCount() const { // Newly added method
        return stockCount;
    }
};

void addNewStock(StockManagement& stockMgmt) {
    system("cls");
     setConsoleColor(11);
    cout << "Add New Stock Menu:" << endl<<endl;
     setConsoleColor(15);
    cout << "1. Add Raw Material" << endl;
    cout << "2. Add Finished Product" << endl;
    cout << "3. Back" << endl<<endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
     cout<<endl;

    if (choice == 1) {
        int id, qty, reorderLvl;
        string name;
        cout << "Enter Raw Material ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Raw Material Name: ";
        getline(cin, name);
        cout << "Enter Quantity: ";
        cin >> qty;
        cout << "Enter Reorder Level: ";
        cin >> reorderLvl;

        RawMaterial* rawMaterial = new RawMaterial(id, name, qty, reorderLvl);
        stockMgmt.addStock(rawMaterial);
        cout << "Raw Material added successfully!" << endl;

    } else if (choice == 2) {
        int id, qty, reorderLvl;
        float price;
        string name;
        cout << "Enter Finished Product ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Finished Product Name: ";
        getline(cin, name);
        cout << "Enter Quantity: ";
        cin >> qty;
        cout << "Enter Reorder Level: ";
        cin >> reorderLvl;
        cout << "Enter Price per Unit: ";
        cin >> price;

        FinishedProduct* finishedProduct = new FinishedProduct(id, name, qty, reorderLvl, price);
        stockMgmt.addStock(finishedProduct);
        cout << "Finished Product added successfully!" << endl;

    }
     else if(choice==3)
	 {
	 	return;
		 }	

	 else {
        cout << "Invalid choice! Returning to menu..." << endl;
    }
    system("pause");
}

void stockMenu(StockManagement& stockMgmt) {
    while (true) {
        system("cls");
        setConsoleColor(11);
        cout << "STOCK MANAGEMENT MENU" << endl<<endl;
        setConsoleColor(15);
        cout << "1. View All Stock\t\t\t4. Add New Stock" << endl;
        cout << "2. View Raw Material Stock\t\t5. Update Existing Stock" << endl;
        cout << "3. View Finished Product Stock\t\t6. Save Stock to File" << endl;
        
        cout << "7. Back to Main Menu" << endl<<endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
         cout<<endl;

        switch (choice) {
        case 1:
            stockMgmt.viewStock();
            system("pause");
            break;
        case 2:
            stockMgmt.viewStockByCategory("Raw Material");
            system("pause");
            break;
        case 3:
            stockMgmt.viewStockByCategory("Finished Product");
            system("pause");
            break;
        case 4:
        
    addNewStock(stockMgmt);
    break;

            break;
        case 5:
            cout << "Enter Stock ID to update: ";
            int id, amount;
            cin >> id;
            cout << "Enter quantity change (positive to add, negative to reduce): ";
            cin >> amount;
            stockMgmt.updateStockQuantity(id, amount);
            system("pause");
            break;
        case 6:
            stockMgmt.saveAllToFile("e:\\stock_data.txt");
            cout << "Stock saved successfully!" << endl;
            system("pause");
            break;
        case 7:
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}
void scheduleProductionBatch(StockManagement& stockMgmt) {
    system("cls");
     setConsoleColor(11);
    cout << "SCHEDULE PRODUCTION BATCH" << endl<<endl;
     setConsoleColor(15);

    int productID;
    cout << "Enter Finished Product ID: ";
    cin >> productID;

    Stock* product = stockMgmt.getStockByID(productID);
    if (product == NULL || product->getCategory() != "Finished Product") {
        cout << "Invalid Finished Product ID!" << endl;
        system("pause");
        return;
    }

    int batchSize;
    cout << "Enter batch size: ";
    cin >> batchSize;

    // For simplicity, assume 1 unit of each raw material is required per unit of the finished product
    for (int i = 0; i < stockMgmt.getStockCount(); i++) {
        Stock* rawMaterial = stockMgmt.getStockByID(i + 1);
        if (rawMaterial && rawMaterial->getCategory() == "Raw Material") {
            int requiredQty = batchSize;  // Assume 1:1 ratio for simplicity
            if (rawMaterial->getQuantity() < requiredQty) {
                cout << "Insufficient raw material: " << rawMaterial->getCategory() << endl;
                system("pause");
                return;
            }
        }
    }

    // Deduct raw materials
    for (int i = 0; i < stockMgmt.getStockCount(); i++) {
        Stock* rawMaterial = stockMgmt.getStockByID(i + 1);
        if (rawMaterial && rawMaterial->getCategory() == "Raw Material") {
            rawMaterial->updateStock(-batchSize);
        }
    }

    // Add finished product to stock
    product->updateStock(batchSize);
    cout << "Production batch scheduled and completed successfully!" << endl;

    system("pause");
}


void productionMenu(StockManagement& stockMgmt) {
    while (true) {
        system("cls");
        setConsoleColor(11);
        cout << "PRODUCTION MANAGEMENT MENU" << endl<<endl;
        setConsoleColor(15);
        cout << "1. Schedule Production Batch" << endl;
        cout << "2. Back to Main Menu" << endl<<endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
         cout<<endl;

        switch (choice) {
        case 1:
            
    scheduleProductionBatch(stockMgmt);
    break;
  
        case 2:
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void notificationsMenu(StockManagement& stockMgmt) {
    while (true) {
        system("cls");
        setConsoleColor(11);
        cout << "NOTIFICATIONS AND ALERTS MENU" << endl<<endl;
        setConsoleColor(15);
        cout << "1. View Low Stock Alerts" << endl;
        cout << "2. Back to Main Menu" << endl<<endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cout<<endl;

        switch (choice) {
        case 1: {
            bool lowStockFound = false;
            for (int i = 0; i < stockMgmt.getStockCount(); i++) {
                Stock* stock = stockMgmt.getStockByID(i + 1);
                if (stock != NULL && stock->checkStock()) {
                    if (!lowStockFound) {
                        cout << "Low Stock Alerts:" << endl;
                        lowStockFound = true;
                    }
                    setConsoleColor(12);
                    stock->displayStock();
                    cout << endl;
                    setConsoleColor(11);
                }
            }
            if (!lowStockFound) {
                cout << "No low stock alerts at this time." << endl;
            }
            system("pause");
            break;
        }
        case 2:
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void mainMenu() {
    StockManagement stockMgmt;
    stockMgmt.addStock(new RawMaterial(1, "Sugar", 1000, 100));
    stockMgmt.addStock(new RawMaterial(2, "Carbonated Water", 5000, 500));
    stockMgmt.addStock(new FinishedProduct(3, "Hamoud Orange", 100, 10, 1.5));

    while (true) {
        system("cls");
        setConsoleColor(11);
        cout << "\t\t\t\tHESPERA SYSTEMS" << endl<<endl;
        setConsoleColor(15);
        cout << "1. Stock Management\t\t\t\t3. Notifications and Alerts" << endl;
        cout << "2. Production Management\t\t\t4. Report Generation" << endl;
       
        
        cout << "5. Exit" << endl<<endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
         cout<<endl;

        switch (choice) {
        case 1:
            stockMenu(stockMgmt);
            break;
        case 2:
            productionMenu(stockMgmt);
            break;
        case 3:
            notificationsMenu(stockMgmt);
            break;
            case 4:
              stockMgmt.saveAllToFile2("e:\\stock_report.txt");
            cout << "report generated" << endl;
            system("pause");
            break;
           
            
        case 5:
            system("cls");
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}
int main() {
	system("cls");
    setConsoleColor(11);
    cout << "\t\t\t\tHESPERA SYSTEMS" << endl;
    setConsoleColor(15);
   
    string user = "admin";
    string pass = "12345";
    bool login=false;
    int loginchk=0;
    string a, b;
    while(!login && loginchk<=1)
    {  
    cout << "Username : ";
    cin >> a;
    cout << "Password : ";
    cin >> b;
    
    if (a == user && b == pass)
    {
    	system("cls");
        cout << "Successfully logged in" << endl;
        mainMenu();
        login=true;
    }
    else
    {
        setConsoleColor(4);
        cout << "Incorrect Username or Password" << endl;
        loginchk++;
        if(loginchk>1)
        {
        setConsoleColor(14);
        cout<<"System locked, please contact Moderators"<<endl<<endl<<endl;
        setConsoleColor(15);
    }
        setConsoleColor(15); 
}
}
    return 0;
}

