USE CloudGaming
GO

-- INSERT
-- Users
INSERT INTO Users VALUES ('John Doe', 'johndoe@gmail.com', 24, 'United States', 1), 
						 ('Mary Jane', 'maryjane@gmail.com', 27, 'Armenia', 0),
						 ('Paul Lancaster', 'paullancaster@yahoo.com', 38, 'Brasil', 0),
						 ('Mark Dupont', 'markdupont@gmail.com', 19, 'Spain', 1),
						 ('Laura Jones', 'laurajones@gmail.com', 45, 'Romania', 1),
						 ('Marco Polo', 'marcopolo@gmail.com', 29, 'United States', 1), 
						 ('Sydney Swan', 'sydneyswan@yahoo.com', 27, 'United States', 0),
						 ('Sonny Gauff', 'sonnygauff@yahoo.com', 31, 'France', 0),
						 ('Ryan Moore', 'ryanmoore@gmail.com', 15, 'South Korea', 1),
						 ('Indie Terry', 'indieterry@gmail.com', 50, 'Romania', 0)

-- VideoGameCompanies
INSERT INTO VideoGameCompanies VALUES ('Rockstar Games', 1998, 'Sam Houses', 56), 
									  ('Crytek', 1999, 'Avni Yerli', 16),
									  ('Hazelight Studios', 2014, 'Oskar Volontis', 2)

-- Genres
INSERT INTO Genres VALUES ('Action'),
						  ('Adventure'),
						  ('Western'),
						  ('Fantasy')

-- Games
INSERT INTO Games VALUES ('Red Dead Redemption 2', 'Western-themed action-adventure game', 2018, 545458, 5, 349999, 28, 35),
						 ('Grand Theft Auto: Vice City', 'Action-adventure game played from a third-person perspective', 2002, 723648, 4, 449679, 28, 33),
						 ('Far Cry', 'First-person shooter (FPS) with action-adventure elements', 2004, 132244, 3, 314444, 29, 36),
						 ('It Takes Two', 'Action-adventure video game with elements from platform games', 2021, 588548, 5, 149949, 30, 34),
						 ('A Way Out', 'Action-adventure game played from a third-person perspective', 2018, 193499, 2, 56388, 30, 34)

-- Achievements
INSERT INTO Achievements VALUES ('Best Cowboy in Town', 78, 36),
								('Gems in your hand', 16, 37),
								('Got rid of the police', 48, 37),
								('No place to hide', 89, 39),
								('Christmas is coming', 48, 39) 

-- UsersGames
INSERT INTO UsersGames VALUES (91, 36),
							  (91, 38),
							  (92, 36),
							  (93, 37),
							  (93, 39),
							  (95, 37),
							  (96, 39),
							  (97, 38),
							  (97, 39),
							  (97, 40),
							  (100, 40)

-- UsersAchievements
INSERT INTO UsersAchievements VALUES (91, 1, '2019-10-29'),
									 (91, 4, '2015-07-07'),
									 (91, 5, '2020-12-22'),
									 (93, 3, '2020-04-30'),
									 (93, 4, '2021-02-05'),
									 (99, 5, '2021-04-01'),
									 (100, 1, '2018-09-19'),
									 (100, 2, '2022-03-01'),
									 (100, 4, '2017-12-31')

-- Violates referential integrity constraints (Genid, Vid)
INSERT INTO Games VALUES ('Wrong game', 'This is a test for violating constraints', 2006, 100, 1, 50, 100234, 13245)

SELECT * FROM Users
SELECT * FROM VideoGameCompanies
SELECT * FROM Genres
SELECT * FROM Games
SELECT * FROM Achievements
SELECT * FROM UsersGames
SELECT * FROM UsersAchievements

-- UPDATE
-- Users
-- >, <=, =
UPDATE Users
SET Name = 'Johnny Doe', Email = 'johnnydoe@gmail.com'
WHERE Name = 'John Doe' AND Age > 23 AND Age <= 26 AND SubscribedToNewsletter = 1

-- OR, <>, AND
UPDATE Users
SET Country = 'France'
WHERE (Country = 'Spain' OR Country = 'South Korea') AND (Age <> 27)

-- NOT, >=, <
UPDATE Users
SET SubscribedToNewsletter = 1
WHERE (NOT Country = 'United States') AND (Age >= 17 AND Age < 25) 

-- VideoGameCompanies
-- IS NOT NULL
UPDATE VideoGameCompanies
SET NoOfReleasedGames = NoOfReleasedGames + 2
WHERE Name IS NOT NULL

-- Games
-- BETWEEN
UPDATE Games
SET NoOfDownloads = 350000
WHERE NoOfDownloads BETWEEN 300000 AND 350000

-- DELETE
-- Users
-- IN
DELETE FROM Users WHERE Uid >= 101

-- IS NULL
DELETE FROM Users WHERE Email IS NULL

-- VideoGameCompanies
DELETE FROM VideoGameCompanies WHERE Vid >= 31

