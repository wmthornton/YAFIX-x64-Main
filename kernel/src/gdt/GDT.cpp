/**
 * Copyright (c) 2021 Wayne Michael Thornton <wmthornton>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "GDT.h"

// Not strictly necessary as the __attribute__ is included in our header file, but better
// safe than sorry. 
__attribute__((aligned(0x1000)))

// Defining the Global Descriptor Table structure...
GDT DefaultGDT = {
    {0, 0, 0, 0x00, 0x00, 0}, // NULL segment
    {0, 0, 0, 0x9a, 0xa0, 0}, // KernelCode segment
    {0, 0, 0, 0x92, 0xa0, 0}, // KernelData segment
    {0, 0, 0, 0x00, 0x00, 0}, // User NULL segment
    {0, 0, 0, 0x9a, 0xa0, 0}, // UserCode segment
    {0, 0, 0, 0x92, 0xa0, 0}, // UserData segment
};