// $Id$

#ifndef TAO_OBJREF_TYPECODE_CPP
#define TAO_OBJREF_TYPECODE_CPP

#include "tao/Objref_TypeCode.h"

#ifndef __ACE_INLINE__
# include "tao/Objref_TypeCode.inl"
#endif  /* !__ACE_INLINE__ */

#include "tao/CDR.h"

#include "ace/OS_NS_string.h"


template <typename StringType, class RefCountPolicy>
bool
TAO::TypeCode::Objref<StringType, RefCountPolicy>::tao_marshal (
  TAO_OutputCDR & cdr) const
{
  // A tk_objref TypeCode has a "complex" parameter list type (see
  // Table 15-2 in Section 15.3.5.1 "TypeCode" in the CDR section of
  // the CORBA specification), meaning that it must be marshaled into
  // a CDR encapsulation.

  // Create a CDR encapsulation.
  TAO_OutputCDR enc;

  return
    enc << TAO_OutputCDR::from_boolean (TAO_ENCAP_BYTE_ORDER)
    && enc << TAO_OutputCDR::from_string (this->attributes_.id (), 0)
    && enc << TAO_OutputCDR::from_string (this->attributes_.name (), 0)
    && cdr << static_cast<CORBA::ULong> (enc.total_length ())
    && cdr.write_octet_array_mb (enc.begin ());
}

template <typename StringType, class RefCountPolicy>
void
TAO::TypeCode::Objref<StringType, RefCountPolicy>::tao_duplicate (void)
{
  this->RefCountPolicy::add_ref ();
}

template <typename StringType, class RefCountPolicy>
void
TAO::TypeCode::Objref<StringType, RefCountPolicy>::tao_release (void)
{
  this->RefCountPolicy::remove_ref ();
}

template <typename StringType, class RefCountPolicy>
CORBA::Boolean
TAO::TypeCode::Objref<StringType, RefCountPolicy>::equal_i (
  CORBA::TypeCode_ptr /* tc */
  ACE_ENV_ARG_DECL_NOT_USED) const
{
  // Equality has already been established in the
  // CORBA::TypeCode base class.

  return true;
}

template <typename StringType, class RefCountPolicy>
CORBA::Boolean
TAO::TypeCode::Objref<StringType, RefCountPolicy>::equivalent_i (
  CORBA::TypeCode_ptr
  ACE_ENV_ARG_DECL_NOT_USED) const
{
  // Equivalence already verified in the base class
  // CORBA::TypeCode::equivalent() method.

  return true;
}

template <typename StringType, class RefCountPolicy>
CORBA::TypeCode_ptr
TAO::TypeCode::Objref<StringType,
                      RefCountPolicy>::get_compact_typecode_i (
  ACE_ENV_SINGLE_ARG_DECL) const
{
  TAO_TypeCodeFactory_Adapter * const adapter =
    ACE_Dynamic_Service<TAO_TypeCodeFactory_Adapter>::instance (
        TAO_ORB_Core::typecodefactory_adapter_name ()
      );

  if (adapter == 0)
    {
      ACE_THROW_RETURN (CORBA::INTERNAL (),
                        CORBA::TypeCode::_nil ());
    }

  if (this->kind_ == CORBA::tk_abstract_interface)
    {
      return adapter->create_abstract_interface_tc (this->attributes_.id (),
                                                    ""  /* empty name */
                                                    ACE_ENV_ARG_PARAMETER);
    }
  else if (this->kind_ == CORBA::tk_component)
    {
      return adapter->create_component_tc (this->attributes_.id (),
                                           ""  /* empty name */
                                           ACE_ENV_ARG_PARAMETER);
    }
  else if (this->kind_ == CORBA::tk_home)
    {
      return adapter->create_home_tc (this->attributes_.id (),
                                      ""  /* empty name */
                                      ACE_ENV_ARG_PARAMETER);
    }
  else if (this->kind_ == CORBA::tk_local_interface)
    {
      return adapter->create_local_interface_tc (this->attributes_.id (),
                                                 ""  /* empty name */
                                                 ACE_ENV_ARG_PARAMETER);

    }
  else if (this->kind_ == CORBA::tk_native)
    {
      return adapter->create_native_tc (this->attributes_.id (),
                                        ""  /* empty name */
                                        ACE_ENV_ARG_PARAMETER);
    }
  else // CORBA::tk_objref
    {
      return adapter->create_interface_tc (this->attributes_.id (),
                                           ""  /* empty name */
                                           ACE_ENV_ARG_PARAMETER);
    }
}

template <typename StringType, class RefCountPolicy>
char const *
TAO::TypeCode::Objref<StringType, RefCountPolicy>::id_i (
  ACE_ENV_SINGLE_ARG_DECL_NOT_USED) const
{
  // Ownership is retained by the TypeCode, as required by the C++
  // mapping.
  return this->attributes_.id ();
}

template <typename StringType, class RefCountPolicy>
char const *
TAO::TypeCode::Objref<StringType, RefCountPolicy>::name_i (
  ACE_ENV_SINGLE_ARG_DECL_NOT_USED) const
{
  // Ownership is retained by the TypeCode, as required by the C++
  // mapping.
  return this->attributes_.name ();
}

#endif  /*  TAO_OBJREF_TYPECODE_CPP */
