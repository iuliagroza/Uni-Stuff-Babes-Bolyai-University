FROM bitnami/testlink:1

USER 0

RUN echo 'Mutex posixsem' >>/opt/bitnami/apache/conf/httpd.conf
