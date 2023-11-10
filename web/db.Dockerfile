FROM mysql:8

COPY initdb/ /docker-entrypoint-initdb.d/

COPY mysql_conf/ /etc/mysql/conf.d/

ENV MYSQL_DATABASE=sfmltetris