-- Genres
DELETE FROM Genres WHERE Genid >= 37

-- Games
DELETE FROM Games WHERE Gid >= 41

-- Achievements
DELETE FROM Achievements WHERE Aid >= 6


-- a. 2 queries with the union operation; use UNION [ALL] and OR;
-- AND, OR, (), DISTINCT, *
-- All distinct users (shown with twice their age) that are from United States OR are in their twenties OR are subscribed to the newsletter (with duplicates)
SELECT DISTINCT U1.Name, U1.Email, U1.Age*2
FROM Users U1 
WHERE Country = 'United States' OR (Age >= 20 AND Age < 30)
UNION ALL
SELECT U2.Name, U2.Email, U2.Age*2
FROM Users U2
WHERE SubscribedToNewsletter = 1

-- OR
-- DISTINCT, -
-- All distinct games (with actual ID) that are developed after 2015 OR have action as their description keyword (first word) OR are developed by Hazelight Studios
SELECT DISTINCT G1.Name, G1.Vid-27
FROM Games G1
WHERE YearOfRelease > 2015 
UNION
SELECT G2.Name, G2.Vid-27
FROM Games G2
WHERE Name LIKE 'Action%' OR Vid = 30


-- b. 2 queries with the intersection operation; use INTERSECT and IN;
-- DISTINCT
-- All distinct game companies that are not founded in 2011 AND have 2 or 20 developed games
SELECT DISTINCT C1.Name
FROM VideoGameCompanies C1
WHERE NOT(YearFounded = 2011)
INTERSECT
SELECT C2.Name
FROM VideoGameCompanies C2
WHERE NoOfReleasedGames IN (2, 20)

-- All the users that are from Romania, Spain or France AND are subscribed to the newsletter
SELECT U1.Name, U1.Email
FROM Users U1
WHERE Country IN ('Romania', 'Spain', 'France')
INTERSECT
SELECT U2.Name, U2.Email
FROM Users U2
WHERE SubscribedToNewsletter = 1


-- c. 2 queries with the difference operation; use EXCEPT and NOT IN;
-- NOT
-- All the users that are NOT from United States, BUT are subscribed to the newsletter
SELECT U1.Name, U1.Email
FROM Users U1
WHERE Country NOT IN ('United States')
EXCEPT
SELECT U2.Name, U2.Email
FROM Users U2
WHERE SubscribedToNewsletter = 0

-- /
-- All the games (with half the actual number of downloads) that are NOT developed by Hazelight Studios or Crytek, BUT have 400.000+ downloads
SELECT G1.Name, G1.NoOfDownloads/2
FROM Games G1
WHERE Vid NOT IN (29, 30)
EXCEPT
SELECT G2.Name, G2.NoOfDownloads/2
FROM Games G2
WHERE NoOfDownloads < 400000


-- d. 4 queries with INNER JOIN, LEFT JOIN, RIGHT JOIN, and FULL JOIN (one query per operator); one query will join at least 3 tables,
-- while another one will join at least two many-to-many relationships;
-- 3 tables
-- INNER JOIN: Genre: Name <genid> Game: Name <vid> VideoGameCompany: Name
SELECT
    game.Name,
    genre.Name,
    company.Name
FROM Games game
JOIN Genres AS genre
ON game.genid = genre.genid
JOIN VideoGameCompanies AS company  
ON game.vid = company.vid;

-- 2 many-to-many relationships: UsersGames, UsersAchievements
-- LEFT JOIN: All users tied to the games they played and achievements they won
SELECT 
	users.Name,
	users_games.Gid,
	users_achievements.Aid
FROM Users users
LEFT JOIN UsersGames AS users_games
ON users_games.Uid = users.Uid
LEFT JOIN UsersAchievements AS users_achievements
ON users_achievements.Uid = users.Uid

-- TOP
-- RIGHT JOIN: Top 3 'Fantasy' and 'Adventure' genres with their associated games
SELECT TOP 3 *
FROM Genres genre
RIGHT JOIN Games AS game
ON genre.Genid = game.Genid AND genre.Name IN ('Fantasy', 'Adventure')

-- TOP
-- FULL JOIN: Complete info about Top 5 achievements and the game they are associated to
SELECT TOP 5 *
FROM Achievements achievement
FULL JOIN Games AS game
ON achievement.Gid = game.Gid


-- e. 2 queries with the IN operator and a subquery in the WHERE clause; in at least one case, the subquery must include a subquery in its own WHERE clause;
-- All video game companies that released games after 2012
SELECT C.Name
FROM VideoGameCompanies C
WHERE C.Vid IN (
	SELECT G.Vid
	FROM Games G
	WHERE G.YearOfRelease >= 2012
)

-- Nested subquery
-- All games played by Americans
SELECT G.Name
FROM Games G
WHERE G.Gid IN (
	SELECT UG.Gid
	FROM UsersGames UG
	WHERE UG.Uid IN (
		SELECT U.Uid
		FROM Users U
		WHERE U.Country LIKE 'United States'
	)
)


