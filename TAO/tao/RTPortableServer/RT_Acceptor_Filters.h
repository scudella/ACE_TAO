// -*- C++ -*-
// $Id$

// ============================================================================
//
// = LIBRARY
//    PortableServer
//
// = FILENAME
//    RT_Acceptor_Filters.h
//
// = DESCRIPTION
//     RTCORBA strategies for populating mprofile.
//
// = AUTHOR
//     Marina Spivak <marina@cs.wustl.edu>
//
// ============================================================================

#ifndef TAO_RT_ACCEPTOR_FILTER_H
#define TAO_RT_ACCEPTOR_FILTER_H
#include "ace/pre.h"

#include "tao/orbconf.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "rtportableserver_export.h"
#include "tao/Acceptor_Filter.h"
#include "tao/RTCORBA/RTCORBA.h"

// This is to remove "inherits via dominance" warnings from MSVC.
// MSVC is being a little too paranoid.
#if defined(_MSC_VER)
#if (_MSC_VER >= 1200)
#pragma warning(push)
#endif /* _MSC_VER >= 1200 */
#pragma warning(disable:4250)
#endif /* _MSC_VER */

class TAO_Acceptor;

class TAO_RTPortableServer_Export TAO_Server_Protocol_Acceptor_Filter :
  public TAO_Acceptor_Filter
{
  // = TITLE
  //   RTCORBA::ServerProtocolPolicy Acceptor_Filter.
  //
  // = DESCRIPTION
  //   Populates mprofile with endpoints selected based on the
  //   RTCORBA::ServerProtocolPolicy.
  //
public:
  TAO_Server_Protocol_Acceptor_Filter (RTCORBA::ProtocolList &protocols);

  /// Populate <mprofile> based on what's in <protocols_>.
  int fill_mprofile (const TAO_ObjectKey &object_key,
                     TAO_MProfile &mprofile,
                     TAO_Acceptor **acceptors_begin,
                     TAO_Acceptor **acceptors_end);

  /// Encodes the endpoints in the profiles into the TAO_TAG_ENDPOINTS
  /// tag component of profiles.
  int encode_endpoints (TAO_MProfile &mprofile);

  virtual int validate_acceptor (TAO_Acceptor *acceptor);
  // Template method pattern.  This method is used by <fill_mprofile>
  // to decide whether <acceptor> endpoint should be added to
  // mprofile or not.  Returns true or false.
  // This implementation always returns true.  Subclasses can override
  // to specify additional conditions that must be met by an
  // <acceptor> for inclusion into mprofile.

private:
  RTCORBA::ProtocolList &protocols_;
  // Value of the ServerProtocolPolicy used for endpoint
  // selection.
};

#if defined (__ACE_INLINE__)
#include "RT_Acceptor_Filters.i"
#endif /* __ACE_INLINE__ */

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma warning(pop)
#endif /* _MSC_VER */

#include "ace/post.h"
#endif /* TAO_RT_ACCEPTOR_FILTER_H */
