/** @file eie.hpp
	Enum Interface Extension declarations.

	Copyright (C) 2018 RmbRT

	This file is part of EIE.

	EIE is free software: you can redistribute it and/or modify
	it under the terms of the GNU Affero General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	EIE is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Affero General Public License for more details.

	You should have received a copy of the GNU Affero General Public License
	along with EIE.  If not, see <https://www.gnu.org/licenses/>. */
#ifndef __cppeie_cppeie_hpp_defined
#define __cppeie_cppeie_hpp_defined

#include <cstddef>
#include <type_traits>
#include <cassert>

/** @def EIE(field)
	Extends an enum class.
	The enum must contain continuous values from 0 onwards.
	Marks `field` as the last constant in an enum.
	Simply surround the last field in the enum with this macro. */
#define EIE(field) field, __eie_last_constant = field


/** @def EIECXDA
	`inline`/`constexpr` modifier depending on whether debug assertions are enabled. */
#ifndef _NDEBUG
#define EIECXDA inline
#else
#define EIECXDA constexpr
#endif

/** The enum interface extension. */
namespace eie
{
	template<
		class Enum,
		class = typename std::enable_if<std::is_enum<Enum>::value>::type>
	/** Returns the enum field count of an enum.
	@tparam Enum:
		The enum type to get the field count of. Must have its size tagged with the `EIE` command.
	@return
		The enum field count. */
	constexpr std::size_t count();

	template<
		class Enum,
		class = typename std::enable_if<std::is_enum<Enum>::value>::type>
	/** Checks whether an enum value is within the valid range.
	@tparam Enum:
		The enum to check. Must have its size tagged with the `EIE` command.
	@param[in] value:
		The enum value to check.
	@return
		Whether the value is valid. */
	constexpr bool valid(
		Enum value);

	template<
		class Enum,
		class = typename std::enable_if<std::is_enum<Enum>::value>::type>
	/** Returns the first value of an enum.
	@tparam Enum:
		The enum type to get the first value of. Must have its size tagged with the `EIE` command.
	@return
		The first value in the enum. */
	constexpr Enum first();

	template<
		class Enum,
		class = typename std::enable_if<std::is_enum<Enum>::value>::type>
	/** Returns the last value of an enum.
	@tparam Enum:
		The enum type to get the last value of. Must have its size tagged with the `EIE` command.
	@return
		The last value in the enum. */
	constexpr Enum last();

	template<
		class Enum,
		class = typename std::enable_if<std::is_enum<Enum>::value>::type>
	/** Iterator type for looping through enum ranges.
	@tparam Enum:
		The iterator's enum type. */
	class Iterator
	{
		/** The iterator's value. */
		Enum m_value;
	public:
		Iterator() = default;

		/** Constructs an iterator for the given value.
		@parma[in] value:
			The iterator's value. */
		constexpr Iterator(
			Enum value);

		/** Retrieves the iterator's value.
			In debug mode, asserts that the value is valid.
		@return
			The iterator's value. */
		EIECXDA Enum operator*() const;

		/** Increments the iterator. */
		inline Iterator<Enum> &operator++();
		/** Increments the iterator. */
		inline Iterator<Enum> operator++(int);
		/** Decrements the iterator. */
		inline Iterator<Enum> &operator--();
		/** Decrements the iterator. */
		inline Iterator<Enum> operator--(int);

		/** Checks for iterator equality.
		@param[in] other:
			The iterator to compare to.
		@return
			Whether both iterators are equal. */
		constexpr bool operator==(
			Iterator<Enum> other) const;
		/** Checks for iterator inequality.
		@param[in] other:
			The iterator to compare to.
		@return
			Whether both iterators are not equal. */
		constexpr bool operator!=(
			Iterator<Enum> other) const;
	};

	template<
		class Enum,
		class = typename std::enable_if<std::is_enum<Enum>::value>::type>
	/** Returns an iterator to the enum's first element. */
	constexpr Iterator<Enum> begin();

	template<
		class Enum,
		class = typename std::enable_if<std::is_enum<Enum>::value>::type>
	/** Returns an iterator to the enum's end. */
	constexpr Iterator<Enum> end();

	template<
		class Enum,
		class = typename std::enable_if<std::is_enum<Enum>::value>::type>
	/** Range covering the whole enum.
		Can be used to simplify for-each notation. */
	struct Range
	{
		/** Alias for `eie::begin<Enum>()`. */
		constexpr Iterator<Enum> begin();
		/** Alias for `eie::end<Enum>()`. */
		constexpr Iterator<Enum> end();
	};
}

#include "eie.inl"

#endif