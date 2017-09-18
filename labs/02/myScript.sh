echo " b)"

Documentation_count=$(find ./$1/Documentation -type f| wc -l)
echo "# Documentation:" $Documentation_count
arch_count=$(find ./$1/arch -type f | wc -l)
echo "# arch:" $arch_count
block_count=$(find ./$1/block -type f | wc -l)
echo "# block:" $block_count
certs_count=$(find ./$1/certs -type f | wc -l)
echo "# certs:" $certs_count
crypto_count=$(find ./$1/crypto -type f | wc -l)
echo "# crypto:" $crypto_count
drivers_count=$(find ./$1/drivers -type f | wc -l)
echo "# drivers:" $drivers_count
firmware_count=$(find ./$1/firmware -type f | wc -l)
echo "# firmware:" $firmware_count
fs_count=$(find ./$1/fs -type f | wc -l)
echo "# fs:" $fs_count
include_count=$(find ./$1/include -type f | wc -l)
echo "# include:" $include_count
init_count=$(find ./$1/init -type f | wc -l)
echo "# init:" $init_count
ipc_count=$(find ./$1/ipc -type f | wc -l)
echo "# ipc:" $ipc_count
kernel_count=$(find ./$1/kernel -type f | wc -l)
echo "# kernel:" $kernel_count
lib_count=$(find ./$1/lib -type f | wc -l)
echo "# lib:" $lib_count
mm_count=$(find ./$1/mm -type f | wc -l)
echo "# mm:" $mm_count
net_count=$(find ./$1/net -type f | wc -l)
echo "# net:" $net_count
samples_count=$(find ./$1/samples -type f | wc -l)
echo "# samples:" $samples_count
scripts_count=$(find ./$1/scripts -type f | wc -l)
echo "# scripts:" $scripts_count
security_count=$(find ./$1/security -type f | wc -l)
echo "# security:" $security_count
sound_count=$(find ./$1/sound -type f | wc -l)
echo "# sound:" $sound_count
tools_count=$(find ./$1/tools -type f | wc -l)
echo "# tools:" $tools_count
usr_count=$(find ./$1/usr -type f | wc -l)
echo "# usr:" $usr_count
virt_count=$(find ./$1/virt -type f | wc -l)
echo "# virt:" $virt_count


echo "----------------------------------------------------------------------------------"


echo "c)"

num_of_README=$(find ./$1/ | grep -i README | wc -l)
echo "# Number of README files:" $num_of_README
num_of_Kconfig=$(find ./$1/ | grep -i Kconfig | wc -l)
echo "# Number of Kconfig files:" $num_of_Kconfig
num_of_Kbuild=$(find ./$1/ | grep -i Kbuild | wc -l)
echo "# Number of Kbuild files:" $num_of_Kbuild
num_of_Makefiles=$(find ./$1/ | grep -i Makefile | wc -l)
echo "# Number of Makefiles files:" $num_of_Makefiles
num_of_c=$(find ./$1/ -type f | grep "\.c$" | wc -l)
echo "# Number of .c files:" $num_of_c
num_of_h=$(find ./$1/ -type f | grep "\.h$" | wc -l)
echo "# Number of .h files:" $num_of_h
num_of_pl=$(find ./$1/ -type f | grep "\.pl$"| wc -l)
echo "# Number of .pl files:" $num_of_pl
num_total=$(find ./$1/ | wc -l)
num_of_other=$((num_total-num_of_README-num_of_Kconfig-num_of_Kbuild-num_of_Makefiles-num_of_c-num_of_h-num_of_pl))
echo "# Number of other files:" $num_of_other
echo""
echo "# Total number of files:" $num_total


echo "----------------------------------------------------------------------------------"


echo "e)"


mkdir ./C_FILES
mkdir ./H_FILES

c_files=$(find . -type f | grep "\.c$")
h_files=$(find . -type f | grep "\.h$")


for i in ${c_files[@]}
do
	
	cp -RfX $i ./C_FILES/
done

for i in ${h_files[@]}
do
	cp -RfX $i ./H_FILES/
done


echo "----------------------------------------------------------------------------------"


echo "d)"


declare -i n=0

for i in ${c_files[@]}
do
	if grep "#include <linux/module.h>" $i > ./msc; then
    	n=$((n + 1))
  	fi
done

for i in ${h_files[@]}
do
	if grep "#include <linux/module.h>" $1 >> ./msc; then
    	n=$((n + 1))
  	fi
done


echo "# Number of times the \" #include <linux/module.h>\" appears = $n"


echo "----------------------------------------------------------------------------------"


echo "e)"

declare -i c=0
declare -i h=0

for i in ${c_files[@]}
do
	c=$((c + 1))
done

for i in ${h_files[@]}
do
	h=$((h + 1))
done

echo "# Number of .c files: $c"
echo "# Number of .h files: $h"
