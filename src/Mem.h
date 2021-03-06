/* XMRig
 * Copyright 2014      imonero <https://github.com/global-blockchain>
 * Copyright 2016-2017 XMRig       <admin@imonero.org>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __MEM_H__
#define __MEM_H__


#include <stddef.h>
#include <stdint.h>


#include "common/xmrig.h"


struct cryptonight_ctx;


struct MemInfo
{
    alignas(16) uint8_t *memory;

    size_t hugePages;
    size_t pages;
    size_t size;
};


class Mem
{
public:
    enum Flags {
        HugepagesAvailable = 1,
        HugepagesEnabled   = 2,
        Lock               = 4
    };

    static MemInfo create(cryptonight_ctx **ctx, xmrig::Algo algorithm, size_t count);
    static void init(bool enabled);
    static void release(cryptonight_ctx **ctx, size_t count, MemInfo &info);

    static inline bool isHugepagesAvailable() { return (m_flags & HugepagesAvailable) != 0; }

private:
    static void allocate(MemInfo &info, bool enabled);
    static void release(MemInfo &info);

    static int m_flags;
    static bool m_enabled;
};


#endif /* __MEM_H__ */
