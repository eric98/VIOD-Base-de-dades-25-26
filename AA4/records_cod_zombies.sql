CREATE DATABASE codzombies;
\c codzombies;

CREATE TYPE tipus_personatge AS ENUM('NIKOLAI','RICHTOFEN','TAKEO','DEMPSEY');

CREATE TYPE record_obj AS (
    ronda_maxima INT,
    mapa VARCHAR(20),
    personatge tipus_personatge,
    jugatAPC BOOL
);

CREATE TABLE jugadors (
    id SERIAL,
    nom VARCHAR(20),
    data_registre TIMESTAMP,
    regio VARCHAR(20)
);

CREATE TABLE records (
    id SERIAL,
    record record_obj,
    jugador INT,
    PRIMARY KEY (id)
);

INSERT INTO jugadors (nom, data_registre, regio) 
    VALUES('Carla', NOW(), 'Espanya'),
        ('Jordi', NOW(), 'Espanya');

INSERT INTO records (record, jugador) 
    VALUES (ROW(56,'Kino der toten','NIKOLAI', TRUE), 1),
        (ROW(32,'Estación','DEMPSEY', FALSE), 2),
        (ROW(123,'Der riese','TAKEO', FALSE), 1);