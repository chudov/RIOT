/*
 * Copyright (C) 2019 Alexander Chudov <chudov@gmail.com>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     boards_deRFmega256
 * @{
 *
 * @file
 * @brief       Board specific definitions for the deRFmega256 modules
 *
 * @author      Alexander Chudov <chudov@gmail.com>
 */

#ifndef BOARD_H
#define BOARD_H

#include "cpu.h"
#include "periph/eeprom.h"

#include "net/eui_provider.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name xtimer configuration values
 * @{
 */
#define XTIMER_WIDTH        (16)
#define XTIMER_HZ           (CLOCK_CORECLOCK / 64)
#define XTIMER_BACKOFF      (40)
/** @} */

/**
 * @name    MAC configuration
 * @{
 */
#define MAC_ADDR            (0x1fe4)
/** @} */

/**
 * @brief    Constant in EEPROM provides a EUI-64, this is also printed on the board
 */
static inline int _eeprom_mac_get_eui64(const void *arg, eui64_t *addr)
{
    (void) arg;
    uint64_t mac_addr;
    if (eeprom_read(MAC_ADDR, &mac_addr, sizeof(eui64_t)) == sizeof(eui64_t))
    {
        addr->uint64 = byteorder_htonll(mac_addr);
        return 0;
    }
    else {
        return -1;
    }

}

/**
 * @name    EUI sources on the board
 *
 * @{
 */
static const eui64_conf_t eui64_conf[] = {
    /* AT24Mac is present on the board */
    {
        .provider = _eeprom_mac_get_eui64,
        .arg = NULL,
        .type = NETDEV_AT86RF2XX,
        .index = 0,
    },
};

#define EUI64_PROVIDER_NUMOF    ARRAY_SIZE(eui64_conf)
/** @} */

/**
 * @brief Initialize board specific hardware, including clock, LEDs and std-IO
 */
void board_init(void);

#ifdef __cplusplus
}
#endif

#endif /* BOARD_H */
/** @} */
