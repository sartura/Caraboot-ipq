/*
 * 8devices Habanero config
 *
 * Copyright (C) 2019 Mantas Pucka <mantas@8devices.com>
 *
 * SPDX-License-Identifier:GPL-2.0-or-later
*/

#ifndef _IPQ40XX_HABANERO_H
#define _IPQ40XX_HABANERO_H

#include <configs/ipq40xx_cdp.h>

#define CONFIG_QCA_MMC

#ifdef CONFIG_QCA_MMC
#define CONFIG_CMD_MMC
#define CONFIG_MMC
#define CONFIG_EFI_PARTITION
#define CONFIG_GENERIC_MMC
#define CONFIG_ENV_IS_IN_MMC
#define CONFIG_SYS_MMC_ENV_DEV  0
#endif

#define CONFIG_IPQ40XX_PCI
#ifdef CONFIG_IPQ40XX_PCI
#define CONFIG_PCI
#define CONFIG_CMD_PCI
#define CONFIG_PCI_SCAN_SHOW
#endif

#define CONFIG_QPIC_NAND
#ifdef CONFIG_QPIC_NAND
#define CONFIG_RBTREE
#define CONFIG_CMD_UBI
#endif

#define MTDPARTS_DEFAULT	"mtdparts=nand2:0x1E40000@0x1C0000(firmware);nand0:128m(ubi1),128m(ubi2)"
#define MTDIDS_DEFAULT		"nand0=nand0,nand2=nand2"

#define CONFIG_FACTORY_IMG_FILENAME    "habanero.bin"

//USB_BOOT
#define CONFIG_USB_BOOT
#define CFG_USB_BOOT_MAX_PARTITIONS_SCAN        16
#define CFG_USB_RECOVERY_LOAD_ADDR              "0x88000000"
#define CFG_USB_RECOVERY_MAX_BOOT_SIZE		"0x7000000" /* 112 MB */
#define CFG_USB_RECOVERY_MAX_FILE_SIZE          "0x1e40000" /* 30.25 MB */
#define CFG_USB_RECOVERY_NAND_DEVICE		"2"
#define CFG_USB_BOOT_FILENAME                   "8dev_uimage.bin"
#define CFG_USB_RECOVERY_FILENAME               "8dev_recovery.bin"
#define CFG_USB_RECOVERY_FW_PART_NAME		"firmware"
#define CONFIG_RESET_BUTTON_GPIO		8

#define CONFIG_EXTRA_ENV_SETTINGS							\
	"bootcmd=run setup && run bootlinux\0"						\
	"setup=partname=1 && setenv bootargs ${args_common}\0"				\
	"args_common=rootfstype=squashfs\0"						\
	"bootlinux=run boot0 boot1 boot2 boot3 boot4 || reset\0"				\
	"boot0=usb_boot_file\0"								\
	"boot1=echo Booting from partition: ${partname}\0"				\
	"boot2=nand device 2\0"								\
	"boot3=nboot firmware\0"							\
	"boot4=bootm\0"									\
	"do_recovery=run rec1 rec2 rec3 rec4; reset\0"					\
	"rec1=echo Doing firmware recovery!\0"						\
	"rec2=sleep 2 && tftpboot ${tftp_loadaddr} ${recovery_file}\0"			\
	"rec3=nand device 2 && nand erase.part firmware\0"				\
	"rec4=nand write ${fileaddr} firmware ${filesize}\0"				\
	"tftp_loadaddr=0x84000000\0"							\
	"recovery_file=fwupdate.bin\0"							\
	"mtdparts=" MTDPARTS_DEFAULT "\0"						\

#endif /* _IPQ40XX_HABANERO_H */
