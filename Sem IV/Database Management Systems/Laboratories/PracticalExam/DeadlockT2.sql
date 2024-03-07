USE Cards
GO

-- Second session (T2)
BEGIN TRANSACTION;
UPDATE Cards SET PurchaseDate = GETDATE() WHERE CardID = 1;

-- Simulate a delay
WAITFOR DELAY '00:00:10';

UPDATE Players SET FirstName = 'Player 1' WHERE PlayerID = 1;
ROLLBACK TRANSACTION;

SELECT * FROM Cards
SELECT * From Players
