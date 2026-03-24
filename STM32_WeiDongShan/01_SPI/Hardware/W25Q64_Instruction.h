#ifndef __W25Q64_INSTRUCTION_H
#define __W25Q64_INSTRUCTION_H

#include <stdint.h>


/* ========================== 基础控制指令 ========================== */
#define W25Q64_CMD_WRITE_ENABLE         0x06    // 写使能 (Write Enable)，置位WEL位
#define W25Q64_CMD_WRITE_DISABLE        0x04    // 写禁止 (Write Disable)，复位WEL位
#define W25Q64_CMD_READ_STATUS_REG1     0x05    // 读状态寄存器1 (RDSR1)，含BUSY/WEL位
#define W25Q64_CMD_READ_STATUS_REG2     0x35    // 读状态寄存器2 (RDSR2)，含Quad Enable位
#define W25Q64_CMD_WRITE_STATUS_REG     0x01    // 写状态寄存器 (WRSR)，配置保护/Quad模式等
#define W25Q64_CMD_RESET_ENABLE         0x66    // 复位使能 (RESET ENABLE)，复位前需先发此指令
#define W25Q64_CMD_RESET_DEVICE         0x99    // 设备复位 (RESET DEVICE)，执行后芯片软复位

/* ========================== 数据读取指令 ========================== */
#define W25Q64_CMD_READ_DATA            0x03    // 标准读数据 (READ)，CLK≤50MHz，1字节指令+3字节地址
#define W25Q64_CMD_FAST_READ            0x0B    // 快速读数据 (FAST READ)，CLK≤80MHz，多1字节空周期
#define W25Q64_CMD_FAST_READ_DUAL       0x3B    // 双线快速读 (FAST READ DUAL OUT)，CLK≤104MHz
#define W25Q64_CMD_FAST_READ_QUAD       0x6B    // 四线快速读 (FAST READ QUAD OUT)，CLK≤104MHz

/* ========================== 数据编程指令 ========================== */
#define W25Q64_CMD_PAGE_PROGRAM         0x02    // 页编程 (PAGE PROGRAM)，单次最多写256字节
#define W25Q64_CMD_QUAD_PAGE_PROGRAM    0x32    // 四线页编程 (QUAD PAGE PROGRAM)，加速写操作

/* ========================== 数据擦除指令 ========================== */
#define W25Q64_CMD_SECTOR_ERASE_4K      0x20    // 扇区擦除 (4KB)，擦除时间~40ms
#define W25Q64_CMD_BLOCK_ERASE_32K      0x52    // 块擦除 (32KB)，擦除时间~150ms
#define W25Q64_CMD_BLOCK_ERASE_64K      0xD8    // 块擦除 (64KB)，擦除时间~200ms
#define W25Q64_CMD_CHIP_ERASE           0xC7    // 整片擦除 (CHIP ERASE)，擦除时间~20s

/* ========================== 地址/ID 指令 ========================== */
#define W25Q64_CMD_READ_JEDEC_ID        0x9F    // 读JEDEC ID，返回厂商ID(EFh)+类型ID(40h)+容量ID(17h)
#define W25Q64_CMD_READ_UNIQUE_ID       0x4B    // 读唯一ID (Unique ID)，64位唯一标识

/* ========================== 状态寄存器位定义 ========================== */
// 状态寄存器1 (SR1) 关键位
#define W25Q64_SR1_BUSY_BIT             0x01    // BIT0: BUSY位，1=芯片忙(擦除/编程中)，0=空闲
#define W25Q64_SR1_WEL_BIT              0x02    // BIT1: WEL位，1=写使能，0=写禁止
// 状态寄存器2 (SR2) 关键位
#define W25Q64_SR2_QE_BIT               0x02    // BIT1: QE位，1=使能四线模式，0=禁用

/* ========================== 硬件参数 ========================== */
#define W25Q64_PAGE_SIZE                256     // 页大小：256字节/页
#define W25Q64_SECTOR_SIZE              4096    // 扇区大小：4KB/扇区
#define W25Q64_BLOCK_SIZE_64K           65536   // 块大小：64KB/块
#define W25Q64_TOTAL_SIZE               8388608 // 总容量：8MB (64Mbit)


#define W25Q64_DUMMY_BYTE 							0xFF

#endif // W25Q64_H

