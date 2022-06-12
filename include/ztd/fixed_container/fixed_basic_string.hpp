// =============================================================================
// ztd::fixed_container
//
// Written 2019 - 2022 by ThePhD <phdofthehouse@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
// ============================================================================ //

#pragma once

#ifndef ZTD_FIXED_CONTAINER_FIXED_BASIC_STRING_HPP
#define ZTD_FIXED_CONTAINER_FIXED_BASIC_STRING_HPP

#include <ztd/fixed_container/version.hpp>

#include <ztd/fixed_container/fixed_vector.hpp>

#include <ztd/idk/empty_string.hpp>
#include <ztd/idk/assert.hpp>

namespace ztd {
	ZTD_FIXED_CONTAINER_INLINE_ABI_NAMESPACE_OPEN_I_

	template <typename _Ty, ::std::size_t _MaxLength>
	class fixed_basic_string : private ::ztd::fixed_vector<_Ty, _MaxLength + 1> {
	private:
		using __base              = ::ztd::fixed_vector<_Ty, _MaxLength + 1>;
		using __base_base_storage = typename __base::__base_storage;
		using __alloc             = typename __base::__alloc;
		using __alloc_traits      = typename __base::__alloc_traits;

		constexpr void _M_set_null_terminator() noexcept {
			if constexpr (::std::is_trivial_v<_Ty>) {
				auto* __sentinel_ptr = this->_M_data(this->_M_layout._M_size);
				*__sentinel_ptr      = _Ty {};
			}
			else {
				__alloc __al {};
				__alloc_traits::construct(__al, this->_M_data(this->_M_layout._M_size));
			}
		}

	public:
		using value_type                                            = typename __base::value_type;
		using reference                                             = typename __base::reference;
		using const_reference                                       = typename __base::const_reference;
		using pointer                                               = typename __base::pointer;
		using const_pointer                                         = typename __base::const_pointer;
		using iterator                                              = typename __base::iterator;
		using const_iterator                                        = typename __base::const_iterator;
		using reverse_iterator                                      = typename __base::reverse_iterator;
		using const_reverse_iterator                                = typename __base::const_reverse_iterator;
		using size_type                                             = typename __base::size_type;
		using difference_type                                       = typename __base::difference_type;
		inline static constexpr const ::std::size_t inline_capacity = _MaxLength;

		constexpr fixed_basic_string() noexcept : __base() {
			this->_M_set_null_terminator();
		}

		constexpr fixed_basic_string(::std::initializer_list<value_type> __values) noexcept : __base(__values) {
			this->_M_set_null_terminator();
		}

		constexpr fixed_basic_string(size_type __count) noexcept : __base(__count) {
			this->insert(this->cend(), __count);
		}

		constexpr fixed_basic_string(size_type __count, const value_type& __value) noexcept
		: __base(__count, __value) {
			this->_M_set_null_terminator();
		}

		template <typename _First, typename _Last,
		     ::std::enable_if_t<!::std::is_integral_v<_First>                    // cf-hack
		          && !::std::is_same_v<::ztd::remove_cvref_t<_Last>, value_type> // cf-hack
		          >* = nullptr>
		constexpr fixed_basic_string(_First __first, _Last __last) noexcept
		: __base(::std::move(__first), ::std::move(__last)) {
			this->_M_set_null_terminator();
		}

		template <typename... _Args>
		reference emplace_back(_Args&&... __args) noexcept {
			reference __val = this->__base::emplace_back(::std::forward<_Args>(__args)...);
			this->_M_set_null_terminator();
			return __val;
		}

		reference push_back(const value_type& __value) noexcept {
			reference __val = this->__base::push_back(__value);
			this->_M_set_null_terminator();
			return __val;
		}

		reference push_back(value_type&& __value) noexcept {
			reference __val = this->__base::push_back(::std::move(__value));
			this->_M_set_null_terminator();
			return __val;
		}

		template <typename... _Args>
		reference emplace_front(_Args&&... __args) noexcept {
			reference __val = this->__base::emplace_front(::std::forward<_Args>(__args)...);
			this->_M_set_null_terminator();
			return __val;
		}

		reference push_front(const value_type& __value) noexcept {
			reference __val = this->__base::push_front(__value);
			this->_M_set_null_terminator();
			return __val;
		}

		reference push_front(value_type&& __value) noexcept {
			reference __val = this->__base::push_front(::std::move(__value));
			this->_M_set_null_terminator();
			return __val;
		}

		template <typename... _Args>
		iterator emplace(const_iterator __where, _Args&&... __args) noexcept {
			iterator __itval = this->__base::emplace(::std::move(__where), ::std::forward<_Args>(__args)...);
			this->_M_set_null_terminator();
			return __itval;
		}

		constexpr iterator insert(const_iterator __where, value_type&& __value) noexcept {
			iterator __itval = this->__base::insert(::std::move(__where), ::std::move(__value));
			this->_M_set_null_terminator();
			return __itval;
		}

