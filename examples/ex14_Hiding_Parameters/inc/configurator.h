/*******************************************************************************
 * The following code is derived, directly or indirectly, from the SystemC
 * source code Copyright (c) 1996-2010 by all Contributors.
 * All Rights reserved.
 * 
 * The contents of this file are subject to the restrictions and limitations
 * set forth in the SystemC Open Source License Version 2.2.0 (the "License");
 * One may not use this file except in compliance with such restrictions and
 * limitations.  One may obtain instructions on how to receive a copy of the
 * License at http://www.systemc.org/.  Software distributed by Contributors
 * under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
 * ANY KIND, either express or implied. See the License for the specific
 * language governing rights and limitations under the License.
 * *******************************************************************************/

/**
 * @file     configurator.h
 * @brief    This header declares and defines the 'configurator' module functionality
 * @author   P V S Phaneendra, CircuitSutra Technologies Pvt. Ltd.
 * @date     5th July, 2011 (Tuesday)
 */
#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

/// Include the "cci.h" header file in all cci-based applications
#include <cci.h>
#include <assert.h>
#include <vector>

/**
 * @brief    The 'configurator' module functionality is defined within this module.
 *           To make changes to the 'priv_int_param' of the 'child' module, the
 *           'configurator' will be making changes to the root module which in turn
 *           will be reflecting the desired changes on the 'parent_inst.parent_buffer'
 *           cci-parameter.  
 * @author   P V S Phaneendra, CircuitSutra Technologies Pvt. Ltd.
 * @date     5th July, 2011 (Tuesday)
 */ 
class configurator : public sc_module
{
	public:
		
		/// Default constructor
		SC_CTOR(configurator)
		{
			/// Gets the reference of a DEFAULT GLOBAL BROKER
			myCfgrBrokerIF	=	&cci::cnf::cci_broker_manager::get_current_broker(cci::cnf::cci_originator(*this));

			// Asserts if the returned broker handle is NULL
			assert(myCfgrBrokerIF != NULL && "Returned broker handle for 'root_module' is NULL");

			if(myCfgrBrokerIF != NULL)
			{
				if(myCfgrBrokerIF->exists_param("root_module.root_int_param"))
				{
					/// Get handle of the root_module's cci-parameter
					root_base_param_ptr = myCfgrBrokerIF->get_param("root_module.root_int_param");

					// Assert if the handle returned is NULL
					assert(root_base_param_ptr != NULL && "Returned handle of root_module's cci-parameter is NULL");
					
					std::cout << "\n\t[CFGR] : Parameter Name : " << root_base_param_ptr->get_name()
						<< "\tParameter Value : " << root_base_param_ptr->json_serialize() << std::endl;
				}
				else
					std::cout << "\n\t[CFGR] : No parameter by name 'root_module.root_int_param' exists" << std::endl;

			}// End of IF

			/// Declare SC_THREAD
			SC_THREAD(run_cfgr);

		}// End of Constructor

		
		/// Implementation of SC_THREAD
		void run_cfgr (void)
		{
			while(1)
			{
				std::vector<std::string> cfgr_param_list = myCfgrBrokerIF->get_param_list();

				wait(15.0, SC_NS);

				std::cout << "\n@ " << sc_time_stamp() << "\tVisible parameters to the 'configurator' module" << std::endl;

				for(unsigned int i = 0; i < cfgr_param_list.size(); i++)
				{
					std::cout << "\t[CFGR] : Parameter Name : " << cfgr_param_list[i] << std::endl;
				}

				wait(5.0, SC_NS);

				std::cout << "\n@ " << sc_time_stamp() << std::endl;

				std::cout << "\t[CFGR] : Change the value of the private cci-parameters through 'root_module'" << std::endl;
				std::cout << "\t[CFGR] : Change the value of the 'root_int_param' to '1000'" << std::endl;

				root_base_param_ptr->json_deserialize("1000");

				std::cout << "\n\t[CFGR] : Parameter Name : " << root_base_param_ptr->get_name()
					<< "\tParameter Value : " << root_base_param_ptr->json_serialize() << std::endl;

				wait(5.0, SC_NS);

			}// End of WHILE
		}// End of SC_THREAD

	private	:

		/// Configuration Broker for TOP_MODULE
		cci::cnf::cci_cnf_broker_if* myCfgrBrokerIF;
	
		/// Few directly accessible cci-parameters
		cci::cnf::cci_base_param*	   root_base_param_ptr;

};// End of Class

#endif	// End of CONFIGURATOR_H

