//=============================================================================
/**
 *  @file    Thread_Pool.h
 *
 *  $Id$
 *
 *  @author Irfan Pyarali
 */
// ===================================================================

#ifndef TAO_THREAD_POOL_H
#define TAO_THREAD_POOL_H

#include "ace/pre.h"
#include "tao/orbconf.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/Task.h"
#include "RTCORBA.h"
#include "ace/Hash_Map_Manager.h"
#include "tao/Thread_Lane_Resources.h"

class TAO_Thread_Lane;

/**
 * @class TAO_Thread_Pool_Threads
 *
 * @brief Class representing a thread running in a thread lane.
 *
 * \nosubgrouping
 *
 **/
class TAO_RTCORBA_Export TAO_Thread_Pool_Threads : public ACE_Task_Base
{
public:

  /// Constructor.
  TAO_Thread_Pool_Threads (TAO_Thread_Lane &lane);

  /// Method executed when a thread is spawned.
  int svc (void);

  /// Accessor to the lane to which this thread belongs to.
  TAO_Thread_Lane &lane (void) const;

  /// Set TSS resources for the current thread.
  static void set_tss_resources (TAO_ORB_Core &orb_core,
                                 TAO_Thread_Lane &thread_lane);

private:

  /// Lane to which this thread belongs to.
  TAO_Thread_Lane &lane_;
};

class TAO_Thread_Pool;

/**
 * @class TAO_Thread_Lane
 *
 * @brief Class representing the thread lane inside a thread pool.
 *
 * \nosubgrouping
 *
 **/
class TAO_RTCORBA_Export TAO_Thread_Lane
{
public:

  /// Constructor.
  TAO_Thread_Lane (TAO_Thread_Pool &pool,
                   CORBA::ULong id,
                   CORBA::Short lane_priority,
                   CORBA::ULong static_threads,
                   CORBA::ULong dynamic_threads,
                   CORBA::Environment &ACE_TRY_ENV);

  /// Destructor.
  ~TAO_Thread_Lane (void);

  /// Open the lane.
  void open (CORBA::Environment &ACE_TRY_ENV);

  /// Finalize the resources.
  void fini (void);

  /// Create the static threads - only called once.
  int create_static_threads (void);

  /// Create <number_of_threads> of dynamic threads.  Can be called
  /// multiple times.
  int create_dynamic_threads (CORBA::ULong number_of_threads);

  /// @name Accessors
  // @{

  TAO_Thread_Pool &pool (void) const;
  CORBA::ULong id (void) const;

  CORBA::Short lane_priority (void) const;
  CORBA::ULong static_threads (void) const;
  CORBA::ULong dynamic_threads (void) const;

  TAO_Thread_Pool_Threads &threads (void);

  TAO_Thread_Lane_Resources &resources (void);
  // @}

private:

  TAO_Thread_Pool &pool_;
  CORBA::ULong id_;

  CORBA::Short lane_priority_;
  CORBA::ULong static_threads_;
  CORBA::ULong dynamic_threads_;

  TAO_Thread_Pool_Threads threads_;

  TAO_Thread_Lane_Resources resources_;
};

class TAO_Thread_Pool_Manager;

/**
 * @class TAO_Thread_Pool
 *
 * @brief Class representing the thread pool inside a thread pool
 * manager.
 *
 * \nosubgrouping
 *
 **/
class TAO_RTCORBA_Export TAO_Thread_Pool
{
  friend class TAO_Thread_Lane;

public:

  /// Constructor (for pools without lanes).
  TAO_Thread_Pool (TAO_Thread_Pool_Manager &manager,
                   CORBA::ULong id,
                   CORBA::ULong stack_size,
                   CORBA::ULong static_threads,
                   CORBA::ULong dynamic_threads,
                   CORBA::Short default_priority,
                   CORBA::Boolean allow_request_buffering,
                   CORBA::ULong max_buffered_requests,
                   CORBA::ULong max_request_buffer_size,
                   CORBA::Environment &ACE_TRY_ENV);

  /// Constructor (for pools with lanes).
  TAO_Thread_Pool (TAO_Thread_Pool_Manager &manager,
                   CORBA::ULong id,
                   CORBA::ULong stack_size,
                   const RTCORBA::ThreadpoolLanes &lanes,
                   CORBA::Boolean allow_borrowing,
                   CORBA::Boolean allow_request_buffering,
                   CORBA::ULong max_buffered_requests,
                   CORBA::ULong max_request_buffer_size,
                   CORBA::Environment &ACE_TRY_ENV);

  /// Destructor.
  ~TAO_Thread_Pool (void);

  /// Open the pool.
  void open (CORBA::Environment &ACE_TRY_ENV);

  /// Finalize the resources.
  void fini (void);

  /// Create the static threads - only called once.
  int create_static_threads (void);

