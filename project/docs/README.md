## Kitchen Assistant Specification and Documentation

### Specification

The Kitchen Assistant is a command-line application that helps users find 
recipes based on the ingredients they have at home. 
The application allows users to search for recipes by entering the ingredients 
they have at home. 
The application will then display a list of recipes that can be made with 
the ingredients entered by the user. 
The user can then select a recipe from the list to view the recipe details, 
including the ingredients and instructions for making the recipe.

Additionally, the application allows users to save recipes to a "Cookbook", where the one 
can then perform operations such as creating, reading, updating and deleting recipes from the Cookbook.

The user can also view the list of recipes in the Cookbook, so they know what they are going to deal with .

### Documentation

The Kitchen Assistant application is built using C++.
The application uses the `nlohmann` library to parse JSON data.

The application consists of the following modules:

1. `main.cpp`: The main module of the application. This module contains the main
   function that is executed when the application is run. The main function
   initializes the application and starts the main loop of the application.


2. `CookBook.cpp` and `CookBook.hpp`: This module contains the implementation of the `CookBook` class.
   The `CookBook` class is responsible for managing the recipes in the Cookbook.
   The `CookBook` class provides methods for creating, reading, updating and deleting
   recipes in the Cookbook as well as suggesting recipes based on the ingredients.


3. `Dish.hpp`: This module contains the implementation of the `Dish` class.
   The `Dish` class represents a single dish in the Cookbook, which has the following attributes:
    1. `name`: The name of the dish.
    2. `type`: The type of the dish, e.g. 'Dinner', 'Dessert', 'Appetizer'.
    3. `cooking_time`: The single number time required to cook the dish (in minutes).
    4. `formatted cooking_time`: The time required to cook the dish (in hours and minutes).
    5. `ingredients`: The ingredients required to make the dish.
    6. `resipe`: The recipe for making the dish.


4. `Constants.hpp`: This module contains the definition of the constants used in the application,
   such as the file paths for the recipe data and the Cookbook data.


5. `Tests.md`: This module contains the test cases for the application.
   The test cases are written in a markdown format and can be run using a command-line interface or an IDE that supports C++.


### Running the Application and Tests

To run the Kitchen Assistant application, user needs to compile the source code
using a C++ compiler. 

After compiling the source code, user can run the compiled executable to start the application.

To test the application, user can run the test cases provided in the `Tests.md` file.

The test cases can be run using a command-line interface or an IDE that supports C++.

