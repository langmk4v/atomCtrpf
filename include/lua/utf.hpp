#pragma once

#include "types.hpp"

namespace CTRPluginFramework::lua::utf {

auto decode_utf8(u32* out, u8 const* code) -> u8 const*;
auto decode_utf16(u32* out, u16 const* in) -> u16 const*;

auto encode_utf8(u8* out, u32 const in) -> u8*;
auto encode_utf16(u16* out, u32 const code) -> u16*;

auto utf8_to_utf16(string const& str) -> std::u16string;
auto utf8_to_utf16(string_view const& str) -> std::u16string;

auto utf16_to_utf8(std::u16string const& str) -> string;

}  // namespace CTRPluginFramework::lua::utf