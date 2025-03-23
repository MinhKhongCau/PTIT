USE [nckh]
GO

/****** Object:  Trigger [dbo].[trg_generateGN]    Script Date: 8/19/2024 11:51:31 PM ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO


CREATE TRIGGER [dbo].[trg_generateGN]
ON [dbo].[GHI_NUOC]
FOR INSERT
AS
BEGIN
    DECLARE @currentID INT, @newID INT, @lastIndex INT, @newIndex INT

    -- Get the current highest ID
    SELECT TOP 1 @lastIndex = a.chi_so_moi
    FROM GHI_NUOC a
	INNER JOIN inserted i on a.ma_dong_ho = i.ma_dong_ho
	WHERE i.ma_dong_ho IS NOT NULL  
    ORDER BY a.ma_ghi DESC

	SELECT @currentID = COUNT(ma_ghi)
    FROM GHI_NUOC

    -- Generate the new ID
   
    
    
        SET @newID = @currentID + 1;
		SET @newIndex = @lastIndex;

    -- Update the inserted rows with the new ID
    UPDATE [dbo].[GHI_NUOC]
    SET ma_ghi = @newID, chi_so_cu = @newIndex
    FROM [dbo].[GHI_NUOC] a
    JOIN inserted i ON a.ma_ghi = i.ma_ghi
END
GO

ALTER TABLE [dbo].[GHI_NUOC] ENABLE TRIGGER [trg_generateGN]
GO

