USE CloudGaming
GO
 
-- a. Modify the type of a column
-- DO
CREATE OR ALTER PROCEDURE setUsersSubscribedToNewsletterToInt AS
    ALTER TABLE Users 
	ALTER COLUMN SubscribedToNewsletter int
    SELECT 'Modified SubscribedToNewsletter of Users to int.'
GO
EXECUTE setUsersSubscribedToNewsletterToInt
GO

-- UNDO
CREATE OR ALTER PROCEDURE setUsersSubscribedToNewsletterToBit AS
    ALTER TABLE Users 
	ALTER COLUMN SubscribedToNewsletter bit
    SELECT 'Modified SubscribedToNewsletter of Users to bit.'
GO
EXECUTE setUsersSubscribedToNewsletterToBit
GO
 
-- b. Add/remove a column
-- DO
CREATE OR ALTER PROCEDURE addPopularityToGenres AS
    ALTER TABLE Genres 
	ADD Popularity int
    SELECT 'Added column Popularity to Genres.'
GO
EXECUTE addPopularityToGenres
GO

-- REDO
CREATE OR ALTER PROCEDURE removePopularityFromGenres AS
    ALTER TABLE Genres 
	DROP COLUMN Popularity
    SELECT 'Removed column Popularity from Genres.'
GO
EXECUTE removePopularityFromGenres
GO
 
-- c. Add/remove a DEFAULT constraint
-- DO
CREATE OR ALTER PROCEDURE addDefaultToNoOfUsersForCommunities AS
    ALTER TABLE Communities 
	ADD CONSTRAINT defaultNoOfUsers 
	DEFAULT(0) FOR NoOfUsers
    SELECT 'Added default constraint to NoOfUsers for Communities.'
GO
EXECUTE addDefaultToNoOfUsersForCommunities
GO

-- REDO
CREATE OR ALTER PROCEDURE removeDefaultOfNoOfUsersFromCommunities AS
    ALTER TABLE Communities 
	DROP CONSTRAINT defaultNoOfUsers
    SELECT 'Removed default of NoOfUsers from Communities.'
GO
EXECUTE removeDefaultOfNoOfUsersFromCommunities
GO
 
--d. Add/remove a primary key
-- DO
CREATE OR ALTER PROCEDURE addAwardsPrimaryKey AS
    CREATE TABLE Awards
	(
        Aid int NOT NULL,
        Name varchar(50),
        Edition int NOT NULL,
		Gid int FOREIGN KEY REFERENCES Games(Gid)
	)
    ALTER TABLE Awards
        ADD CONSTRAINT AWARDS_PRIMARY_KEY PRIMARY KEY(Aid)
    SELECT 'Added primary key Aid to Awards.'
GO
EXECUTE addAwardsPrimaryKey
GO

-- UNDO
CREATE OR ALTER PROCEDURE removeAwardsPrimaryKey AS
    ALTER TABLE Awards
        DROP CONSTRAINT AWARDS_PRIMARY_KEY
    DROP TABLE Awards
    SELECT 'Removed primary key Aid from Awards.'
GO 
EXECUTE removeAwardsPrimaryKey
GO

--e. Add/remove a candidate key
-- DO
CREATE OR ALTER PROCEDURE addUsersCandidateKey AS
    ALTER TABLE Users
        ADD CONSTRAINT USERS_CANDIDATE_KEY UNIQUE(Uid, Name, Email)
    SELECT 'Added candidate key for Users.'
GO
EXECUTE addUsersCandidateKey
GO

-- UNDO
CREATE OR ALTER PROCEDURE removeUsersCandidateKey AS
    ALTER TABLE Users
        DROP CONSTRAINT USERS_CANDIDATE_KEY
    SELECT 'Removed candidate key of Users.'
GO
EXECUTE removeUsersCandidateKey
GO
 
--f. Add/remove a foreign key
-- DO
CREATE OR ALTER PROCEDURE addVidForeignKeyForEsports AS
    ALTER TABLE Esports
        ADD Vid int
    ALTER TABLE Esports
        ADD CONSTRAINT ESPORTS_ORGANIZER_FOREIGN_KEY FOREIGN KEY(Vid) REFERENCES VideoGameCompanies(Vid)
    SELECT 'Added VideoGameCompanies id foreign key for Esports.'
