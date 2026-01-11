#include "lua/utf.hpp"

namespace CTRPluginFramework::lua::utf {

auto decode_utf8(u32* out, u8 const* code) -> u8 const* {
  if (code[0] < 0x80) {
    *out = code[0];
    code++;
  } else if ((code[0] >> 5) == 0x6) {
    *out = (u32)(((code[0] & 0x1F) << 6) | (code[1] & 0x3F));
    code += 2;
  } else if ((code[0] >> 4) == 0xE) {
    *out = (u32)(((code[0] & 0xF) << 12) | ((code[1] & 0x3F) << 6) |
                 (code[2] & 0x3F));
    code += 3;
  } else {
    *out = (u32)(((code[0] & 0x7) << 18) | ((code[1] & 0x3F) << 12) |
                 ((code[2] & 0x3F) << 6) | (code[3] & 0x3F));
    code += 4;
  }

  return code;
}

auto encode_utf8(u8* out, u32 const in) -> u8* {
  if (in < 0x80) {
    *out++ = in;
  } else if (in < 0x800) {
    *out++ = (in >> 6) + 0xC0;
    *out++ = (in & 0x3F) + 0x80;
  } else if (in < 0x10000) {
    *out++ = (in >> 12) + 0xE0;
    *out++ = ((in >> 6) & 0x3F) + 0x80;
    *out++ = (in & 0x3F) + 0x80;
  } else if (in < 0x110000) {
    *out++ = (in >> 18) + 0xF0;
    *out++ = ((in >> 12) & 0x3F) + 0x80;
    *out++ = ((in >> 6) & 0x3F) + 0x80;
    *out++ = (in & 0x3F) + 0x80;
  } else {
    return nullptr;
  }

  return out;
}

auto decode_utf16(u32* out, u16 const* in) -> u16 const* {
  if (in[0] >= 0xD800 && in[0] < 0xDC00) {
    if (in[1] >= 0xDC00 && in[1] < 0xE000) {
      *out = (in[0] << 10) + in[1] - 0x35FDC00;
      return in + 2;
    } else
      return nullptr;
  }

  *out = (u32)*in;

  return in + 1;
}

auto encode_utf16(u16* out, u32 const code) -> u16* {
  if (code <= 0xFFFF) {
    *out = (u16)code;
    return out + 1;
  } else {
    out[0] = (u16)(0xD800 + (code >> 10));
    out[1] = (u16)(0xDC00 + (code & 0x3FF));
    return out + 2;
  }
}

auto utf8_to_utf16_impl(char const* str, size_t len) -> std::u16string {
  u8 const* from = (u8 const*)str;
  u8 const* end = from + len;

  std::u16string result;
  result.reserve(len * 2 + 1);

  while (from < end) {
    u32 tmp;
    from = decode_utf8(&tmp, from);

    u16 buf[2] = {0};
    encode_utf16(buf, tmp);

    result.push_back(buf[0]);
    if (buf[1]) result.push_back(buf[1]);
  }

  return result;
}

//
// UTF8 --> UTF16
//
auto utf8_to_utf16(string const& str) -> std::u16string {
  return utf8_to_utf16_impl(str.data(), str.length());
}

auto utf8_to_utf16(string_view const& str) -> std::u16string {
  return utf8_to_utf16_impl(str.data(), str.length());
}

//
// UTF16 --> UTF8
//
auto utf16_to_utf8(std::u16string const& str) -> string {
  u16 const* from = (u16 const*)str.data();
  u16 const* end = from + str.length();

  string result;
  result.reserve(str.length());

  while (from < end) {
    u32 tmp;
    from = decode_utf16(&tmp, from);

    u8 buf[4] = {0};
    encode_utf8(buf, tmp);

    result.push_back(buf[0]);
    if (buf[1]) result.push_back(buf[1]);
    if (buf[2]) result.push_back(buf[2]);
    if (buf[3]) result.push_back(buf[3]);
  }

  return result;
}

}  // namespace CTRPluginFramework::lua::utf