  /// Check if this thread pool has (explicit) lanes.
  int with_lanes (void) const;

  /// @name Accessors
  // @{

  TAO_Thread_Pool_Manager &manager (void) const;
  CORBA::ULong id (void) const;

  CORBA::ULong stack_size (void) const;
  CORBA::Boolean allow_borrowing (void) const;
  CORBA::Boolean allow_request_buffering (void) const;
  CORBA::ULong max_buffered_requests (void) const;
  CORBA::ULong max_request_buffer_size (void) const;

  TAO_Thread_Lane **lanes (void);
  CORBA::ULong number_of_lanes (void) const;

  // @}

private:

  TAO_Thread_Pool_Manager &manager_;
  CORBA::ULong id_;

  CORBA::ULong stack_size_;
  CORBA::Boolean allow_borrowing_;
  CORBA::Boolean allow_request_buffering_;
  CORBA::ULong max_buffered_requests_;
  CORBA::ULong max_request_buffer_size_;

  TAO_Thread_Lane **lanes_;
  CORBA::ULong number_of_lanes_;
  int with_lanes_;
};

class TAO_ORB_Core;

/**
 * @class TAO_Thread_Pool_Manager
 *
 * @brief Class for managing thread pools.
 *
 * \nosubgrouping
 *
 **/
class TAO_RTCORBA_Export TAO_Thread_Pool_Manager
{
public:

  /// Constructor.
  TAO_Thread_Pool_Manager (TAO_ORB_Core &orb_core);

  /// Destructor.
  ~TAO_Thread_Pool_Manager (void);

  /// Finalize the resources.
  void fini (void);

  /// Create the static threads - only called once.
  int
  create_static_threads (void);

  /// Create a threadpool without lanes.
  RTCORBA::ThreadpoolId
  create_threadpool (CORBA::ULong stacksize,
                     CORBA::ULong static_threads,
                     CORBA::ULong dynamic_threads,
                     RTCORBA::Priority default_priority,
                     CORBA::Boolean allow_request_buffering,
                     CORBA::ULong max_buffered_requests,
                     CORBA::ULong max_request_buffer_size,
                     int call_open,
                     CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));

  /// Create a threadpool with lanes.
  RTCORBA::ThreadpoolId
  create_threadpool_with_lanes (CORBA::ULong stacksize,
                                const RTCORBA::ThreadpoolLanes & lanes,
                                CORBA::Boolean allow_borrowing,
                                CORBA::Boolean allow_request_buffering,
                                CORBA::ULong max_buffered_requests,
                                CORBA::ULong max_request_buffer_size,
                                int call_open,
                                CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));

  /// Destroy a threadpool.
  void
  destroy_threadpool (RTCORBA::ThreadpoolId threadpool,
                      CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     RTCORBA::RTORB::InvalidThreadpool));

  /// ORB_Core accessor.
  TAO_ORB_Core &orb_core (void) const;

  /// Collection of thread pools.
  typedef ACE_Hash_Map_Manager<RTCORBA::ThreadpoolId, TAO_Thread_Pool *, ACE_Null_Mutex> THREAD_POOLS;

  /// Access the thread pools managed by this class.
  THREAD_POOLS &thread_pools (void);

private:

  /// @name Helpers
  // @{

  RTCORBA::ThreadpoolId
  create_threadpool_i (CORBA::ULong stacksize,
                       CORBA::ULong static_threads,
                       CORBA::ULong dynamic_threads,
                       RTCORBA::Priority default_priority,
                       CORBA::Boolean allow_request_buffering,
                       CORBA::ULong max_buffered_requests,
                       CORBA::ULong max_request_buffer_size,
                       int call_open,
                       CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));

  RTCORBA::ThreadpoolId
  create_threadpool_with_lanes_i (CORBA::ULong stacksize,
                                  const RTCORBA::ThreadpoolLanes & lanes,
                                  CORBA::Boolean allow_borrowing,
                                  CORBA::Boolean allow_request_buffering,
                                  CORBA::ULong max_buffered_requests,
                                  CORBA::ULong max_request_buffer_size,
                                  int call_open,
                                  CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));

  void destroy_threadpool_i (RTCORBA::ThreadpoolId threadpool,
                             CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     RTCORBA::RTORB::InvalidThreadpool));

  RTCORBA::ThreadpoolId
  create_threadpool_helper (TAO_Thread_Pool *thread_pool,
                            int call_open,
                            CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));

  // @}

  TAO_ORB_Core &orb_core_;

  THREAD_POOLS thread_pools_;
  RTCORBA::ThreadpoolId thread_pool_id_counter_;
  ACE_SYNCH_MUTEX lock_;
};

#if defined (__ACE_INLINE__)
# include "Thread_Pool.i"
#endif /* __ACE_INLINE__ */

#include "ace/post.h"

#endif /* TAO_THREAD_POOL_H */
