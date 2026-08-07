// sub_42C220 @ 0x0042C220 — __thiscall
// Extracted from BMF.c:36633-37113 by extract.py per incdec.md.

typedef int t_sub_42C220_dword_439CA4[5];
static t_sub_42C220_dword_439CA4& __sub_42C220_dword_439CA4 = *(t_sub_42C220_dword_439CA4*)0x00439CA4;
typedef int t_sub_42C220_dword_439CB8[5];
static t_sub_42C220_dword_439CB8& __sub_42C220_dword_439CB8 = *(t_sub_42C220_dword_439CB8*)0x00439CB8;
typedef int t_sub_42C220_dword_445900;
static t_sub_42C220_dword_445900& __sub_42C220_dword_445900 = *(t_sub_42C220_dword_445900*)0x00445900;
typedef int t_sub_42C220_dword_445904;
static t_sub_42C220_dword_445904& __sub_42C220_dword_445904 = *(t_sub_42C220_dword_445904*)0x00445904;
typedef int t_sub_42C220_dword_445908;
static t_sub_42C220_dword_445908& __sub_42C220_dword_445908 = *(t_sub_42C220_dword_445908*)0x00445908;
typedef int t_sub_42C220_dword_445924;
static t_sub_42C220_dword_445924& __sub_42C220_dword_445924 = *(t_sub_42C220_dword_445924*)0x00445924;
typedef int t_sub_42C220_dword_445928;
static t_sub_42C220_dword_445928& __sub_42C220_dword_445928 = *(t_sub_42C220_dword_445928*)0x00445928;
typedef int t_sub_42C220_dword_44592C;
static t_sub_42C220_dword_44592C& __sub_42C220_dword_44592C = *(t_sub_42C220_dword_44592C*)0x0044592C;
typedef __int16 t_sub_42C220_word_445910[10];
static t_sub_42C220_word_445910& __sub_42C220_word_445910 = *(t_sub_42C220_word_445910*)0x00445910;

#ifndef __PE_DECL___sub_4349F0
#define __PE_DECL___sub_4349F0
typedef void * t_sub_4349F0(void *, int, unsigned int);   // stack arguments only
static t_sub_4349F0& __sub_4349F0 = *(t_sub_4349F0*)0x004349F0;
#endif
#define sub_4349F0 __sub_4349F0
#define sub_42BB20 __sub_42BB20

// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___fgetc
#define __PE_DECL___fgetc
typedef int t_fgetc(FILE1 *);   // _fgetc
static t_fgetc& __fgetc = *(t_fgetc*)0x00431320;
#endif
#define fgetc __fgetc
#ifndef __PE_DECL___fread
#define __PE_DECL___fread
typedef unsigned int t_fread(void *, unsigned int, unsigned int, FILE1 *);   // _fread
static t_fread& __fread = *(t_fread*)0x0042CDCC;
#endif
#define fread __fread
#ifndef __PE_DECL___op_new
#define __PE_DECL___op_new
typedef void *t_op_new(unsigned int);   // ??2@YAPAXI@Z
static t_op_new& __op_new = *(t_op_new*)0x0042CF0A;
#endif
#ifndef __PE_DECL___op_delete
#define __PE_DECL___op_delete
typedef void t_op_delete(void *);       // ??3@YAXPAX@Z
static t_op_delete& __op_delete = *(t_op_delete*)0x0042CF18;
#endif
#define FILE FILE1

