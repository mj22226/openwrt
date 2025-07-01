#!/bin/bash

FDISK=$(which fdisk) || { echo "E: You must have fdisk" && exit 1; }
LOSETUP=$(which losetup) || { echo "E: You must have losetup" && exit 1; }
roottype=$(findmnt -n -o SOURCE / -o FSTYPE)
case ${roottype} in
	overlay)
		FSCKEXT4=$(which fsck.ext4) || { echo "E: You must have fsck.ext4" && exit 1; }
		RESIZE2FS=$(which resize2fs) || { echo "E: You must have resize2fs" && exit 1; }
		rootsource=$(findmnt -n -o SOURCE / | sed 's~\[.*\]~~')		# i.e. /dev/mmcblk0p2
		rootdevice=${rootsource%p*}				# i.e. /dev/mmcblk0
		partitions=${rootsource##*p}
		;;
	ext4)
		FSCKEXT4=$(which fsck.ext4) || { echo "E: You must have fsck.ext4" && exit 1; }
		RESIZE2FS=$(which resize2fs) || { echo "E: You must have resize2fs" && exit 1; }
		rootsource=$(findmnt -n -o SOURCE / | sed 's~\[.*\]~~')		# i.e. /dev/mmcblk0p2
		rootdevice=${rootsource%p*}					# i.e. /dev/mmcblk0
		partitions=${rootsource##*p}

		# Resizing partitions
		lastsector=$(${FDISK} -l ${rootdevice} |grep "Disk ${rootdevice}" |awk '{print $7}')
		lastsector=$(( $lastsector - 1 ))
		startfrom=$(${FDISK} -l ${rootdevice} |grep ${rootsource} |awk '{print $2}')
		partend=$(${FDISK} -l ${rootdevice} |grep ${rootsource} |awk '{print $3}')
		[[ $lastsector -eq $partend ]] && exit 0
		(echo d; echo $partitions; echo n; echo p; echo ; echo $startfrom; echo $lastsector ; echo w;) | fdisk $rootdevice

		# Start resizing filesystem
		LOOP="$(losetup -f)"
		${LOSETUP} ${LOOP} ${rootsource}
		${FSCKEXT4} -y ${LOOP}
		${RESIZE2FS} ${LOOP}
		reboot
		;;
esac

exit 0

