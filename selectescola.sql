-- a) Extreure el nombre total d'alumnes (comptar-los).
SELECT COUNT(*) AS 'Nombre total d\'alumnes' FROM alumnes;

-- b) Extreure el nombre total d'alumnes matriculats en l'any acadèmic '2022'.
SELECT COUNT(*) FROM matriculacions
	WHERE AnyAcademic IN ('20212022','20222023');
-- Versió alternativa
SELECT COUNT(*) FROM matriculacions
	WHERE AnyAcademic LIKE '2022%' OR AnyAcademic LIKE '%2022'

-- c) Extreure els ID dels professors amb NIF que comença amb '4'.
SELECT ID_P FROM professors WHERE NIF_P LIKE '4%';
-- Versió alternativa
SELECT ID_P FROM professors
	WHERE SUBSTRING(NIF_P,1,1) = '4';

-- d) Extreure el nom i telèfon dels professors que tenen telèfon acabat en '9'.
SELECT nom, telefon FROM professors
	WHERE telefon LIKE '%9';

-- e) Extreure el num_matricula, nom i telefon dels alumnes que han nascut entre el 1995 i el 2005.
SELECT NumMatricula, Nom, Telefon FROM alumnes
	WHERE YEAR(DataNaixement) BETWEEN 1995 AND 2005;

-- f) Extreure el nom i el telèfon dels professors que imparteixen alguna assignatura. 
SELECT Nom,Telefon FROM professors
	WHERE ID_P IN (
		SELECT ID_Professor FROM assignatures
	);

-- g) Extreure el nom i any acadèmic de les assignatures en que està matriculat algun alumne.

-- Versió SQL 1
SELECT assignatures.Nom, matriculacions.AnyAcademic FROM matriculacions, assignatures
        WHERE matriculacions.CodiAssignatura=assignatures.Codi;

-- Versió SQL 2
SELECT assignatures.Nom, matriculacions.AnyAcademic FROM matriculacions
	INNER JOIN assignatures
	ON matriculacions.CodiAssignatura=assignatures.Codi;

-- h) Extreure el nom de cada assignatura i nombre total d'alumnes que estan matriculats en cadascuna.
-- Pas 1:
-- 	A la taula matriculacions tenim llistades les matriculacions 
-- 	que s'han fet a cada assignatura.
SELECT * FROM matriculacions;

-- Pas 2:
--	Podem agrupar el registres per a mostrar la quantitat
--	de matriculacions que hi ha a cada assignatura.
SELECT CodiAssignatura, COUNT(*) FROM matriculacions GROUP BY CodiAssignatura;

-- Pas 3:
--	Combinem la taula matriculacions amb assignatures
--	per a poder mostrar el nom de l'assignatura en comptes
--	del seu codi.
SELECT assignatures.Nom, COUNT(*) FROM assignatures
	JOIN matriculacions
	ON assignatures.Codi = matriculacions.CodiAssignatura
	GROUP BY matriculacions.CodiAssignatura;

-- Pas 4:
--	Afegim algunes simplificacions sintàctiques
SELECT a.Nom, COUNT(*) AS 'Quantitat d\'alumnes matriculats'
	FROM assignatures AS a
        JOIN matriculacions AS m
        ON a.Codi = m.CodiAssignatura
        GROUP BY m.CodiAssignatura;