PROBE_DECL(__sub_42C220)
__attribute__((force_align_arg_pointer)) __attribute__((thiscall)) int __sub_42C220(int _this, void (__cdecl *sub_42BB20)(int, int, int, int))
{
  PROBE_HIT(__sub_42C220);
  int this_1; // ebx
  char *buf; // eax
  char v4; // fps
  char *buf_1; // esi
  int v6; // edx
  void *Buffer_1; // edi
  int v8; // ebp
  int n2; // eax
  int n4096_10; // ebp
  int v12; // eax
  int v13; // edx
  unsigned int v14; // eax
  _BYTE *v15; // edx
  signed int ElementCount_1; // eax
  signed int ElementCount_8; // ebp
  size_t v18; // eax
  int n8_1; // ebp
  unsigned int v20; // ebx
  int n8; // esi
  size_t v22; // eax
  size_t v23; // eax
  int v24; // esi
  int n4096_2; // ebx
  int n4096_11; // edi
  _BYTE *Buffer__1; // esi
  _BYTE *buf_3; // ecx
  int n4096_4; // edx
  int v30; // ecx
  void (__cdecl *sub_42BB20_1)(int, int, int, int); // eax
  int this_3; // edi
  int v33; // ebp
  int v34; // edx
  int n4096_9; // edi
  _BYTE *buf_4; // ebx
  int n4096_7; // esi
  char n4096_8; // al
  void *buf_5; // esi
  int this_4; // ebx
  unsigned __int8 n33; // al
  int n44_1; // edi
  int v43; // eax
  size_t ElementCount_5; // eax
  int ElementCount_11; // ebp
  int v46; // eax
  size_t ElementCount_6; // eax
  size_t ElementCount_4; // eax
  int ElementCount_10; // ebp
  char v50; // cl
  size_t ElementCount_7; // ebp
  size_t v52; // edx
  int v53; // ebp
  int v54; // eax
  int v55; // esi
  char v56; // cl
  int v57; // edi
  char v58; // cl
  bool v59; // cf
  int v60; // ebp
  int v61; // ecx
  char v62; // al
  size_t ElementCount_3; // eax
  int ElementCount_9; // ebp
  _BYTE *Buffer_; // [esp+0h] [ebp-14Ch] BYREF
  size_t ElementCount_2; // [esp+4h] [ebp-148h]
  int v67; // [esp+8h] [ebp-144h]
  int v68; // [esp+Ch] [ebp-140h]
  int n4096_13; // [esp+10h] [ebp-13Ch]
  int n8_2; // [esp+14h] [ebp-138h]
  void *Buffer; // [esp+18h] [ebp-134h]
  size_t ElementCount; // [esp+1Ch] [ebp-130h]
  int v73; // [esp+20h] [ebp-12Ch]
  int n4096_12; // [esp+24h] [ebp-128h]
  int n4096_3; // [esp+28h] [ebp-124h]
  int v76; // [esp+2Ch] [ebp-120h]
  int n4096_1; // [esp+30h] [ebp-11Ch]
  int n4096; // [esp+34h] [ebp-118h]
  int n4096_6; // [esp+38h] [ebp-114h]
  int v80; // [esp+3Ch] [ebp-110h]
  int n4096_5; // [esp+40h] [ebp-10Ch]
  int v82; // [esp+44h] [ebp-108h]
  _BYTE *v83; // [esp+48h] [ebp-104h]
  char *v84; // [esp+4Ch] [ebp-100h]
  int v85; // [esp+50h] [ebp-FCh]
  _BYTE *v86; // [esp+54h] [ebp-F8h]
  int v87; // [esp+58h] [ebp-F4h]
  _BYTE *Buffer__2; // [esp+5Ch] [ebp-F0h]
  unsigned int ElementCount_12; // [esp+100h] [ebp-4Ch]
  int n44; // [esp+104h] [ebp-48h]
  char Buffer_2[16]; // [esp+108h] [ebp-44h] BYREF
  char Buffer_4[12]; // [esp+118h] [ebp-34h] BYREF
  int v93; // [esp+124h] [ebp-28h]
  size_t v94; // [esp+128h] [ebp-24h]
  char Buffer_3[8]; // [esp+12Ch] [ebp-20h] BYREF
  void *buf_2; // [esp+134h] [ebp-18h]
  int this_2; // [esp+138h] [ebp-14h]

  this_1 = _this;
  buf = (char *)__op_new(2 * *(unsigned __int16 *)(_this + 21) + 16640);
  buf_1 = buf;
  if ( !buf )
    return 7;
  sub_4349F0(buf,0,*(unsigned __int16 *)(this_1 + 21) + 16512);
  v6 = *(unsigned __int16 *)(this_1 + 21);
  Buffer__2 = buf_1 + 0x2000;
  Buffer_1 = buf_1 + 0x4000;
  v84 = buf_1 + 0x4000;
  v83 = buf_1 + 0x4000;
  v86 = buf_1 + 0x4000;
  v8 = (int)(buf_1 + 16640);
  if ( !sub_42BB20 )
    v8 = __sub_42C220_dword_44592C + v6 * __sub_42C220_dword_445928 + 16;
  v85 = v8;
  __sub_42C220_dword_445900 = 0;
  __sub_42C220_dword_445904 = 0;
  __sub_42C220_dword_445908 = 0;
  v87 = __sub_42C220_dword_445924 + v6 - 1;
  n2 = fgetc(*(FILE **)this_1);
  if ( n2 == -1 )
    goto LABEL_52;
  if ( n2 < 2 || n2 > 8 )
  {
    __op_delete(buf_1);
    return 6;
  }
  n4096_10 = 1 << n2;
  v12 = n2 + 1;
  __sub_42C220_word_445910[0] = v12;
  n4096_5 = n4096_10;
  v73 = v12;
  n4096 = n4096_10 + 2;
  n4096_1 = n4096_10 + 2;
  v13 = 1 << v12;
  v14 = (unsigned int)v84;
  v80 = v13;
  v76 = v13;
  v68 = 0;
  n4096_12 = n4096_10 + 1;
  v67 = 0;
  n4096_6 = -1;
  n4096_3 = -1;
  Buffer_ = buf_1 + 8193;
  v15 = v83;
LABEL_9:
  if ( (unsigned int)++v15 >= v14 )
  {
    ElementCount_1 = fgetc(*(FILE **)this_1);
    ElementCount_8 = ElementCount_1;
    if ( ElementCount_1 <= 0 )
      goto LABEL_52;
    v18 = fread(Buffer_1, 1u, ElementCount_1, *(FILE **)this_1);
    v15 = v86;
    v14 = (unsigned int)&buf_1[v18 + 0x4000];
    if ( v14 < (unsigned int)&buf_1[ElementCount_8 + 0x4000] )
      goto LABEL_52;
  }
  v84 = (char *)v14;
  Buffer = Buffer_1;
  buf_2 = buf_1;
  this_2 = this_1;
  n8_1 = 0;
  while ( 1 )
  {
    v20 = (unsigned __int8)*v15;
    v82 = (unsigned __int16)__sub_42C220_word_445910[0];
    n8 = n8_1 + (unsigned __int16)__sub_42C220_word_445910[0];
    if ( n8 <= 8 )
    {
      n8_1 += (unsigned __int16)__sub_42C220_word_445910[0];
      *v15 = v20 >> SLOBYTE(__sub_42C220_word_445910[0]);
      goto LABEL_24;
    }
    if ( ++v15 >= v84 )
    {
      ElementCount = fgetc(*(FILE **)this_2);
      if ( (int)ElementCount <= 0
        || (v22 = fread(Buffer, 1u, ElementCount, *(FILE **)this_2),
            v15 = v86,
            v84 = (char *)buf_2 + v22 + 0x4000,
            v84 < (char *)buf_2 + ElementCount + 0x4000) )
      {
        __op_delete(buf_2);
        return 3;
      }
    }
    v20 |= (unsigned __int8)*v15 << (8 - n8_1);
    if ( n8 <= 16 )
    {
      n8_1 = n8_1 + v82 - 8;
      *v15 = (unsigned __int8)*v15 >> n8_1;
      goto LABEL_24;
    }
    if ( ++v15 >= v84 )
    {
      ElementCount_2 = fgetc(*(FILE **)this_2);
      if ( (int)ElementCount_2 <= 0 )
      {
        buf_1 = (char *)buf_2;
      }
      else
      {
        v23 = fread(Buffer, 1u, ElementCount_2, *(FILE **)this_2);
        v15 = v86;
        v84 = (char *)buf_2 + v23 + 0x4000;
        if ( v84 >= (char *)buf_2 + ElementCount_2 + 0x4000 )
          goto LABEL_23;
        buf_1 = (char *)buf_2;
      }
LABEL_52:
      __op_delete(buf_1);
      return 3;
    }
LABEL_23:
    v24 = (unsigned __int8)*v15 << (16 - n8_1);
    n8_1 = n8_1 + v82 - 16;
    LOWORD(v20) = v24 | v20;
    *v15 = (unsigned __int8)*v15 >> n8_1;
LABEL_24:
    n4096_2 = (unsigned __int16)(~(-1 << v82) & v20);
    n4096_11 = n4096_2;
    if ( n4096_2 == n4096_5 )
    {
      n4096 = n4096_1;
      __sub_42C220_word_445910[0] = v73;
      v80 = v76;
      n4096_3 = -1;
      n4096_6 = -1;
      goto LABEL_26;
    }
    if ( n4096_2 == n4096_12 )
      break;
    if ( n4096_2 > n4096 )
    {
      __op_delete(buf_2);
      return 4;
    }
    Buffer__1 = Buffer__2;
    if ( n4096_2 == n4096 )
    {
      if ( n4096_3 == -1 )
      {
        __op_delete(buf_2);
        return 5;
      }
      Buffer__1 = Buffer_;
      n4096_2 = n4096_3;
      *((_BYTE *)buf_2 + 0x2000) = n4096_6;
    }
    if ( n4096_2 >= n4096_5 )
    {
      buf_3 = buf_2;
      v83 = v15;
      n4096_4 = n4096_5;
      do
      {
        *Buffer__1 = buf_3[n4096_2 + 12288];
        n4096_2 = *(unsigned __int16 *)&buf_3[2 * n4096_2];
        ++Buffer__1;
      }
      while ( n4096_2 >= n4096_4 );
      v15 = v83;
    }
    v30 = v85;
    sub_42BB20_1 = sub_42BB20;
    n4096_6 = n4096_2;
    n4096_13 = n4096_11;
    this_3 = this_2;
    n8_2 = n8_1;
    v33 = v68;
    v83 = v15;
    v34 = v67;
    while ( 1 )
    {
      *(_BYTE *)(v30 + v34++) = n4096_2;
      if ( v34 >= *(unsigned __int16 *)(this_3 + 21) )
      {
        if ( sub_42BB20_1 )
        {
          v85 = v30;
          sub_42BB20_1(__sub_42C220_dword_445924, v87, __sub_42C220_dword_445928 + v33, v30);
          sub_42BB20_1 = sub_42BB20;
          v30 = v85;
        }
        if ( (*(_BYTE *)(this_3 + 25) & 0x40) != 0 )
        {
          v33 += __sub_42C220_dword_439CA4[__sub_42C220_dword_445908];
          if ( v33 >= *(unsigned __int16 *)(this_3 + 23) )
            v33 = __sub_42C220_dword_439CB8[++__sub_42C220_dword_445908];
        }
        else
        {
          ++v33;
        }
        v34 = 0;
        if ( !sub_42BB20_1 )
          v30 = __sub_42C220_dword_44592C + *(unsigned __int16 *)(this_3 + 21) * (__sub_42C220_dword_445928 + v33) + 16;
      }
      if ( Buffer__1 <= Buffer__2 )
        break;
      LOBYTE(n4096_2) = *--Buffer__1;
    }
    n4096_9 = n4096_13;
    v67 = v34;
    v15 = v83;
    v68 = v33;
    n8_1 = n8_2;
    v85 = v30;
    if ( n4096 < 4096 && n4096_3 != -1 )
    {
      buf_4 = buf_2;
      n4096_7 = n4096;
      n4096_8 = n4096_6;
      *((_WORD *)buf_2 + n4096) = n4096_3;
      buf_4[n4096_7 + 12288] = n4096_8;
      n4096 = n4096_7 + 1;
      if ( n4096_7 + 1 >= v80 && (unsigned __int16)__sub_42C220_word_445910[0] < 0xCu )
      {
        ++__sub_42C220_word_445910[0];
        v80 = 1 << SLOBYTE(__sub_42C220_word_445910[0]);
      }
    }
    n4096_3 = n4096_9;
LABEL_26:
    if ( n8_1 == 8 )
    {
      v14 = (unsigned int)v84;
      Buffer_1 = Buffer;
      buf_1 = (char *)buf_2;
      this_1 = this_2;
      goto LABEL_9;
    }
  }
  buf_5 = buf_2;
  this_4 = this_2;
  if ( v67 && sub_42BB20 )
    sub_42BB20(__sub_42C220_dword_445924, __sub_42C220_dword_445924 + v67, __sub_42C220_dword_445928 + v68, v85);
  if ( *(_DWORD *)(this_2 + 1564) )
    goto LABEL_89;
  while ( 2 )
  {
    n33 = fgetc(*(FILE **)this_4);
    n44_1 = n33;
    if ( n33 != 44 )
    {
      if ( !n33 )
        goto LABEL_76;
      if ( n33 != 33 )
        goto LABEL_86;
      v43 = fgetc(*(FILE **)this_4);
      switch ( v43 )
      {
        case 1:
          if ( fread(Buffer_2, 0xDu, 1u, *(FILE **)this_4) != 1 )
            goto LABEL_82;
          do
          {
            ElementCount_3 = fgetc(*(FILE **)this_4);
            ElementCount_9 = ElementCount_3;
            if ( ElementCount_3 == -1 )
              break;
            fread(&Buffer_, 1u, ElementCount_3, *(FILE **)this_4);
          }
          while ( ElementCount_9 > 0 );
          v46 = *(_DWORD *)(this_4 + 1564);
          break;
        case 249:
          if ( fread(Buffer_3, 6u, 1u, *(FILE **)this_4) != 1 )
            goto LABEL_82;
LABEL_76:
          v46 = *(_DWORD *)(this_4 + 1564);
          break;
        case 254:
          do
          {
            ElementCount_4 = fgetc(*(FILE **)this_4);
            ElementCount_10 = ElementCount_4;
            if ( ElementCount_4 == -1 )
              break;
            fread(&Buffer_, 1u, ElementCount_4, *(FILE **)this_4);
          }
          while ( ElementCount_10 > 0 );
          v46 = *(_DWORD *)(this_4 + 1564);
          break;
        case 255:
          if ( fread(Buffer_4, 0xCu, 1u, *(FILE **)this_4) != 1 )
            goto LABEL_82;
          do
          {
            ElementCount_5 = fgetc(*(FILE **)this_4);
            ElementCount_11 = ElementCount_5;
            if ( ElementCount_5 == -1 )
              break;
            fread(&Buffer_, 1u, ElementCount_5, *(FILE **)this_4);
          }
          while ( ElementCount_11 > 0 );
          goto LABEL_76;
        default:
          ElementCount_6 = fgetc(*(FILE **)this_4);
          fread(&Buffer_, 1u, ElementCount_6, *(FILE **)this_4);
          v46 = *(_DWORD *)(this_4 + 1564);
          break;
      }
      if ( v46 )
        goto LABEL_89;
      continue;
    }
    break;
  }
  if ( fread((void *)(this_4 + 17), 9u, 1u, *(FILE **)this_4) != 1 )
  {
LABEL_82:
    *(_DWORD *)(this_4 + 1564) = 1;
    goto LABEL_89;
  }
  v50 = *(_BYTE *)(this_4 + 25);
  if ( v50 < 0 )
  {
    ElementCount_7 = 1 << ((v50 & 7) + 1);
    v93 = this_4 + 794;
    if ( fread((void *)(this_4 + 794), 3u, ElementCount_7, *(FILE **)this_4) == ElementCount_7 )
    {
      v52 = ElementCount_7 - 1;
      v94 = ElementCount_7 >> 1;
      ElementCount_12 = ElementCount_7;
      v53 = v93;
      n44 = 44;
      buf_2 = buf_5;
      this_2 = this_4;
      v54 = 0;
      do
      {
        v55 = 3 * v52;
        v56 = *(_BYTE *)(3 * v52 + v53 + 2);
        *(_BYTE *)(v55 + v53 + 2) = *(_BYTE *)(3 * v52 + v53);
        v57 = 3 * v52 - 3;
        *(_BYTE *)(v55 + v53) = v56;
        v58 = *(_BYTE *)(v57 + v53 + 2);
        v52 -= 2;
        v59 = ++v54 < v94;
        *(_BYTE *)(v57 + v53 + 2) = *(_BYTE *)(v57 + v53);
        *(_BYTE *)(v57 + v53) = v58;
      }
      while ( v59 );
      n44_1 = n44;
      buf_5 = buf_2;
      this_4 = this_2;
      if ( ElementCount_12 > 2 * v54 )
      {
        v60 = v93;
        v61 = 3 * v52;
        v62 = *(_BYTE *)(3 * v52 + v93 + 2);
        *(_BYTE *)(v61 + v93 + 2) = *(_BYTE *)(3 * v52 + v93);
        *(_BYTE *)(v61 + v60) = v62;
      }
      goto LABEL_85;
    }
    *(_DWORD *)(this_4 + 1564) = 1;
  }
  else
  {
LABEL_85:
    if ( n44_1 == 44 )
      *(_DWORD *)(this_4 + 1564) = 0;
    else
LABEL_86:
      *(_DWORD *)(this_4 + 1564) = 1;
  }
LABEL_89:
  __op_delete(buf_5);
  return 0;
}

#undef FILE
#undef fgetc
#undef fread
#undef sub_42BB20
#undef sub_4349F0
