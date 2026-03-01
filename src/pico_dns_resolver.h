#include "lwip/ip_addr.h"

static void dns_found_cb(const char *name, const ip_addr_t *ipaddr, void *callback_arg);

void resolve_hostname(const char *hostname, ip_addr_t *addr);