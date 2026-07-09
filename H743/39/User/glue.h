#ifndef __GLUE_H
#define __GLUE_H

#include "./SYSTEM/sys/sys.h"

/* Comment out to disable step-by-step debug mode */
//#define STEP_DEBUG

uint8_t qspi_self_test(void);
uint8_t wifi_self_test(void);
void glue_run(void);

#endif
