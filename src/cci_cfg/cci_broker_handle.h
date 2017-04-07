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

#ifndef CCI_CCI_BROKER_HANDLE_H_INCLUDED_
#define CCI_CCI_BROKER_HANDLE_H_INCLUDED_

#include <string>
#include "cci_cfg/cci_config_macros.h"
#include "cci_cfg/cci_broker_if.h"

/**
 * @author Guillaume Delbergue, Ericsson / GreenSocs
 */

CCI_OPEN_NAMESPACE_

// Forward declarations
class cci_param_untyped_handle;

// CCI Broker handle class
/**
* Broker handle class informing broker of originator when required.
* Provides a broker-like interface.
*/
class cci_broker_handle
{
public:
    /// Constructor to create handle with given originator.
    cci_broker_handle(cci_broker_if& broker,
                      const cci_originator& originator);

    /// Copy constructor
    cci_broker_handle(const cci_broker_handle& broker_handle);

    /// Destructor.
    virtual ~cci_broker_handle();

    /// @copydoc cci_broker_if::create_broker_handle
    cci_broker_handle create_broker_handle(
            const cci_originator &originator = cci_originator());

    /// Gets the originator of the broker.
    /**
     * The originator identifies the entity accessing the broker through
     * this handle.
     */
    cci_originator get_originator() const;

    /// @copydoc cci_broker_if::name
    const std::string& name() const;

    /// @copydoc cci_broker_if::set_initial_cci_value
    void set_initial_cci_value(const std::string &parname,
                               const cci::cci_value &cci_value);

    /// @copydoc cci_broker_if::get_initial_cci_value
    const cci::cci_value get_initial_cci_value(const std::string &parname);

    /// @copydoc cci_broker_if::get_unconsumed_initial_values()
    std::vector<cci_name_value_pair> get_unconsumed_initial_values();

    /// @copydoc cci_broker_if::get_unconsumed_initial_values(const cci_initial_value_predicate&)
    cci_initial_value_range get_unconsumed_initial_values(
            const cci_initial_value_predicate &pred);

    /// @copydoc cci_broker_if::ignore_unconsumed_initial_values
    void ignore_unconsumed_initial_values(
            const cci_initial_value_predicate &pred);

    /// @copydoc cci_broker_if::get_latest_write_originator
    cci_originator
    get_latest_write_originator(const std::string &parname) const;

    /// @copydoc cci_broker_if::lock_initial_value
    void lock_initial_value(const std::string &parname);

    /// @copydoc cci_broker_if::get_cci_value
    const cci::cci_value get_cci_value(const std::string &parname);

    /// @copydoc cci_broker_if::get_cci_value_keep_unused
    const cci::cci_value
    get_cci_value_keep_unused(const std::string &parname) const;

    /// @copydoc cci_broker_if::get_param_handle
    cci_param_untyped_handle get_param_handle(const std::string &parname);

    /// @copydoc cci_broker_if::param_exists
    bool param_exists(const std::string &parname);

    /// @copydoc cci_broker_if::is_used
    bool is_used(const std::string &parname);

    /// @copydoc cci_broker_if::add_param
    void add_param(cci_param_if *par);

    /// @copydoc cci_broker_if::remove_param
    void remove_param(cci_param_if *par);

    /// @copydoc cci_broker_if::get_param_handles(const std::string&)
    const std::vector <cci_param_untyped_handle>
    get_param_handles(const std::string &pattern = "");

    /// @copydoc cci_broker_if::get_param_handles(cci_param_predicate&)
    cci_param_range
    get_param_handles(cci_param_predicate& pred);

    /// @copydoc cci_broker_if::is_private_broker
    bool is_private_broker() const;

    /// @copydoc cci_broker_callback_if::register_create_callback
    cci_param_create_callback_handle
    register_create_callback(const cci_param_create_callback& cb);

    /// @copydoc cci_broker_callback_if::unregister_create_callback
    bool unregister_create_callback(const cci_param_create_callback_handle& cb);

    /// @copydoc cci_broker_callback_if::register_destroy_callback
    cci_param_destroy_callback_handle
    register_destroy_callback(const cci_param_destroy_callback& cb);

    /// @copydoc cci_broker_callback_if::unregister_destroy_callback
    bool
    unregister_destroy_callback(const cci_param_destroy_callback_handle& cb);

    /// @copydoc cci_broker_callback_if::unregister_all_callbacks
    bool unregister_all_callbacks();

    /// @copydoc cci_broker_callback_if::has_callbacks
    bool has_callbacks() const;

    /// Convenience function to get a typed parameter handle.
    /**
     * @param   parname   Full hierarchical parameter name.
     * @return  Parameter handle (invalid if not existing or the type is not correct)
     */
    template<class T>
    cci_param_typed_handle<T> get_cci_param_handle(const std::string &parname) {
        return cci_param_typed_handle<T>(get_param_handle(parname));
    }

    /// Assigns broker handle a new value from another legacy broker handle
    /**
     * @param broker_handle New broker handle to assign
     * @return reference to this object
     */
    cci_broker_handle& operator=(const cci_broker_handle& broker_handle);

private:
    /// Originator of the broker handle.
    cci_originator m_originator;

    /// Original broker
    cci_broker_if& m_orig_broker;
};

CCI_CLOSE_NAMESPACE_

#endif // CCI_CCI_BROKER_HANDLE_H_INCLUDED_