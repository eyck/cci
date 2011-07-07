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
 * @file     parent.h
 * @brief    This header declares and defines the 'parent' which instantiates
 *           'child' and hides its parameters
 * @author   P V S Phaneendra, CircuitSutra Technologies Pvt. Ltd.
 * @date     5th June, 2011 (Tuesday)
 */
#ifndef PARENT_H
#define PARENT_H

/// Include the "cci.h" header file in all cci-based applications
#include <cci.h>
#include <assert.h>
#include <vector>

#include "child.h"

#include "gs_cci_cnf_private_broker_accessor.h"

/**
 * @brief    The 'parent' module derives from the 'cci_broker_manager'
 *           class and manages it own private broker stack
 * @author   P V S Phaneendra, CircuitSutra Technologies Pvt. Ltd.
 * @date     5th June, 2011 (Tuesday)
 */ 
class parent : public sc_module, public cci::cnf::cci_broker_manager
{
	public:
		
		/// Default constructor
		SC_CTOR(parent)
		: cci::cnf::cci_broker_manager(new cci::cnf::gs_cci_private_broker_accessor(*this, boost::assign::list_of("param"), cci::cnf::cci_originator(*this)))
		,	child_inst("child_inst")
		,	parent_int_param("parent_int_param", 300, get_broker())
		{
			/// Gets the reference of a private broker for the module
			parent_BrokerIF	=	&get_broker();

			// Asserts if the returned broker handle is NULL
			assert(parent_BrokerIF != NULL && "Returned broker handle for 'parent' is NULL");

			std::cout << "\n\t[PARENT C_TOR] : Parameter Name : " << parent_int_param.get_name()
				<< "\tParameter Value : " << parent_int_param.get() << std::endl;			


			if(parent_BrokerIF != NULL)
			{
				if(parent_BrokerIF->exists_param("root_module.parent_inst.child_inst.priv_int_param"))
				{
					child_base_param_ptr = parent_BrokerIF->get_param("root_module.parent_inst.child_inst.priv_int_param");

					assert(child_base_param_ptr != NULL && "Returned broker handle for 'priv_int_param' of 'child' is NULL");
				}
				else
					std::cout << "\n\t[PARENT C_TOR] : Desired cci-parameter of 'child' module is not available" << std::endl;

			}// End of IF


			// Declaration of SC_THREAD
			SC_THREAD(run_parent);

			// Still on the TODO list:
			//
			// This hack to pop out the previous private broker is a must.  Otherwise,
			// the modules registering their cci-parameters after the instantiation of
			// this module will not be able to append their cci-parameters to the 
			// desired brokers but to the broker instance of this module only.
			cci::cnf::cci_broker_stack::stack().pop();


			/// This definition of the cci-parameter after the 'popping' from 'cci_broker_stack'
			/// registers it to the DEFAULT GLOBAL BROKER
			parent_buffer = new cci::cnf::cci_param<int>("parent_int_buffer", 123);

			/// Registering Callbacks
			parent_post_write_cb = parent_buffer->register_callback(cci::cnf::post_write,
				this, cci::bind(&parent::write_callback, this, _1, _2, child_base_param_ptr));

			std::cout << "\n\t[PARENT C_TOR] : Parameter Name : " << parent_buffer->get_name()\
				<< "\tParameter Value : " << parent_buffer->get() << std::endl;			

		}// End of Constructor

		/// Callback Implementation
		cci::cnf::callback_return_type
			write_callback(cci::cnf::cci_base_param & _base_param, const cci::cnf::callback_type & cb_reason, cci::cnf::cci_base_param * _child_base_param_ptr)
			{
				_child_base_param_ptr->json_deserialize(_base_param.json_serialize());
				
				std::cout << "\n\t[PARENT - post_write_cb] : Parameter Name : " << _base_param.get_name()\
					<< "\tParameter Value : " << _base_param.json_serialize() << std::endl;
			
				return cci::cnf::return_nothing;
			}


		/// SC_THREAD Implementation
		void run_parent (void)
		{
			while(1)
			{
				wait(5.0, SC_NS);

				std::vector<std::string> parent_param_list = parent_BrokerIF->get_param_list();

				std::cout << "\n@ " << sc_time_stamp() << "\tVisible parameters to the 'parent' module" << std::endl;

				for(unsigned int i = 0; i < parent_param_list.size(); i++)
				{
					std::cout << "\t[PARENT] : Parameter Name : " << parent_param_list[i] << std::endl;
				}

				wait(30.0, SC_NS);

			}// End of WHILE

		}// End of SC_THREAD


	private	:

		/// Owner Module instantiation
		child                      child_inst;

		/// Configuration Broker for TOP_MODULE
		cci::cnf::cci_cnf_broker_if* parent_BrokerIF;
	
		/// Declare cci-parameters (registered with the private broker)
		cci::cnf::cci_param<int>	   parent_int_param;

		/// Globally registered and visible cci-parameters
		cci::cnf::cci_param<int>*    parent_buffer;

		/// Declare cci_base_param pointers
    cci::cnf::cci_base_param*    child_base_param_ptr;

		/// Callback Adaptor Object
		cci::shared_ptr<cci::cnf::callb_adapt_b> parent_post_write_cb;

};// End of Class

#endif	// End of PARENT_H

