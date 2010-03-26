// LICENSETEXT
//
//   Copyright (C) 2009-2010 : GreenSocs Ltd
// 	 http://www.greensocs.com/ , email: info@greensocs.com
//
//   Developed by:
//    Christian Schroeder <schroeder@eis.cs.tu-bs.de>,
//    Mark Burton, mark@greensocs.com
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


#ifndef __GS_CCI_CNF_BROKER_H__
#define __GS_CCI_CNF_BROKER_H__


#include <cci.h>
#include "cci_params.h"
#include "greencontrol/config.h"
#include "gs_cci_cnf_broker_if.h"

namespace cci {
  namespace cnf {

  class cci_base_param;

  class gs_cci_cnf_broker
  : public cci::cnf::cci_cnf_broker
  , public gs_cci_cnf_broker_if
  {
  public:
    
    gs_cci_cnf_broker();
    
    ~gs_cci_cnf_broker();

    void set_init_value(const std::string &parname, const std::string &value);
    
    const std::string get_json_string(const std::string &parname);

    cci_base_param* get_param(const std::string &parname);
    
    bool exists_param(const std::string &parname);
    
    bool is_used(const std::string &parname);
    
    const std::vector<std::string> get_param_list();
    
    shared_ptr< cci::cnf::callb_adapt_b> register_callback(const std::string& parname, const cci::cnf::callback_type type, shared_ptr< cci::cnf::callb_adapt_b> callb);

    void unregister_all_callbacks(void* observer);
    
    bool unregister_param_callback(cci::cnf::callb_adapt_b* callb);
    
    bool has_callbacks(const std::string& parname);
    
    void add_param(cci::cnf::cci_base_param_if* par);
    
    void remove_param(cci::cnf::cci_base_param_if* par);
    
    //void set_alias(std::string& orig_parname, std::string& alias_parname);
        
    const std::vector<std::string> get_param_list(const std::string& pattern);
    
    const std::vector<cci::cnf::cci_base_param*> get_params(const std::string& pattern = "");

    gs::cnf::cnf_api* get_gcnf_api();
  
  protected:
  
    gs::cnf::cnf_api* m_gcnf_api;
    
    std::map<std::string, cci::cnf::cci_base_param_if*> m_mirrored_registry;

  };


  } // end namespace cci
} // end namespace cci

#endif