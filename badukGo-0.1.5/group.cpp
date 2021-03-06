/**********************************************************************************************
* Copyright (C) 2016 <BadukGo Project>                                                        *
* All rights reserved                                                                         *
*                                                                                             *
* Permission is hereby granted, free of charge, to any person obtaining a copy of             *
* this software and associated documentation files (the “Software”), to deal in the Software  *
* without restriction, including without limitation the rights to use, copy, modify, merge,   *
* publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons  *
* to whom the Software is furnished to do so, subject to the following conditions:            *
*                                                                                             *
* The above copyright notice and this permission notice shall be included in all copies or    *
* substantial portions of the Software.                                                       *
*                                                                                             *
* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,         *
* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR    *
* PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE   *
* FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR        *
* OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER      *
* DEALINGS IN THE SOFTWARE.                                                                   *
**********************************************************************************************/
#include "group.h"
#include <cstring>
#include <assert.h>

Group::Group()
{
  color = 0;
  stones[0] = 0;
  liberties[0] = 0;
  num_stones = 0;
  num_libs = 0;
  memset(libs_ptr,0,sizeof(libs_ptr));
}

void Group::set_up(int point, bool new_color, const LList &new_liberties)
{
  color = new_color;
  num_stones = 0;
  stones[num_stones++] = point;
  stones[num_stones] = 0;
  num_libs = 0;
  memset(libs_ptr,0,sizeof(libs_ptr));

  for (int i = 0; i < new_liberties.length(); i++) {
    liberties[num_libs++] = new_liberties[i];
    libs_ptr[new_liberties[i]] = num_libs;
    liberties[num_libs] = 0;
  }
}

int Group::add_liberties(int i)
{
  if (libs_ptr[i] != 0) return 0; 


  libs_ptr[i] = num_libs+1;
  liberties[num_libs++] = i;
  liberties[num_libs] = 0;
  return num_libs;
}

int Group::erase_liberties(int lib)
{
  if (libs_ptr[lib] == 0 ) return 0;
  else{
    int pos = libs_ptr[lib]-1;
     if (pos<num_libs-1){
      liberties[pos] = liberties[--num_libs];
      libs_ptr[lib] = 0;
      libs_ptr[liberties[num_libs]] = pos+1;
      liberties[num_libs] = 0;
    }else{
      libs_ptr[lib] = 0;
      liberties[pos] = 0;
      --num_libs;
    }
    return num_libs;
  }

}

void Group::clear()
{
  num_stones = 0;
  stones[num_stones] = 0;
  num_libs = 0;
  liberties[num_libs] = 0;
  memset(libs_ptr,0,sizeof(libs_ptr));
}

void Group::attach_group(Group *attached)
{  
  for (int i = 0; i < attached->num_stones; i++) {
    this->stones[num_stones++] = attached->stones[i];
    this->stones[num_stones] = 0;
  }
  for (int i = 0; i < attached->num_libs; i++) {
    this->add_liberties(attached->liberties[i]);
  }
}
void Group::print_group() const
{
  std::cerr << "Color: " << color;
  for (int i = 0; i < num_stones; i++) std::cerr << " " << stones[i];
  std::cerr << "\n";
}
