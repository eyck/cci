/*****************************************************************************
  Copyright 2006-2015 Accellera Systems Initiative Inc.
  All rights reserved.

  Copyright 2009-2011 GreenSocs Ltd
  All rights reserved.

  Copyright 2006-2014 OFFIS Institute for Information Technology
  All rights reserved.

  Copyright 2006-2015 Intel Corporation
  All rights reserved.

  Copyright 2016 Ericsson AB
  All rights reserved.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
 *****************************************************************************/

#ifndef CCI_CCI_PARAM_IF_H_INCLUDED_
#define CCI_CCI_PARAM_IF_H_INCLUDED_

#include "cci_cfg/cci_shared_ptr.h"
#include "cci_cfg/cci_callbacks.h"
#include "cci_cfg/cci_value.h"

/**
 * @author Enrico Galli, Intel
 */

CCI_OPEN_NAMESPACE_

class cci_param_untyped_handle;
class cci_originator;

/// Interfaces for cci_param_typed implementation
/**
* Features:
* - Name of the parameter,
* - stores value untyped as string representation
* - allows generic typed and list access
* - JSON (de)serialize functions
* - Callback handling
*/

class cci_param_if {

    friend class cci_param_untyped_handle;

public:

    /// Destructor.
    virtual ~cci_param_if() {}

    ///@name Set and Get with JSON String Representation
    ///@{

    /// @copydoc cci_param_untyped_handle::json_deserialize
    virtual void json_deserialize(const std::string &json_string) = 0;

    /// @copydoc cci_param_untyped_handle::json_serialize
    virtual std::string json_serialize() const = 0;

    ///@}

    ///@name JSON Data Type and access
    ///@{

    /// @copydoc cci_param_untyped_handle::set_cci_value
    virtual void set_cci_value(const cci_value &val) = 0;

    /// @copydoc cci_param_typed::get_cci_value
    virtual cci_value get_cci_value() const = 0;

    ///@}


    ///@name Description
    ///@{

    /// @copydoc cci_param_untyped::get_description
    virtual std::string get_description() const = 0;

    /// @copydoc cci_param_untyped::set_description
    virtual void set_description(const std::string &desc) = 0;

    ///@}


    ///@}

    ///@name Parameter Value Status
    ///@{

    /// @copydoc cci_param_untyped::is_default_value
    virtual bool is_default_value() = 0;

    /// @copydoc cci_param_untyped::is_initial_value
    virtual bool is_initial_value() const = 0;

    ///@}

    ///@name Miscellaneous
    ///@{

    /// @copydoc cci_param_untyped::get_latest_write_originator
    virtual const cci_originator *get_latest_write_originator() const = 0;

    ///@}

    ///@name Callback Handling
    ///@{

    /// @copydoc cci_param_untyped::register_callback(const callback_type, void*, param_callb_func_ptr)
    virtual shared_ptr <callb_adapt> register_callback(const callback_type type,
                                                       void *observer,
                                                       param_callb_func_ptr function) = 0;

    /// @copydoc cci_param_untyped::register_callback(const callback_type, cci::shared_ptr<callb_adapt>)
    virtual shared_ptr <callb_adapt> register_callback(const callback_type type,
                                                       shared_ptr <callb_adapt> callb) = 0;

    /// @copydoc cci_param_untyped::unregister_all_callbacks
    virtual void unregister_all_callbacks(void *observer) = 0;

    /// @copydoc cci_param_untyped::unregister_callback(cci::shared_ptr<callb_adapt>)
    virtual bool unregister_callback(shared_ptr <callb_adapt> callb) = 0;

    /// @copydoc cci_param_untyped::unregister_callback(callb_adapt*)
    virtual bool unregister_callback(callb_adapt *callb) = 0;

    /// @copydoc cci_param_untyped::has_callbacks
    virtual bool has_callbacks() = 0;

    ///@}

    ///@name Write-access control
    ///@{

    /// @copydoc cci_param_untyped::lock
    virtual bool lock(void *pwd = NULL) = 0;

    /// @copydoc cci_param_untyped::unlock
    virtual bool unlock(void *pwd = NULL) = 0;

    /// @copydoc cci_param_untyped::is_locked
    virtual bool is_locked() const = 0;

    ///@}

    ///@name Query parameter type and name
    ///@{

    /// @copydoc cci_param_typed::get_basic_type
    virtual basic_param_type get_basic_type() const = 0;

    /// @copydoc cci_param_untyped::get_name
    virtual const std::string &get_name() const = 0;

    ///@}

    ///@name Type-punned value operations
    ///@{

    /// @copydoc cci_param_typed::get_raw_value
    virtual const void *get_raw_value() const = 0;

    /// @copydoc cci_param_typed::get_default_value_raw
    virtual const void *get_default_value_raw() const = 0;

    /// Computer if the stored values are equal
    /**
    * @param rhs reference to another cci_param_if implementation
    * @return True if both values are equal
    */
    virtual bool equals(const cci_param_if &rhs) const = 0;

    /// Computer if the stored values are equal
    /**
    * @param rhs reference to another cci_param_untyped_handle implementation
    * @return True if both values are equal
    */
    virtual bool equals(const cci_param_untyped_handle &rhs) const = 0;

    ///@}

    /// @copydoc cci_param_untyped::is_handle
    virtual bool is_handle() const = 0;

    ///@name Initialization and Destructions methods
    ///@{

    /// Initialize.
    virtual void init() = 0;

    /// @copydoc cci_param_typed::destroy
    virtual void destroy() = 0;

    ///@}

    /// @copydoc cci_param_typed::create_param_handle
    virtual cci_param_untyped_handle *
    create_param_handle(const cci_originator &originator) = 0;

private:
    /// @copydoc cci_param_typed::json_deserialize(const std::string&, const cci_originator&)
    virtual void json_deserialize(const std::string &json_string,
                                  const cci_originator &originator) = 0;

    /// @copydoc cci_param_typed::set_cci_value(const cci_value&, const cci_originator&)
    virtual void set_cci_value(const cci_value &val,
                               const cci_originator &originator) = 0;

    /// @copydoc cci_param_typed::set_raw_value(const void*, const cci_originator&)
    virtual void set_raw_value(const void *vp, const cci_originator &originator) = 0;

    /// @copydoc cci_param_typed::set_raw_value(const void*, const void*, const cci_originator&)
    virtual void set_raw_value(const void *vp, const void *pwd,
                               const cci_originator &originator) = 0;

    virtual shared_ptr <callb_adapt> register_callback(const callback_type type,
                                                       void *observer,
                                                       param_callb_func_ptr function,
                                                       cci_param_untyped_handle& param) = 0;

    virtual shared_ptr <callb_adapt> register_callback(const callback_type type,
                                                       shared_ptr <callb_adapt> callb,
                                                       cci_param_untyped_handle& param) = 0;

};

CCI_CLOSE_NAMESPACE_

#endif