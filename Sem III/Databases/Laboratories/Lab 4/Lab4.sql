USE CloudGaming
GO

CREATE OR ALTER PROCEDURE addToTables (@tableName varchar(50)) AS
    IF @tableName IN 
		(SELECT Name 
		FROM Tables) 
	BEGIN
        PRINT 'Table already present in Tables'
        RETURN
    END

    IF @tableName NOT IN 
		(SELECT TABLE_NAME 
		FROM INFORMATION_SCHEMA.TABLES) 
	BEGIN
        PRINT 'Table not present in the database'
        RETURN
    END

    INSERT INTO Tables (Name) 
	VALUES (@tableName)
GO


CREATE OR ALTER PROCEDURE addToViews (@viewName varchar(50)) AS
    IF @viewName IN 
		(SELECT Name 
		FROM Views) 
	BEGIN
        PRINT 'View already present in Views'
        RETURN
    END

    IF @viewName NOT IN 
		(SELECT TABLE_NAME 
		FROM INFORMATION_SCHEMA.VIEWS) 
	BEGIN
        PRINT 'View not present in the database'
        RETURN
    END

    INSERT INTO Views (Name)
	VALUES (@viewName)
GO


CREATE OR ALTER PROCEDURE addToTests (@testName varchar(50)) AS
	IF @testName IN 
		(SELECT Name 
		FROM Tests) 
	BEGIN
        PRINT 'Test already present in Tests'
        RETURN
    END
	INSERT INTO Tests (Name) 
	VALUES (@testName)
GO


CREATE OR ALTER PROCEDURE connectTableToTest (@tableName varchar(50), @testName varchar(50), @rows int, @pos int) AS
    IF @tableName NOT IN 
		(SELECT Name 
		FROM Tables) 
	BEGIN
        PRINT 'Table not present in Tables'
        RETURN
    END

    IF @testName NOT IN 
		(SELECT Name 
		FROM Tests) 
	BEGIN
        PRINT 'Tests not present in Tests'
        RETURN
    END

    IF EXISTS(
        SELECT *
        FROM TestTables T1 JOIN Tests T2 ON T1.TestID = T2.TestID
        WHERE T2.Name=@testName AND Position=@pos
        ) 
	BEGIN
        PRINT 'Position provided conflicts with previous positions'
        RETURN
    END

    INSERT INTO TestTables (TestID, TableID, NoOfRows, Position) 
	VALUES (
        (SELECT Tests.TestID 
		FROM Tests 
		WHERE Name=@testName),
        (SELECT Tables.TableID 
		FROM Tables 
		WHERE Name=@tableName),
        @rows,
        @pos
    )
GO


CREATE OR ALTER PROCEDURE connectViewToTest (@viewName varchar(50), @testName varchar(50)) AS
    IF @viewName NOT IN 
		(SELECT Name 
		FROM Views) 
	BEGIN
        PRINT 'View not present in Views'
        RETURN
    END

    IF @testName NOT IN 
		(SELECT Name 
		FROM Tests) 
	BEGIN
        PRINT 'Tests not present in Tests'
        RETURN
    END

    INSERT INTO TestViews (TestID, ViewID) VALUES (
        (SELECT Tests.TestID 
		FROM Tests 
		WHERE Name=@testName),
        (SELECT Views.ViewID 
		FROM Views 
		WHERE Name=@viewName)
    )
GO


