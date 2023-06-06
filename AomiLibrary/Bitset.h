#pragma once
#include <cstdint>
#include "Assert.h"

namespace AomiLibrary {

	template<size_t kBitCount>
	class Bitset {
		static_assert(kBitCount > 0, "A bitset with 0 bits is not possible.");
	public:
		Bitset() {
			Reset();
		}

		friend std::ostream& operator<<(std::ostream& os, const Bitset& bitset) {
			for (size_t i = kBitCount; i > 0; --i) {
				os << bitset.Test(i - 1) ? '1' : '0';
			}
			return os;
		}

		inline Bitset& Flip() {
			for (auto& word : words_) {
				word = ~word;
			}
			return *this;
		}
		inline Bitset& Flip(size_t bitIndex) {
			auto& word = GetWord(bitIndex);
			word = word ^ static_cast<uint64_t>(1) << (bitIndex & kWordMask);
			return *this;
		}
		inline Bitset& Set(bool value = true) {
			memset(words_, value ? ~0 : 0, sizeof(words_));
			return *this;
		}
		inline Bitset& Set(size_t bitIndex, bool value = true) {
			ASSERT_MSG(bitIndex < kBitCount, "Out of range");
			uint64_t& word = GetWord(bitIndex);
			if (value) {
				word |= static_cast<uint64_t>(1) << (bitIndex & kWordMask);
			}
			else {
				word &= ~(static_cast<uint64_t>(1) << (bitIndex & kWordMask));
			}
			return *this;
		}
		inline Bitset& Reset() {
			Set(false);
			return *this;
		}
		inline Bitset& Reset(size_t bitIndex) {
			Set(bitIndex, false);
			return *this;
		}
		inline bool Test(size_t bitIndex) const {
			ASSERT_MSG(bitIndex < kBitCount, "Out of range");
			return (GetWord(bitIndex) & (static_cast<uint64_t>(1) << (bitIndex & kWordMask))) != 0;
		}

		inline size_t GetBitCount() const { return kBitCount; }

	private:
		inline uint64_t& GetWord(size_t bitIndex) {
			return words_[bitIndex >> kBitIndexToWordIndex];
		}
		inline const uint64_t& GetWord(size_t bitIndex) const {
			return words_[bitIndex >> kBitIndexToWordIndex];
		}

		static constexpr size_t kWordSize = CHAR_BIT * sizeof(uint64_t);
		static constexpr size_t kWordCount = (kBitCount - 1) / kWordSize + 1;
		static constexpr size_t kWordMask = kWordSize - 1;
		static constexpr size_t kBitIndexToWordIndex = 6;

		uint64_t words_[kWordCount];
	};


}
