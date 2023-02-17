//
// Created by nilicheng on 23-2-16.
//

#include "server.h"
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

namespace remote {

static void HandleSockServerInput(struct bufferevent *bev, void *ctx) {
  struct evbuffer *input = bufferevent_get_input(bev);
  struct evbuffer *output = bufferevent_get_output(bev);
  char buf[1024];
  bufferevent_read(bev, buf, sizeof(buf));
  printf("client send data: %s\n", buf);

  evbuffer_add_buffer(output, input);
}

static void echo_event_cb(struct bufferevent *bev, short events, void *ctx) {
  if (events & BEV_EVENT_ERROR) {
	perror("Error from bufferevent");
  }
  if (events & (BEV_EVENT_EOF | BEV_EVENT_ERROR)) {
	bufferevent_free(bev);
  }
}

static void listener_cb(evutil_socket_t fd, short events, void *arg) {
  struct event_base *base = (struct event_base *)arg;
  struct sockaddr_storage ss;
  socklen_t slen = sizeof(ss);
  int client_fd = accept(fd, (struct sockaddr *)&ss, &slen);
  if (client_fd < 0) {
	perror("accept");
  } else if (client_fd > FD_SETSIZE) {
	close(client_fd);
  } else {
	struct bufferevent *bev = bufferevent_socket_new(base, client_fd, BEV_OPT_CLOSE_ON_FREE);
	bufferevent_setcb(bev, HandleSockServerInput, NULL, echo_event_cb, NULL);
	bufferevent_enable(bev, EV_READ | EV_WRITE);
  }
}

int Server::Run() {
  struct event_base *base;
  struct event *listener_event;

  int listenfd = socket(AF_INET, SOCK_STREAM, 0);
  if (listenfd < 0) {
	perror("socket error");
	return 1;
  }
  int reuseaddr_on = 1;
  setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr_on, sizeof(reuseaddr_on));
  struct sockaddr_in servaddr;
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  in_addr_t ip_addr = inet_addr(this->ip_.c_str());
  servaddr.sin_addr.s_addr = htonl(ip_addr);
  servaddr.sin_port = htons(this->port_);
  if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
	perror("bind error");
	return 1;
  }
  if (listen(listenfd, 10) < 0) {
	perror("listen error");
	return 1;
  }

  base = event_base_new();
  if (!base) {
	fprintf(stderr, "Couldn't create an event_base: exiting\n");
	return 1;
  }

  listener_event = event_new(base, listenfd, EV_READ | EV_PERSIST, listener_cb, (void *)base);
  if (!listener_event) {
	fprintf(stderr, "Couldn't create an event: exiting\n");
	return 1;
  }
  event_add(listener_event, NULL);

  event_base_dispatch(base);

  return 0;
}

} // namespace remote
