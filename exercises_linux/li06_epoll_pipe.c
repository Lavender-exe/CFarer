// CFarer - Linux Internals Exercise 06
// TOPIC: epoll - event-driven I/O multiplexing
// DIFFICULTY: Intermediate  PLATFORM: Linux
// PURPOSE: Linux internals / high-performance I/O
//
// epoll is Linux's scalable I/O event notification mechanism.
// Unlike select/poll (O(n) scan), epoll is O(1) per event - suitable for
// thousands of connections (servers, event loops, async runtimes).
//
// API:
//   epoll_create1(0)          - create epoll instance, returns fd
//   epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event) - register fd
//   epoll_wait(epfd, events, maxevents, timeout_ms) - block until events
//
// Task:
//   1. pipe(fds) - create a pipe (fds[0]=read, fds[1]=write).
//   2. epoll_create1(0) - create epoll fd.
//   3. Register fds[0] (read end) for EPOLLIN with epoll_ctl.
//   4. Write "hello epoll\n" to fds[1].
//   5. epoll_wait(epfd, events, 1, 1000) - wait up to 1 second.
//   6. On EPOLLIN: read from fds[0] and print the message.
//   7. Close all fds.

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/epoll.h>

int main(void) {
    int fds[2];
    // TODO 1: pipe(fds)
    if (pipe(fds) != 0) {
        perror("pipe");
        return 1;
    }

    // TODO 2: epoll_create1(0) -> epfd
    int epfd = -1; // replace with epoll_create1(0)
    if (epfd < 0) {
        perror("epoll_create1");
        return 1;
    }

    // TODO 3: epoll_ctl - register fds[0] for EPOLLIN
    struct epoll_event ev = {0};
    ev.events  = EPOLLIN;
    ev.data.fd = fds[0];
    // epoll_ctl(epfd, EPOLL_CTL_ADD, fds[0], &ev);

    // TODO 4: write to pipe
    const char *msg = "hello epoll\n";
    // write(fds[1], msg, strlen(msg));

    // TODO 5: epoll_wait
    struct epoll_event events[1];
    int nready = 0; // replace: nready = epoll_wait(epfd, events, 1, 1000)
    printf("epoll_wait returned %d event(s)\n", nready);

    // TODO 6: read on EPOLLIN
    if (nready > 0 && (events[0].events & EPOLLIN)) {
        char buf[64] = {0};
        // ssize_t n = read(events[0].data.fd, buf, sizeof(buf)-1);
        // printf("read: %s", buf);
        (void)buf;
    }

    // TODO 7: close fds
    close(fds[0]);
    close(fds[1]);
    // close(epfd);
    return 0;
}

// I AM NOT DONE
