//   GreenControl framework
//
// LICENSETEXT
//
//   Copyright (C) 2007 : GreenSocs Ltd
// 	 http://www.greensocs.com/ , email: info@greensocs.com
//
//   Developed by :
//   
//   Christian Schroeder <schroeder@eis.cs.tu-bs.de>,
//   Wolfgang Klingauf <klingauf@eis.cs.tu-bs.de>
//     Technical University of Braunschweig, Dept. E.I.S.
//     http://www.eis.cs.tu-bs.de
//
//
//   This program is free software.
// 
//   If you have no applicable agreement with GreenSocs Ltd, this software
//   is licensed to you, and you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
// 
//   If you have a applicable agreement with GreenSocs Ltd, the terms of that
//   agreement prevail.
// 
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
// 
//   You should have received a copy of the GNU General Public License
//   along with this program; if not, write to the Free Software
//   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
//   02110-1301  USA 
// 
// ENDLICENSETEXT

// doxygen comments

#ifndef __GC_PORT_IF_H__
#define __GC_PORT_IF_H__


#include "gc_globals.h"        // global settings
#include "gc_transaction.h"


namespace gs {
namespace ctr {

  
/// Interface to be implemented by APIs which use the gc_port.
/**
 * This interface is to be implemented by each API which uses the gc_port directly
 * (and then acts as channel).
 * That API can be either the GCnf_Api or an User API adaptor (e.g. Tool_Api)
 */
class gc_port_if
: public sc_interface
{
public:

  /// Called by master connector in the gc_port.
  /**
   * Called by payload event queue instead of being notified by the default_event (faster).
   */
  virtual void masterAccess(ControlTransactionContainer& t_p) = 0;

  /// Called by slave connector in the gc_port.
  /**
   * Called by payload event queue instead of being notified by the default_event (faster).
   */
  virtual void slaveAccess(ControlTransactionContainer& t_p) = 0;
};


} // end namespace ctr
} // end namespace gs

#endif