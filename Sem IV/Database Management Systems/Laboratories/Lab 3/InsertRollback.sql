USE CloudGaming
GO

--Games, Users, UsersGames
CREATE OR ALTER PROCEDURE addRowGames @name VARCHAR(50), @description VARCHAR(300), @yearOfRelease INT, @noOfPlayers INT, @rating INT, @noOfDownloads INT, @vidName VARCHAR(50), @genName VARCHAR(50) AS
BEGIN
	SET NOCOUNT ON
	DECLARE @maxId INT
	SET @maxId = 1
	SELECT TOP 1 @maxId = Gid + 1 FROM Games ORDER BY Gid DESC
	DECLARE @error VARCHAR(max)
	SET @error = ''
	IF(@name IS NULL)
	BEGIN
		SET @error = 'Game name must be non-null.'
		RAISERROR('Game name must be non-null.', 16, 1);
	END
	IF(@description IS NULL)
	BEGIN
		SET @error = 'Game description must be non-null.'
		RAISERROR('Game description must be non-null.', 16, 1);
	END
	IF(@yearOfRelease < 1950)
	BEGIN
		SET @error = 'Year of release must be above 1950.'
		RAISERROR('Year of release must be above 1950.', 16, 1);
	END
	IF(@noOfPlayers < 0)
	BEGIN 
		SET @error = 'Number of players must be positive.'
		RAISERROR('Number of players must be positive.', 16, 1);
	END
	IF(@rating < 0 OR @rating > 5)
	BEGIN
		SET @error = 'Rating must be between 0 and 5.'
		RAISERROR('Rating must be between 0 and 5.', 16, 1);
	END
	IF(@noOfDownloads < 0)
	BEGIN
		SET @error = 'Number of downloads must be positive.'
		RAISERROR('Number of downloads must be positive.', 16, 1);
	END
	IF(@vidName IS NULL)
	BEGIN
		SET @error = 'Name of video game company must be non-null.'
		RAISERROR('Name of video game company must be non-null.', 16, 1);
	END
	IF(@genName IS NULL)
	BEGIN
		SET @error = 'Name of genre must be non-null.'
		RAISERROR('Name of genre must be non-null.', 16, 1);
	END
	DECLARE @vid INT
	SET @vid = (SELECT Vid FROM VideoGameCompanies WHERE Name = @vidName)
	DECLARE @genid INT
	SET @genid = (SELECT Genid FROM Genres WHERE Name = @genName)
	SET IDENTITY_INSERT Games ON
	INSERT INTO Games(Gid, Name, Description, YearOfRelease, NoOfPlayers, Rating, NoOfDownloads, Vid, Genid)
	VALUES (@maxId, @name, @description, @yearOfRelease, @noOfPlayers, @rating, @noOfDownloads, @vid, @genid)
	EXEC sp_log_changes '', @name, 'Add row to Games.', @error
	SET IDENTITY_INSERT Games OFF
END


GO
CREATE OR ALTER PROCEDURE addRowUsers @name VARCHAR(50), @email VARCHAR(50), @age INT, @country VARCHAR(50), @subscribedToNewsletter BIT AS
BEGIN
	SET NOCOUNT ON
	DECLARE @maxId INT
	SET @maxId = 1
	SELECT TOP 1 @maxId = Uid + 1 FROM Users ORDER BY Uid DESC
	DECLARE @error VARCHAR(max)
	SET @error = ''
	IF(@name IS NULL)
	BEGIN
		SET @error = 'User name must be non-null.'
		RAISERROR('User name must be non-null.', 16, 1);
	END
	IF(@email IS NULL)
	BEGIN
		SET @error = 'User email must be non-null.'
		RAISERROR('User email must be non-null.', 16, 1);
	END
	IF(@age < 13)
	BEGIN
		SET @error = 'User must be older than 13.'
		RAISERROR('User must be older than 13.', 16, 1);
	END
	IF(@country IS NULL)
	BEGIN
		SET @error = 'Country must be non-null.'
		RAISERROR('Country must be non-null.', 16, 1);
	END
	IF(@subscribedToNewsletter IS NULL)
	BEGIN
		SET @error = 'SubscribedToNewsletter must be non-null.'
		RAISERROR('SubscribedToNewsletter must be non-null.', 16, 1);
	END
	SET IDENTITY_INSERT Users ON
	INSERT INTO Users(Uid, Name, Email, Age, Country, SubscribedToNewsletter) 
	VALUES (@maxId, @name, @email, @age, @country, @subscribedToNewsletter)
	EXEC sp_log_changes '', @name, 'Add row to Users.', @error
	SET IDENTITY_INSERT Users OFF
