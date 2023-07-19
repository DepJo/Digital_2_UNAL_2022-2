PACKAGES=libc libcompiler_rt libbase libfatfs liblitespi liblitedram libliteeth liblitesdcard liblitesata bios
PACKAGE_DIRS=/opt/Litex/litex/litex/soc/software/libc /opt/Litex/litex/litex/soc/software/libcompiler_rt /opt/Litex/litex/litex/soc/software/libbase /opt/Litex/litex/litex/soc/software/libfatfs /opt/Litex/litex/litex/soc/software/liblitespi /opt/Litex/litex/litex/soc/software/liblitedram /opt/Litex/litex/litex/soc/software/libliteeth /opt/Litex/litex/litex/soc/software/liblitesdcard /opt/Litex/litex/litex/soc/software/liblitesata /opt/Litex/litex/litex/soc/software/bios
LIBS=libc libcompiler_rt libbase libfatfs liblitespi liblitedram libliteeth liblitesdcard liblitesata
TRIPLE=riscv64-unknown-elf
CPU=vexriscv
CPUFAMILY=riscv
CPUFLAGS=-march=rv32i2p0_m     -mabi=ilp32 -D__vexriscv__
CPUENDIANNESS=little
CLANG=0
CPU_DIRECTORY=/opt/Litex/litex/litex/soc/cores/cpu/vexriscv
SOC_DIRECTORY=/opt/Litex/litex/litex/soc
PICOLIBC_DIRECTORY=/opt/Litex/pythondata-software-picolibc/pythondata_software_picolibc/data
COMPILER_RT_DIRECTORY=/opt/Litex/pythondata-software-compiler_rt/pythondata_software_compiler_rt/data
export BUILDINC_DIRECTORY
BUILDINC_DIRECTORY=/home/depjo/Descargas/SoC_project/build/software/include
LIBC_DIRECTORY=/opt/Litex/litex/litex/soc/software/libc
LIBCOMPILER_RT_DIRECTORY=/opt/Litex/litex/litex/soc/software/libcompiler_rt
LIBBASE_DIRECTORY=/opt/Litex/litex/litex/soc/software/libbase
LIBFATFS_DIRECTORY=/opt/Litex/litex/litex/soc/software/libfatfs
LIBLITESPI_DIRECTORY=/opt/Litex/litex/litex/soc/software/liblitespi
LIBLITEDRAM_DIRECTORY=/opt/Litex/litex/litex/soc/software/liblitedram
LIBLITEETH_DIRECTORY=/opt/Litex/litex/litex/soc/software/libliteeth
LIBLITESDCARD_DIRECTORY=/opt/Litex/litex/litex/soc/software/liblitesdcard
LIBLITESATA_DIRECTORY=/opt/Litex/litex/litex/soc/software/liblitesata
BIOS_DIRECTORY=/opt/Litex/litex/litex/soc/software/bios
LTO=0
BIOS_CONSOLE_FULL=1