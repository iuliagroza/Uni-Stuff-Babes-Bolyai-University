USE CloudGaming
GO

ALTER DATABASE CloudGaming SET ALLOW_SNAPSHOT_ISOLATION ON;

SET TRAN ISOLATION LEVEL SNAPSHOT
BEGIN TRAN
WAITFOR DELAY '00:00:05'
-- T1 has updated and has a lock on the table
-- T2 will be blocked when trying to update the table
UPDATE Users SET Country = 'Austria' WHERE Uid = 2
COMMIT TRAN

SELECT * FROM Users