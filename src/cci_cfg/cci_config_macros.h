// LICENSETEXT
//
//   Copyright (C) 2010 : GreenSocs Ltd
// 	 http://www.greensocs.com/ , email: info@greensocs.com
//
//   Developed by:
//    Christian Schroeder <schroeder@eis.cs.tu-bs.de>,
//    Mark Burton, mark@greensocs.com
//
//
// The contents of this file are subject to the licensing terms specified
// in the file LICENSE. Please consult this file for restrictions and
// limitations that may apply.
// 
// ENDLICENSETEXT



#ifndef CCI_CCI_CONFIG_MACROS_H_INCLUDED_
#define CCI_CCI_CONFIG_MACROS_H_INCLUDED_

/// Namespace for ASI Configuration, Control & Inspection (CCI) standard, Config part
#define CCI_OPEN_NAMESPACE_  namespace cci {
#define CCI_CLOSE_NAMESPACE_ }

// Some default strings - user should define custom ones before including CCI
// (and before building parameter or broker code since they are used beyond
// the client API library)
#ifndef  __CCI_OWNER_ORIGINATOR_STRING__
#define __CCI_OWNER_ORIGINATOR_STRING__   "OWNER_ORIGINATOR"
#endif
#ifndef __CCI_DEFAULT_BROKER_STRING__
#define __CCI_DEFAULT_BROKER_STRING__     "DEFAULT_BROKER"
#endif
#ifndef __CCI_UNKNOWN_ORIGINATOR_STRING__
#define __CCI_UNKNOWN_ORIGINATOR_STRING__ "UNKNOWN_ORIGINATOR"
#endif
#ifndef __CCI_SC_REPORT_MSG_TYPE_PREFIX__
#define __CCI_SC_REPORT_MSG_TYPE_PREFIX__ "/ASI/CCI/"
#endif

#endif