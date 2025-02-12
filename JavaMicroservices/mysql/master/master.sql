CREATE USER 'root'@'%' IDENTIFIED BY 'root';
grant replication slav, replication client on *.* to 'root'@'%';
flush privileges;