
How to Use: 

- Clone or download the project files.
- Open the project file named as main2.cpp in Dev-C++ (recommended) or any other C++ IDE/compiler that
  supports the Windows console (e.g., Code::Blocks, Visual Studio, or g++ on Windows).
- Compile and run the main2.cpp file.
- Use the console menu to interact with the system.


Important Notes:

- If you encounter an error such as "id returned 1 exit status", follow these steps:
- Copy all the code provided in the main2.cpp file.
- Create a new .cpp file in your IDE.
- Paste the code into the new file and compile it again.


The provided code in main.cpp demonstrates the use of several Object-Oriented Programming (OOP) principles,
 which are foundational to its design and implementation. Here's a breakdown:

1. Encapsulation
The Stock, RawMaterial, and FinishedProduct classes encapsulate data members (stockID, name, quantity, etc.)
and provide access through member functions (updateStock, checkStock, displayStock, etc.).
Access specifiers (private, protected, public) are used to control visibility and restrict direct access to internal data.

2. Inheritance
RawMaterial and FinishedProduct inherit from the Stock base class. This demonstrates hierarchical inheritance
where both derived classes share the attributes and behaviors of the Stock class while adding or overriding 
functionality specific to their types.

3. Polymorphism
Compile-time Polymorphism: Overloading is demonstrated by methods like saveToFile in Stock and 
FinishedProduct, where each class has its version of the function.
Run-time Polymorphism: The StockManagement class uses an array of pointers to the base class (Stock** stockArray).
This allows storing objects of both RawMaterial and FinishedProduct, enabling polymorphic behavior.

4. Abstraction
Classes like Stock, RawMaterial, and FinishedProduct abstract the complex details of stock management into
simple, manageable units, hiding the internal implementation details from the user.
Functions such as scheduleProductionBatch and viewStockByCategory further simplify the high-level
operations for managing stocks and production.

5. Dynamic Memory Management
The StockManagement class dynamically manages an array of Stock pointers using new and delete.
This demonstrates efficient resource handling and scalability.

6. Reusability
The modular design of the classes and their methods promotes code reuse. For example, addStock,
updateStock, and viewStock in StockManagement can work with any Stock object or its derivatives (RawMaterial and FinishedProduct).

7. Modularity
The project is divided into multiple logical components, such as stock management, production management, and notification handling, enhancing clarity and separation of concerns.

That’s all for now.