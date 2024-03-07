USE Cards
GO

-- Player Table
CREATE TABLE Players (
    PlayerID INT PRIMARY KEY,
    FirstName VARCHAR(255),
    LastName VARCHAR(255),
    Birthday DATE,
    Gender CHAR(1) -- M for Male, F for Female
);

-- Team Table
CREATE TABLE Teams (
    TeamID INT PRIMARY KEY,
    Name VARCHAR(255),
    City VARCHAR(255),
    Members INT
);

-- Contracts between Player and Team
CREATE TABLE Contracts (
    ContractID INT PRIMARY KEY,
    TeamID INT,
    PlayerID INT,
    StartDate DATE,
    EndDate DATE,
    FOREIGN KEY (TeamID) REFERENCES Teams(TeamID),
    FOREIGN KEY (PlayerID) REFERENCES Players(PlayerID)
);

-- Card Types Table
CREATE TABLE CardTypes (
    TypeID INT PRIMARY KEY,
    Description VARCHAR(255)
);

-- Cards Table
CREATE TABLE Cards (
    CardID INT PRIMARY KEY,
    PlayerID INT,
    TypeID INT,
    PurchaseDate DATE,
    Tracer VARCHAR(255),
    DueDate DATE,
    FOREIGN KEY (PlayerID) REFERENCES Players(PlayerID),
    FOREIGN KEY (TypeID) REFERENCES CardTypes(TypeID)
);

-- Insert data into Players table
INSERT INTO Players (PlayerID, FirstName, LastName, Birthday, Gender) VALUES
(1, 'John', 'Doe', '1990-02-10', 'M'),
(2, 'Jane', 'Smith', '1985-03-20', 'F'),
(3, 'Bob', 'Johnson', '1988-04-05', 'M'),
(4, 'Alice', 'Williams', '1992-05-15', 'F'),
(5, 'Charlie', 'Brown', '1995-06-01', 'M');

-- Insert data into Teams table
INSERT INTO Teams (TeamID, Name, City, Members) VALUES
(1, 'Dragons', 'New York', 20),
(2, 'Tigers', 'Los Angeles', 22),
(3, 'Wolves', 'Chicago', 21),
(4, 'Hawks', 'Houston', 19),
(5, 'Eagles', 'Philadelphia', 23);

-- Insert data into Contracts table
INSERT INTO Contracts (ContractID, TeamID, PlayerID, StartDate, EndDate) VALUES
(1, 1, 1, '2022-01-01', '2024-12-31'),
(2, 2, 2, '2022-02-01', '2025-01-31'),
(3, 3, 3, '2023-03-01', '2026-02-28'),
(4, 4, 4, '2022-04-01', '2025-03-31'),
(5, 5, 5, '2023-05-01', '2026-04-30');

-- Insert data into CardTypes table
INSERT INTO CardTypes (TypeID, Description) VALUES
(1, 'Silver Card'),
(2, 'Gold Card'),
(3, 'Platinum Card'),
(4, 'Diamond Card'),
(5, 'Black Card');

-- Insert data into Cards table
INSERT INTO Cards (CardID, PlayerID, TypeID, PurchaseDate, Tracer, DueDate) VALUES
(1, 1, 1, '2022-01-10', 'TRC1', '2024-01-10'),
(2, 2, 2, '2022-02-20', 'TRC2', '2024-02-20'),
(3, 3, 3, '2023-03-05', 'TRC3', '2025-03-05'),
(4, 4, 4, '2022-04-15', 'TRC4', '2024-04-15'),
(5, 5, 5, '2023-05-01', 'TRC5', '2025-05-01');

SELECT * FROM Cards
SELECT * FROM CardTypes
SELECT * FROM Teams
SELECT * FROM Players
SELECT * FROM Contracts