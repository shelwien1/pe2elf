// =====================================================================
// sub_14001D7A0 @ 0x14001D7A0
// Auto-extracted scaffold. REVIEW: see TODO comments below.
// =====================================================================

#define FILE FILE1

// ---- Data references ------------------------------------------------
#ifndef __PE_DECL___dword_140028E14
#define __PE_DECL___dword_140028E14
static int& __dword_140028E14 = *(int*)0x140028E14;
#endif
#define dword_140028E14 __dword_140028E14
#ifndef __PE_DECL___dword_1411345E0
#define __PE_DECL___dword_1411345E0
typedef int t_dword_1411345E0[400];
static t_dword_1411345E0& __dword_1411345E0 = *(t_dword_1411345E0*)0x1411345E0;
#endif
#define dword_1411345E0 __dword_1411345E0
#ifndef __PE_DECL___dword_141134C20
#define __PE_DECL___dword_141134C20
static int& __dword_141134C20 = *(int*)0x141134C20;
#endif
#define dword_141134C20 __dword_141134C20

// ---- PE-internal function references --------------------------------
#ifndef __PE_DECL___intel_cpuid
#define __PE_DECL___intel_cpuid
typedef __attribute__((ms_abi)) void t_intel_cpuid();
static t_intel_cpuid& __intel_cpuid = *(t_intel_cpuid*)0x14001D7D0;
#endif
#define intel_cpuid __intel_cpuid
#define sub_140021280 __sub_140021280
#ifndef __PE_DECL___unknown_libname_20
#define __PE_DECL___unknown_libname_20
typedef __attribute__((ms_abi)) __int64 t_unknown_libname_20();
static t_unknown_libname_20& __unknown_libname_20 = *(t_unknown_libname_20*)0x14001D780;
#endif
#define unknown_libname_20 __unknown_libname_20

