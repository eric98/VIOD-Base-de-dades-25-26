/*Exercici5: Escriu les instruccions per crear els següents rols, assignar-los i 
treure’ls privilegis. Abans de començar, necessites fer:
• Crear base de dades hyrule.
• Crear taules herois, mascares i armes al teu gust. La taula armes 
necessita els camps id i nom.
• Inserir algunes dades a les taules creades.*/

-- a) Crea dos rols, un anomenat ORNI amb tots els privilegis sobre la taula herois i mascares i un altre anomenat GERUDO amb tots els privilegis sobre la taula armes.
CREATE ROLE orni; 
GRANT ALL PRIVILEGES ON herois TO orni;
GRANT ALL PRIVILEGES ON mascares TO orni;

CREATE ROLE gerudo;
GRANT ALL PRIVILEGES ON armes TO gerudo;

-- > Comprovació creació rols
SELECT user FROM mysql.user;

-- > Comprovació privilegis
SHOW GRANTS FOR orni;
SHOW GRANTS FOR gerudo;

-- b) Crea un usuari anomenat ganon i atorga-li el rol GERUDO per defecte.
CREATE USER ganon IDENTIFIED BY 'Alumne.123';
GRANT gerudo TO ganon;
SET DEFAULT ROLE gerudo TO ganon;

-- > Comprovació
SHOW GRANTS FOR ganon;

-- c) Connectat amb l'usuari ganon i prova d'executar una consulta sobre la 
-- taula herois i una altra sobre la taula armes.
SELECT * FROM hyrule.herois; -- Es denega la comanda
SELECT * FROM hyrule.armes; -- It works! :)

-- > Veure l'usuari actual
SELECT CURRENT_ROLE();

-- d) A continuació, des de root, atorga el rol ORNI a ganon i repeteix la 
-- consulta sobre la taula armes amb l'usuari ganon.
-- (connectat amb root)
GRANT orni TO ganon;
-- (connectat amb ganon)
SELECT * FROM hyrule.herois; -- Es denega la comanda

-- e) Seguidament, amb l'usuari ganon activa el rol ORNI per a la sessió 
-- actual (SET ROLE) i repeteix una altra vegada la consulta sobre la taula 
-- armes.
SET ROLE orni;
SELECT * FROM hyrule.herois; -- Ja funciona :D

-- f) Desactiva tots els rols de l'usuari ganon.
SET ROLE NONE;

-- > Comprovació 
SELECT CURRENT_ROLE();

-- g) Consulta la taula herois amb l'usuari ganon.
SELECT * FROM hyrule.herois; -- Es denega la comanda

