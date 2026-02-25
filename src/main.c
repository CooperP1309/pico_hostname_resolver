#include <stdio.h>
#include "pico/stdlib.h"        // sleep_ms, stdio...
#include "pico/cyw43_arch.h"    // wifi chip library

#include "pico_dns_resolver.h" // our DNS resolver header
#include "secret_wifi_creds.h"

// define for wikilift's logging lib
#define RP2040
#include "wl_log.h"

err_t connect_wifi(const char* ssid, const char* password);

int main() {

// ---------- Basic Inits and Wifi Connections ----------

    stdio_init_all();
    cyw43_arch_init();
    sleep_ms(3000); // give some time for the USB serial to initialize

    WL_LOGI("main", "Starting WiFi connection with SSID: %s, PASSWORD:%s ", SSID, PASSWORD);

    if (connect_wifi(SSID, PASSWORD) != ERR_OK) {
        WL_LOGE("main", "failed to connect to WiFi");
        return -1;
    }
// ---------- DNS RESOLUTION ----------

    const char hostname[] = "www.anticipateapi.com.au";    
    WL_LOGI("main", "now resolving hostname: %s", hostname);

    resolve_hostname(hostname);

    while(1) {
        // keep main alive whilst DNS resolver works in background thread
        
        // call "cyw43_arch_poll()" here if not using "threadsafe_backgroud"
    }

    return 0;
}





err_t connect_wifi(const char *ssid, const char *password) {
    
    // connect to wifi with obtained credentials
    WL_LOGI("main", "connecting to WiFi with credentials:\n    ssid: \"%s\"\n    password: \"%s\"", ssid, password);

    cyw43_arch_enable_sta_mode();
    
    if (cyw43_arch_wifi_connect_timeout_ms(ssid, password, CYW43_AUTH_WPA2_AES_PSK, 30000)) {
        return ERR_CONN;
    }

    WL_LOGI("main", "connected to WiFi successfully");

    return ERR_OK;
}