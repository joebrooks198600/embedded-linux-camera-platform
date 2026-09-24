#include <fcntl.h>
#include <linux/videodev2.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main(void)
{
    const char *device = "/dev/video0";

    int fd = open(device, O_RDWR);

    if (fd < 0) {
        perror("open /dev/video0");
        return 1;
    }

    struct v4l2_capability cap = {0};

    if (ioctl(fd, VIDIOC_QUERYCAP, &cap) < 0) {
        perror("VIDIOC_QUERYCAP");
        close(fd);
        return 1;
    }

    printf("Camera device: %s\n", device);
    printf("Driver: %s\n", cap.driver);
    printf("Card: %s\n", cap.card);
    printf("Bus: %s\n", cap.bus_info);

    close(fd);
    return 0;
}