		constexpr iterator insert(const_iterator __where, const value_type& __value) noexcept {
			iterator __itval = this->__base::insert(::std::move(__where), __value);
			this->_M_set_null_terminator();
			return __itval;
		}

		constexpr iterator insert(const_iterator __where, ::std::initializer_list<value_type> __ilvalue) noexcept {
			iterator __itval = this->__base::insert(::std::move(__where), __ilvalue);
			this->_M_set_null_terminator();
			return __itval;
		}

		constexpr iterator insert(const_iterator __where, size_type __count) noexcept {
			iterator __itval = this->__base::insert(::std::move(__where), __count);
			this->_M_set_null_terminator();
			return __itval;
		}

		constexpr iterator insert(const_iterator __where, size_type __count, const value_type& __value) noexcept {
			iterator __itval = this->__base::insert(::std::move(__where), __count, __value);
			this->_M_set_null_terminator();
			return __itval;
		}

		template <typename _First, typename _Last,
		     ::std::enable_if_t<!::std::is_integral_v<_First>                    // cf-hack
		          && !::std::is_same_v<::ztd::remove_cvref_t<_Last>, value_type> // cf-hack
		          >* = nullptr>
		constexpr iterator insert(const_iterator __where, _First __first, _Last __last) {
			iterator __itval = this->__base::insert(::std::move(__where), ::std::move(__first), ::std::move(__last));
			this->_M_set_null_terminator();
			return __itval;
		}

		constexpr iterator erase(const_iterator __where) noexcept {
			iterator __itval = this->__base::erase(::std::move(__where));
			this->_M_set_null_terminator();
			return __itval;
		}

		constexpr iterator erase(const_iterator __where_from, const_iterator __where_to) noexcept {
			iterator __itval = this->__base::erase(::std::move(__where_from), ::std::move(__where_to));
			this->_M_set_null_terminator();
			return __itval;
		}

		using __base::operator[];
		using __base::back;
		using __base::begin;
		using __base::cbegin;
		using __base::cend;
		using __base::clear;
		using __base::crbegin;
		using __base::crend;
		using __base::data;
		using __base::empty;
		using __base::end;
		using __base::front;
		using __base::rbegin;
		using __base::rend;
		using __base::size;

		constexpr const_pointer c_str() const noexcept {
			return this->data();
		}

		constexpr size_type max_size() const noexcept {
			return _MaxLength;
		}

		constexpr size_type capacity() const noexcept {
			return _MaxLength;
		}
	};

	template <typename _Ty>
	class fixed_basic_string<_Ty, 0> {
	public:
		using value_type                                            = _Ty;
		using reference                                             = ::std::add_lvalue_reference_t<_Ty>;
		using const_reference                                       = ::std::add_lvalue_reference_t<const _Ty>;
		using pointer                                               = ::std::add_pointer_t<_Ty>;
		using const_pointer                                         = ::std::add_pointer_t<const _Ty>;
		using iterator                                              = __fv_detail::__wrap_pointer<_Ty>;
		using const_iterator                                        = __fv_detail::__wrap_pointer<const _Ty>;
		using size_type                                             = ::std::size_t;
		using difference_type                                       = ::std::ptrdiff_t;
		inline static constexpr const ::std::size_t inline_capacity = 0;

		constexpr fixed_basic_string() noexcept {
		}

		constexpr fixed_basic_string(::std::initializer_list<value_type> __values) noexcept {
			ZTD_ASSERT_MESSAGE("there must be no values", __values.size() < size_type(1));
		}

		constexpr fixed_basic_string(size_type __count) noexcept {
			ZTD_ASSERT_MESSAGE("there must be no values", __count < size_type(1));
		}

		template <typename... _Args>
		reference emplace_back(_Args&&...) noexcept {
			ZTD_ASSERT_MESSAGE("there is no capacity in this fixed_basic_string", false);
			return *static_cast<pointer>(nullptr);
		}

		reference push_back(const value_type&) noexcept {
			ZTD_ASSERT_MESSAGE("there is no capacity in this fixed_basic_string", false);
			return *static_cast<pointer>(nullptr);
		}

		reference push_back(value_type&&) noexcept {
			ZTD_ASSERT_MESSAGE("there is no capacity in this fixed_basic_string", false);
			return *static_cast<pointer>(nullptr);
		}

		template <typename... _Args>
		reference emplace_front(_Args&&...) noexcept {
			ZTD_ASSERT_MESSAGE("there is no capacity in this fixed_basic_string", false);
			return *static_cast<pointer>(nullptr);
		}

		reference push_front(const value_type&) noexcept {
			ZTD_ASSERT_MESSAGE("there is no capacity in this fixed_basic_string", false);
			return *static_cast<pointer>(nullptr);
		}

		reference push_front(value_type&&) noexcept {
			ZTD_ASSERT_MESSAGE("there is no capacity in this fixed_basic_string", false);
			return *static_cast<pointer>(nullptr);
		}

