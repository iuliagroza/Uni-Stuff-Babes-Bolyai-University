USE Cards
GO

-- First session (T1)
BEGIN TRANSACTION;
UPDATE Players SET FirstName = 'Player 1' WHERE PlayerID = 1;

-- Simulate a delay
WAITFOR DELAY '00:00:10';

UPDATE Cards SET PurchaseDate = GETDATE() WHERE CardID = 1;
ROLLBACK TRANSACTION

SELECT * FROM Cards
SELECT * From Players