PROBE_DECL(__sub_14001D7A0)
__attribute__((ms_abi)) __int64 __sub_14001D7A0(int *a1, unsigned __int8 a2, __int64 a3) {

  PROBE_HIT(__sub_14001D7A0);
  char v3;        // fps
  __int64 result; // rax
  __int64 v5;     // rdx
  char *v6;       // rcx
  __int64 v7;     // r9
  __m128i v8;     // xmm0
  char v9;        // r9
  __int64 v10;    // r10
  __m128i *v11;   // rcx
  __int64 v12;    // r8
  __m128i *v13;   // rcx
  __int64 v14;    // [rsp-20h] [rbp-20h]
  __int64 v15;    // [rsp-18h] [rbp-18h]
  int *v16;       // [rsp-10h] [rbp-10h]
  __int64 v17;    // [rsp-8h] [rbp-8h]

  while((dword_1411345E0[0] & 0xFFFFFE00) == 0) {
    if(dword_1411345E0[0])
      return unknown_libname_20();
    intel_cpuid();
  }
  result = (__int64)a1;
  if(a3 == 1) {
    *(_BYTE *)a1 = a2;
  } else if(a3 >= 1) {
    v5 = 0x101010101010101LL * a2;
    if(((unsigned __int8)a1 & 7) != 0 && a3 > 8) {
      v7 = 8LL - ((unsigned __int8)a1 & 7);
      a1 = (int *)((char *)a1 + v7);
      a3 -= v7;
      switch(v7) {
      case 0LL:
        break;
      case 1LL:
        goto LABEL_15;
      case 2LL:
        goto LABEL_17;
      case 3LL:
        goto LABEL_19;
      case 4LL:
        *(a1 - 1) = v5;
        break;
      case 5LL:
        *(int *)((char *)a1 - 5) = v5;
      LABEL_15:
        *((_BYTE *)a1 - 1) = v5;
        break;
      case 6LL:
        *(int *)((char *)a1 - 6) = v5;
      LABEL_17:
        *((_WORD *)a1 - 1) = v5;
        break;
      case 7LL:
        *(int *)((char *)a1 - 7) = v5;
      LABEL_19:
        *(_WORD *)((char *)a1 - 3) = v5;
        *((_BYTE *)a1 - 1) = v5;
        break;
      }
    }
    if(a3 >= 128) {
      while(1) {
        if(dword_140028E14 >= 2) {
          v8 = _mm_unpacklo_epi64(_mm_cvtsi64_si128(v5), _mm_cvtsi64_si128(v5));
          v9 = (unsigned __int8)a1 & 0xF;
          v10 = (16 - ((unsigned __int8)a1 & 0xF)) & 0xF;
          v11 = (__m128i *)((char *)a1 + v10);
          v12 = a3 - v10;
          switch((16 - v9) & 0xF) {
          case 0:
            break;
          case 1:
            goto LABEL_159;
          case 2:
            goto LABEL_161;
          case 3:
            goto LABEL_163;
          case 4:
            goto LABEL_165;
          case 5:
            goto LABEL_167;
          case 6:
            goto LABEL_169;
          case 7:
            goto LABEL_171;
          case 8:
            *((__int64 *)v11 - 1) = v5;
            break;
          case 9:
            *(__int64 *)((char *)v11 - 9) = v5;
          LABEL_159:
            *((_BYTE *)v11 - 1) = v5;
            break;
          case 0xA:
            *(__int64 *)((char *)v11 - 10) = v5;
          LABEL_161:
            *((__int16 *)v11 - 1) = v5;
            break;
          case 0xB:
            *(__int64 *)((char *)v11 - 11) = v5;
          LABEL_163:
            *(__int16 *)((char *)v11 - 3) = v5;
            *((_BYTE *)v11 - 1) = v5;
            break;
          case 0xC:
            *(__int64 *)((char *)v11 - 12) = v5;
          LABEL_165:
            *((__int32 *)v11 - 1) = v5;
            break;
          case 0xD:
            *(__int64 *)((char *)v11 - 13) = v5;
          LABEL_167:
            *(__int32 *)((char *)v11 - 5) = v5;
            *((_BYTE *)v11 - 1) = v5;
            break;
          case 0xE:
            *(__int64 *)((char *)v11 - 14) = v5;
          LABEL_169:
            *(__int32 *)((char *)v11 - 6) = v5;
            *((__int16 *)v11 - 1) = v5;
            break;
          case 0xF:
            *(__int64 *)((char *)v11 - 15) = v5;
          LABEL_171:
            *(__int32 *)((char *)v11 - 7) = v5;
            *(__int16 *)((char *)v11 - 3) = v5;
            *((_BYTE *)v11 - 1) = v5;
            break;
          }
          if(v12 >= 176) {
            if(v12 > (unsigned int)dword_141134C20 && dword_141134C20) {
              do {
                v12 -= 128;
                _mm_stream_si128(v11, v8);
                _mm_stream_si128(v11 + 1, v8);
                _mm_stream_si128(v11 + 2, v8);
                _mm_stream_si128(v11 + 3, v8);
                _mm_stream_si128(v11 + 4, v8);
                _mm_stream_si128(v11 + 5, v8);
                _mm_stream_si128(v11 + 6, v8);
                _mm_stream_si128(v11 + 7, v8);
                v11 += 8;
              } while(v12 >= 128);
              _mm_sfence();
              v13 = (__m128i *)((char *)v11 + v12);
              switch(v12) {
              case 0LL:
                return result;
              case 1LL:
                goto LABEL_196;
              case 2LL:
                goto LABEL_208;
              case 3LL:
                goto LABEL_220;
              case 4LL:
                goto LABEL_232;
              case 5LL:
                goto LABEL_244;
              case 6LL:
                goto LABEL_256;
              case 7LL:
                goto LABEL_268;
              case 8LL:
                goto LABEL_280;
              case 9LL:
                goto LABEL_292;
              case 10LL:
                goto LABEL_304;
              case 11LL:
                goto LABEL_316;
              case 12LL:
                goto LABEL_328;
              case 13LL:
                goto LABEL_340;
              case 14LL:
                goto LABEL_352;
              case 15LL:
                goto LABEL_364;
              case 16LL:
                goto LABEL_184;
              case 17LL:
                goto LABEL_195;
              case 18LL:
                goto LABEL_207;
              case 19LL:
                goto LABEL_219;
              case 20LL:
                goto LABEL_231;
              case 21LL:
                goto LABEL_243;
              case 22LL:
                goto LABEL_255;
              case 23LL:
                goto LABEL_267;
              case 24LL:
                goto LABEL_279;
              case 25LL:
                goto LABEL_291;
              case 26LL:
                goto LABEL_303;
              case 27LL:
                goto LABEL_315;
              case 28LL:
                goto LABEL_327;
              case 29LL:
                goto LABEL_339;
              case 30LL:
                goto LABEL_351;
              case 31LL:
                goto LABEL_363;
              case 32LL:
                goto LABEL_183;
              case 33LL:
                goto LABEL_194;
              case 34LL:
                goto LABEL_206;
              case 35LL:
                goto LABEL_218;
              case 36LL:
                goto LABEL_230;
              case 37LL:
                goto LABEL_242;
              case 38LL:
                goto LABEL_254;
              case 39LL:
                goto LABEL_266;
              case 40LL:
                goto LABEL_278;
              case 41LL:
                goto LABEL_290;
              case 42LL:
                goto LABEL_302;
              case 43LL:
                goto LABEL_314;
              case 44LL:
                goto LABEL_326;
              case 45LL:
                goto LABEL_338;
              case 46LL:
                goto LABEL_350;
              case 47LL:
                goto LABEL_362;
              case 48LL:
                goto LABEL_182;
              case 49LL:
                goto LABEL_193;
              case 50LL:
                goto LABEL_205;
              case 51LL:
                goto LABEL_217;
              case 52LL:
                goto LABEL_229;
              case 53LL:
                goto LABEL_241;
              case 54LL:
                goto LABEL_253;
              case 55LL:
                goto LABEL_265;
              case 56LL:
                goto LABEL_277;
              case 57LL:
                goto LABEL_289;
              case 58LL:
                goto LABEL_301;
              case 59LL:
                goto LABEL_313;
              case 60LL:
                goto LABEL_325;
              case 61LL:
                goto LABEL_337;
              case 62LL:
                goto LABEL_349;
              case 63LL:
                goto LABEL_361;
              case 64LL:
                goto LABEL_181;
              case 65LL:
                goto LABEL_192;
              case 66LL:
                goto LABEL_204;
              case 67LL:
                goto LABEL_216;
              case 68LL:
                goto LABEL_228;
              case 69LL:
                goto LABEL_240;
              case 70LL:
                goto LABEL_252;
              case 71LL:
                goto LABEL_264;
              case 72LL:
                goto LABEL_276;
              case 73LL:
                goto LABEL_288;
              case 74LL:
                goto LABEL_300;
              case 75LL:
                goto LABEL_312;
              case 76LL:
                goto LABEL_324;
              case 77LL:
                goto LABEL_336;
              case 78LL:
                goto LABEL_348;
              case 79LL:
                goto LABEL_360;
              case 80LL:
                goto LABEL_180;
              case 81LL:
                goto LABEL_191;
              case 82LL:
                goto LABEL_203;
              case 83LL:
                goto LABEL_215;
              case 84LL:
                goto LABEL_227;
              case 85LL:
                goto LABEL_239;
              case 86LL:
                goto LABEL_251;
              case 87LL:
                goto LABEL_263;
              case 88LL:
                goto LABEL_275;
              case 89LL:
                goto LABEL_287;
              case 90LL:
                goto LABEL_299;
              case 91LL:
                goto LABEL_311;
              case 92LL:
                goto LABEL_323;
              case 93LL:
                goto LABEL_335;
              case 94LL:
                goto LABEL_347;
              case 95LL:
                goto LABEL_359;
              case 96LL:
                goto LABEL_179;
              case 97LL:
                goto LABEL_190;
              case 98LL:
                goto LABEL_202;
              case 99LL:
                goto LABEL_214;
              case 100LL:
                goto LABEL_226;
              case 101LL:
                goto LABEL_238;
              case 102LL:
                goto LABEL_250;
              case 103LL:
                goto LABEL_262;
              case 104LL:
                goto LABEL_274;
              case 105LL:
                goto LABEL_286;
              case 106LL:
                goto LABEL_298;
              case 107LL:
                goto LABEL_310;
              case 108LL:
                goto LABEL_322;
              case 109LL:
                goto LABEL_334;
              case 110LL:
                goto LABEL_346;
              case 111LL:
                goto LABEL_358;
              case 112LL:
                goto LABEL_178;
              case 113LL:
                goto LABEL_189;
              case 114LL:
                goto LABEL_201;
              case 115LL:
                goto LABEL_213;
              case 116LL:
                goto LABEL_225;
              case 117LL:
                goto LABEL_237;
              case 118LL:
                goto LABEL_249;
              case 119LL:
                goto LABEL_261;
              case 120LL:
                goto LABEL_273;
              case 121LL:
                goto LABEL_285;
              case 122LL:
                goto LABEL_297;
              case 123LL:
                goto LABEL_309;
              case 124LL:
                goto LABEL_321;
              case 125LL:
                goto LABEL_333;
              case 126LL:
                goto LABEL_345;
              case 127LL:
                goto LABEL_357;
              case 128LL:
                goto LABEL_177;
              case 129LL:
                goto LABEL_188;
              case 130LL:
                goto LABEL_200;
              case 131LL:
                goto LABEL_212;
              case 132LL:
                goto LABEL_224;
              case 133LL:
                goto LABEL_236;
              case 134LL:
                goto LABEL_248;
              case 135LL:
                goto LABEL_260;
              case 136LL:
                goto LABEL_272;
              case 137LL:
                goto LABEL_284;
              case 138LL:
                goto LABEL_296;
              case 139LL:
                goto LABEL_308;
              case 140LL:
                goto LABEL_320;
              case 141LL:
                goto LABEL_332;
              case 142LL:
                goto LABEL_344;
              case 143LL:
                goto LABEL_356;
              case 144LL:
                goto LABEL_176;
              case 145LL:
                goto LABEL_187;
              case 146LL:
                goto LABEL_199;
              case 147LL:
                goto LABEL_211;
              case 148LL:
                goto LABEL_223;
              case 149LL:
                goto LABEL_235;
              case 150LL:
                goto LABEL_247;
              case 151LL:
                goto LABEL_259;
              case 152LL:
                goto LABEL_271;
              case 153LL:
                goto LABEL_283;
              case 154LL:
                goto LABEL_295;
              case 155LL:
                goto LABEL_307;
              case 156LL:
                goto LABEL_319;
              case 157LL:
                goto LABEL_331;
              case 158LL:
                goto LABEL_343;
              case 159LL:
                goto LABEL_355;
              case 160LL:
                goto LABEL_175;
              case 161LL:
                goto LABEL_186;
              case 162LL:
                goto LABEL_198;
              case 163LL:
                goto LABEL_210;
              case 164LL:
                goto LABEL_222;
              case 165LL:
                goto LABEL_234;
              case 166LL:
                goto LABEL_246;
              case 167LL:
                goto LABEL_258;
              case 168LL:
                goto LABEL_270;
              case 169LL:
                goto LABEL_282;
              case 170LL:
                goto LABEL_294;
              case 171LL:
                goto LABEL_306;
              case 172LL:
                goto LABEL_318;
              case 173LL:
                goto LABEL_330;
              case 174LL:
                goto LABEL_342;
              case 175LL:
                goto LABEL_354;
              case 176LL:
                goto LABEL_174;
              case 177LL:
                goto LABEL_185;
              case 178LL:
                goto LABEL_197;
              case 179LL:
                goto LABEL_209;
              case 180LL:
                goto LABEL_221;
              case 181LL:
                goto LABEL_233;
              case 182LL:
                goto LABEL_245;
              case 183LL:
                goto LABEL_257;
              case 184LL:
                goto LABEL_269;
              case 185LL:
                goto LABEL_281;
              case 186LL:
                goto LABEL_293;
              case 187LL:
                goto LABEL_305;
              case 188LL:
                goto LABEL_317;
              case 189LL:
                goto LABEL_329;
              case 190LL:
                goto LABEL_341;
              case 191LL:
                goto LABEL_353;
              }
            } else {
              do {
                v12 -= 128;
                *v11 = v8;
                v11[1] = v8;
                v11[2] = v8;
                v11[3] = v8;
                v11[4] = v8;
                v11[5] = v8;
                v11[6] = v8;
                v11[7] = v8;
                v11 += 8;
              } while(v12 >= 128);
              v13 = (__m128i *)((char *)v11 + v12);
              switch(v12) {
              case 0LL:
                return result;
              case 1LL:
                goto LABEL_196;
              case 2LL:
                goto LABEL_208;
              case 3LL:
                goto LABEL_220;
              case 4LL:
                goto LABEL_232;
              case 5LL:
                goto LABEL_244;
              case 6LL:
                goto LABEL_256;
              case 7LL:
                goto LABEL_268;
              case 8LL:
                goto LABEL_280;
              case 9LL:
                goto LABEL_292;
              case 10LL:
                goto LABEL_304;
              case 11LL:
                goto LABEL_316;
              case 12LL:
                goto LABEL_328;
              case 13LL:
                goto LABEL_340;
              case 14LL:
                goto LABEL_352;
              case 15LL:
                goto LABEL_364;
              case 16LL:
                goto LABEL_184;
              case 17LL:
                goto LABEL_195;
              case 18LL:
                goto LABEL_207;
              case 19LL:
                goto LABEL_219;
              case 20LL:
                goto LABEL_231;
              case 21LL:
                goto LABEL_243;
              case 22LL:
                goto LABEL_255;
              case 23LL:
                goto LABEL_267;
              case 24LL:
                goto LABEL_279;
              case 25LL:
                goto LABEL_291;
              case 26LL:
                goto LABEL_303;
              case 27LL:
                goto LABEL_315;
              case 28LL:
                goto LABEL_327;
              case 29LL:
                goto LABEL_339;
              case 30LL:
                goto LABEL_351;
              case 31LL:
                goto LABEL_363;
              case 32LL:
                goto LABEL_183;
              case 33LL:
                goto LABEL_194;
              case 34LL:
                goto LABEL_206;
              case 35LL:
                goto LABEL_218;
              case 36LL:
                goto LABEL_230;
              case 37LL:
                goto LABEL_242;
              case 38LL:
                goto LABEL_254;
              case 39LL:
                goto LABEL_266;
              case 40LL:
                goto LABEL_278;
              case 41LL:
                goto LABEL_290;
              case 42LL:
                goto LABEL_302;
              case 43LL:
                goto LABEL_314;
              case 44LL:
                goto LABEL_326;
              case 45LL:
                goto LABEL_338;
              case 46LL:
                goto LABEL_350;
              case 47LL:
                goto LABEL_362;
              case 48LL:
                goto LABEL_182;
              case 49LL:
                goto LABEL_193;
              case 50LL:
                goto LABEL_205;
              case 51LL:
                goto LABEL_217;
              case 52LL:
                goto LABEL_229;
              case 53LL:
                goto LABEL_241;
              case 54LL:
                goto LABEL_253;
              case 55LL:
                goto LABEL_265;
              case 56LL:
                goto LABEL_277;
              case 57LL:
                goto LABEL_289;
              case 58LL:
                goto LABEL_301;
              case 59LL:
                goto LABEL_313;
              case 60LL:
                goto LABEL_325;
              case 61LL:
                goto LABEL_337;
              case 62LL:
                goto LABEL_349;
              case 63LL:
                goto LABEL_361;
              case 64LL:
                goto LABEL_181;
              case 65LL:
                goto LABEL_192;
              case 66LL:
                goto LABEL_204;
              case 67LL:
                goto LABEL_216;
              case 68LL:
                goto LABEL_228;
              case 69LL:
                goto LABEL_240;
              case 70LL:
                goto LABEL_252;
              case 71LL:
                goto LABEL_264;
              case 72LL:
                goto LABEL_276;
              case 73LL:
                goto LABEL_288;
              case 74LL:
                goto LABEL_300;
              case 75LL:
                goto LABEL_312;
              case 76LL:
                goto LABEL_324;
              case 77LL:
                goto LABEL_336;
              case 78LL:
                goto LABEL_348;
              case 79LL:
                goto LABEL_360;
              case 80LL:
                goto LABEL_180;
              case 81LL:
                goto LABEL_191;
              case 82LL:
                goto LABEL_203;
              case 83LL:
                goto LABEL_215;
              case 84LL:
                goto LABEL_227;
              case 85LL:
                goto LABEL_239;
              case 86LL:
                goto LABEL_251;
              case 87LL:
                goto LABEL_263;
              case 88LL:
                goto LABEL_275;
              case 89LL:
                goto LABEL_287;
              case 90LL:
                goto LABEL_299;
              case 91LL:
                goto LABEL_311;
              case 92LL:
                goto LABEL_323;
              case 93LL:
                goto LABEL_335;
              case 94LL:
                goto LABEL_347;
              case 95LL:
                goto LABEL_359;
              case 96LL:
                goto LABEL_179;
              case 97LL:
                goto LABEL_190;
              case 98LL:
                goto LABEL_202;
              case 99LL:
                goto LABEL_214;
              case 100LL:
                goto LABEL_226;
              case 101LL:
                goto LABEL_238;
              case 102LL:
                goto LABEL_250;
              case 103LL:
                goto LABEL_262;
              case 104LL:
                goto LABEL_274;
              case 105LL:
                goto LABEL_286;
              case 106LL:
                goto LABEL_298;
              case 107LL:
                goto LABEL_310;
              case 108LL:
                goto LABEL_322;
              case 109LL:
                goto LABEL_334;
              case 110LL:
                goto LABEL_346;
              case 111LL:
                goto LABEL_358;
              case 112LL:
                goto LABEL_178;
              case 113LL:
                goto LABEL_189;
              case 114LL:
                goto LABEL_201;
              case 115LL:
                goto LABEL_213;
              case 116LL:
                goto LABEL_225;
              case 117LL:
                goto LABEL_237;
              case 118LL:
                goto LABEL_249;
              case 119LL:
                goto LABEL_261;
              case 120LL:
                goto LABEL_273;
              case 121LL:
                goto LABEL_285;
              case 122LL:
                goto LABEL_297;
              case 123LL:
                goto LABEL_309;
              case 124LL:
                goto LABEL_321;
              case 125LL:
                goto LABEL_333;
              case 126LL:
                goto LABEL_345;
              case 127LL:
                goto LABEL_357;
              case 128LL:
                goto LABEL_177;
              case 129LL:
                goto LABEL_188;
              case 130LL:
                goto LABEL_200;
              case 131LL:
                goto LABEL_212;
              case 132LL:
                goto LABEL_224;
              case 133LL:
                goto LABEL_236;
              case 134LL:
                goto LABEL_248;
              case 135LL:
                goto LABEL_260;
              case 136LL:
                goto LABEL_272;
              case 137LL:
                goto LABEL_284;
              case 138LL:
                goto LABEL_296;
              case 139LL:
                goto LABEL_308;
              case 140LL:
                goto LABEL_320;
              case 141LL:
                goto LABEL_332;
              case 142LL:
                goto LABEL_344;
              case 143LL:
                goto LABEL_356;
              case 144LL:
                goto LABEL_176;
              case 145LL:
                goto LABEL_187;
              case 146LL:
                goto LABEL_199;
              case 147LL:
                goto LABEL_211;
              case 148LL:
                goto LABEL_223;
              case 149LL:
                goto LABEL_235;
              case 150LL:
                goto LABEL_247;
              case 151LL:
                goto LABEL_259;
              case 152LL:
                goto LABEL_271;
              case 153LL:
                goto LABEL_283;
              case 154LL:
                goto LABEL_295;
              case 155LL:
                goto LABEL_307;
              case 156LL:
                goto LABEL_319;
              case 157LL:
                goto LABEL_331;
              case 158LL:
                goto LABEL_343;
              case 159LL:
                goto LABEL_355;
              case 160LL:
                goto LABEL_175;
              case 161LL:
                goto LABEL_186;
              case 162LL:
                goto LABEL_198;
              case 163LL:
                goto LABEL_210;
              case 164LL:
                goto LABEL_222;
              case 165LL:
                goto LABEL_234;
              case 166LL:
                goto LABEL_246;
              case 167LL:
                goto LABEL_258;
              case 168LL:
                goto LABEL_270;
              case 169LL:
                goto LABEL_282;
              case 170LL:
                goto LABEL_294;
              case 171LL:
                goto LABEL_306;
              case 172LL:
                goto LABEL_318;
              case 173LL:
                goto LABEL_330;
              case 174LL:
                goto LABEL_342;
              case 175LL:
                goto LABEL_354;
              case 176LL:
              LABEL_174:
                v13[-11] = v8;
              LABEL_175:
                v13[-10] = v8;
              LABEL_176:
                v13[-9] = v8;
              LABEL_177:
                v13[-8] = v8;
              LABEL_178:
                v13[-7] = v8;
              LABEL_179:
                v13[-6] = v8;
              LABEL_180:
                v13[-5] = v8;
              LABEL_181:
                v13[-4] = v8;
              LABEL_182:
                v13[-3] = v8;
              LABEL_183:
                v13[-2] = v8;
              LABEL_184:
                v13[-1] = v8;
                break;
              case 177LL:
              LABEL_185:
                *(__m128i *)((char *)v13 - 177) = v8;
              LABEL_186:
                *(__m128i *)((char *)v13 - 161) = v8;
              LABEL_187:
                *(__m128i *)((char *)v13 - 145) = v8;
              LABEL_188:
                *(__m128i *)((char *)v13 - 129) = v8;
              LABEL_189:
                *(__m128i *)((char *)v13 - 113) = v8;
              LABEL_190:
                *(__m128i *)((char *)v13 - 97) = v8;
              LABEL_191:
                *(__m128i *)((char *)v13 - 81) = v8;
              LABEL_192:
                *(__m128i *)((char *)v13 - 65) = v8;
              LABEL_193:
                *(__m128i *)((char *)v13 - 49) = v8;
              LABEL_194:
                *(__m128i *)((char *)v13 - 33) = v8;
              LABEL_195:
                *(__m128i *)((char *)v13 - 17) = v8;
              LABEL_196:
                *((_BYTE *)v13 - 1) = v5;
                break;
              case 178LL:
              LABEL_197:
                *(__m128i *)((char *)v13 - 178) = v8;
              LABEL_198:
                *(__m128i *)((char *)v13 - 162) = v8;
              LABEL_199:
                *(__m128i *)((char *)v13 - 146) = v8;
              LABEL_200:
                *(__m128i *)((char *)v13 - 130) = v8;
              LABEL_201:
                *(__m128i *)((char *)v13 - 114) = v8;
              LABEL_202:
                *(__m128i *)((char *)v13 - 98) = v8;
              LABEL_203:
                *(__m128i *)((char *)v13 - 82) = v8;
              LABEL_204:
                *(__m128i *)((char *)v13 - 66) = v8;
              LABEL_205:
                *(__m128i *)((char *)v13 - 50) = v8;
              LABEL_206:
                *(__m128i *)((char *)v13 - 34) = v8;
              LABEL_207:
                *(__m128i *)((char *)v13 - 18) = v8;
              LABEL_208:
                *((__int16 *)v13 - 1) = v5;
                break;
              case 179LL:
              LABEL_209:
                *(__m128i *)((char *)v13 - 179) = v8;
              LABEL_210:
                *(__m128i *)((char *)v13 - 163) = v8;
              LABEL_211:
                *(__m128i *)((char *)v13 - 147) = v8;
              LABEL_212:
                *(__m128i *)((char *)v13 - 131) = v8;
              LABEL_213:
                *(__m128i *)((char *)v13 - 115) = v8;
              LABEL_214:
                *(__m128i *)((char *)v13 - 99) = v8;
              LABEL_215:
                *(__m128i *)((char *)v13 - 83) = v8;
              LABEL_216:
                *(__m128i *)((char *)v13 - 67) = v8;
              LABEL_217:
                *(__m128i *)((char *)v13 - 51) = v8;
              LABEL_218:
                *(__m128i *)((char *)v13 - 35) = v8;
              LABEL_219:
                *(__m128i *)((char *)v13 - 19) = v8;
              LABEL_220:
                *(__int16 *)((char *)v13 - 3) = v5;
                *((_BYTE *)v13 - 1) = v5;
                break;
              case 180LL:
              LABEL_221:
                *(__m128i *)((char *)v13 - 180) = v8;
              LABEL_222:
                *(__m128i *)((char *)v13 - 164) = v8;
              LABEL_223:
                *(__m128i *)((char *)v13 - 148) = v8;
              LABEL_224:
                *(__m128i *)((char *)v13 - 132) = v8;
              LABEL_225:
                *(__m128i *)((char *)v13 - 116) = v8;
              LABEL_226:
                *(__m128i *)((char *)v13 - 100) = v8;
              LABEL_227:
                *(__m128i *)((char *)v13 - 84) = v8;
              LABEL_228:
                *(__m128i *)((char *)v13 - 68) = v8;
              LABEL_229:
                *(__m128i *)((char *)v13 - 52) = v8;
              LABEL_230:
                *(__m128i *)((char *)v13 - 36) = v8;
              LABEL_231:
                *(__m128i *)((char *)v13 - 20) = v8;
              LABEL_232:
                *((__int32 *)v13 - 1) = v5;
                break;
              case 181LL:
              LABEL_233:
                *(__m128i *)((char *)v13 - 181) = v8;
              LABEL_234:
                *(__m128i *)((char *)v13 - 165) = v8;
              LABEL_235:
                *(__m128i *)((char *)v13 - 149) = v8;
              LABEL_236:
                *(__m128i *)((char *)v13 - 133) = v8;
              LABEL_237:
                *(__m128i *)((char *)v13 - 117) = v8;
              LABEL_238:
                *(__m128i *)((char *)v13 - 101) = v8;
              LABEL_239:
                *(__m128i *)((char *)v13 - 85) = v8;
              LABEL_240:
                *(__m128i *)((char *)v13 - 69) = v8;
              LABEL_241:
                *(__m128i *)((char *)v13 - 53) = v8;
              LABEL_242:
                *(__m128i *)((char *)v13 - 37) = v8;
              LABEL_243:
                *(__m128i *)((char *)v13 - 21) = v8;
              LABEL_244:
                *(__int32 *)((char *)v13 - 5) = v5;
                *((_BYTE *)v13 - 1) = v5;
                break;
              case 182LL:
              LABEL_245:
                *(__m128i *)((char *)v13 - 182) = v8;
              LABEL_246:
                *(__m128i *)((char *)v13 - 166) = v8;
              LABEL_247:
                *(__m128i *)((char *)v13 - 150) = v8;
              LABEL_248:
                *(__m128i *)((char *)v13 - 134) = v8;
              LABEL_249:
                *(__m128i *)((char *)v13 - 118) = v8;
              LABEL_250:
                *(__m128i *)((char *)v13 - 102) = v8;
              LABEL_251:
                *(__m128i *)((char *)v13 - 86) = v8;
              LABEL_252:
                *(__m128i *)((char *)v13 - 70) = v8;
              LABEL_253:
                *(__m128i *)((char *)v13 - 54) = v8;
              LABEL_254:
                *(__m128i *)((char *)v13 - 38) = v8;
              LABEL_255:
                *(__m128i *)((char *)v13 - 22) = v8;
              LABEL_256:
                *(__int32 *)((char *)v13 - 6) = v5;
                *((__int16 *)v13 - 1) = v5;
                break;
              case 183LL:
              LABEL_257:
                *(__m128i *)((char *)v13 - 183) = v8;
              LABEL_258:
                *(__m128i *)((char *)v13 - 167) = v8;
              LABEL_259:
                *(__m128i *)((char *)v13 - 151) = v8;
              LABEL_260:
                *(__m128i *)((char *)v13 - 135) = v8;
              LABEL_261:
                *(__m128i *)((char *)v13 - 119) = v8;
              LABEL_262:
                *(__m128i *)((char *)v13 - 103) = v8;
              LABEL_263:
                *(__m128i *)((char *)v13 - 87) = v8;
              LABEL_264:
                *(__m128i *)((char *)v13 - 71) = v8;
              LABEL_265:
                *(__m128i *)((char *)v13 - 55) = v8;
              LABEL_266:
                *(__m128i *)((char *)v13 - 39) = v8;
              LABEL_267:
                *(__m128i *)((char *)v13 - 23) = v8;
              LABEL_268:
                *(__int32 *)((char *)v13 - 7) = v5;
                *(__int16 *)((char *)v13 - 3) = v5;
                *((_BYTE *)v13 - 1) = v5;
                break;
              case 184LL:
              LABEL_269:
                *(__m128i *)((char *)v13 - 184) = v8;
              LABEL_270:
                *(__m128i *)((char *)v13 - 168) = v8;
              LABEL_271:
                *(__m128i *)((char *)v13 - 152) = v8;
              LABEL_272:
                *(__m128i *)((char *)v13 - 136) = v8;
              LABEL_273:
                *(__m128i *)((char *)v13 - 120) = v8;
              LABEL_274:
                *(__m128i *)((char *)v13 - 104) = v8;
              LABEL_275:
                *(__m128i *)((char *)v13 - 88) = v8;
              LABEL_276:
                *(__m128i *)((char *)v13 - 72) = v8;
              LABEL_277:
                *(__m128i *)((char *)v13 - 56) = v8;
              LABEL_278:
                *(__m128i *)((char *)v13 - 40) = v8;
              LABEL_279:
                *(__m128i *)((char *)v13 - 24) = v8;
              LABEL_280:
                *((__int64 *)v13 - 1) = _mm_cvtsi128_si64(v8);
                break;
              case 185LL:
              LABEL_281:
                *(__m128i *)((char *)v13 - 185) = v8;
              LABEL_282:
                *(__m128i *)((char *)v13 - 169) = v8;
              LABEL_283:
                *(__m128i *)((char *)v13 - 153) = v8;
              LABEL_284:
                *(__m128i *)((char *)v13 - 137) = v8;
              LABEL_285:
                *(__m128i *)((char *)v13 - 121) = v8;
              LABEL_286:
                *(__m128i *)((char *)v13 - 105) = v8;
              LABEL_287:
                *(__m128i *)((char *)v13 - 89) = v8;
              LABEL_288:
                *(__m128i *)((char *)v13 - 73) = v8;
              LABEL_289:
                *(__m128i *)((char *)v13 - 57) = v8;
              LABEL_290:
                *(__m128i *)((char *)v13 - 41) = v8;
              LABEL_291:
                *(__m128i *)((char *)v13 - 25) = v8;
              LABEL_292:
                *(__int64 *)((char *)v13 - 9) = _mm_cvtsi128_si64(v8);
                *((_BYTE *)v13 - 1) = v5;
                break;
              case 186LL:
              LABEL_293:
                *(__m128i *)((char *)v13 - 186) = v8;
              LABEL_294:
                *(__m128i *)((char *)v13 - 170) = v8;
              LABEL_295:
                *(__m128i *)((char *)v13 - 154) = v8;
              LABEL_296:
                *(__m128i *)((char *)v13 - 138) = v8;
              LABEL_297:
                *(__m128i *)((char *)v13 - 122) = v8;
              LABEL_298:
                *(__m128i *)((char *)v13 - 106) = v8;
              LABEL_299:
                *(__m128i *)((char *)v13 - 90) = v8;
              LABEL_300:
                *(__m128i *)((char *)v13 - 74) = v8;
              LABEL_301:
                *(__m128i *)((char *)v13 - 58) = v8;
              LABEL_302:
                *(__m128i *)((char *)v13 - 42) = v8;
              LABEL_303:
                *(__m128i *)((char *)v13 - 26) = v8;
              LABEL_304:
                *(__int64 *)((char *)v13 - 10) = _mm_cvtsi128_si64(v8);
                *((__int16 *)v13 - 1) = v5;
                break;
              case 187LL:
              LABEL_305:
                *(__m128i *)((char *)v13 - 187) = v8;
              LABEL_306:
                *(__m128i *)((char *)v13 - 171) = v8;
              LABEL_307:
                *(__m128i *)((char *)v13 - 155) = v8;
              LABEL_308:
                *(__m128i *)((char *)v13 - 139) = v8;
              LABEL_309:
                *(__m128i *)((char *)v13 - 123) = v8;
              LABEL_310:
                *(__m128i *)((char *)v13 - 107) = v8;
              LABEL_311:
                *(__m128i *)((char *)v13 - 91) = v8;
              LABEL_312:
                *(__m128i *)((char *)v13 - 75) = v8;
              LABEL_313:
                *(__m128i *)((char *)v13 - 59) = v8;
              LABEL_314:
                *(__m128i *)((char *)v13 - 43) = v8;
              LABEL_315:
                *(__m128i *)((char *)v13 - 27) = v8;
              LABEL_316:
                *(__int64 *)((char *)v13 - 11) = _mm_cvtsi128_si64(v8);
                *(__int16 *)((char *)v13 - 3) = v5;
                *((_BYTE *)v13 - 1) = v5;
                break;
              case 188LL:
              LABEL_317:
                *(__m128i *)((char *)v13 - 188) = v8;
              LABEL_318:
                *(__m128i *)((char *)v13 - 172) = v8;
              LABEL_319:
                *(__m128i *)((char *)v13 - 156) = v8;
              LABEL_320:
                *(__m128i *)((char *)v13 - 140) = v8;
              LABEL_321:
                *(__m128i *)((char *)v13 - 124) = v8;
              LABEL_322:
                *(__m128i *)((char *)v13 - 108) = v8;
              LABEL_323:
                *(__m128i *)((char *)v13 - 92) = v8;
              LABEL_324:
                *(__m128i *)((char *)v13 - 76) = v8;
              LABEL_325:
                *(__m128i *)((char *)v13 - 60) = v8;
              LABEL_326:
                *(__m128i *)((char *)v13 - 44) = v8;
              LABEL_327:
                *(__m128i *)((char *)v13 - 28) = v8;
              LABEL_328:
                *(__int64 *)((char *)v13 - 12) = _mm_cvtsi128_si64(v8);
                *((__int32 *)v13 - 1) = v5;
                break;
              case 189LL:
              LABEL_329:
                *(__m128i *)((char *)v13 - 189) = v8;
              LABEL_330:
                *(__m128i *)((char *)v13 - 173) = v8;
              LABEL_331:
                *(__m128i *)((char *)v13 - 157) = v8;
              LABEL_332:
                *(__m128i *)((char *)v13 - 141) = v8;
              LABEL_333:
                *(__m128i *)((char *)v13 - 125) = v8;
              LABEL_334:
                *(__m128i *)((char *)v13 - 109) = v8;
              LABEL_335:
                *(__m128i *)((char *)v13 - 93) = v8;
              LABEL_336:
                *(__m128i *)((char *)v13 - 77) = v8;
              LABEL_337:
                *(__m128i *)((char *)v13 - 61) = v8;
              LABEL_338:
                *(__m128i *)((char *)v13 - 45) = v8;
              LABEL_339:
                *(__m128i *)((char *)v13 - 29) = v8;
              LABEL_340:
                *(__int64 *)((char *)v13 - 13) = _mm_cvtsi128_si64(v8);
                *(__int32 *)((char *)v13 - 5) = v5;
                *((_BYTE *)v13 - 1) = v5;
                break;
              case 190LL:
              LABEL_341:
                *(__m128i *)((char *)v13 - 190) = v8;
              LABEL_342:
                *(__m128i *)((char *)v13 - 174) = v8;
              LABEL_343:
                *(__m128i *)((char *)v13 - 158) = v8;
              LABEL_344:
                *(__m128i *)((char *)v13 - 142) = v8;
              LABEL_345:
                *(__m128i *)((char *)v13 - 126) = v8;
              LABEL_346:
                *(__m128i *)((char *)v13 - 110) = v8;
              LABEL_347:
                *(__m128i *)((char *)v13 - 94) = v8;
              LABEL_348:
                *(__m128i *)((char *)v13 - 78) = v8;
              LABEL_349:
                *(__m128i *)((char *)v13 - 62) = v8;
              LABEL_350:
                *(__m128i *)((char *)v13 - 46) = v8;
              LABEL_351:
                *(__m128i *)((char *)v13 - 30) = v8;
              LABEL_352:
                *(__int64 *)((char *)v13 - 14) = v5;
                *(__int32 *)((char *)v13 - 6) = v5;
                *((__int16 *)v13 - 1) = v5;
                break;
              case 191LL:
              LABEL_353:
                *(__m128i *)((char *)v13 - 191) = v8;
              LABEL_354:
                *(__m128i *)((char *)v13 - 175) = v8;
              LABEL_355:
                *(__m128i *)((char *)v13 - 159) = v8;
              LABEL_356:
                *(__m128i *)((char *)v13 - 143) = v8;
              LABEL_357:
                *(__m128i *)((char *)v13 - 127) = v8;
              LABEL_358:
                *(__m128i *)((char *)v13 - 111) = v8;
              LABEL_359:
                *(__m128i *)((char *)v13 - 95) = v8;
              LABEL_360:
                *(__m128i *)((char *)v13 - 79) = v8;
              LABEL_361:
                *(__m128i *)((char *)v13 - 63) = v8;
              LABEL_362:
                *(__m128i *)((char *)v13 - 47) = v8;
              LABEL_363:
                *(__m128i *)((char *)v13 - 31) = v8;
              LABEL_364:
                *(__int64 *)((char *)v13 - 15) = v5;
                *(__int32 *)((char *)v13 - 7) = v5;
                *(__int16 *)((char *)v13 - 3) = v5;
                *((_BYTE *)v13 - 1) = v5;
                break;
              }
            }
          } else {
            v13 = (__m128i *)((char *)v11 + v12);
            switch(v12) {
            case 0LL:
              return result;
            case 1LL:
              goto LABEL_196;
            case 2LL:
              goto LABEL_208;
            case 3LL:
              goto LABEL_220;
            case 4LL:
              goto LABEL_232;
            case 5LL:
              goto LABEL_244;
            case 6LL:
              goto LABEL_256;
            case 7LL:
              goto LABEL_268;
            case 8LL:
              goto LABEL_280;
            case 9LL:
              goto LABEL_292;
            case 10LL:
              goto LABEL_304;
            case 11LL:
              goto LABEL_316;
            case 12LL:
              goto LABEL_328;
            case 13LL:
              goto LABEL_340;
            case 14LL:
              goto LABEL_352;
            case 15LL:
              goto LABEL_364;
            case 16LL:
              goto LABEL_184;
            case 17LL:
              goto LABEL_195;
            case 18LL:
              goto LABEL_207;
            case 19LL:
              goto LABEL_219;
            case 20LL:
              goto LABEL_231;
            case 21LL:
              goto LABEL_243;
            case 22LL:
              goto LABEL_255;
            case 23LL:
              goto LABEL_267;
            case 24LL:
              goto LABEL_279;
            case 25LL:
              goto LABEL_291;
            case 26LL:
              goto LABEL_303;
            case 27LL:
              goto LABEL_315;
            case 28LL:
              goto LABEL_327;
            case 29LL:
              goto LABEL_339;
            case 30LL:
              goto LABEL_351;
            case 31LL:
              goto LABEL_363;
            case 32LL:
              goto LABEL_183;
            case 33LL:
              goto LABEL_194;
            case 34LL:
              goto LABEL_206;
            case 35LL:
              goto LABEL_218;
            case 36LL:
              goto LABEL_230;
            case 37LL:
              goto LABEL_242;
            case 38LL:
              goto LABEL_254;
            case 39LL:
              goto LABEL_266;
            case 40LL:
              goto LABEL_278;
            case 41LL:
              goto LABEL_290;
            case 42LL:
              goto LABEL_302;
            case 43LL:
              goto LABEL_314;
            case 44LL:
              goto LABEL_326;
            case 45LL:
              goto LABEL_338;
            case 46LL:
              goto LABEL_350;
            case 47LL:
              goto LABEL_362;
            case 48LL:
              goto LABEL_182;
            case 49LL:
              goto LABEL_193;
            case 50LL:
              goto LABEL_205;
            case 51LL:
              goto LABEL_217;
            case 52LL:
              goto LABEL_229;
            case 53LL:
              goto LABEL_241;
            case 54LL:
              goto LABEL_253;
            case 55LL:
              goto LABEL_265;
            case 56LL:
              goto LABEL_277;
            case 57LL:
              goto LABEL_289;
            case 58LL:
              goto LABEL_301;
            case 59LL:
              goto LABEL_313;
            case 60LL:
              goto LABEL_325;
            case 61LL:
              goto LABEL_337;
            case 62LL:
              goto LABEL_349;
            case 63LL:
              goto LABEL_361;
            case 64LL:
              goto LABEL_181;
            case 65LL:
              goto LABEL_192;
            case 66LL:
              goto LABEL_204;
            case 67LL:
              goto LABEL_216;
            case 68LL:
              goto LABEL_228;
            case 69LL:
              goto LABEL_240;
            case 70LL:
              goto LABEL_252;
            case 71LL:
              goto LABEL_264;
            case 72LL:
              goto LABEL_276;
            case 73LL:
              goto LABEL_288;
            case 74LL:
              goto LABEL_300;
            case 75LL:
              goto LABEL_312;
            case 76LL:
              goto LABEL_324;
            case 77LL:
              goto LABEL_336;
            case 78LL:
              goto LABEL_348;
            case 79LL:
              goto LABEL_360;
            case 80LL:
              goto LABEL_180;
            case 81LL:
              goto LABEL_191;
            case 82LL:
              goto LABEL_203;
            case 83LL:
              goto LABEL_215;
            case 84LL:
              goto LABEL_227;
            case 85LL:
              goto LABEL_239;
            case 86LL:
              goto LABEL_251;
            case 87LL:
              goto LABEL_263;
            case 88LL:
              goto LABEL_275;
            case 89LL:
              goto LABEL_287;
            case 90LL:
              goto LABEL_299;
            case 91LL:
              goto LABEL_311;
            case 92LL:
              goto LABEL_323;
            case 93LL:
              goto LABEL_335;
            case 94LL:
              goto LABEL_347;
            case 95LL:
              goto LABEL_359;
            case 96LL:
              goto LABEL_179;
            case 97LL:
              goto LABEL_190;
            case 98LL:
              goto LABEL_202;
            case 99LL:
              goto LABEL_214;
            case 100LL:
              goto LABEL_226;
            case 101LL:
              goto LABEL_238;
            case 102LL:
              goto LABEL_250;
            case 103LL:
              goto LABEL_262;
            case 104LL:
              goto LABEL_274;
            case 105LL:
              goto LABEL_286;
            case 106LL:
              goto LABEL_298;
            case 107LL:
              goto LABEL_310;
            case 108LL:
              goto LABEL_322;
            case 109LL:
              goto LABEL_334;
            case 110LL:
              goto LABEL_346;
            case 111LL:
              goto LABEL_358;
            case 112LL:
              goto LABEL_178;
            case 113LL:
              goto LABEL_189;
            case 114LL:
              goto LABEL_201;
            case 115LL:
              goto LABEL_213;
            case 116LL:
              goto LABEL_225;
            case 117LL:
              goto LABEL_237;
            case 118LL:
              goto LABEL_249;
            case 119LL:
              goto LABEL_261;
            case 120LL:
              goto LABEL_273;
            case 121LL:
              goto LABEL_285;
            case 122LL:
              goto LABEL_297;
            case 123LL:
              goto LABEL_309;
            case 124LL:
              goto LABEL_321;
            case 125LL:
              goto LABEL_333;
            case 126LL:
              goto LABEL_345;
            case 127LL:
              goto LABEL_357;
            case 128LL:
              goto LABEL_177;
            case 129LL:
              goto LABEL_188;
            case 130LL:
              goto LABEL_200;
            case 131LL:
              goto LABEL_212;
            case 132LL:
              goto LABEL_224;
            case 133LL:
              goto LABEL_236;
            case 134LL:
              goto LABEL_248;
            case 135LL:
              goto LABEL_260;
            case 136LL:
              goto LABEL_272;
            case 137LL:
              goto LABEL_284;
            case 138LL:
              goto LABEL_296;
            case 139LL:
              goto LABEL_308;
            case 140LL:
              goto LABEL_320;
            case 141LL:
              goto LABEL_332;
            case 142LL:
              goto LABEL_344;
            case 143LL:
              goto LABEL_356;
            case 144LL:
              goto LABEL_176;
            case 145LL:
              goto LABEL_187;
            case 146LL:
              goto LABEL_199;
            case 147LL:
              goto LABEL_211;
            case 148LL:
              goto LABEL_223;
            case 149LL:
              goto LABEL_235;
            case 150LL:
              goto LABEL_247;
            case 151LL:
              goto LABEL_259;
            case 152LL:
              goto LABEL_271;
            case 153LL:
              goto LABEL_283;
            case 154LL:
              goto LABEL_295;
            case 155LL:
              goto LABEL_307;
            case 156LL:
              goto LABEL_319;
            case 157LL:
              goto LABEL_331;
            case 158LL:
              goto LABEL_343;
            case 159LL:
              goto LABEL_355;
            case 160LL:
              goto LABEL_175;
            case 161LL:
              goto LABEL_186;
            case 162LL:
              goto LABEL_198;
            case 163LL:
              goto LABEL_210;
            case 164LL:
              goto LABEL_222;
            case 165LL:
              goto LABEL_234;
            case 166LL:
              goto LABEL_246;
            case 167LL:
              goto LABEL_258;
            case 168LL:
              goto LABEL_270;
            case 169LL:
              goto LABEL_282;
            case 170LL:
              goto LABEL_294;
            case 171LL:
              goto LABEL_306;
            case 172LL:
              goto LABEL_318;
            case 173LL:
              goto LABEL_330;
            case 174LL:
              goto LABEL_342;
            case 175LL:
              goto LABEL_354;
            case 176LL:
              goto LABEL_174;
            case 177LL:
              goto LABEL_185;
            case 178LL:
              goto LABEL_197;
            case 179LL:
              goto LABEL_209;
            case 180LL:
              goto LABEL_221;
            case 181LL:
              goto LABEL_233;
            case 182LL:
              goto LABEL_245;
            case 183LL:
              goto LABEL_257;
            case 184LL:
              goto LABEL_269;
            case 185LL:
              goto LABEL_281;
            case 186LL:
              goto LABEL_293;
            case 187LL:
              goto LABEL_305;
            case 188LL:
              goto LABEL_317;
            case 189LL:
              goto LABEL_329;
            case 190LL:
              goto LABEL_341;
            case 191LL:
              goto LABEL_353;
            }
          }
          return result;
        }
        if(dword_140028E14 > -1)
          break;
        if(v3 < 0)
          goto LABEL_373;
        v17 = result;
        v16 = a1;
        v15 = v5;
        v14 = a3;
        sub_140021280();
        a3 = v14;
        v5 = v15;
        a1 = v16;
        result = v17;
      }
      if(a3 > (unsigned int)dword_141134C20 && dword_141134C20) {
        do {
          _mm_stream_si32(a1, v5);
          _mm_stream_si32(a1 + 2, v5);
          a3 -= 64;
          _mm_stream_si32(a1 + 4, v5);
          _mm_stream_si32(a1 + 6, v5);
          _mm_stream_si32(a1 + 8, v5);
          _mm_stream_si32(a1 + 10, v5);
          _mm_stream_si32(a1 + 12, v5);
          _mm_stream_si32(a1 + 14, v5);
          a1 += 16;
        } while(a3 >= 64);
        v6 = (char *)a1 + a3;
        switch(a3) {
        case 0LL:
          return result;
        case 1LL:
          goto LABEL_36;
        case 2LL:
          goto LABEL_69;
        case 3LL:
          goto LABEL_86;
        case 4LL:
          goto LABEL_103;
        case 5LL:
          goto LABEL_120;
        case 6LL:
          goto LABEL_137;
        case 7LL:
          goto LABEL_154;
        case 8LL:
          goto LABEL_52;
        case 9LL:
          goto LABEL_35;
        case 10LL:
          goto LABEL_68;
        case 11LL:
          goto LABEL_85;
        case 12LL:
          goto LABEL_102;
        case 13LL:
          goto LABEL_119;
        case 14LL:
          goto LABEL_136;
        case 15LL:
          goto LABEL_153;
        case 16LL:
          goto LABEL_51;
        case 17LL:
          goto LABEL_34;
        case 18LL:
          goto LABEL_67;
        case 19LL:
          goto LABEL_84;
        case 20LL:
          goto LABEL_101;
        case 21LL:
          goto LABEL_118;
        case 22LL:
          goto LABEL_135;
        case 23LL:
          goto LABEL_152;
        case 24LL:
          goto LABEL_50;
        case 25LL:
          goto LABEL_33;
        case 26LL:
          goto LABEL_66;
        case 27LL:
          goto LABEL_83;
        case 28LL:
          goto LABEL_100;
        case 29LL:
          goto LABEL_117;
        case 30LL:
          goto LABEL_134;
        case 31LL:
          goto LABEL_151;
        case 32LL:
          goto LABEL_49;
        case 33LL:
          goto LABEL_32;
        case 34LL:
          goto LABEL_65;
        case 35LL:
          goto LABEL_82;
        case 36LL:
          goto LABEL_99;
        case 37LL:
          goto LABEL_116;
        case 38LL:
          goto LABEL_133;
        case 39LL:
          goto LABEL_150;
        case 40LL:
          goto LABEL_48;
        case 41LL:
          goto LABEL_31;
        case 42LL:
          goto LABEL_64;
        case 43LL:
          goto LABEL_81;
        case 44LL:
          goto LABEL_98;
        case 45LL:
          goto LABEL_115;
        case 46LL:
          goto LABEL_132;
        case 47LL:
          goto LABEL_149;
        case 48LL:
          goto LABEL_47;
        case 49LL:
          goto LABEL_30;
        case 50LL:
          goto LABEL_63;
        case 51LL:
          goto LABEL_80;
        case 52LL:
          goto LABEL_97;
        case 53LL:
          goto LABEL_114;
        case 54LL:
          goto LABEL_131;
        case 55LL:
          goto LABEL_148;
        case 56LL:
          goto LABEL_46;
        case 57LL:
          goto LABEL_29;
        case 58LL:
          goto LABEL_62;
        case 59LL:
          goto LABEL_79;
        case 60LL:
          goto LABEL_96;
        case 61LL:
          goto LABEL_113;
        case 62LL:
          goto LABEL_130;
        case 63LL:
          goto LABEL_147;
        case 64LL:
          goto LABEL_45;
        case 65LL:
          goto LABEL_28;
        case 66LL:
          goto LABEL_61;
        case 67LL:
          goto LABEL_78;
        case 68LL:
          goto LABEL_95;
        case 69LL:
          goto LABEL_112;
        case 70LL:
          goto LABEL_129;
        case 71LL:
          goto LABEL_146;
        case 72LL:
          goto LABEL_44;
        case 73LL:
          goto LABEL_27;
        case 74LL:
          goto LABEL_60;
        case 75LL:
          goto LABEL_77;
        case 76LL:
          goto LABEL_94;
        case 77LL:
          goto LABEL_111;
        case 78LL:
          goto LABEL_128;
        case 79LL:
          goto LABEL_145;
        case 80LL:
          goto LABEL_43;
        case 81LL:
          goto LABEL_26;
        case 82LL:
          goto LABEL_59;
        case 83LL:
          goto LABEL_76;
        case 84LL:
          goto LABEL_93;
        case 85LL:
          goto LABEL_110;
        case 86LL:
          goto LABEL_127;
        case 87LL:
          goto LABEL_144;
        case 88LL:
          goto LABEL_42;
        case 89LL:
          goto LABEL_25;
        case 90LL:
          goto LABEL_58;
        case 91LL:
          goto LABEL_75;
        case 92LL:
          goto LABEL_92;
        case 93LL:
          goto LABEL_109;
        case 94LL:
          goto LABEL_126;
        case 95LL:
          goto LABEL_143;
        case 96LL:
          goto LABEL_41;
        case 97LL:
          goto LABEL_24;
        case 98LL:
          goto LABEL_57;
        case 99LL:
          goto LABEL_74;
        case 100LL:
          goto LABEL_91;
        case 101LL:
          goto LABEL_108;
        case 102LL:
          goto LABEL_125;
        case 103LL:
          goto LABEL_142;
        case 104LL:
          goto LABEL_40;
        case 105LL:
          goto LABEL_23;
        case 106LL:
          goto LABEL_56;
        case 107LL:
          goto LABEL_73;
        case 108LL:
          goto LABEL_90;
        case 109LL:
          goto LABEL_107;
        case 110LL:
          goto LABEL_124;
        case 111LL:
          goto LABEL_141;
        case 112LL:
          goto LABEL_39;
        case 113LL:
          goto LABEL_22;
        case 114LL:
          goto LABEL_55;
        case 115LL:
          goto LABEL_72;
        case 116LL:
          goto LABEL_89;
        case 117LL:
          goto LABEL_106;
        case 118LL:
          goto LABEL_123;
        case 119LL:
          goto LABEL_140;
        case 120LL:
          goto LABEL_38;
        case 121LL:
          goto LABEL_21;
        case 122LL:
          goto LABEL_54;
        case 123LL:
          goto LABEL_71;
        case 124LL:
          goto LABEL_88;
        case 125LL:
          goto LABEL_105;
        case 126LL:
          goto LABEL_122;
        case 127LL:
          goto LABEL_139;
        case 128LL:
          goto LABEL_37;
        case 129LL:
          goto LABEL_20;
        case 130LL:
          goto LABEL_53;
        case 131LL:
          goto LABEL_70;
        case 132LL:
          goto LABEL_87;
        case 133LL:
          goto LABEL_104;
        case 134LL:
          goto LABEL_121;
        case 135LL:
          goto LABEL_138;
        }
        return result;
      }
      do {
      LABEL_373:
        *(_QWORD *)a1 = v5;
        *((_QWORD *)a1 + 1) = v5;
        a3 -= 64;
        *((_QWORD *)a1 + 2) = v5;
        *((_QWORD *)a1 + 3) = v5;
        *((_QWORD *)a1 + 4) = v5;
        *((_QWORD *)a1 + 5) = v5;
        *((_QWORD *)a1 + 6) = v5;
        *((_QWORD *)a1 + 7) = v5;
        a1 += 16;
      } while(a3 > 64);
      v6 = (char *)a1 + a3;
      switch(a3) {
      case 0LL:
        return result;
      case 1LL:
        goto LABEL_36;
      case 2LL:
        goto LABEL_69;
      case 3LL:
        goto LABEL_86;
      case 4LL:
        goto LABEL_103;
      case 5LL:
        goto LABEL_120;
      case 6LL:
        goto LABEL_137;
      case 7LL:
        goto LABEL_154;
      case 8LL:
        goto LABEL_52;
      case 9LL:
        goto LABEL_35;
      case 10LL:
        goto LABEL_68;
      case 11LL:
        goto LABEL_85;
      case 12LL:
        goto LABEL_102;
      case 13LL:
        goto LABEL_119;
      case 14LL:
        goto LABEL_136;
      case 15LL:
        goto LABEL_153;
      case 16LL:
        goto LABEL_51;
      case 17LL:
        goto LABEL_34;
      case 18LL:
        goto LABEL_67;
      case 19LL:
        goto LABEL_84;
      case 20LL:
        goto LABEL_101;
      case 21LL:
        goto LABEL_118;
      case 22LL:
        goto LABEL_135;
      case 23LL:
        goto LABEL_152;
      case 24LL:
        goto LABEL_50;
      case 25LL:
        goto LABEL_33;
      case 26LL:
        goto LABEL_66;
      case 27LL:
        goto LABEL_83;
      case 28LL:
        goto LABEL_100;
      case 29LL:
        goto LABEL_117;
      case 30LL:
        goto LABEL_134;
      case 31LL:
        goto LABEL_151;
      case 32LL:
        goto LABEL_49;
      case 33LL:
        goto LABEL_32;
      case 34LL:
        goto LABEL_65;
      case 35LL:
        goto LABEL_82;
      case 36LL:
        goto LABEL_99;
      case 37LL:
        goto LABEL_116;
      case 38LL:
        goto LABEL_133;
      case 39LL:
        goto LABEL_150;
      case 40LL:
        goto LABEL_48;
      case 41LL:
        goto LABEL_31;
      case 42LL:
        goto LABEL_64;
      case 43LL:
        goto LABEL_81;
      case 44LL:
        goto LABEL_98;
      case 45LL:
        goto LABEL_115;
      case 46LL:
        goto LABEL_132;
      case 47LL:
        goto LABEL_149;
      case 48LL:
        goto LABEL_47;
      case 49LL:
        goto LABEL_30;
      case 50LL:
        goto LABEL_63;
      case 51LL:
        goto LABEL_80;
      case 52LL:
        goto LABEL_97;
      case 53LL:
        goto LABEL_114;
      case 54LL:
        goto LABEL_131;
      case 55LL:
        goto LABEL_148;
      case 56LL:
        goto LABEL_46;
      case 57LL:
        goto LABEL_29;
      case 58LL:
        goto LABEL_62;
      case 59LL:
        goto LABEL_79;
      case 60LL:
        goto LABEL_96;
      case 61LL:
        goto LABEL_113;
      case 62LL:
        goto LABEL_130;
      case 63LL:
        goto LABEL_147;
      case 64LL:
        goto LABEL_45;
      case 65LL:
        goto LABEL_28;
      case 66LL:
        goto LABEL_61;
      case 67LL:
        goto LABEL_78;
      case 68LL:
        goto LABEL_95;
      case 69LL:
        goto LABEL_112;
      case 70LL:
        goto LABEL_129;
      case 71LL:
        goto LABEL_146;
      case 72LL:
        goto LABEL_44;
      case 73LL:
        goto LABEL_27;
      case 74LL:
        goto LABEL_60;
      case 75LL:
        goto LABEL_77;
      case 76LL:
        goto LABEL_94;
      case 77LL:
        goto LABEL_111;
      case 78LL:
        goto LABEL_128;
      case 79LL:
        goto LABEL_145;
      case 80LL:
        goto LABEL_43;
      case 81LL:
        goto LABEL_26;
      case 82LL:
        goto LABEL_59;
      case 83LL:
        goto LABEL_76;
      case 84LL:
        goto LABEL_93;
      case 85LL:
        goto LABEL_110;
      case 86LL:
        goto LABEL_127;
      case 87LL:
        goto LABEL_144;
      case 88LL:
        goto LABEL_42;
      case 89LL:
        goto LABEL_25;
      case 90LL:
        goto LABEL_58;
      case 91LL:
        goto LABEL_75;
      case 92LL:
        goto LABEL_92;
      case 93LL:
        goto LABEL_109;
      case 94LL:
        goto LABEL_126;
      case 95LL:
        goto LABEL_143;
      case 96LL:
        goto LABEL_41;
      case 97LL:
        goto LABEL_24;
      case 98LL:
        goto LABEL_57;
      case 99LL:
        goto LABEL_74;
      case 100LL:
        goto LABEL_91;
      case 101LL:
        goto LABEL_108;
      case 102LL:
        goto LABEL_125;
      case 103LL:
        goto LABEL_142;
      case 104LL:
        goto LABEL_40;
      case 105LL:
        goto LABEL_23;
      case 106LL:
        goto LABEL_56;
      case 107LL:
        goto LABEL_73;
      case 108LL:
        goto LABEL_90;
      case 109LL:
        goto LABEL_107;
      case 110LL:
        goto LABEL_124;
      case 111LL:
        goto LABEL_141;
      case 112LL:
        goto LABEL_39;
      case 113LL:
        goto LABEL_22;
      case 114LL:
        goto LABEL_55;
      case 115LL:
        goto LABEL_72;
      case 116LL:
        goto LABEL_89;
      case 117LL:
        goto LABEL_106;
      case 118LL:
        goto LABEL_123;
      case 119LL:
        goto LABEL_140;
      case 120LL:
        goto LABEL_38;
      case 121LL:
        goto LABEL_21;
      case 122LL:
        goto LABEL_54;
      case 123LL:
        goto LABEL_71;
      case 124LL:
        goto LABEL_88;
      case 125LL:
        goto LABEL_105;
      case 126LL:
        goto LABEL_122;
      case 127LL:
        goto LABEL_139;
      case 128LL:
      LABEL_37:
        *((_QWORD *)v6 - 16) = v5;
      LABEL_38:
        *((_QWORD *)v6 - 15) = v5;
      LABEL_39:
        *((_QWORD *)v6 - 14) = v5;
      LABEL_40:
        *((_QWORD *)v6 - 13) = v5;
      LABEL_41:
        *((_QWORD *)v6 - 12) = v5;
      LABEL_42:
        *((_QWORD *)v6 - 11) = v5;
      LABEL_43:
        *((_QWORD *)v6 - 10) = v5;
      LABEL_44:
        *((_QWORD *)v6 - 9) = v5;
      LABEL_45:
        *((_QWORD *)v6 - 8) = v5;
      LABEL_46:
        *((_QWORD *)v6 - 7) = v5;
      LABEL_47:
        *((_QWORD *)v6 - 6) = v5;
      LABEL_48:
        *((_QWORD *)v6 - 5) = v5;
      LABEL_49:
        *((_QWORD *)v6 - 4) = v5;
      LABEL_50:
        *((_QWORD *)v6 - 3) = v5;
      LABEL_51:
        *((_QWORD *)v6 - 2) = v5;
      LABEL_52:
        *((_QWORD *)v6 - 1) = v5;
        break;
      case 129LL:
      LABEL_20:
        *(_QWORD *)(v6 - 129) = v5;
      LABEL_21:
        *(_QWORD *)(v6 - 121) = v5;
      LABEL_22:
        *(_QWORD *)(v6 - 113) = v5;
      LABEL_23:
        *(_QWORD *)(v6 - 105) = v5;
      LABEL_24:
        *(_QWORD *)(v6 - 97) = v5;
      LABEL_25:
        *(_QWORD *)(v6 - 89) = v5;
      LABEL_26:
        *(_QWORD *)(v6 - 81) = v5;
      LABEL_27:
        *(_QWORD *)(v6 - 73) = v5;
      LABEL_28:
        *(_QWORD *)(v6 - 65) = v5;
      LABEL_29:
        *(_QWORD *)(v6 - 57) = v5;
      LABEL_30:
        *(_QWORD *)(v6 - 49) = v5;
      LABEL_31:
        *(_QWORD *)(v6 - 41) = v5;
      LABEL_32:
        *(_QWORD *)(v6 - 33) = v5;
      LABEL_33:
        *(_QWORD *)(v6 - 25) = v5;
      LABEL_34:
        *(_QWORD *)(v6 - 17) = v5;
      LABEL_35:
        *(_QWORD *)(v6 - 9) = v5;
      LABEL_36:
        *(v6 - 1) = v5;
        break;
      case 130LL:
      LABEL_53:
        *(_QWORD *)(v6 - 130) = v5;
      LABEL_54:
        *(_QWORD *)(v6 - 122) = v5;
      LABEL_55:
        *(_QWORD *)(v6 - 114) = v5;
      LABEL_56:
        *(_QWORD *)(v6 - 106) = v5;
      LABEL_57:
        *(_QWORD *)(v6 - 98) = v5;
      LABEL_58:
        *(_QWORD *)(v6 - 90) = v5;
      LABEL_59:
        *(_QWORD *)(v6 - 82) = v5;
      LABEL_60:
        *(_QWORD *)(v6 - 74) = v5;
      LABEL_61:
        *(_QWORD *)(v6 - 66) = v5;
      LABEL_62:
        *(_QWORD *)(v6 - 58) = v5;
      LABEL_63:
        *(_QWORD *)(v6 - 50) = v5;
      LABEL_64:
        *(_QWORD *)(v6 - 42) = v5;
      LABEL_65:
        *(_QWORD *)(v6 - 34) = v5;
      LABEL_66:
        *(_QWORD *)(v6 - 26) = v5;
      LABEL_67:
        *(_QWORD *)(v6 - 18) = v5;
      LABEL_68:
        *(_QWORD *)(v6 - 10) = v5;
      LABEL_69:
        *((_WORD *)v6 - 1) = v5;
        break;
      case 131LL:
      LABEL_70:
        *(_QWORD *)(v6 - 131) = v5;
      LABEL_71:
        *(_QWORD *)(v6 - 123) = v5;
      LABEL_72:
        *(_QWORD *)(v6 - 115) = v5;
      LABEL_73:
        *(_QWORD *)(v6 - 107) = v5;
      LABEL_74:
        *(_QWORD *)(v6 - 99) = v5;
      LABEL_75:
        *(_QWORD *)(v6 - 91) = v5;
      LABEL_76:
        *(_QWORD *)(v6 - 83) = v5;
      LABEL_77:
        *(_QWORD *)(v6 - 75) = v5;
      LABEL_78:
        *(_QWORD *)(v6 - 67) = v5;
      LABEL_79:
        *(_QWORD *)(v6 - 59) = v5;
      LABEL_80:
        *(_QWORD *)(v6 - 51) = v5;
      LABEL_81:
        *(_QWORD *)(v6 - 43) = v5;
      LABEL_82:
        *(_QWORD *)(v6 - 35) = v5;
      LABEL_83:
        *(_QWORD *)(v6 - 27) = v5;
      LABEL_84:
        *(_QWORD *)(v6 - 19) = v5;
      LABEL_85:
        *(_QWORD *)(v6 - 11) = v5;
      LABEL_86:
        *(_WORD *)(v6 - 3) = v5;
        *(v6 - 1) = v5;
        break;
      case 132LL:
      LABEL_87:
        *(_QWORD *)(v6 - 132) = v5;
      LABEL_88:
        *(_QWORD *)(v6 - 124) = v5;
      LABEL_89:
        *(_QWORD *)(v6 - 116) = v5;
      LABEL_90:
        *(_QWORD *)(v6 - 108) = v5;
      LABEL_91:
        *(_QWORD *)(v6 - 100) = v5;
      LABEL_92:
        *(_QWORD *)(v6 - 92) = v5;
      LABEL_93:
        *(_QWORD *)(v6 - 84) = v5;
      LABEL_94:
        *(_QWORD *)(v6 - 76) = v5;
      LABEL_95:
        *(_QWORD *)(v6 - 68) = v5;
      LABEL_96:
        *(_QWORD *)(v6 - 60) = v5;
      LABEL_97:
        *(_QWORD *)(v6 - 52) = v5;
      LABEL_98:
        *(_QWORD *)(v6 - 44) = v5;
      LABEL_99:
        *(_QWORD *)(v6 - 36) = v5;
      LABEL_100:
        *(_QWORD *)(v6 - 28) = v5;
      LABEL_101:
        *(_QWORD *)(v6 - 20) = v5;
      LABEL_102:
        *(_QWORD *)(v6 - 12) = v5;
      LABEL_103:
        *((_DWORD *)v6 - 1) = v5;
        break;
      case 133LL:
      LABEL_104:
        *(_QWORD *)(v6 - 132) = v5;
      LABEL_105:
        *(_QWORD *)(v6 - 125) = v5;
      LABEL_106:
        *(_QWORD *)(v6 - 117) = v5;
      LABEL_107:
        *(_QWORD *)(v6 - 109) = v5;
      LABEL_108:
        *(_QWORD *)(v6 - 101) = v5;
      LABEL_109:
        *(_QWORD *)(v6 - 93) = v5;
      LABEL_110:
        *(_QWORD *)(v6 - 85) = v5;
      LABEL_111:
        *(_QWORD *)(v6 - 77) = v5;
      LABEL_112:
        *(_QWORD *)(v6 - 69) = v5;
      LABEL_113:
        *(_QWORD *)(v6 - 61) = v5;
      LABEL_114:
        *(_QWORD *)(v6 - 53) = v5;
      LABEL_115:
        *(_QWORD *)(v6 - 45) = v5;
      LABEL_116:
        *(_QWORD *)(v6 - 37) = v5;
      LABEL_117:
        *(_QWORD *)(v6 - 29) = v5;
      LABEL_118:
        *(_QWORD *)(v6 - 21) = v5;
      LABEL_119:
        *(_QWORD *)(v6 - 13) = v5;
      LABEL_120:
        *(_DWORD *)(v6 - 5) = v5;
        *(v6 - 1) = v5;
        break;
      case 134LL:
      LABEL_121:
        *(_QWORD *)(v6 - 134) = v5;
      LABEL_122:
        *(_QWORD *)(v6 - 126) = v5;
      LABEL_123:
        *(_QWORD *)(v6 - 118) = v5;
      LABEL_124:
        *(_QWORD *)(v6 - 110) = v5;
      LABEL_125:
        *(_QWORD *)(v6 - 102) = v5;
      LABEL_126:
        *(_QWORD *)(v6 - 94) = v5;
      LABEL_127:
        *(_QWORD *)(v6 - 86) = v5;
      LABEL_128:
        *(_QWORD *)(v6 - 78) = v5;
      LABEL_129:
        *(_QWORD *)(v6 - 70) = v5;
      LABEL_130:
        *(_QWORD *)(v6 - 62) = v5;
      LABEL_131:
        *(_QWORD *)(v6 - 54) = v5;
      LABEL_132:
        *(_QWORD *)(v6 - 46) = v5;
      LABEL_133:
        *(_QWORD *)(v6 - 38) = v5;
      LABEL_134:
        *(_QWORD *)(v6 - 30) = v5;
      LABEL_135:
        *(_QWORD *)(v6 - 22) = v5;
      LABEL_136:
        *(_QWORD *)(v6 - 14) = v5;
      LABEL_137:
        *(_DWORD *)(v6 - 6) = v5;
        *((_WORD *)v6 - 1) = v5;
        break;
      case 135LL:
      LABEL_138:
        *(_QWORD *)(v6 - 135) = v5;
      LABEL_139:
        *(_QWORD *)(v6 - 127) = v5;
      LABEL_140:
        *(_QWORD *)(v6 - 119) = v5;
      LABEL_141:
        *(_QWORD *)(v6 - 111) = v5;
      LABEL_142:
        *(_QWORD *)(v6 - 103) = v5;
      LABEL_143:
        *(_QWORD *)(v6 - 95) = v5;
      LABEL_144:
        *(_QWORD *)(v6 - 87) = v5;
      LABEL_145:
        *(_QWORD *)(v6 - 79) = v5;
      LABEL_146:
        *(_QWORD *)(v6 - 71) = v5;
      LABEL_147:
        *(_QWORD *)(v6 - 63) = v5;
      LABEL_148:
        *(_QWORD *)(v6 - 55) = v5;
      LABEL_149:
        *(_QWORD *)(v6 - 47) = v5;
      LABEL_150:
        *(_QWORD *)(v6 - 39) = v5;
      LABEL_151:
        *(_QWORD *)(v6 - 31) = v5;
      LABEL_152:
        *(_QWORD *)(v6 - 23) = v5;
      LABEL_153:
        *(_QWORD *)(v6 - 15) = v5;
      LABEL_154:
        *(_DWORD *)(v6 - 7) = v5;
        *(_WORD *)(v6 - 3) = v5;
        *(v6 - 1) = v5;
        break;
      }
    } else {
      v6 = (char *)a1 + a3;
      switch(a3) {
      case 0LL:
        return result;
      case 1LL:
        goto LABEL_36;
      case 2LL:
        goto LABEL_69;
      case 3LL:
        goto LABEL_86;
      case 4LL:
        goto LABEL_103;
      case 5LL:
        goto LABEL_120;
      case 6LL:
        goto LABEL_137;
      case 7LL:
        goto LABEL_154;
      case 8LL:
        goto LABEL_52;
      case 9LL:
        goto LABEL_35;
      case 10LL:
        goto LABEL_68;
      case 11LL:
        goto LABEL_85;
      case 12LL:
        goto LABEL_102;
      case 13LL:
        goto LABEL_119;
      case 14LL:
        goto LABEL_136;
      case 15LL:
        goto LABEL_153;
      case 16LL:
        goto LABEL_51;
      case 17LL:
        goto LABEL_34;
      case 18LL:
        goto LABEL_67;
      case 19LL:
        goto LABEL_84;
      case 20LL:
        goto LABEL_101;
      case 21LL:
        goto LABEL_118;
      case 22LL:
        goto LABEL_135;
      case 23LL:
        goto LABEL_152;
      case 24LL:
        goto LABEL_50;
      case 25LL:
        goto LABEL_33;
      case 26LL:
        goto LABEL_66;
      case 27LL:
        goto LABEL_83;
      case 28LL:
        goto LABEL_100;
      case 29LL:
        goto LABEL_117;
      case 30LL:
        goto LABEL_134;
      case 31LL:
        goto LABEL_151;
      case 32LL:
        goto LABEL_49;
      case 33LL:
        goto LABEL_32;
      case 34LL:
        goto LABEL_65;
      case 35LL:
        goto LABEL_82;
      case 36LL:
        goto LABEL_99;
      case 37LL:
        goto LABEL_116;
      case 38LL:
        goto LABEL_133;
      case 39LL:
        goto LABEL_150;
      case 40LL:
        goto LABEL_48;
      case 41LL:
        goto LABEL_31;
      case 42LL:
        goto LABEL_64;
      case 43LL:
        goto LABEL_81;
      case 44LL:
        goto LABEL_98;
      case 45LL:
        goto LABEL_115;
      case 46LL:
        goto LABEL_132;
      case 47LL:
        goto LABEL_149;
      case 48LL:
        goto LABEL_47;
      case 49LL:
        goto LABEL_30;
      case 50LL:
        goto LABEL_63;
      case 51LL:
        goto LABEL_80;
      case 52LL:
        goto LABEL_97;
      case 53LL:
        goto LABEL_114;
      case 54LL:
        goto LABEL_131;
      case 55LL:
        goto LABEL_148;
      case 56LL:
        goto LABEL_46;
      case 57LL:
        goto LABEL_29;
      case 58LL:
        goto LABEL_62;
      case 59LL:
        goto LABEL_79;
      case 60LL:
        goto LABEL_96;
      case 61LL:
        goto LABEL_113;
      case 62LL:
        goto LABEL_130;
      case 63LL:
        goto LABEL_147;
      case 64LL:
        goto LABEL_45;
      case 65LL:
        goto LABEL_28;
      case 66LL:
        goto LABEL_61;
      case 67LL:
        goto LABEL_78;
      case 68LL:
        goto LABEL_95;
      case 69LL:
        goto LABEL_112;
      case 70LL:
        goto LABEL_129;
      case 71LL:
        goto LABEL_146;
      case 72LL:
        goto LABEL_44;
      case 73LL:
        goto LABEL_27;
      case 74LL:
        goto LABEL_60;
      case 75LL:
        goto LABEL_77;
      case 76LL:
        goto LABEL_94;
      case 77LL:
        goto LABEL_111;
      case 78LL:
        goto LABEL_128;
      case 79LL:
        goto LABEL_145;
      case 80LL:
        goto LABEL_43;
      case 81LL:
        goto LABEL_26;
      case 82LL:
        goto LABEL_59;
      case 83LL:
        goto LABEL_76;
      case 84LL:
        goto LABEL_93;
      case 85LL:
        goto LABEL_110;
      case 86LL:
        goto LABEL_127;
      case 87LL:
        goto LABEL_144;
      case 88LL:
        goto LABEL_42;
      case 89LL:
        goto LABEL_25;
      case 90LL:
        goto LABEL_58;
      case 91LL:
        goto LABEL_75;
      case 92LL:
        goto LABEL_92;
      case 93LL:
        goto LABEL_109;
      case 94LL:
        goto LABEL_126;
      case 95LL:
        goto LABEL_143;
      case 96LL:
        goto LABEL_41;
      case 97LL:
        goto LABEL_24;
      case 98LL:
        goto LABEL_57;
      case 99LL:
        goto LABEL_74;
      case 100LL:
        goto LABEL_91;
      case 101LL:
        goto LABEL_108;
      case 102LL:
        goto LABEL_125;
      case 103LL:
        goto LABEL_142;
      case 104LL:
        goto LABEL_40;
      case 105LL:
        goto LABEL_23;
      case 106LL:
        goto LABEL_56;
      case 107LL:
        goto LABEL_73;
      case 108LL:
        goto LABEL_90;
      case 109LL:
        goto LABEL_107;
      case 110LL:
        goto LABEL_124;
      case 111LL:
        goto LABEL_141;
      case 112LL:
        goto LABEL_39;
      case 113LL:
        goto LABEL_22;
      case 114LL:
        goto LABEL_55;
      case 115LL:
        goto LABEL_72;
      case 116LL:
        goto LABEL_89;
      case 117LL:
        goto LABEL_106;
      case 118LL:
        goto LABEL_123;
      case 119LL:
        goto LABEL_140;
      case 120LL:
        goto LABEL_38;
      case 121LL:
        goto LABEL_21;
      case 122LL:
        goto LABEL_54;
      case 123LL:
        goto LABEL_71;
      case 124LL:
        goto LABEL_88;
      case 125LL:
        goto LABEL_105;
      case 126LL:
        goto LABEL_122;
      case 127LL:
        goto LABEL_139;
      case 128LL:
        goto LABEL_37;
      case 129LL:
        goto LABEL_20;
      case 130LL:
        goto LABEL_53;
      case 131LL:
        goto LABEL_70;
      case 132LL:
        goto LABEL_87;
      case 133LL:
        goto LABEL_104;
      case 134LL:
        goto LABEL_121;
      case 135LL:
        goto LABEL_138;
      }
    }
  }
  return result;
}
// 14001FD24: variable 'a1' is possibly undefined
// 14001FD27: variable 'a3' is possibly undefined
// 14001FD29: variable 'a2' is possibly undefined
// 14001D780: using guessed type __int64 unknown_libname_20(void);
// 140028E14: using guessed type int dword_140028E14;
// 1411345E0: using guessed type int dword_1411345E0[400];
// 141134C20: using guessed type int dword_141134C20;

// ---- Cleanup --------------------------------------------------------
#undef dword_140028E14
#undef dword_1411345E0
#undef dword_141134C20
#undef intel_cpuid
#undef sub_140021280
#undef unknown_libname_20
#undef FILE
