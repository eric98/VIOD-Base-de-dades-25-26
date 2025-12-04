CREATE TABLE regio (
	Codi INT PRIMARY KEY,
	Nom VARCHAR(20)
);

CREATE TABLE provincia (
	Codi INT PRIMARY KEY,
	Nom VARCHAR(20),
	Codi_regio INT,
	FOREIGN KEY (Codi_regio) REFERENCES regio(Codi)
);

CREATE TABLE localitat (
	Codi INT PRIMARY KEY,
	Nom VARCHAR(20),
	Codi_provincia INT,
	FOREIGN KEY (Codi_provincia) REFERENCES provincia(Codi)
);

CREATE TABLE empleat (
	ID_E INT PRIMARY KEY,
	DNI_E CHAR(9),
	Nom VARCHAR(20),
	Salari INT,
	Codi_localitat INT,
	FOREIGN KEY (Codi_localitat) REFERENCES localitat(Codi)
);
