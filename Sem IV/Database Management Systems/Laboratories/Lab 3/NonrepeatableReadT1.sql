USE CloudGaming
GO

SET IDENTITY_INSERT Users ON
INSERT INTO Users(Uid, Name, Email, Age, Country, SubscribedToNewsletter)
VALUES (5, 'Cian Li', 'cl@cider.gl', 18, 'North Korea', 0)
BEGIN TRAN
WAITFOR DELAY '00:00:05'
UPDATE Users SET Country='Russia'
WHERE Uid = 5
COMMIT TRAN

INSERT INTO Users(Uid, Name, Email, Age, Country, SubscribedToNewsletter)
VALUES (6, 'Gigi Becali', 'gg@bcl.gl', 65, 'North Korea', 1)
BEGIN TRAN
WAITFOR DELAY '00:00:05'
UPDATE Users SET Country='Romania'
WHERE Uid = 6
COMMIT TRAN
SET IDENTITY_INSERT Users OFF

SELECT * FROM Users