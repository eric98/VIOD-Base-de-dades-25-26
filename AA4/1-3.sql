/* Exercici3. Amb l’ajuda dels apunts i de la documentació, recrea la base de  dades empresa. */

CREATE DATABASE empresa;
\c empresa;

-- a) Crea l’objecte tipus adreca amb els atributs carrer, ciutat i codi_postal.
CREATE TYPE adressa AS (
	carrer VARCHAR(20),
	ciutat VARCHAR(20),
	codi_postal CHAR(5)
);

-- b) Crea l’objecte tipus persona amb els atributs nom, casada, edat i adreca.
CREATE TYPE persona AS (
	nom VARCHAR(20),
	casada BOOL,
	edat INT,
	adreca adressa
);

-- c) Crea la taula treballadors amb els camps id, persona, sou i carrec.
CREATE TABLE treballadors (
	id SERIAL,
	usuari persona,
	sou INT,
	carrec VARCHAR(20),
	PRIMARY KEY(id)
);

-- d) Insereix 3 registres a la taula treballadors.
INSERT INTO treballadors (usuari, sou, carrec) VALUES 
	(ROW('Ramon','TRUE',28,ROW('C/ 1','Barcelona','08029')), 600, 'President'),
	(ROW('Chuky','FALSE',33,ROW('C/ Brook','Washington DC','12345')), 0, 'Amic'),
	(ROW('Shrek','TRUE', 28,ROW('C/ Pantà','Molt llunyà','54321')), 200, 'Cavaller');

-- e) Llista els camps nom i sou de tots els treballadors.
SELECT (usuari).nom, sou FROM treballadors;