-- f. 2 queries with the EXISTS operator and a subquery in the WHERE clause;
-- Games if there are games that have 500000+ players
SELECT G.Name, G.NoOfPlayers
FROM Games G
WHERE EXISTS(
	SELECT *
	FROM Games G
	WHERE G.NoOfPlayers > 500000
)

-- Emails of the users if there are any whose name starts with letter M
SELECT U.Email
FROM Users U
WHERE EXISTS(
	SELECT *
	FROM Users U
	WHERE U.Name LIKE 'M%'
)


-- g. 2 queries with a subquery in the FROM clause;
-- All users whose age is greater or equal than the average number of games a company has developed
SELECT U.Name, U.Email, U.Age, GameNo.average 
FROM (SELECT avg(NoOfReleasedGames) AS average 
	  FROM VideoGameCompanies) AS GameNo, Users AS U
WHERE U.Age >= GameNo.average

-- ORDER BY
-- All games whose number of players is greater than the average number of downloads 
SELECT G.Name, G.NoOfPlayers, GameDownloads.average 
FROM (SELECT avg(NoOfDownloads) AS average 
	  FROM Games) AS GameDownloads, Games AS G
WHERE G.NoOfPlayers >= GameDownloads.average
ORDER BY G.NoOfPlayers


-- h. 4 queries with the GROUP BY clause, 3 of which also contain the HAVING clause; 2 of the latter will also have a subquery in the HAVING clause;
-- use the aggregation operators: COUNT, SUM, AVG, MIN, MAX;
-- COUNT, MIN, ORDER BY
-- Number of users per each country ordered in descending order by minimum age of the users
SELECT COUNT(U.Uid), U.Country
FROM Users U
GROUP BY U.Country
ORDER BY MIN(U.Age) DESC

-- MAX, HAVING
-- Latest release year of games under genre 'Adventure'
SELECT MAX(G.YearOfRelease)
FROM Games G
GROUP BY G.Genid 
HAVING G.Genid = 34

-- SUM, HAVING, subquery
-- Total downloads of games produced by video game companies founded after 2000
SELECT SUM(G.NoOfDownloads)
FROM Games G
GROUP BY G.Vid
HAVING G.Vid in (
	SELECT C.Vid
	FROM VideoGameCompanies C
	WHERE C.YearFounded >= 2000
)

-- AVG, HAVING, subquery
-- Average age of users that have a name formed of exactly 10 letters in each country
SELECT AVG(U.Age), U.Country
FROM Users U
GROUP BY U.Country
HAVING U.Country IN (
	SELECT U.Country
	FROM Users U
	WHERE U.Name LIKE '__________'
)

-- i. 4 queries using ANY and ALL to introduce a subquery in the WHERE clause (2 queries per operator); rewrite 2 of them with aggregation operators,
-- and the other 2 with IN / [NOT] IN.
-- ALL
-- Users with age different than all users not from France
SELECT U1.Name, U1.Age
FROM Users U1
WHERE U1.Age <> all (
    select U2.Age
    from Users U2
    where U2.Country = 'France'
)

-- Rewritten query: NOT IN
SELECT U1.Name, U1.Age
FROM Users U1
WHERE U1.Age NOT IN (
    select U2.Age
    from Users U2
    where U2.Country = 'France'
)

-- Games with more players than all games produced by Hazelight Studios
SELECT G1.Name, G1.NoOfPlayers
FROM Games G1
WHERE G1.NoOfPlayers > all (
    SELECT G2.NoOfPlayers
    FROM Games G2
    WHERE G2.Vid = 30
)

-- Rewritten query: MAX
SELECT G1.Name, G1.NoOfPlayers
FROM Games G1
WHERE G1.NoOfPlayers > (
    SELECT MAX(G2.NoOfPlayers)
    FROM Games G2
    WHERE G2.Vid = 30
)

-- ANY
-- Games with more downloads than any game released in 2018
SELECT G1.Name, G1.NoOfDownloads
FROM Games G1
WHERE G1.NoOfDownloads > any (
    SELECT G2.NoOfPlayers
    FROM Games G2
    WHERE G2.Vid = 30
)

-- Rewritten query: MIN
SELECT G1.Name, G1.NoOfDownloads
FROM Games G1
WHERE G1.NoOfDownloads > (
    SELECT MIN(G2.NoOfPlayers)
    FROM Games G2
    WHERE G2.Vid = 30
)

-- Users with the same age as any user subscribed to the newsletter
SELECT U1.Name, U1.Age
FROM Users U1
WHERE U1.Age = any (
    select U2.Age
    from Users U2
    where U2.SubscribedToNewsletter = 1
)

-- Rewritten query: IN
SELECT U1.Name, U1.Age
FROM Users U1
WHERE U1.Age IN (
    select U2.Age
    from Users U2
    where U2.SubscribedToNewsletter = 1
)