CREATE OR ALTER PROCEDURE runTest (@testName varchar(50)) AS
    IF @testName NOT IN 
		(SELECT Name 
		FROM Tests) 
	BEGIN
        PRINT 'test not in Tests'
        RETURN
    END

    DECLARE @command varchar(100)
    DECLARE @testStartTime datetime2
    DECLARE @startTime datetime2
    DECLARE @endTime datetime2
    DECLARE @table varchar(50)
    DECLARE @rows int
    DECLARE @pos int
    DECLARE @view varchar(50)
    DECLARE @testId int

    SELECT @testId=TestID 
	FROM Tests 
	WHERE Name=@testName

    DECLARE @testRunId int
    SET @testRunId = 
		(SELECT MAX(TestRunID)+1 
		FROM TestRuns)
    IF @testRunId IS NULL
        SET @testRunId = 0

    DECLARE tableCursor CURSOR SCROLL FOR
        SELECT T1.Name, T2.NoOfRows, T2.Position
        FROM Tables T1 JOIN TestTables T2 ON T1.TableID = T2.TableID
        WHERE T2.TestID = @testId
        ORDER BY T2.Position
    DECLARE viewCursor CURSOR FOR
        SELECT V.Name
        FROM Views V JOIN TestViews TV ON V.ViewID = TV.ViewID
        WHERE TV.TestID = @testId

    SET @testStartTime = SYSDATETIME()
    OPEN tableCursor
    FETCH LAST FROM tableCursor INTO @table, @rows, @pos
    WHILE @@FETCH_STATUS = 0 BEGIN
        EXEC ('delete from '+ @table)
        FETCH PRIOR FROM tableCursor INTO @table, @rows, @pos
    END
    CLOSE tableCursor

    OPEN tableCursor
    SET IDENTITY_INSERT TestRuns ON
    INSERT INTO TestRuns (TestRunID, Description, StartAt) VALUES (@testRunId, 'Tests results for: ' + @testName, @testStartTime)
    SET IDENTITY_INSERT TestRuns OFF
    FETCH tableCursor INTO @table, @rows, @pos
    WHILE @@FETCH_STATUS = 0 BEGIN
        SET @command = 'populateTable' + @table
        IF @command NOT IN (SELECT ROUTINE_NAME FROM INFORMATION_SCHEMA.ROUTINES) BEGIN
            PRINT @command + 'does not exist'
            RETURN
        END
        SET @startTime = SYSDATETIME()
        EXEC @command @rows
        SET @endTime = SYSDATETIME()
        INSERT INTO TestRunTables (TestRunID, TableId, StartAt, EndAt) 
		VALUES (@testRunId, 
			(SELECT TableID 
			FROM Tables 
			WHERE Name=@table), 
			@startTime, @endTime)
        FETCH tableCursor INTO @table, @rows, @pos
    END
    CLOSE tableCursor
    DEALLOCATE tableCursor

    OPEN viewCursor
    FETCH viewCursor INTO @view
    WHILE @@FETCH_STATUS = 0 BEGIN
        SET @command = 'select * from ' + @view
        SET @startTime = SYSDATETIME()
        EXEC (@command)
        SET @endTime = SYSDATETIME()
        INSERT INTO TestRunViews (TestRunID, ViewID, StartAt, EndAt) 
		VALUES (@testRunId, 
			(SELECT ViewID 
			FROM Views 
			WHERE Name=@view), 
			@startTime, @endTime)
        FETCH viewCursor INTO @view
    END
    CLOSE viewCursor
    DEALLOCATE viewCursor

    UPDATE TestRuns
    SET EndAt=SYSDATETIME()
    WHERE TestRunID = @testRunId
GO


-- TEST 1 --
EXEC addToTables 'Users'
GO

CREATE OR ALTER VIEW getAgeGroups AS
    SELECT Age, COUNT(*) AS number_of_users
    FROM Users
    GROUP BY Age
GO

EXEC addToViews 'getAgeGroups'
EXEC addToTests 'test1'
EXEC connectTableToTest 'Users', 'test1', 1000, 1
EXEC connectViewToTest 'getAgeGroups', 'test1'
GO

CREATE OR ALTER PROCEDURE populateTableUsers (@rows int) AS
    WHILE @rows > 0 BEGIN
        INSERT INTO Users(Uid, Name, Email, Age, Country, SubscribedToNewsletter) 
		VALUES (@rows, 'Name', 'Email', floor(rand()*100), 'Country', 1)
        SET @rows = @rows-1
    END
GO

EXECUTE runTest 'test1'

SELECT *
FROM TestRunTables
GO