END

GO
CREATE OR ALTER PROCEDURE addRowUsersGames @userName VARCHAR(50), @gameName VARCHAR(50) AS
BEGIN
	SET NOCOUNT ON
	DECLARE @error VARCHAR(max)
	SET @error = ''
	IF(@userName IS NULL)
	BEGIN
		SET @error = 'User name must be non null.'
		RAISERROR(@error, 16, 1);
	END
	IF(@gameName IS NULL)
	BEGIN
		SET @error = 'Game name must be non-null.'
		RAISERROR(@error, 16, 1);
	END
	DECLARE @uid INT
	SET @uid = (SELECT Uid FROM Users WHERE Name = @userName)
	DECLARE @gid INT
	SET @gid = (SELECT Gid FROM Games WHERE Name = @gameName)
	IF(@uid IS NULL)
	BEGIN
		SET @error = 'No user with the given name.'
		RAISERROR(@error, 16, 1);
	END
	IF(@gid IS NULL)
	BEGIN
		SET @error = 'No game with the given name.'
		RAISERROR(@error, 16, 1);
	END
	INSERT INTO UsersGames(Uid, Gid)
	VALUES (@uid, @gid)
	DECLARE @newData VARCHAR(350)
	SET @newData = @userName + ' ' + @gameName
	EXEC sp_log_changes '', @newData, 'Connect Users to Games.', @error
END

EXEC addRowGames 'Minecraft', 'cool kidz game', 2011, 1354533, 5, 540004, 'Crytek', 'Adventure'
EXEC addRowUsers 'Gigel Gigel', 'gg@bro.com', 13, 'Romania', 1
EXEC addRowUsersGames 'Gigel Gigel', 'Minecraft'

SELECT * FROM Games
SELECT * FROM Users
SELECT * FROM UsersGames
SELECT * FROM LogChanges
DELETE FROM UsersGames
DELETE FROM Games
DELETE FROM Users
DELETE FROM LogChanges

GO
CREATE OR ALTER PROCEDURE successfulAddRollback AS
BEGIN
	BEGIN TRAN
	BEGIN TRY 
		EXEC addRowGames 'Minecraft', 'cool kidz game', 2011, 1354533, 5, 540004, 'Crytek', 'Adventure'
		EXEC addRowUsers 'Gigel Gigel', 'gg@bro.com', 13, 'Romania', 1
		EXEC addRowUsersGames 'Gigel Gigel', 'Minecraft'
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		EXEC sp_log_changes '', '', 'Rolledback all data.', ''
		RETURN
	END CATCH
	COMMIT TRAN
END

GO 
CREATE OR ALTER PROCEDURE failAddRollback AS
BEGIN
	BEGIN TRAN
	BEGIN TRY
		EXEC addRowGames 'Minecraft', 'cool kidz game', 2011, 1354533, 5, 540004, 'Crytek', 'Adventure'
		EXEC addRowUsers 'Gigel Gigel', 'gg@bro.com', 13, 'Romania', 1
		EXEC addRowUsersGames 'G', 'Minecraft'
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		EXEC sp_log_changes '', '', 'Rolledback all data.', ''
		RETURN
	END CATCH
	COMMIT TRAN
END

EXEC successfulAddRollback
EXEC failAddRollback