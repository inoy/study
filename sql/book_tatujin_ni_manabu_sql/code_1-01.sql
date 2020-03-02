DROP DATABASE IF EXISTS tatujin;
CREATE DATABASE tatujin;
USE tatujin;

-- 日本語使うため utf8mb4 に設定しておきたい 予期しない動作防止するため
-- SHOW VARIABLES like 'char%';

CREATE TABLE PopTbl (
    pref_name VARCHAR(32) PRIMARY KEY,
    population INTEGER NOT NULL
);

INSERT INTO PopTbl(pref_name, population) VALUES('徳島', 100), ('香川', 200) , ('愛媛', 150) , ('高知', 200) , ('福岡', 300) , ('佐賀', 100) , ('長崎', 200) , ('東京', 400) , ('群馬', 50);

CREATE TABLE PopTbl2 (
    pref_name VARCHAR(32),
    sex CHAR(1) NOT NULL,
    population INTEGER NOT NULL,
    PRIMARY KEY (pref_name , sex)
);

INSERT INTO PopTbl2(pref_name, sex, population) VALUES('徳島', '1',	60 ), ('徳島', '2', 40 ), ('香川', '1', 100), ('香川', '2', 100), ('愛媛', '1', 100), ('愛媛', '2', 50 ), ('高知', '1', 100), ('高知', '2', 100), ('福岡', '1', 100), ('福岡', '2', 200), ('佐賀', '1', 20 ), ('佐賀', '2', 80 ), ('長崎', '1', 125), ('長崎', '2', 125), ('東京', '1', 250), ('東京', '2', 150);


SELECT 
    pref_name,
    SUM(CASE
        WHEN sex = '1' THEN population
        ELSE 0
    END) AS cnt_m,
    SUM(CASE
        WHEN sex = '2' THEN population
        ELSE 0
    END) AS cnt_f
FROM
    PopTbl2
GROUP BY pref_name;
