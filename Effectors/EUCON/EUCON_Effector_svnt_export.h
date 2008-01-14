
// -*- C++ -*-
// $Id$
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl EUCON_EFFECTOR_SVNT
// ------------------------------
#ifndef EUCON_EFFECTOR_SVNT_EXPORT_H
#define EUCON_EFFECTOR_SVNT_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (EUCON_EFFECTOR_SVNT_HAS_DLL)
#  define EUCON_EFFECTOR_SVNT_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && EUCON_EFFECTOR_SVNT_HAS_DLL */

#if !defined (EUCON_EFFECTOR_SVNT_HAS_DLL)
#  define EUCON_EFFECTOR_SVNT_HAS_DLL 1
#endif /* ! EUCON_EFFECTOR_SVNT_HAS_DLL */

#if defined (EUCON_EFFECTOR_SVNT_HAS_DLL) && (EUCON_EFFECTOR_SVNT_HAS_DLL == 1)
#  if defined (EUCON_EFFECTOR_SVNT_BUILD_DLL)
#    define EUCON_EFFECTOR_SVNT_Export ACE_Proper_Export_Flag
#    define EUCON_EFFECTOR_SVNT_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define EUCON_EFFECTOR_SVNT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* EUCON_EFFECTOR_SVNT_BUILD_DLL */
#    define EUCON_EFFECTOR_SVNT_Export ACE_Proper_Import_Flag
#    define EUCON_EFFECTOR_SVNT_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define EUCON_EFFECTOR_SVNT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* EUCON_EFFECTOR_SVNT_BUILD_DLL */
#else /* EUCON_EFFECTOR_SVNT_HAS_DLL == 1 */
#  define EUCON_EFFECTOR_SVNT_Export
#  define EUCON_EFFECTOR_SVNT_SINGLETON_DECLARATION(T)
#  define EUCON_EFFECTOR_SVNT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* EUCON_EFFECTOR_SVNT_HAS_DLL == 1 */

// Set EUCON_EFFECTOR_SVNT_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (EUCON_EFFECTOR_SVNT_NTRACE)
#  if (ACE_NTRACE == 1)
#    define EUCON_EFFECTOR_SVNT_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define EUCON_EFFECTOR_SVNT_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !EUCON_EFFECTOR_SVNT_NTRACE */

#if (EUCON_EFFECTOR_SVNT_NTRACE == 1)
#  define EUCON_EFFECTOR_SVNT_TRACE(X)
#else /* (EUCON_EFFECTOR_SVNT_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define EUCON_EFFECTOR_SVNT_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (EUCON_EFFECTOR_SVNT_NTRACE == 1) */

#endif /* EUCON_EFFECTOR_SVNT_EXPORT_H */

// End of auto generated file.
