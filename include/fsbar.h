/**
 * @file fsbar.h
 *
 * @brief Filesystem mount points display declaration
 *
 * @author J. A. Corbal <jacorbal@gmail.com>
 */

/* System includes */
#include <stdio.h>  /* FILE*/

/* Main defintions */
#define BAR_CHARACTER_FILL '#'              /**< Bar full character */
#define BAR_CHARACTER_EMPTY '.'             /**< Bar empty character */
#define BAR_WIDTH_MAX (50)                  /**< Maximum bar width */
#define BAR_WIDTH_RESTRICTION_PERCENT (40)  /**< Restriction of the bar */
#define TABLE_COLUMN_OFFSET (5)             /**< Column separation (char) */


/**
 * @brief Get the used percentage for a mount point
 *
 * @param mountpoint Mount point to calculate size of
 *
 * @return Percent of use on that mount point
 */
double disk_usage_percent(const char *mountpoint);

/**
 * @brief Print the percentage bar
 *
 * @param stream  Output stream
 * @param percent Percentage to display on screen in a text bar
 * @param width   Maximum width of the bar in characters
 */
void fprint_bar(FILE *stream, double percent, int width);

/**
 * @brief Print mount points table
 *
 * @param stream   Output stream
 * @param filename Mounts information filename
 *
 * @return 0 if successful
 *         1 if cannot open the mounts file
 *         2 if cannot get terminal size
 */
int fprint_mountpoints_percent(FILE *stream, const char *filename);

/**
 * @brief Print header on screen
 *
 * @param stream Output stream
 */
void fprint_header(FILE *stream);
