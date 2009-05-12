//   OSCI CCI WG
//
// LICENSETEXT
//
//   Copyright (C) 2009 : GreenSocs Ltd
// 	 http://www.greensocs.com/ , email: info@greensocs.com
//
//   Developed by :
//   
//   Christian Schroeder <schroeder@eis.cs.tu-bs.de>,
//     Technical University of Braunschweig, Dept. E.I.S.
//     http://www.eis.cs.tu-bs.de
//
//
// 
// ENDLICENSETEXT


#ifndef __GS_CCI_PARAM_H__
#define __GS_CCI_PARAM_H__


#include <string>
#include <iostream>
#include <sstream>

#include <systemc>


namespace cci {

  template<typename T>
  class gs_cci_param 
  : public cci_param<T>
  {
  protected:
    /// Typedef for the value.
    typedef T val_type;
    /// Typedef for the param itself.
    typedef cci_param<T> my_type;

  public:

    // //////////////////////////////////////////////////////////////////// //
    // ///////////////   Construction / Destruction   ///////////////////// //

    // Explicit constructors to avoid implicit construction of parameters.
    
    /// Empty constructor. Name will be set in base
    explicit gs_cci_param()                    : cci_param_t<val_type>(false, true) { init(); }
    explicit gs_cci_param(const val_type& val) : cci_param_t<val_type>(false, true) { init(); }
    
    /// Constructor with (local/hierarchical) name.
    explicit gs_cci_param(const std::string& nam) : cci_param_t<val_type>(nam             , false, true) { gs_cci_param_t<val_type>::init(); }
    explicit gs_cci_param(const char* nam       ) : cci_param_t<val_type>(std::string(nam), false, true) { gs_cci_param_t<val_type>::init(); }
    
    /// Constructor with (local/hierarchical) name and string representation of initial value.
    explicit gs_cci_param(const std::string& nam, const std::string& val, const bool force_top_level_name = false) : cci_param_t<val_type>(nam             , force_top_level_name, true ) { cci_param_t<val_type>::init(convertStringToValue(val));         } 
    explicit gs_cci_param(const char* nam,        const char* val       , const bool force_top_level_name = false) : cci_param_t<val_type>(std::string(nam), force_top_level_name, true ) { cci_param_t<val_type>::init(convertStringToValue(std::string(val))); } 
    explicit cci_param(const std::string& nam, const char* val       , const bool force_top_level_name = false) : cci_param_t<val_type>(nam             , force_top_level_name, true ) { cci_param_t<val_type>::init(convertStringToValue(std::string(val))); } 
    explicit cci_param(const char* nam,        const std::string& val, const bool force_top_level_name = false) : cci_param_t<val_type>(std::string(nam), force_top_level_name, true ) { cci_param_t<val_type>::init(convertStringToValue(val));         } 
    
    /// Constructor with (local/hierarchical) name and initial value.
    explicit cci_param(const std::string& nam, const val_type& val, const bool force_top_level_name = false) : cci_param_t<val_type>(nam             , force_top_level_name, true )  { cci_param_t<val_type>::init(val); }    
    explicit cci_param(const char* nam,        const val_type& val, const bool force_top_level_name = false) : cci_param_t<val_type>(std::string(nam), force_top_level_name, true )  { cci_param_t<val_type>::init(val); }    
    
    // Constructors with register_at_db bool
    explicit cci_param(const std::string& nam, const std::string& val, const bool force_top_level_name, const bool register_at_db) : cci_param_t<val_type>(nam, force_top_level_name, register_at_db) { cci_param_t<val_type>::init(convertStringToValue(val));         } 

    ~gs_cci_param();
    
    void init(const val_type& default_val);
    
    void init();

    my_type& operator +=  (val_type);
    my_type& operator -=  (val_type);
    my_type& operator /=  (val_type);
    my_type& operator *=  (val_type);
    val_type operator +  (val_type);
    val_type operator -  (val_type);
    val_type operator /  (val_type);
    val_type operator *  (val_type);
    my_type& operator %=  (val_type);
    my_type& operator ^=  (val_type);
    my_type& operator &=  (val_type);
    my_type& operator |=  (val_type);
    my_type& operator <<= (val_type);
    my_type& operator >>= (val_type);
    
    my_type& operator -- ();    // prefix
    val_type operator -- (int); // postfix
    my_type& operator ++ ();    // prefix
    val_type operator ++ (int); // postfix  
       
    void set(const val_type& val);
    
    const val_type& get() const;
    
    std::string serialize(const val_type& val) const;

    const bool deserialize(val_type& target_val, const std::string& str);

  };
    
  template<class T> bool operator == (cci_param<T>& p1, cci_param<T>& p2) {
    return p1.get() == p2.getValue();
  }

  template<class T> bool operator == (cci_param<T>& p1, T& p2) {
    return p1.get() == p2;
  }

  template<class T> bool operator == (T& p1, cci_param<T>& p2) {
    return p1 == p2.get();
  }
  
  
} // end namespace cci

#endif
