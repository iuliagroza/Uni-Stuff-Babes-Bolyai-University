USE CloudGaming
GO

SET IDENTITY_INSERT Users ON
BEGIN TRAN
WAITFOR DELAY '00:00:04'
INSERT INTO Users(Uid, Name, Email, Age, Country, SubscribedToNewsletter)
VALUES (1, 'Edgar Allan Poe', 'whothehellisedgar@ftw.com', 150, 'UK', 1)
COMMIT TRAN

BEGIN TRAN
WAITFOR DELAY '00:00:05'
INSERT INTO Users(Uid, Name, Email, Age, Country, SubscribedToNewsletter)
VALUES (2, 'Edgar Allan Poe', 'whothehellisedgar@ftw.com', 150, 'UK', 1)
COMMIT TRAN
SET IDENTITY_INSERT Users OFF

SELECT * FROM Users