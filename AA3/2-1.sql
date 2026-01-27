/*Exercici1: Escriu les instruccions per consultar la següent metainformació. 
Abans de començar, necessites fer:
• Crear base de dades hyrule.
• Crear taules herois, mascares i armes al teu gust. La taula armes 
necessita els camps id i nom.
• Inserir algunes dades a les taules creades.*/

-- a) Amb les taules mysql.user i mysql.tables_priv crea una consulta per a 
-- que et retorni els privilegis dels usuaris sobre les taules de la BD hyrule
-- que tens dins SGBD.
SELECT * FROM mysql.tables_priv WHERE db='hyrule'\G

-- b) Amb la taula views de la base de dades information_schema consulta la 
-- definició de les vistes creades al SGBD. Pensa que abans hauràs de crear 
-- una vista o vistes sobre alguna de les taules de la BD hyrule.
CREATE VIEW herois_disponibles AS
	SELECT nom FROM herois;

SELECT view_definition FROM information_schema.views WHERE table_schema='hyrule';

-- c) Consulta el nombre de files que té cada taula de la base de dades hyrule.
SELECT table_name, table_rows FROM information_schema.tables WHERE table_schema='hyrule';

-- d) Mostra les columnes de la taula armes de la base de dades hyrule.
SELECT column_name FROM information_schema.columns WHERE table_name='armes' AND table_schema='hyrule';
