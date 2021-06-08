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

#include "ACPI.h"

namespace ACPI{

    void* FindTable(SDTHeader* sdtHeader, char* signature){

        int entries = (sdtHeader->Length - sizeof(ACPI::SDTHeader)) / 8;

        for (int t = 0; t < entries; t++){
            ACPI::SDTHeader* newSDTHeader = (ACPI::SDTHeader*)*(uint64_t*)((uint64_t)sdtHeader + sizeof(ACPI::SDTHeader) + (t * 8));
            for (int i = 0; i < 4; i++){
                if (newSDTHeader->Signature[i] != signature[i])
                {
                    break;
                }
                if (i == 3) return newSDTHeader;
            }
        }
        return 0;
    }

}