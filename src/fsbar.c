/**
 * @file fsbar.c
 *
 * @brief Filesystem mount points display implementation
 *
 * @author J. A. Corbal <jacorbal@gmail.com>
 */

/* System includes */
#include <float.h>          /* FLT_EPSILON */
#include <mntent.h>         /* setmntent, getmntent */
#include <stdio.h>          /* fprintf, fputc, stdout, FILE */
#include <sys/ioctl.h>      /* winsize, ioctl */
#include <sys/statvfs.h>    /* statvfs */

/* Local includes */
#include <fsbar.h>


/* Get the used percentage by a mount point */
double disk_usage_percent(const char *mountpoint)
{
    struct statvfs buf;  /* Structure for filesystem statistics */
    double sz_total;
    double sz_available;
    double sz_used;

    /* Get filesystem statistics */
    statvfs(mountpoint, &buf);

    sz_total = (double) (buf.f_blocks * buf.f_frsize);
    sz_available = (double) (buf.f_bfree * buf.f_frsize);
    sz_used = sz_total - sz_available;

    return ((double) (sz_used / sz_total) * (double) 100.);
}


/* Print the percentage bar */
void fprint_bar(FILE *stream, double percent, int width)
{
    int width_effective = (width < BAR_WIDTH_MAX) ? width: BAR_WIDTH_MAX;
    int m = (int) ((percent * width_effective) / 100);

    fputc('[', stream);
    for (int i = 0; i < width_effective; ++i) {
        if (i <= m && m != 0) {
            fputc(BAR_CHARACTER_FILL, stream);
        } else {
            fputc(BAR_CHARACTER_EMPTY, stream);
        }
    }
    fputc(']', stream);
}


/* Print mount points table */
int fprint_mountpoints_percent(FILE *stream, const char *filename)
{
    FILE *fp;           /**< File pointer for the filesystem */
    struct winsize w;   /**< Window size information */
    struct mntent *ent; /**< Mount points information */
    double n;           /**< Percentage of use on the mount point */

    /* Get the window size */
    if (ioctl(0, TIOCGWINSZ, &w) != 0) {
        /* Exit with error */
        perror("ioctl");
        return 2;
    }

    /* Open the filesystem descriptor for the mounts file */
    fp = setmntent(filename, "r");
    if (fp == NULL) {
        /* Exit with error */
        perror("setmntent");
        return 1;
    }

    /* Print header */
    fprint_header(stdout);

    /* Print the information for every mount point */
    while (NULL != (ent = getmntent(fp))) {
        /* Get the data */
        n = disk_usage_percent(ent->mnt_dir);

        if (n >= FLT_EPSILON) {
            /* Print the percentage bar */
            fprintf(stream, "%-24s", ent->mnt_dir);
            fprintf(stream, "%*.2f%%" , TABLE_COLUMN_OFFSET, n);
            fprintf(stream, "%*s", TABLE_COLUMN_OFFSET, " ");
            fprint_bar(stream,
                    n, w.ws_col - BAR_WIDTH_RESTRICTION_PERCENT);
            fprintf(stream, "\n");
        }
    }

    /* Close the stream associated with the filesystem descriptor file */
    endmntent(fp);    

    return 0;
}


/* Print output header */
void fprint_header(FILE *stream)
{
    fprintf(stream, "%-24s", "[MOUNT POINT]");
    fprintf(stream, "%*s", TABLE_COLUMN_OFFSET, "[USE %]");
    fprintf(stream, "\n");
}
