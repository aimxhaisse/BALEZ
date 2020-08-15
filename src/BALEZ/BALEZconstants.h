#pragma once

constexpr int kPaddingWidth = 15;
constexpr int kPaddingHeight = 10;

constexpr int kHeaderHeight = 20 + 2 * kPaddingWidth;
constexpr int kFooterHeight = 10 + 2 * kPaddingHeight;

constexpr int kDialTextHeight = 40;
constexpr int kDialWidth = 100;
constexpr int kDialHeight = kDialWidth + kDialTextHeight;

constexpr int kSizeWidth = 600;
constexpr int kSizeHeight = kHeaderHeight + kFooterHeight + kDialHeight;
