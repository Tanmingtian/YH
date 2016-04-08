/*
	FLASH中内嵌小字库，只包括本程序用到的汉字点阵
	每行点阵数据，头2字节是汉子的内码，后面32字节是16点阵汉子的字模数据。
*/

unsigned char const g_Hz16[] = {
0xB0,0xB2, 0x02,0x00,0x01,0x00,0x7F,0xFE,0x40,0x02,0x82,0x04,0x02,0x00,0x02,0x04,0xFF,0xFE,// 安 //
           0x04,0x20,0x08,0x20,0x18,0x20,0x06,0x40,0x01,0x80,0x02,0x40,0x0C,0x30,0x30,0x10,

0xB1,0xB8, 0x04,0x00,0x07,0xF0,0x08,0x20,0x14,0x40,0x23,0x80,0x02,0x80,0x0C,0x60,0x30,0x1E,// 备 //
           0xDF,0xF4,0x11,0x10,0x11,0x10,0x1F,0xF0,0x11,0x10,0x11,0x10,0x1F,0xF0,0x10,0x10,

0xB2,0xCE, 0x02,0x00,0x02,0x40,0x04,0x20,0x1F,0xF0,0x02,0x04,0xFF,0xFE,0x04,0x40,0x08,0xA0,// 参 //
           0x13,0x10,0x2C,0x4E,0xC1,0x84,0x0E,0x10,0x00,0x60,0x01,0x80,0x0E,0x00,0x70,0x00,

0xB2,0xE2, 0x00,0x00,0x40,0x44,0x27,0xE4,0x24,0x54,0x85,0x54,0x65,0x54,0x25,0x54,0x0D,0x54,// 测 //
           0x15,0x54,0x25,0x54,0xE5,0x54,0x21,0x04,0x22,0x84,0x24,0x44,0x28,0x54,0x20,0x08,

0xB4,0xA5, 0x20,0x20,0x20,0x20,0x3C,0x20,0x48,0x24,0x51,0xFE,0xFD,0x24,0x55,0x24,0x55,0x24,// 触 //
           0x7D,0x24,0x55,0x24,0x55,0xFC,0x7D,0x20,0x54,0x28,0x54,0x3C,0x55,0xE2,0x8C,0x82,

0xB4,0xF2, 0x10,0x00,0x10,0x00,0x10,0x04,0x13,0xFE,0xFC,0x20,0x10,0x20,0x14,0x20,0x18,0x20,// 打 //
           0x30,0x20,0xD0,0x20,0x10,0x20,0x10,0x20,0x10,0x20,0x10,0x20,0x50,0xA0,0x20,0x40,

0xB6,0xC8, 0x01,0x00,0x00,0x84,0x3F,0xFE,0x22,0x20,0x22,0x28,0x3F,0xFC,0x22,0x20,0x23,0xE0,// 度 //
           0x20,0x00,0x2F,0xF0,0x22,0x20,0x21,0x40,0x20,0x80,0x43,0x60,0x8C,0x1E,0x30,0x04,

0xB9,0xAB, 0x00,0x00,0x00,0x80,0x04,0x80,0x04,0x40,0x08,0x40,0x08,0x20,0x11,0x10,0x21,0x0E,// 公 //
           0xC2,0x04,0x02,0x00,0x04,0x00,0x08,0x40,0x10,0x20,0x1F,0xF0,0x00,0x10,0x00,0x00,

0xB9,0xE2, 0x01,0x00,0x21,0x08,0x11,0x0C,0x09,0x10,0x09,0x20,0x01,0x04,0xFF,0xFE,0x04,0x40,// 光 //
           0x04,0x40,0x04,0x40,0x04,0x40,0x08,0x40,0x08,0x42,0x10,0x42,0x20,0x3E,0x40,0x00,

0xBA,0xCD, 0x02,0x00,0x07,0x00,0x78,0x00,0x08,0x04,0x0A,0xFE,0xFF,0x84,0x08,0x84,0x18,0x84,// 和 //
           0x1C,0x84,0x2A,0x84,0x2A,0x84,0x48,0x84,0x88,0xFC,0x08,0x84,0x08,0x00,0x08,0x00,

0xBA,0xEC, 0x10,0x00,0x10,0x08,0x23,0xFC,0x20,0x20,0x44,0x20,0xF8,0x20,0x10,0x20,0x20,0x20,// 红 //
           0x40,0x20,0xFC,0x20,0x40,0x20,0x00,0x20,0x1C,0x20,0xE0,0x24,0x47,0xFE,0x00,0x00,

0xBB,0xA4, 0x10,0x80,0x10,0x60,0x10,0x24,0x13,0xFE,0xFE,0x04,0x12,0x04,0x16,0x04,0x1B,0xFC,// 护 //
           0x32,0x04,0xD2,0x00,0x12,0x00,0x12,0x00,0x12,0x00,0x14,0x00,0x54,0x00,0x28,0x00,

0xBB,0xD5, 0x12,0x10,0x12,0x10,0x2A,0x90,0x2A,0x90,0x4F,0xBE,0x90,0x44,0x1F,0x84,0x24,0xA4,// 徽 //
           0x6F,0x24,0xA2,0x24,0x25,0x28,0x2F,0x98,0x22,0x10,0x2A,0xA8,0x32,0x46,0x26,0x84,

0xBC,0xC7, 0x00,0x00,0x20,0x08,0x17,0xFC,0x10,0x08,0x00,0x08,0x00,0x08,0xF0,0x08,0x13,0xF8,// 记 //
           0x12,0x08,0x12,0x00,0x12,0x00,0x12,0x02,0x16,0x02,0x1A,0x02,0x11,0xFE,0x00,0x00,

0xBC,0xEC, 0x10,0x40,0x10,0x40,0x10,0xA0,0x10,0xA0,0xFD,0x10,0x12,0x0E,0x35,0xF4,0x30,0x00,// 检 //
           0x58,0x40,0x56,0x48,0x91,0x4C,0x11,0x48,0x11,0x50,0x10,0x04,0x1F,0xFE,0x10,0x00,

0xBF,0xD8, 0x10,0x40,0x10,0x20,0x13,0xFE,0x12,0x02,0xFC,0x54,0x10,0x88,0x15,0x04,0x18,0x00,// 控 //
           0x30,0x08,0xD3,0xFC,0x10,0x20,0x10,0x20,0x10,0x20,0x10,0x24,0x57,0xFE,0x20,0x00,

0xC1,0xBF, 0x00,0x10,0x1F,0xF8,0x10,0x10,0x1F,0xF0,0x10,0x14,0xFF,0xFE,0x00,0x00,0x1F,0xF0,// 量 //
           0x11,0x10,0x1F,0xF0,0x11,0x10,0x1F,0xF0,0x01,0x00,0x1F,0xF0,0x01,0x00,0x7F,0xFC,

0xC1,0xC6, 0x01,0x00,0x00,0x84,0x1F,0xFE,0x10,0x00,0x90,0x00,0x57,0xF8,0x50,0x10,0x10,0x20,// 疗 //
           0x30,0x40,0x50,0x40,0xD0,0x40,0x10,0x40,0x20,0x40,0x22,0x40,0x41,0x40,0x00,0x80,

0xC2,0xBC, 0x00,0x10,0x3F,0xF8,0x00,0x10,0x00,0x10,0x1F,0xF0,0x00,0x10,0x00,0x14,0xFF,0xFE,// 录 //
           0x01,0x08,0x11,0x10,0x09,0xA0,0x05,0x40,0x09,0x20,0x11,0x1E,0x65,0x04,0x02,0x00,

0xC3,0xFE, 0x11,0x10,0x11,0x14,0x1F,0xFE,0x11,0x10,0xFD,0x18,0x13,0xFC,0x16,0x08,0x1B,0xF8,// 摸 //
           0x32,0x08,0xD3,0xF8,0x10,0x40,0x1F,0xFE,0x10,0x40,0x10,0xA0,0x51,0x1C,0x26,0x08,

0xC6,0xB7, 0x00,0x10,0x1F,0xF8,0x10,0x10,0x10,0x10,0x10,0x10,0x1F,0xF0,0x10,0x10,0x02,0x04,// 品 //
           0x7F,0xFE,0x42,0x84,0x42,0x84,0x42,0x84,0x42,0x84,0x42,0x84,0x7E,0xFC,0x42,0x84,

0xC6,0xC1, 0x00,0x08,0x3F,0xFC,0x20,0x08,0x20,0x08,0x3F,0xF8,0x22,0x20,0x21,0x48,0x2F,0xFC,// 屏 //
           0x22,0x20,0x22,0x24,0x3F,0xFE,0x22,0x20,0x22,0x20,0x42,0x20,0x84,0x20,0x08,0x20,

0xC6,0xD7, 0x01,0x10,0x40,0xA0,0x27,0xFC,0x20,0xA0,0x02,0xA8,0x01,0xB0,0xEF,0xFE,0x20,0x08,// 谱 //
           0x23,0xFC,0x22,0x08,0x22,0x08,0x23,0xF8,0x2A,0x08,0x32,0x08,0x23,0xF8,0x02,0x08,

0xC6,0xF7, 0x3E,0xF8,0x22,0x88,0x22,0x88,0x22,0x88,0x3E,0xF8,0x01,0x20,0x01,0x14,0xFF,0xFE,// 器 //
           0x02,0x80,0x0C,0x60,0x30,0x18,0xFE,0xFE,0x22,0x88,0x22,0x88,0x22,0x88,0x3E,0xF8,

0xC9,0xE8, 0x01,0xF0,0x21,0x10,0x11,0x10,0x11,0x10,0x01,0x10,0x02,0x0E,0xF4,0x00,0x13,0xF8,// 设 //
           0x11,0x08,0x11,0x10,0x10,0x90,0x10,0xA0,0x14,0x40,0x18,0xB0,0x13,0x0E,0x0C,0x04,

0xCA,0xFD, 0x08,0x40,0x49,0x40,0x2A,0x40,0x08,0x84,0xFF,0xFE,0x19,0x08,0x2C,0x88,0x4A,0x88,// 数 //
           0x10,0x88,0xFE,0x90,0x22,0x50,0x22,0x20,0x14,0x50,0x18,0x88,0x25,0x0E,0x42,0x04,

0xCB,0xBE, 0x00,0x08,0x3F,0xFC,0x00,0x08,0x00,0x48,0xFF,0xE8,0x00,0x08,0x00,0x88,0x3F,0xC8,// 司 //
           0x20,0x88,0x20,0x88,0x20,0x88,0x20,0x88,0x3F,0x88,0x20,0x88,0x00,0x28,0x00,0x10,

0xCD,0xA3, 0x10,0x80,0x10,0x48,0x17,0xFC,0x20,0x00,0x23,0xF8,0x62,0x08,0xA3,0xF8,0x20,0x00,// 停 //
           0x2F,0xFE,0x28,0x02,0x33,0xF4,0x20,0x40,0x20,0x40,0x20,0x40,0x21,0x40,0x20,0x80,

0xCD,0xE2, 0x08,0x40,0x08,0x40,0x08,0x40,0x10,0x40,0x1F,0x40,0x21,0x60,0x21,0x50,0x62,0x48,// 外 //
           0x92,0x46,0x0A,0x42,0x04,0x40,0x08,0x40,0x10,0x40,0x20,0x40,0x40,0x40,0x00,0x40,

0xCE,0xAC, 0x10,0x80,0x10,0xA0,0x20,0x94,0x21,0xFE,0x49,0x10,0xFB,0x10,0x15,0xFC,0x21,0x10,// 维 //
           0x41,0x10,0xFD,0xFC,0x01,0x10,0x01,0x10,0x1D,0x14,0xE1,0xFE,0x41,0x00,0x01,0x00,

0xCE,0xC2, 0x00,0x08,0x43,0xFC,0x32,0x08,0x12,0x08,0x83,0xF8,0x62,0x08,0x22,0x08,0x0B,0xF8,// 温 //
           0x10,0x00,0x27,0xFC,0xE4,0xA4,0x24,0xA4,0x24,0xA4,0x24,0xA4,0x2F,0xFE,0x20,0x00,

0xCF,0xDE, 0x00,0x08,0x7D,0xFC,0x45,0x08,0x49,0x08,0x49,0xF8,0x51,0x08,0x49,0x08,0x49,0xF8,// 限 //
           0x45,0x04,0x45,0x88,0x45,0x50,0x69,0x20,0x51,0x10,0x41,0x4E,0x41,0x84,0x41,0x00,

0xD0,0xA3, 0x10,0x40,0x10,0x20,0x10,0x04,0x13,0xFE,0xFC,0x00,0x10,0x88,0x31,0x06,0x3A,0x8A,// 校 //
           0x54,0x88,0x50,0x50,0x90,0x50,0x10,0x20,0x10,0x50,0x10,0x88,0x13,0x0E,0x1C,0x04,

0xD0,0xB5, 0x10,0x20,0x10,0x28,0x10,0x24,0x17,0xFE,0xFC,0x20,0x12,0xA0,0x32,0xA0,0x3A,0xA4,// 械 //
           0x57,0xE4,0x52,0xA8,0x92,0xA8,0x12,0x90,0x14,0xB0,0x18,0x52,0x10,0x8A,0x13,0x06,

0xD1,0xF8, 0x08,0x20,0x04,0x40,0x02,0x88,0x7F,0xFC,0x01,0x00,0x3F,0xF8,0x01,0x00,0xFF,0xFE,// 养 //
           0x04,0x40,0x08,0x30,0x34,0x4E,0xC4,0x44,0x04,0x40,0x04,0x40,0x08,0x40,0x10,0x40,

0xD1,0xF9, 0x12,0x08,0x11,0x10,0x10,0xA0,0x17,0xFC,0xFC,0x40,0x10,0x50,0x3B,0xF8,0x34,0x40,// 样 //
           0x50,0x40,0x50,0x44,0x9F,0xFE,0x10,0x40,0x10,0x40,0x10,0x40,0x10,0x40,0x10,0x40,

0xD2,0xBD, 0x00,0x08,0x7F,0xFC,0x44,0x00,0x44,0x10,0x4F,0xF8,0x50,0x80,0x40,0x88,0x5F,0xFC,// 医 //
           0x40,0x80,0x41,0x40,0x41,0x30,0x42,0x18,0x4C,0x08,0x40,0x00,0x7F,0xFC,0x00,0x00,

0xD2,0xC7, 0x08,0x00,0x08,0x80,0x08,0x64,0x12,0x24,0x12,0x04,0x32,0x08,0x51,0x08,0x91,0x10,// 仪 //
           0x10,0x90,0x10,0xA0,0x10,0x40,0x10,0xA0,0x11,0x10,0x12,0x08,0x14,0x0E,0x18,0x04,

0xD3,0xA1, 0x06,0x04,0x78,0xFE,0x40,0x84,0x40,0x84,0x40,0x84,0x44,0x84,0x7E,0x84,0x40,0x84,// 印 //
           0x40,0x84,0x40,0x84,0x40,0x84,0x4E,0xA8,0x70,0x90,0x00,0x80,0x00,0x80,0x00,0x80,

0xD3,0xD0, 0x02,0x00,0x02,0x04,0xFF,0xFE,0x04,0x00,0x04,0x10,0x0F,0xF8,0x08,0x10,0x18,0x10,// 有 //
           0x2F,0xF0,0x48,0x10,0x88,0x10,0x0F,0xF0,0x08,0x10,0x08,0x10,0x08,0x50,0x08,0x20,

0xD6,0xB9, 0x01,0x00,0x01,0x00,0x01,0x00,0x11,0x00,0x11,0x00,0x11,0x10,0x11,0xF8,0x11,0x00,// 止 //
           0x11,0x00,0x11,0x00,0x11,0x00,0x11,0x00,0x11,0x00,0x11,0x04,0xFF,0xFE,0x00,0x00,

0xD6,0xC3, 0x3F,0xF8,0x24,0x48,0x3F,0xF8,0x01,0x00,0x7F,0xFC,0x01,0x00,0x1F,0xF0,0x10,0x10,// 置 //
           0x1F,0xF0,0x10,0x10,0x1F,0xF0,0x10,0x10,0x1F,0xF0,0x10,0x14,0xFF,0xFE,0x00,0x00,

0xD6,0xC6, 0x04,0x04,0x24,0x04,0x25,0x04,0x3F,0xA4,0x24,0x24,0x44,0xA4,0xFF,0xE4,0x04,0x24,// 制 //
           0x3F,0xA4,0x24,0xA4,0x24,0xA4,0x24,0x84,0x26,0x84,0x25,0x04,0x04,0x14,0x04,0x08,

0xD6,0xCA, 0x00,0x78,0x3F,0x80,0x20,0x80,0x20,0x84,0x3F,0xFE,0x20,0x80,0x20,0x88,0x2F,0xFC,// 质 //
           0x28,0x08,0x28,0x88,0x28,0x88,0x28,0x88,0x49,0x08,0x42,0x70,0x8C,0x0C,0x30,0x04,

0xD7,0xBC, 0x01,0x40,0x41,0x20,0x31,0x24,0x13,0xFE,0x02,0x20,0x16,0x28,0x1B,0xFC,0x12,0x20,// 准 //
           0x22,0x28,0xE3,0xFC,0x22,0x20,0x22,0x20,0x22,0x24,0x23,0xFE,0x22,0x00,0x02,0x00,


/* 最后一行必须用0xFF,0xFF结束，这是字库数组结束标志 */
0xFF,0xFF

};
