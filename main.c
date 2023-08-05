#include <linux/fb.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>

static struct fb_var_screeninfo original_vinfo;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s [save | restore]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "save") == 0) {

        int fb_fd = open("/dev/fb0", O_RDWR);
        if (fb_fd == -1) {
            perror("Error opening framebuffer device");
            return 1;
        }

        if (ioctl(fb_fd, FBIOGET_VSCREENINFO, &original_vinfo)) {
            perror("Error reading original variable information");
            close(fb_fd);
            return 1;
        }

        close(fb_fd);

        FILE *file = fopen("/tmp/framebuffer_vinfo.bin", "wb");
        if (!file) {
            perror("Error opening file");
            return 1;
        }
        fwrite(&original_vinfo, sizeof(original_vinfo), 1, file);
        fclose(file);

        return 0;
    }
    else if (strcmp(argv[1], "restore") == 0) {

        FILE *file = fopen("/tmp/framebuffer_vinfo.bin", "rb");
        if (!file) {
            perror("Error opening file");
            return 1;
        }
        fread(&original_vinfo, sizeof(original_vinfo), 1, file);
        fclose(file);

        int fb_fd = open("/dev/fb0", O_RDWR);
        if (fb_fd == -1) {
            perror("Error opening framebuffer device");
            return 1;
        }

        if (ioctl(fb_fd, FBIOPUT_VSCREENINFO, &original_vinfo)) {
            perror("Error restoring variable information");
            close(fb_fd);
            return 1;
        }

        close(fb_fd);

        return 0;
    }
    else {
        fprintf(stderr, "Unknown option: %s\n", argv[1]);
        fprintf(stderr, "Usage: %s [save | restore]\n", argv[0]);
        return 1;
    }
}