USE [nckh]
GO

/****** Object:  Trigger [dbo].[trg_generateGN]    Script Date: 8/24/2024 3:35:23 PM ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO



CREATE TRIGGER [dbo].[trg_generateGN]
ON [dbo].[GHI_NUOC]
FOR INSERT
AS
BEGIN
    DECLARE @currentID INT, @newID INT

    -- Get the current highest ID

	SELECT @currentID = COUNT(ma_ghi)
    FROM GHI_NUOC

    -- Generate the new ID
    
        SET @newID = @currentID + 1;

    -- Update the inserted rows with the new ID
    UPDATE [dbo].[GHI_NUOC]
    SET ma_ghi = @newID
    FROM [dbo].[GHI_NUOC] a
    JOIN inserted i ON a.ma_ghi = i.ma_ghi
END
GO

ALTER TABLE [dbo].[GHI_NUOC] ENABLE TRIGGER [trg_generateGN]
GO

