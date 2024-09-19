#include <libudev.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define USB_MOUNT_PATH "/media/usb"

void check_usb_sticks() {
    struct udev *udev;
    struct udev_enumerate *enumerate;
    struct udev_list_entry *devices, *dev_list_entry;
    struct udev_device *dev;

    udev = udev_new();
    if (!udev) {
        fprintf(stderr, "Cannot create udev context.\n");
        exit(1);
    }

    enumerate = udev_enumerate_new(udev);
    udev_enumerate_add_match_subsystem(enumerate, "block");
    udev_enumerate_scan_devices(enumerate);
    devices = udev_enumerate_get_list_entry(enumerate);

    int usb_count = 0;

    udev_list_entry_foreach(dev_list_entry, devices) {
        const char *path = udev_list_entry_get_name(dev_list_entry);
        dev = udev_device_new_from_syspath(udev, path);

        if (udev_device_get_devtype(dev) && strcmp(udev_device_get_devtype(dev), "partition") == 0) {
            const char *devnode = udev_device_get_devnode(dev);
            char mount_path[256];
            snprintf(mount_path, sizeof(mount_path), "%s%d", USB_MOUNT_PATH, usb_count + 1);

            // Try to mount the USB device
            char mount_cmd[512];
            snprintf(mount_cmd, sizeof(mount_cmd), "mount %s %s", devnode, mount_path);
            if (system(mount_cmd) == 0) {
                char file_path[512];
                snprintf(file_path, sizeof(file_path), "%s/1.txt", mount_path);

                if (access(file_path, F_OK) == 0) {
                    printf("USB stick %d with 1.txt detected at %s\n", usb_count + 1, mount_path);
                    usb_count++;
                }

                // Unmount the USB device
                char umount_cmd[512];
                snprintf(umount_cmd, sizeof(umount_cmd), "umount %s", mount_path);
                system(umount_cmd);
            }
        }

        udev_device_unref(dev);
    }

    udev_enumerate_unref(enumerate);
    udev_unref(udev);

    if (usb_count < 3) {
        printf("Not all USB sticks detected. Only %d found.\n", usb_count);
    } else {
        printf("All 3 USB sticks detected.\n");
    }
}

int main() {
    check_usb_sticks();
    return 0;
}