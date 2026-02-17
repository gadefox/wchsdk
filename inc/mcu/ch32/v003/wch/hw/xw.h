// Encoder for some of the proprietary 'XW' RISC-V instructions present on the
// QingKe RV32 processor. Examples:
//  c_xw_lbu(a3, a1, 27); // c.xw.lbu a3, 27(a1)
//  c_xw_sb(a0, s0, 13);  // c.xw.sb a0, 13(s0)
//  c_xw_lhu(a5, a5, 38); // c.xw.lhu a5, 38(a5)
//  c_xw_sh(a2, s1, 14);  // c.xw.sh a2, 14(s1)
// Thanks to @macyler, @jnk0le, @duk for this reverse engineering.

#pragma once

/******************************************************************************/
/*                              XW Opcodes                                    */
/******************************************************************************/

// [15] [14] [13] [12] [11] [10] [9] [8] [7] [6] [5] [4] [3] [2] [1] [0]
//  o4   o3   o2   i0   i4   i3   r2  r2  r2  i2  i1  r1  r1  r1  o1  o0

//------------------------------------------------------------------------------

typedef enum {
  XW_s0 = 0b000,
  XW_s1 = 0b001,
  XW_a0 = 0b010,
  XW_a1 = 0b011,
  XW_a2 = 0b100,
  XW_a3 = 0b101,
  XW_a4 = 0b110,
  XW_a5 = 0b111
} xw_reg_t;

#define xw_r(x)  XW_##x

// Registers to encoding:  [9] [8] [7] [6] [5] [4] [3] [2] [1] [0]
//                          r2  r2  r2  0   0   r1  r1  r1  0   0

#define XW_REGS_ENC(r1, r2)  ((xw_r(r2) << 7) | (xw_r(r1) << 2))

//------------------------------------------------------------------------------
// OP to encoding:
//  [15] [14] [13] [12] [11] [10] [9] [8] [7] [6] [5] [4] [3] [2] [1] [0]
//   o4   o3   o2   0    0    0    0   0   0   0   0   0   0   0   o1  o0

#define XW_OP_ENC(op)  (((op) & 0b11) | (((op) & 0b11100) << 10))

//------------------------------------------------------------------------------
// IMM to encoding1:  [12] [11] [10] [9] [8] [7] [6] [5] [4] [3] [2] [1] [0]
//                     i0   i4   i3   0   0   0   i2  i1  0   0   0   0   0

#define XW_IMM_ENC(imm)  ((((imm) & 1) << 12) | (((imm) & 0b11000) << 7) | \
                          (((imm) & 0b110) << 4))

#define xw_imm_assert1(imm)  asm_assert(BETWEEN((imm), 0, 32))
#define xw_imm_assert2(imm)  asm_assert(((imm) & 1) == 0)

//------------------------------------------------------------------------------
// Integer encodings of the possible compressed registers.

#define XW_ENC(op, r1, r2, imm)  xw_imm_assert1(imm); \
  .2byte (XW_OP_ENC(op) | XW_REGS_ENC(r1, r2) | XW_IMM_ENC(imm))

// Compressed load byte, zero-extend result
#define c_xw_lbu(rd, rs, imm)  XW_ENC(0b00100, rd, rs, imm)

// Compressed load half, zero-extend result
#define c_xw_lhu(rd, rs, imm)  XW_ENC(0b00110, rd, rs, imm)

// Compressed store byte
#define c_xw_sb(rs1, rs2, imm) xw_imm_assert2(imm); XW_ENC(0b10100, rs1, rs2, imm)

// Compressed store half
#define c_xw_sh(rs1, rs2, imm) xw_imm_assert2(imm); XW_ENC(0b10110, rs1, rs2, imm)

// FIXME:
#define XW_OP_LBUSP  0b1000000000000000
#define XW_OP_STSP   0b1000000001000000

#define XW_OP_LHUSP  0b1000000000100000
#define XW_OP_SHSP   0b1000000001100000

//------------------------------------------------------------------------------
