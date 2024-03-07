USE CloudGaming
GO

CREATE TABLE Users
(
    Uid INT PRIMARY KEY IDENTITY,
    Name varchar(50),
    Email varchar(50) NOT NULL,
    Age int CHECK (Age >= 13),
    Country varchar(50),
    SubscribedToNewsletter bit
)

CREATE TABLE VideoGameCompanies
(
    Vid INT PRIMARY KEY IDENTITY,
    Name varchar(50),
    YearFounded int CHECK (YearFounded >= 1850),
    CEO varchar(50),
    NoOfReleasedGames int CHECK (NoOfReleasedGames >= 1)
)

 
CREATE TABLE Genres
(
    Genid INT PRIMARY KEY IDENTITY,
    Name varchar(50) NOT NULL,
)

 
CREATE TABLE Games
(
    Gid INT PRIMARY KEY IDENTITY,
    Name varchar(50),
    Description varchar(300),
    YearOfRelease int CHECK (YearOfRelease >= 1950),
    NoOfPlayers int CHECK (NoOfPlayers >= 1),
    Rating int CHECK (Rating >= 0 AND Rating <=5),
    NoOfDownloads int,
    Vid int FOREIGN KEY REFERENCES VideoGameCompanies(Vid),
	Genid int FOREIGN KEY REFERENCES Genres(Genid)
)
 
CREATE TABLE UsersGames
(
    Uid INT FOREIGN KEY REFERENCES Users(Uid),
    Gid INT FOREIGN KEY REFERENCES Games(Gid),
    CONSTRAINT pk_UsersGames PRIMARY KEY (Uid, Gid)
)

 
CREATE TABLE Communities
(
    Cid INT FOREIGN KEY REFERENCES Games(Gid),
    Name varchar(50),
    NoOfUsers int NOT NULL,
    CONSTRAINT pk_GameCommunity PRIMARY KEY(Cid)
)
 
CREATE TABLE UsersCommunities
(
    Uid INT FOREIGN KEY REFERENCES Users(Uid),
    Cid INT FOREIGN KEY REFERENCES Communities(Cid),
    CONSTRAINT pk_UserCommunity PRIMARY KEY (Uid, Cid)
)

CREATE TABLE Achievements
(
    Aid INT PRIMARY KEY IDENTITY,
	Name varchar(50),
    PercentageOfCompletion int CHECK (PercentageOfCompletion >= 0 AND PercentageOfCompletion <= 100),
    Gid int FOREIGN KEY REFERENCES Games(Gid)
)
ALTER TABLE Achievements
ALTER COLUMN PercentageOfCompletion int CHECK (PercentageOfCompletion >= 0 AND PercentageOfCompletion <= 100)
 
CREATE TABLE UsersAchievements
(
    Uid INT FOREIGN KEY REFERENCES Users(Uid),
    Aid INT FOREIGN KEY REFERENCES Achievements(Aid),
    dateObtained date NOT NULL,
    CONSTRAINT pk_UsersAchievements PRIMARY KEY (Uid, Aid)
)
 
CREATE TABLE Esports
(
    Eid INT FOREIGN KEY REFERENCES Games(Gid),
    Name varchar(50),
    DateOfStart date NOT NULL,
    DateOfEnd date NOT NULL,
    NoOfParticipants int CHECK (NoOfParticipants >= 0),
    Winner varchar(50),
    RunnerUp varchar(50),
    Prize int,
    CONSTRAINT pk_GameEsports PRIMARY KEY(Eid)
)
