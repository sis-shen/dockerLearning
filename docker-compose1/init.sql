DROP DATABASE if EXISTS test;
CREATE DATABASE test DEFAULT CHARACTER SET utf8mb4;
use test;

create TABLE users(
	sno int(11) DEFAULT NULL,
	sname varchar(50) DEFAULT NULL
)ENGINE=INNODB DEFAULT CHARSET=utf8mb4;

INSERT INTO users (sno,sname) VALUES (1,'pony'),(2,'sup');