		template <typename... _Args>
		iterator emplace(const_iterator, _Args&&...) noexcept {
			ZTD_ASSERT_MESSAGE("nothing can be emplaced in this fixed_basic_string", false);
			return iterator(nullptr);
		}

		constexpr iterator insert(const_iterator, value_type&&) noexcept {
			ZTD_ASSERT_MESSAGE("nothing can be inserted in this fixed_basic_string", false);
			return iterator(nullptr);
		}

		constexpr iterator insert(const_iterator, const value_type&) noexcept {
			ZTD_ASSERT_MESSAGE("nothing can be inserted in this fixed_basic_string", false);
			return iterator(nullptr);
		}

		constexpr iterator insert(const_iterator, ::std::initializer_list<value_type>) noexcept {
			ZTD_ASSERT_MESSAGE("nothing can be inserted in this fixed_basic_string", false);
			return iterator(nullptr);
		}

		constexpr iterator insert(const_iterator, size_type) noexcept {
			ZTD_ASSERT_MESSAGE("nothing can be inserted in this fixed_basic_string", false);
			return iterator(nullptr);
		}

		constexpr iterator insert(const_iterator, size_type, const value_type&) noexcept {
			ZTD_ASSERT_MESSAGE("nothing can be inserted in this fixed_basic_string", false);
			return iterator(nullptr);
		}

		template <typename _First, typename _Last,
		     ::std::enable_if_t<!::std::is_integral_v<_First>                    // cf-hack
		          && !::std::is_same_v<::ztd::remove_cvref_t<_Last>, value_type> // cf-hack
		          >* = nullptr>
		constexpr iterator insert(const_iterator, _First, _Last) {
			ZTD_ASSERT_MESSAGE("there is no capacity in this fixed_basic_string", false);
			return iterator(nullptr);
		}

		constexpr iterator erase(const_iterator) noexcept {
			ZTD_ASSERT_MESSAGE("there is nothing to erase in this fixed_basic_string", false);
			return iterator(nullptr);
		}

		constexpr iterator erase(const_iterator, const_iterator) noexcept {
			ZTD_ASSERT_MESSAGE("there is nothing to erase in this fixed_basic_string", false);
			return iterator(nullptr);
		}

		constexpr void pop_back() noexcept {
			ZTD_ASSERT_MESSAGE("there is nothing to erase in this fixed_basic_string", false);
		}

		constexpr void pop_front() noexcept {
			ZTD_ASSERT_MESSAGE("there is nothing to erase in this fixed_basic_string", false);
		}

		constexpr const_reference front() const noexcept {
#if 0
			ZTD_ASSERT_MESSAGE("there is no capacity in this fixed_basic_string", false);
#endif
			return *::ztd::empty_string<value_type>();
		}

		constexpr const_reference back() const noexcept {
#if 0
			ZTD_ASSERT_MESSAGE("there is no capacity in this fixed_basic_string", false);
#endif
			return *::ztd::empty_string<value_type>();
		}

		constexpr bool empty() const noexcept {
			return true;
		}

		constexpr void clear() noexcept {
		}

		constexpr size_type size() const noexcept {
			return 0;
		}

		constexpr size_type capacity() const noexcept {
			return 0;
		}

		constexpr size_type max_size() const noexcept {
			return 0;
		}

		constexpr const_pointer data() const noexcept {
			return ::ztd::empty_string<value_type>();
		}

		constexpr const_pointer c_str() const noexcept {
			return ::ztd::empty_string<value_type>();
		}

		constexpr const_iterator begin() const noexcept {
			return const_iterator(::ztd::empty_string<value_type>() + 0);
		}

		constexpr const_iterator cbegin() const noexcept {
			return const_iterator(::ztd::empty_string<value_type>() + 0);
		}

		constexpr const_iterator end() const noexcept {
			return const_iterator(::ztd::empty_string<value_type>() + 0);
		}

		constexpr const_iterator cend() const noexcept {
			return const_iterator(::ztd::empty_string<value_type>() + 0);
		}

		constexpr reference operator[](size_type) {
			ZTD_ASSERT_MESSAGE("there is no capacity in this fixed_basic_string", false);
			return *static_cast<pointer>(nullptr);
		}

		constexpr const_reference operator[](size_type) const {
			ZTD_ASSERT_MESSAGE("there is no capacity in this fixed_basic_string", false);
			return *static_cast<const_pointer>(nullptr);
		}

		constexpr void resize(size_type __count) noexcept {
			ZTD_ASSERT_MESSAGE("there is no capacity in this fixed_basic_string to resize to anything but 0",
			     __count < size_type(1));
		}

		constexpr void resize(size_type __count, const value_type&) noexcept {
			ZTD_ASSERT_MESSAGE("there is no capacity in this fixed_basic_string to resize to anything but 0",
			     __count < size_type(1));
		}
	};

	ZTD_FIXED_CONTAINER_INLINE_ABI_NAMESPACE_CLOSE_I_

} // namespace ztd

#endif // ZTD_FIXED_CONTAINER_FIXED_BASIC_STRING_HPP
