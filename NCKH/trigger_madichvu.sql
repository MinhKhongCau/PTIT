USE [nckh]
GO

/****** Object:  Trigger [dbo].[trg_generateDV]    Script Date: 8/19/2024 9:10:49 PM ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TRIGGER [dbo].[trg_generateDV]
ON [dbo].[DICH_VU]
FOR INSERT
AS
BEGIN
    DECLARE @currentID char(10), @newID char(10)

    -- Get the current highest ID
    SELECT TOP 1 @currentID = ma_dich_vu
    FROM DICH_VU
    ORDER BY ma_dich_vu DESC

    -- Generate the new ID
   
    
    
        SET @newID = 'DV' + RIGHT( CAST(CAST(SUBSTRING(@currentID, 3, 8) AS INT) + 1 AS VARCHAR(8)), 8)
   

    -- Update the inserted rows with the new ID
    UPDATE [dbo].[DICH_VU]
    SET ma_dich_vu = @newID
    FROM [dbo].[DICH_VU] dv
    JOIN inserted i ON dv.ma_dich_vu = i.ma_dich_vu
END
GO

ALTER TABLE [dbo].[DICH_VU] ENABLE TRIGGER [trg_generateDV]
GO

