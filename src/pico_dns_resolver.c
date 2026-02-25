#include "lwip/dns.h"
#include "lwip/ip_addr.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "wl_log.h"

static void dns_found_cb(const char *name, const ip_addr_t *ipaddr, void *callback_arg) {
    if (ipaddr) {
        WL_LOGI("DNS", "Hostname '%s' resolved to IP: %s", name, ipaddr_ntoa(ipaddr));
    } else {
        WL_LOGE("DNS", "Failed to resolve hostname '%s'", name);
    }
}

void resolve_hostname(const char *hostname) {

    ip_addr_t dns0 = *dns_getserver(0);
    WL_LOGI("NET", "DNS0: %s", ipaddr_ntoa(&dns0));

    ip_addr_t addr; // we can pass NULL here since we're using a callback

    cyw43_arch_lwip_begin();

    

    err_t err = dns_gethostbyname(hostname, &addr, dns_found_cb, NULL);
    cyw43_arch_lwip_end();

    if (err == ERR_OK) {
        WL_LOGI("DNS", "Hostname '%s' resolved immediately", hostname);
    }
    else if (err == ERR_INPROGRESS) {
        printf("Hostname resolution in progress for '%s'...\n", hostname);
        
    }
    else {
         WL_LOGE("DNS", "dns_gethostbyname('%s') failed: %d (%s)",
                hostname, (int)err, lwip_strerr(err));
    }
}