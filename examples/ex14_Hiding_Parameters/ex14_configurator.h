/*****************************************************************************

  Licensed to Accellera Systems Initiative Inc. (Accellera) under one or
  more contributor license agreements.  See the NOTICE file distributed
  with this work for additional information regarding copyright ownership.
  Accellera licenses this file to you under the Apache License, Version 2.0
  (the "License"); you may not use this file except in compliance with the
  License.  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
  implied.  See the License for the specific language governing
  permissions and limitations under the License.

 ****************************************************************************/

/**
 *  @file     configurator.h
 *  @brief    This header declares and defines the 'configurator' module functionality
 *  @author   P V S Phaneendra, CircuitSutra Technologies   <pvs@circuitsutra.com>
 *  @date     5th July, 2011 (Tuesday)
 */

#ifndef EXAMPLES_EX14_HIDING_PARAMETERS_EX14_CONFIGURATOR_H_
#define EXAMPLES_EX14_HIDING_PARAMETERS_EX14_CONFIGURATOR_H_

#include <cci_configuration>
#include <cassert>
#include <vector>
#include <string>

#include "xreport.hpp"

/**
 *  @class  ex14_configurator
 *  @brief  This module defines the configurator module which will make changes
 *          to the 'priv_int_param' of the child by making changes to the
 *          'parent_inst. parent_buffer' cci_parameter
 */
SC_MODULE(ex14_configurator) {
 public:
  /**
   *  @fn     ex14_configurator
   *  @brief  The class constructor
   *  @return void
   */
  SC_CTOR(ex14_configurator):
      myCfgrBrokerIF(cci::cci_broker_manager::get_broker()),
      parent_base_param(cci::cci_originator(*this))
  {
    std::string parameterName(
            "Top.private.parent_inst.parent_int_buffer");
    if (myCfgrBrokerIF.param_exists(parameterName)) {
      // Get handle of the parent_module's cci-parameter
      parent_base_param = myCfgrBrokerIF.get_param_handle(parameterName);

      // Assert if the handle returned is NULL
      assert(parent_base_param.is_valid()
             && "Returned handle of parent_module's cci-parameter is not valid");

      XREPORT("[CFGR] : Parameter Name : "
              << parent_base_param.get_name() << "\tParameter Value : "
              << parent_base_param.get_cci_value().to_json());
    } else {
      XREPORT("[CFGR] : Parameter by name"
              " " << parameterName << " doesn't exist");
    }

    // Declare SC_THREAD
    SC_THREAD(run_cfgr);
  }

  /**
   *  @fn     void run_cfgr(void)
   *  @brief  Main function executed to configure the parameters
   *  @return void
   */
  void run_cfgr(void) {
    while (1) {
      std::vector<std::string> cfgr_param_list =
          myCfgrBrokerIF.get_param_list();

      wait(15.0, sc_core::SC_NS);

      XREPORT("@ " << sc_core::sc_time_stamp()
              << "\tVisible parameters to the 'configurator' module");

      for (unsigned int i = 0; i < cfgr_param_list.size(); i++) {
        XREPORT("[CFGR] : Parameter Name : " << cfgr_param_list[i]);
      }

      wait(5.0, sc_core::SC_NS);

      XREPORT("@ " << sc_core::sc_time_stamp());

      XREPORT("[CFGR] : Change the value of the 'parent_int_buffer' to '1000'");

      parent_base_param.set_cci_value(cci::cci_value::from_json("1000"));

      XREPORT("[CFGR] : Parameter Name : "
              << parent_base_param.get_name() << "\tParameter Value : "
              << parent_base_param.get_cci_value().to_json());

      wait(5.0, sc_core::SC_NS);
    }
  }

 private:
  cci::cci_broker_handle myCfgrBrokerIF;  ///< Configuration Broker for TOP_MODULE
  cci::cci_param_handle parent_base_param;  ///< Few directly accessible cci-parameters
};
/// ex14_configurator

#endif  // EXAMPLES_EX14_HIDING_PARAMETERS_EX14_CONFIGURATOR_H_
