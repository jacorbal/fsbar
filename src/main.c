/**
 * @file main.c
 *
 * @brief Print mount points use (in percent) and visual bar
 *
 * @author J. A. Corbal <jacorbal@gmail.com>
 *
 * @date Creation date: Wed Dec 18 00:33:17 UTC 2024
 * @date Last update: Wed Dec 18 00:33:17 UTC 2024
 */

/* Project includes */
#include <fsbar.h>

/* Main defintions */
#define FILE_FS_MOUNTS "/proc/mounts"   /* /proc/mounts; /etc/mtab; ... */


/* Main entry */
int main(void)
{
    /* Print mount points information and exit */
    return fprint_mountpoints_percent(stdout, FILE_FS_MOUNTS);
}
