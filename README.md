# IoT basics with ZYBO (Zynq)

This is a project to create an IoT device with ZYBO (Zynq). I implemented a web server using Python and bottle framework, which works with another C++ application. The C++ application controls my custom IPs (such as PWM) implemented in PL block. A user can control LEDs, 3-color LEDs, buttons and switches mounted on ZYBO board.

<img src="01_doc\pic.jpg">

<img src="01_doc\overview.jpg">

YouTube Video: https://youtu.be/z613J8RVpog

## Development Environment
 - Target Board: ZYBO (Z7-20)
 - Host PC: Windows 10 64-bit 
    - Vivado 2017.4 WebPACK (for HW design)
    - Xilinx SDK 2017.4 (for C++ application development)
    - Visual Studio Code (for Python script development)
 - Host PC: Ubuntu 16.04 (on VirtualBox 5.2.4)
    - PetaLinux 2017.4 (for Linux/Boot image making)

## Source Code
 - Vivado Project
    - https://github.com/take-iwiw/ZYBO_IoT_Vivado
- Xilinx SDK Project
    - https://github.com/take-iwiw/ZYBO_IoT_SDK
- PetaLinux Project
    - https://github.com/take-iwiw/ZYBO_IoT_PetaLinux
    - includes:
        - C application binary (built by XSDK)
        - Python script
        - init.d script

## How to Build
<img src="01_doc\flow.jpg">

You need to work on PetaLinux. Pre-built C application binary and Python script are already installed in PetaLinux project. So, all you need is the process 4 in the above picture.
```sh
git clone https://github.com/take-iwiw/ZYBO_IoT_PetaLinux.git
cd ZYBO_IoT_PetaLinux/PjIoT
# Modify `SERVER_URL` variable in main.js depending on your environment. The current value (192.168.1.87) is in my environment.
code project-spec/meta-user/recipes-apps/myinit/files/ServerIoT/static/js/main.js &
petalinux-build
petalinux-package --boot --force --fsbl images/linux/zynq_fsbl.elf --fpga images/linux/design_iot_wrapper.bit --u-boot
```

Copy created files (`images/linux/BOOT.bin` and `images/linux/image.ub`) to SD Card (FAT 32 format). After starting ZYBO with the SD card, you can access `http://192.168.1.87:8080/` from a browser in the same network as ZYBO. (again, the IP address varies depending on the environment).


## More Information
https://qiita.com/take-iwiw/items/e9311292c5078d785699

## Keywords (technology I used in this project)
- bottle
- Ajax
- Device Tree (dts, dtsi)
- User space IO (UIO)
- Named pipe
- Modifying the Petalinux Yocto recipe to install a directory
