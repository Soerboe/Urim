/*
 * Copyright (C) Dag Henning Liodden Sørbø <daghenning@lioddensorbo.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef UTILS_H
#define UTILS_H

#include <functional>

template<typename T>
void ignore_unused(const T&) { }
template<typename T, typename U>
void ignore_unused(const T&, const U&) { }
template<typename T, typename U, typename V>
void ignore_unused(const T&, const U&, const V&) { }

template <typename T>
inline void hash_combine_std(std::size_t& seed, const T& v)
{
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

template <typename T>
inline void hash_combine_custom(std::size_t& seed, const T& v)
{
    seed ^= v.hash() + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

#endif // UTILS_H
