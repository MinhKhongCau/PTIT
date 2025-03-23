USE [nckh]
GO

/****** Object:  Trigger [dbo].[trg_generateCH]    Script Date: 8/19/2024 11:46:00 PM ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TRIGGER [dbo].[trg_generateCH]
ON [dbo].[CAN_HO]
FOR INSERT
AS
BEGIN
    DECLARE @currentID char(10), @newID char(10), @count INT

    -- Get the current highest ID
    SELECT @count = COUNT(ma_can_ho)
    FROM CAN_HO

    -- Generate the new ID
   
    
    
        SET @newID = 'CH' + RIGHT( CAST(@count + 1 AS VARCHAR(10)), 8);
   

    -- Update the inserted rows with the new ID
    UPDATE [dbo].[CAN_HO]
    SET ma_can_ho = @newID
    FROM [dbo].[CAN_HO] ch
    JOIN inserted i ON ch.ma_can_ho = i.ma_can_ho
END
GO

ALTER TABLE [dbo].[CAN_HO] ENABLE TRIGGER [trg_generateCH]
GO

