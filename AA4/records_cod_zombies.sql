CREATE DATABASE codzombies;
\c codzombies;

CREATE TYPE tipus_record AS ENUM('SOLO','COOP');

CREATE TYPE record_obj AS (
    maxima_ronda INT,
    mapa VARCHAR(20),
    tipus tipus_record
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
    VALUES (ROW(56,'Kino der toten','SOLO'), 1),
        (ROW(32,'Estación','COOP'), 2),
        (ROW(123,'Der riese','SOLO'), 1);