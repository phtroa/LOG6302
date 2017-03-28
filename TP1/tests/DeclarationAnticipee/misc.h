template <bool overflow> struct SafeShifter;

template<> struct SafeShifter<true>
{
	template <class T>
	static inline T RightShift(T value, unsigned int bits)
	{
		return 0;
	}
	template <class T>
	static inline T LeftShift(T value, unsigned int bits)
	{
		return 0;
	}
};

template<> struct SafeShifter<false>
{
	template <class T>
	static inline T RightShift(T value, unsigned int bits)
	{
		return value >> bits;
	}

	template <class T>
	static inline T LeftShift(T value, unsigned int bits)
	{
		return value << bits;
	}
};

template <unsigned int bits, class T>
inline T SafeRightShift(T value)
{
	return SafeShifter<(bits>=(8*sizeof(T)))>::RightShift(value, bits);
}

template <unsigned int bits, class T>
inline T SafeLeftShift(T value)
{
	return SafeShifter<(bits>=(8*sizeof(T)))>::LeftShift(value, bits);
}
