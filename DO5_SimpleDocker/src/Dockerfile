FROM alpine:3.20 AS build
RUN apk add --no-cache build-base fcgi-dev
WORKDIR /app
COPY server/server.c .
RUN gcc -Wall -Wextra -Werror server.c -o server_fcgi -lfcgi

FROM alpine:3.20
RUN apk add --no-cache nginx fcgi spawn-fcgi curl \
 && adduser -D -H -s /sbin/nologin app \
 && mkdir -p /run/nginx \
 && chown -R app:app /run/nginx /var/lib/nginx /var/log/nginx

WORKDIR /app
COPY --from=build /app/server_fcgi /app/server_fcgi
COPY nginx/nginx.conf /etc/nginx/nginx.conf

HEALTHCHECK --interval=30s --timeout=3s --start-period=5s --retries=3 \
  CMD curl -fsS http://127.0.0.1:81/status || exit 1

USER app
CMD spawn-fcgi -p 8080 /app/server_fcgi && nginx -g 'daemon off;'
