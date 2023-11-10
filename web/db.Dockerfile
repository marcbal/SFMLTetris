FROM mysql:8

COPY initdb/ /docker-entrypoint-initdb.d/

ENV MYSQL_DATABASE=sfmltetris