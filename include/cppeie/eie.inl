/** @file eie.inl
	Enum Interface Extension definitions.
	
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
namespace eie
{
	template<class Enum, class>
	constexpr std::size_t count()
	{
		return std::size_t(Enum::__eie_last_constant) + 1;
	}

	template<class Enum, class>
	constexpr bool valid(
		Enum value)
	{
		return std::size_t(value) < count<Enum>();
	}

	template<class Enum, class>
	constexpr Enum first()
	{
		return Enum(0);
	}

	template<class Enum, class>
	constexpr Enum last()
	{
		return Enum::__eie_last_constant;
	}

	template<class Enum, class S>
	constexpr Iterator<Enum, S>::Iterator(
		Enum value):
		m_value(value)
	{
	}

	template<class Enum, class S>
	EIECXDA Enum Iterator<Enum, S>::operator*() const
	{
#ifndef _NDEBUG
		assert(valid(m_value));
#endif
		return m_value;
	}

	template<class Enum, class S>
	Iterator<Enum> &Iterator<Enum, S>::operator++()
	{
		m_value = Enum(std::size_t(m_value)+1);
		return *this;
	}

	template<class Enum, class S>
	Iterator<Enum> Iterator<Enum, S>::operator++(int)
	{
		Enum result = m_value;
		m_value = Enum(std::size_t(m_value)+1);
		return result;
	}

	template<class Enum, class S>
	Iterator<Enum> &Iterator<Enum, S>::operator--()
	{
		m_value = Enum(std::size_t(m_value)-1);
		return *this;
	}

	template<class Enum, class S>
	Iterator<Enum> Iterator<Enum, S>::operator--(int)
	{
		Enum result = m_value;
		m_value = Enum(std::size_t(m_value)-1);
		return result;
	}

	template<class Enum, class S>
	constexpr bool Iterator<Enum, S>::operator==(
		Iterator<Enum> other) const
	{
		return m_value == other.m_value;
	}

	template<class Enum, class S>
	constexpr bool Iterator<Enum, S>::operator!=(
		Iterator<Enum> other) const
	{
		return m_value != other.m_value;
	}

	template<class Enum, class>
	constexpr Iterator<Enum> begin()
	{
		return first<Enum>();
	}

	template<class Enum, class>
	constexpr Iterator<Enum> end()
	{
		return Enum(count<Enum>() + 1);
	}

	template<class Enum, class S>
	constexpr Iterator<Enum> Range<Enum, S>::begin()
	{
		return eie::begin<Enum>();
	}

	template<class Enum, class S>
	constexpr Iterator<Enum> Range<Enum, S>::end()
	{
		return eie::end<Enum>();
	}
}