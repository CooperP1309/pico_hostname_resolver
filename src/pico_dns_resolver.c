#include "lwip/dns.h"
#include "lwip/ip_addr.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "wl_log.h"

static void dns_found_cb(const char *name, const ip_addr_t *ipaddr, void *callback_arg) {
    
    ip_addr_t *passed_ip = (ip_addr_t *)callback_arg;

    if (ipaddr && passed_ip) {
        *passed_ip = *ipaddr; // copy resolved IP to caller's variable
        WL_LOGI("DNS", "Hostname '%s' resolved to IP: %s", name, ipaddr_ntoa(ipaddr));
    } else {
        WL_LOGE("DNS", "Failed to resolve hostname '%s'", name);
    }
}

void resolve_hostname(const char *hostname, ip_addr_t *addr) {

    ip_addr_t dns0 = *dns_getserver(0);
    WL_LOGI("NET", "DNS0: %s", ipaddr_ntoa(&dns0));

    // dns_gethostbyname() must be wrapped wrapped with lwip's begin and end calls
    // to ensure thread safety when using lwip in a background thread
    cyw43_arch_lwip_begin();

    // dns_gethostbyname() (name to resolve, addr to store for immmadiate results,
    //                       callback for async results, callback arg)
    // Callback arg is where the address will be stored if results are async
    err_t err = dns_gethostbyname(hostname, addr, dns_found_cb, addr);
    
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