/*
* (C) Copyright 2015 Kurento (http://kurento.org/)
*
* All rights reserved. This program and the accompanying materials
* are made available under the terms of the GNU Lesser General Public License
* (LGPL) version 2.1 which accompanies this distribution, and is available at
* http://www.gnu.org/licenses/lgpl-2.1.html
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* Lesser General Public License for more details.
*
*/

#ifndef __REGISTER_PARENT_HPP__
#define __REGISTER_PARENT_HPP__

#include <map>
#include <functional>
#include <atomic>

namespace kurento
{

class RegisterParent
{
public:
  RegisterParent () {}
  virtual ~RegisterParent () {}

  static void registerType (std::string type,
                            std::function<RegisterParent* (void) > func);

  static RegisterParent *createRegister (std::string type);

private:
  static std::map <std::string, std::function<RegisterParent* (void) >>
      complexTypesRegistered;

};

} /* kurento */

#endif /*  __REGISTER_PARENT_HPP__ */