GO
EXECUTE addVidForeignKeyForEsports
GO

-- UNDO
CREATE OR ALTER PROCEDURE removeVidForeignKeyFromEsports AS
    ALTER TABLE Esports
        DROP CONSTRAINT ESPORTS_ORGANIZER_FOREIGN_KEY
    ALTER TABLE Esports
        DROP COLUMN Vid
    SELECT 'Removed VideoGameCompanies id foreign key from Esports.'
GO
EXECUTE removeVidForeignKeyFromEsports
GO
 
--g. Create/drop a table
-- DO
CREATE OR ALTER PROCEDURE createEsportsChampionsTable AS
    CREATE TABLE EsportsChampions
	(
        ECid INT PRIMARY KEY NOT NULL,
        Name varchar(50),
        Edition int,
        POSITION varchar(50),
		Eid int FOREIGN KEY REFERENCES Esports(Eid)
	)
    SELECT 'Created EsportsChampions table.'
GO
EXECUTE createEsportsChampionsTable
GO

-- UNDO
CREATE OR ALTER PROCEDURE dropEsportsChampionsTable AS
    DROP TABLE EsportsChampions
    SELECT 'Dropped EsportsChampions table.'
GO
EXECUTE dropEsportsChampionsTable
GO

-- Version table setup
CREATE TABLE VersionTable 
(
    Version INT
)
 
INSERT INTO VersionTable VALUES (1)
 
CREATE TABLE ProcedureTable
(
    FirstVersion INT,
    LastVersion INT,
    ProcedureName VARCHAR(MAX),
    PRIMARY KEY(FirstVersion, LastVersion)
)
 
INSERT INTO ProcedureTable VALUES (1, 2, 'setUsersSubscribedToNewsletterToInt'),
								   (2, 1, 'setUsersSubscribedToNewsletterToBit'),
								   (2, 3, 'addPopularityToGenres'),
								   (3, 2, 'removePopularityFromGenres'),
								   (3, 4, 'addDefaultToNoOfUsersForCommunities'),
								   (4, 3, 'removeDefaultOfNoOfUsersFromCommunities'),
								   (4, 5, 'addAwardsPrimaryKey'),
								   (5, 4, 'removeAwardsPrimaryKey'),
								   (5, 6, 'addUsersCandidateKey'),
								   (6, 5, 'removeUsersCandidateKey'),
								   (6, 7, 'addVidForeignKeyForEsports'),
								   (7, 6, 'removeVidForeignKeyFromEsports'),
								   (7, 8, 'createEsportsChampionsTable'),
								   (8, 7, 'dropEsportsChampionsTable')
GO
 
-- Versioning mechanism
CREATE OR ALTER PROCEDURE restoreVersion(@version INT) AS
    DECLARE @currentVersion INT
    DECLARE @procedureName VARCHAR(MAX)
    SELECT @currentVersion = Version FROM VersionTable
 
    IF @version > (
					SELECT MAX(firstVersion) 
					FROM ProcedureTable
				  )
         RAISERROR ('Invalid version.', 10, 1)
 
    WHILE @currentVersion > @version BEGIN
        SELECT @procedureName = ProcedureName 
		FROM ProcedureTable 
		WHERE FirstVersion = @currentVersion AND LastVersion = @currentVersion-1

        PRINT('Executing ' + @procedureName);
        EXEC (@procedureName)
        SET @currentVersion = @currentVersion-1
    END
 
    WHILE @currentVersion < @version BEGIN
        SELECT @procedureName = ProcedureName 
		FROM ProcedureTable 
		WHERE FirstVersion = @currentVersion AND LastVersion = @currentVersion+1

        PRINT('Executing ' + @procedureName);
        EXEC (@procedureName)
        SET @currentVersion = @currentVersion+1
    END
 
    UPDATE VersionTable SET Version = @version
    RETURN
 
EXECUTE restoreVersion 7
