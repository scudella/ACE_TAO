// -*- C++ -*-
// $Id$

// ============================================================================
//
// = LIBRARY
//    TAO
//
// = FILENAME
//    POAManager.h
//
// = DESCRIPTION
//     POAManager
//
// = AUTHOR
//     Irfan Pyarali
//
// ============================================================================

#ifndef TAO_POAMANAGER_H
#define TAO_POAMANAGER_H

#include "tao/POAS.h"
// for POA skeleton.

#include "tao/poa_macros.h"

class TAO_POA;
// Forward decl.

class TAO_Export TAO_POA_Manager : public POA_PortableServer::POAManager
{
  friend class TAO_POA;

public:
  enum Processing_State
  {
    ACTIVE,
    DISCARDING,
    HOLDING,
    INACTIVE,
    UNKNOWN
  };

  virtual void activate (CORBA_Environment &ACE_TRY_ENV = CORBA::default_environment ());

#if !defined (TAO_HAS_MINIMUM_CORBA)

  virtual void hold_requests (CORBA::Boolean wait_for_completion,
                              CORBA_Environment &ACE_TRY_ENV = CORBA::default_environment ());

  virtual void discard_requests (CORBA::Boolean wait_for_completion,
                                 CORBA_Environment &ACE_TRY_ENV = CORBA::default_environment ());

  virtual void deactivate (CORBA::Boolean etherealize_objects,
                           CORBA::Boolean wait_for_completion,
                           CORBA_Environment &ACE_TRY_ENV = CORBA::default_environment ());

#endif /* TAO_HAS_MINIMUM_CORBA */

  TAO_POA_Manager (void);

  virtual TAO_POA_Manager *clone (void);

  virtual ~TAO_POA_Manager (void);

  virtual Processing_State state (CORBA_Environment &ACE_TRY_ENV = CORBA::default_environment ());

protected:

  virtual void activate_i (CORBA_Environment &ACE_TRY_ENV);

#if !defined (TAO_HAS_MINIMUM_CORBA)

  virtual void hold_requests_i (CORBA::Boolean wait_for_completion,
                                CORBA_Environment &ACE_TRY_ENV);

  virtual void discard_requests_i (CORBA::Boolean wait_for_completion,
                                   CORBA_Environment &ACE_TRY_ENV);

  virtual void deactivate_i (CORBA::Boolean etherealize_objects,
                             CORBA::Boolean wait_for_completion,
                             CORBA_Environment &ACE_TRY_ENV);

#endif /* TAO_HAS_MINIMUM_CORBA */

  virtual ACE_Lock &lock (void);

  virtual void remove_poa (TAO_POA *poa,
                           CORBA_Environment &ACE_TRY_ENV = CORBA::default_environment ());

  virtual void remove_poa_i (TAO_POA *poa,
                             CORBA_Environment &ACE_TRY_ENV = CORBA::default_environment ());

  virtual void register_poa (TAO_POA *poa,
                             CORBA_Environment &ACE_TRY_ENV = CORBA::default_environment ());

  virtual void register_poa_i (TAO_POA *poa,
                               CORBA_Environment &ACE_TRY_ENV = CORBA::default_environment ());

  virtual void destroy (void);

  Processing_State state_;

  int closing_down_;

  ACE_Lock *lock_;

  typedef ACE_Unbounded_Set<TAO_POA *> POA_COLLECTION;

  POA_COLLECTION poa_collection_;
};

#if defined (__ACE_INLINE__)
# include "tao/POAManager.i"
#endif /* __ACE_INLINE__ */

#endif /* TAO_POAMANAGER_H */
