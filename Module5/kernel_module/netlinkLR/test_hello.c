#include <linux/netlink.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define NETLINK_USER 31

#define MAX_PAYLOAD 1024 /* maximum payload size*/
struct sockaddr_nl src_addr, dest_addr;
struct nlmsghdr *nlh = NULL;
/*
    struct nlmsghdr {
       __u32 nlmsg_len;    // Length of message including header
       __u16 nlmsg_type;   // Type of message content 
       __u16 nlmsg_flags;  // Additional flags 
       __u32 nlmsg_seq;    // Sequence number 
       __u32 nlmsg_pid;    // Sender port ID 
   };
*/
struct iovec iov;
/*
    struct iovec {
        void  *iov_base;    // начальный адрес
        size_t iov_len;     // количество передаваемых байт
    };
*/
int sock_fd;
struct msghdr msg;
/*
struct msghdr {
    void         *msg_name;       // optional address
    socklen_t     msg_namelen;    // size of address
    struct iovec *msg_iov;        // scatter/gather array
    size_t        msg_iovlen;     // # elements in msg_iov
    void         *msg_control;    // ancillary data, see below
    size_t        msg_controllen; // ancillary data buffer len
    int           msg_flags;      // flags on received message
};
*/

int main()
{
    sock_fd = socket(PF_NETLINK, SOCK_RAW, NETLINK_USER);
    if (sock_fd < 0)
        return -1;

    memset(&src_addr, 0, sizeof(src_addr));
    src_addr.nl_family = AF_NETLINK;
    src_addr.nl_pid = getpid();             // self pid

    bind(sock_fd, (struct sockaddr *)&src_addr, sizeof(src_addr));

    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.nl_family = AF_NETLINK;
    dest_addr.nl_pid = 0;                   // For Linux Kernel 
    dest_addr.nl_groups = 0;                // unicast 

    // int NLMSG_SPACE(size_t len) - 
    // return the number of bytes that a netlink message with payload of len would occupy.
    nlh = (struct nlmsghdr *)malloc(NLMSG_SPACE(MAX_PAYLOAD));
    memset(nlh, 0, NLMSG_SPACE(MAX_PAYLOAD));
    nlh->nlmsg_len = NLMSG_SPACE(MAX_PAYLOAD);
    nlh->nlmsg_pid = getpid();
    nlh->nlmsg_flags = 0;

    // void *NLMSG_DATA(struct nlmsghdr *nlh) - 
    // return a pointer to the payload associated with the passed nlmsghdr.
    strcpy(NLMSG_DATA(nlh), "Hello");

    iov.iov_base = (void *)nlh;
    iov.iov_len = nlh->nlmsg_len;
    msg.msg_name = (void *)&dest_addr;
    msg.msg_namelen = sizeof(dest_addr);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    printf("Sending message to kernel\n");
    sendmsg(sock_fd, &msg, 0);
    printf("Waiting for message from kernel\n");

    /* Read message from kernel */
    recvmsg(sock_fd, &msg, 0);
    printf("Received message payload: %s\n", NLMSG_DATA(nlh));
    close(sock_fd);
}