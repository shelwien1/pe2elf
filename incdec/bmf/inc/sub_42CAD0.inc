// sub_42CAD0 @ 0x0042CAD0 — __cdecl
// Extracted from BMF.cpp:37116-37176 by extract.py per incdec.md.


PROBE_DECL(__sub_42CAD0)
BMF_REALIGN int __sub_42CAD0(_BYTE *i, int a2)
{
  PROBE_HIT(__sub_42CAD0);
  int result; // eax
  int n122; // edx
  int n122_1; // ebx

  result = 0;
  if ( *i )
  {
    do
    {
      n122 = (char)i[result];
      if ( n122 < 97 )
      {
        if ( n122 >= -96 )
        {
          if ( n122 > -81 )
          {
            if ( n122 >= -32 && n122 <= -17 )
              n122 = (char)(n122 - 80);
          }
          else
          {
            n122 = (char)(n122 - 32);
          }
        }
      }
      else if ( n122 <= 122 )
      {
        n122 = (char)(n122 - 32);
      }
      n122_1 = *(char *)(result + a2);
      if ( n122_1 < 97 )
      {
        if ( n122_1 >= -96 )
        {
          if ( n122_1 > -81 )
          {
            if ( n122_1 >= -32 && n122_1 <= -17 )
              n122_1 = (char)(n122_1 - 80);
          }
          else
          {
            n122_1 = (char)(n122_1 - 32);
          }
        }
      }
      else if ( n122_1 <= 122 )
      {
        n122_1 = (char)(n122_1 - 32);
      }
      if ( n122 != n122_1 )
        break;
      ++result;
    }
    while ( i[result] );
  }
  return result;
}

