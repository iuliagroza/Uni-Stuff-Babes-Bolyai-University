# 💻 Assignment 09
## Requirements
For the program you developed for Assignment 06-08 implement persistent storage for all entities using file-based repositories. Also implement a `settings.properties` file to configure your application. Observations:
1. You must implement two additional repository sets: one using text files for storage, and one using binary files (e.g. using object serialization with [Pickle](https://docs.python.org/3.8/library/pickle.html)).
2. The program must work the same way using in-memory repositories, text-file repositories and binary file repositories.
3. The decision of which repositories are employed, as well as the location of the repository input files will be made in the program’s `settings.properties` file. An example is below:

    a. `settings.properties` for loading from memory (input files are not required):
    ```
    repository = inmemory
    cars = “”
    clients = “”
    rentals = “”
    ```
    b. `settings.properties` for loading from binary files, for someone who also created a GUI:
    ```
    repository = binaryfiles
    cars = “cars.pickle”
    clients = “clients.pickle”
    rentals = “rentals.pickle”
    ui = “GUI”
    ```

**NB!** If your Assignment 06-08 uses layered architecture properly, these are the only places where source code needs to change:
1. *Repository layer* – for implementing the required code.
2. *Application start module* – to load the properties file and start the required repositories.

## Bonus possibility (0.1p, deadline week 12)
- In addition to the file-based implementations above, implement the repository layer to use JSON or XML files for storage (at your choice).
- Create a `Settings` class into which you load the data from the `settings.properties` file. Then, the application start module decides which modules are started by examining the `settings` object. This further decouples the properties input file from the application.

## Bonus possibility (0.1p, deadline week 12)
- Implement a database-backed (SQL or NoSQL) repository. Use the database system’s update functionalities properly (don’t rewrite the entire database at each operation).
