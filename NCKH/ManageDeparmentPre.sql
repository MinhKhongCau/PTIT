USE ManageDepartment
GO
DROP TABLE IF EXISTS PHONG_BAN
GO
CREATE TABLE PHONG_BAN(
	Ma_phong_ban NVARCHAR(50) PRIMARY KEY NOT NULL,
	Ten_phong_ban NVARCHAR(50) NOT NULL
);
DROP TABLE IF EXISTS THANH_TOAN
GO
CREATE TABLE THANH_TOAN (
	Ma_thanh_toan INT NOT NULL PRIMARY KEY IDENTITY,
	So_tai_khoan INT NOT NULL,
	Ten_ngan_hang NVARCHAR(50) NOT NULL
);
GO
DROP TABLE IF EXISTS _LOGIN
CREATE TABLE _LOGIN (
	Usermame NVARCHAR(50) NOT NULL PRIMARY KEY,
	Pass_word NVARCHAR(50) NOT NULL,
	Quyen NVARCHAR(50) NOT NULL,
	CHECK (Quyen = 'NV' OR Quyen = 'CSH')
);
GO
GO
DROP TABLE IF EXISTS NHAN_VIEN
GO
CREATE TABLE NHAN_VIEN(
	Ma_nhan_vien INT PRIMARY KEY NOT NULL IDENTITY,
	Ho_ten NVARCHAR(50) NOT NULL,
	SDT INT NOT NULL,
	Ma_phong_ban NVARCHAR(50) FOREIGN KEY REFERENCES PHONG_BAN(Ma_phong_ban) NOT NULL,
	Phai NVARCHAR(3) DEFAULT ('NAM'),
	Ngay_sinh DATE,
	CCCD INT,
	Username NVARCHAR(50) UNIQUE NOT NULL,
	CHECK (PHAI = 'NAM' OR PHAI = 'NU'),
);

GO
DROP TABLE IF EXISTS CHU_SO_HUU
GO
CREATE TABLE CHU_SO_HUU(
	Ma_chu_so_huu INT PRIMARY KEY NOT NULL IDENTITY,
	Ho_ten NVARCHAR(50) NOT NULL,
	SDT INT NOT NULL,
	Phai NVARCHAR(3) DEFAULT ('NAM'),
	Ngay_sinh DATE,
	CCCD INT NOT NULL,
	Username NVARCHAR(50) NOT NULL UNIQUE,
	CHECK (PHAI = 'NAM' OR PHAI = 'NU'),
);

GO
DROP TABLE IF EXISTS CAN_HO
GO
CREATE TABLE CAN_HO(
	Ma_can_ho NVARCHAR(50) PRIMARY KEY NOT NULL,
	Ma_chu_so_huu INT FOREIGN KEY REFERENCES CHU_SO_HUU(Ma_chu_so_huu),
	Du_no INT DEFAULT(0),
);
GO
DROP TABLE IF EXISTS HOA_DON
GO
CREATE TABLE HOA_DON(
	Ma_hoa_don INT PRIMARY KEY NOT NULL IDENTITY,
	Ngay_lap DATE NOT NULL,
	Ma_can_ho NVARCHAR(50) NOT NULL FOREIGN KEY REFERENCES CAN_HO(Ma_can_ho),
	Ma_nhan_vien INT NOT NULL FOREIGN KEY REFERENCES NHAN_VIEN(Ma_nhan_vien),
	Ma_thanh_toan INT NOT NULL FOREIGN KEY REFERENCES THANH_TOAN(Ma_thanh_toan)
);
GO
DROP TABLE IF EXISTS DICH_VU
GO
CREATE TABLE DICH_VU(
	Ma_dich_vu NVARCHAR(50) PRIMARY KEY NOT NULL,
	Ten_dich_vu NVARCHAR(50) NOT NULL,
	VAT FLOAT DEFAULT(0),
	Don_gia INT NOT NULL,
	So_ngay_het_han INT DEFAULT(15)
);
GO
DROP TABLE IF EXISTS CHI_TIET_DICH_VU
GO
CREATE TABLE CHI_TIET_DICH_VU(
	Id_chi_tiet_dich_vu INT PRIMARY KEY NOT NULL IDENTITY,
	Ma_dich_vu NVARCHAR(50) NOT NULL,
	Ma_can_ho NVARCHAR(50) NOT NULL,
	Ngay_bat_dau DATE NOT NULL,
	Ngay_ket_thuc DATE NOT NULL,
	So_luong INT NOT NULL,
	CONSTRAINT UNIQUE_CTDV UNIQUE (Ma_dich_vu,Ma_can_ho),
	FOREIGN KEY (Ma_dich_vu) REFERENCES DICH_VU(Ma_dich_vu),
	FOREIGN KEY (Ma_can_ho) REFERENCES CAN_HO(Ma_can_ho)
);
GO
INSERT INTO CHU_SO_HUU(Ho_ten,SDT,Phai,Ngay_sinh,CCCD,Username) VALUES
('truong van a','01234567891','NAM','1/1/1999','123','user1'),
('nguyen van b','01234567891','NAM','1/2/1999','123','user2'),
('nguyen thi c','01234567891','NU','1/3/1999','123','user3'),
('truong thi a','01234567891','NU','1/4/1999','123','user4'),
('le thi c','01234567891','NU','1/5/1999','123','user5')
GO
INSERT INTO CAN_HO (Ma_can_ho,Ma_chu_so_huu,Du_no) VALUES
('CH1','1',0),
('CH2','2',0),
('CH3','3',0),
('CH4','2',0),
('CH5','4',0);
GO
INSERT INTO _LOGIN(Usermame,Pass_word,Quyen) VALUES
('User1','123','CSH'),
('User2','123','CSH'),
('User3','123','CSH'),
('User4','123','CSH'),
('User5','123','CSH'),
('User6','123','NV'),
('User7','123','NV'),
('User8','123','NV'),
('User9','123','NV'),
('User10','123','NV');
GO
INSERT INTO PHONG_BAN(Ma_phong_ban,Ten_phong_ban) VALUES
('pb1','phong ban 1'),
('pb2','phong ban 1'),
('pb3','phong ban 1')
GO
INSERT INTO NHAN_VIEN(Ho_ten,SDT,Phai,Ngay_sinh,CCCD,Username,Ma_phong_ban) VALUES
('truong van a','01234567891','NAM','1/1/1999','123','user6','pb1'),
('nguyen van b','01234567891','NAM','1/2/1999','123','user7','pb2'),
('nguyen thi c','01234567891','NU','1/3/1999','123','user8','pb1'),
('truong thi a','01234567891','NU','1/4/1999','123','user9','pb3'),
('le thi c','01234567891','NU','1/5/1999','123','user10','pb1')
GO
INSERT INTO DICH_VU(Ma_dich_vu,Ten_dich_vu,VAT,Don_gia,So_ngay_het_han) VALUES
('DV1','dich vu 1',0.03,10000,15),
('DV2','dich vu 2',0.03,10000,15),
('DV3','dich vu 3',0.03,10000,15)
GO
INSERT INTO CHI_TIET_DICH_VU(Ma_can_ho,Ma_dich_vu,So_luong,Ngay_bat_dau,Ngay_ket_thuc) VALUES
('CH1','DV1',1,'1/1/2024','2/2/2024'),
('CH2','DV1',1,'1/2/2024','2/3/2024'),
('CH2','DV2',1,'1/3/2024','2/4/2024'),
('CH1','DV3',1,'1/4/2024','2/5/2024'),
('CH4','DV1',1,'1/5/2024','2/6/2024'),
('CH5','DV3',1,'1/6/2024','2/7/2024'),
('CH1','DV2',1,'1/7/2024','2/8/2024')
GO
INSERT INTO THANH_TOAN(So_tai_khoan,Ten_ngan_hang) VALUES
('123','ABC'),
('456','ACB'),
('789','ABC')
GO
INSERT INTO HOA_DON(Ma_can_ho,Ma_thanh_toan,Ma_nhan_vien,Ngay_lap) VALUES
('CH1',1,1,'1/1/2024'),
('CH1',1,1,'1/1/2024')

